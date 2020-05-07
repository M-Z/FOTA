'use strict';

const User = require('mongoose').model('User');
const Team = require('mongoose').model('Team');
const fs = require('fs');
const shortid = require('shortid');
const {
  TokenGenerator,
  roles,
  upload,
  sendEmail
} = require('../../helper');

const loginTokenGenerator = new TokenGenerator({
  priv: fs.readFileSync('Server/cryptKeys/key.pem'),
  pub: fs.readFileSync('Server/cryptKeys/cert.pem'),
  passphrase: 'PEM pass phrase',
  options: {
    algorithm: 'RS256',
    expiresIn: '60m'
  }
});

const refreshTokenGenerator = new TokenGenerator({
  priv: fs.readFileSync('Server/cryptKeys/refreshToken/priv.pem'),
  pub: fs.readFileSync('Server/cryptKeys/refreshToken/pub.pem'),
  passphrase: 'PEM pass phrase',
  options: {
    algorithm: 'RS256',
    expiresIn: '7d'
  }
});

/**
 * User's username and password to login
 * @typedef userCredentials
 * @property {string} username.required - Email of user - eg: mario@mail.com
 * @property {string} password.required - password of user - eg: 111111111111
 */

/**
 * User's skeleton data
 * @typedef userData
 * @property {string} email.required - Email of user - eg: mario@mail.com
 * @property {enum} role.required - Role of the user in team - eg: Developer, Leader
 * @property {string} teamID.required - Team's unique identifier - eg: 5e9274770bfe6bc0f0e8d947
 */

/**
 * @route POST /user/login
 * @group User - Endpoints for user actions
 * @summary Login the user
 * @param {userCredentials.model} body.body.required - Vehicle's credentials
 * @returns {string}  200 - success
 * @returns {Error}  default: Error message.
 * @produces application/json
 */
exports.login_User = function(req, res) {

  const {
    username,
    password
  } = req.body;

  let getUser;
  // fetch user and test password verification
  User.findOne({
      email: req.body.username.toLowerCase()
    })
    .populate({
      path: 'team',
      values: '-secret',
      populate: {
        path: 'firmware'
      }
    })
    .then(userData => {

      if (!userData) {
        throw ("User not found.");
      }

      getUser = userData;
      return userData.comparePassword(req.body.password);
    }).then(response => {

      // Incorrect credentials
      if (!response) {
        throw ("Incorrect Password.");
      }

      const jwtToken = loginTokenGenerator.sign({
        username: getUser.username,
        userId: getUser._id,
        role: getUser.role,
        team: getUser.team,
        joinDate: getUser.joinDate
      });

      const jwtRefreshToken = refreshTokenGenerator.sign({
        uuid: shortid.generate()
      });

      res.cookie(
        "refresh",
        jwtRefreshToken, {
          httpOnly: true,
          secure: true,
          path: '/API',
          sameSite: true,
          maxAge: 24 * 60 * 60 * 1000
        }
      );

      // ALL OK
      res.send({
        token: jwtToken
      });
    }).catch(err => {
      // Log the err and send 401 to user
      res.send({
        error: "Incorrect username and/or password."
      });
    });

};

exports.refreshToken = function(req, res) {
  try {
    const refreshToken = req.cookies.refresh;

    if (refreshToken === undefined) {
      res.clearCookie("refresh");
      res.send({
        data: "error"
      });
      return false;
    }

    if (!refreshTokenGenerator.verify(refreshToken)) {
      throw ("Authentication failed!");
    }

    const token = req.headers.authorization.split(" ")[1];

    const jwtRefreshToken = refreshTokenGenerator.sign({
      uuid: shortid.generate()
    });

    res.cookie(
      "refresh",
      jwtRefreshToken, {
        httpOnly: true,
        secure: true,
        path: '/API',
        sameSite: true,
        maxAge: 24 * 60 * 60 * 1000
      }
    );

    const newToken = loginTokenGenerator.refresh(token);
    res.send({
      token: newToken
    });

  } catch (error) {
    res.clearCookie("refresh");
    res.send({
      message: "Token expired."
    });
  }
}

exports.logout = function(req, res) {
  res.clearCookie("refresh");
  res.send({
    data: 'success'
  });
}

const inviteTokenGenerator = new TokenGenerator({
  priv: fs.readFileSync('Server/cryptKeys/invitationKeys/priv.pem'),
  pub: fs.readFileSync('Server/cryptKeys/invitationKeys/pub.pem'),
  passphrase: 'Enter pass phrase',
  options: {
    audience: 'newUser',
    algorithm: 'RS256',
    expiresIn: '24h'
  }
});

/**
 * Adds a new user to a team and then sends in invitation email
 * @route POST /user/add
 * @group User - Endpoints for user actions
 * @summary Adds a new user
 * @param {userData.model} body.body.required - User's data
 * @returns {string}  200 - success
 * @returns {Error}  default: Error message.
 * @security userKey
 * @produces application/json
 */
exports.add_User = async function(req, res) {

  const {
    email,
    role,
    teamID
  } = req.body;

  // Find or create the new user
  await User.findOneAndUpdate({
      email: email.toLowerCase()
    }, {
      team: teamID,
      role: role
    }, {
      upsert: true,
      new: true,
      rawResult: true // Return the raw result from the MongoDB driver
    })
    .populate('team', 'teamName')
    .then(async (foundUser) => {

      // If user already joined and used his key
      if (foundUser.lastErrorObject && foundUser.lastErrorObject.updatedExisting) {

        // Remove from old team (if any)
        await Team.updateOne({}, {
            $pull: {
              members: foundUser.value._id
            }
          })
          .catch(() => {
            throw ("Error deleting " + foundUser.value.name.firstName + ' from his current team.');
          });

        // Add to current team
        await Team.updateOne({
            _id: teamID
          }, {
            $push: {
              members: foundUser.value._id
            }
          })
          .catch(() => {
            throw ("Error adding to the new team.")
          });

        // Already registered
        if (foundUser.value.userKey === 'created') {
          throw {
            type: "response",
            message: `${foundUser.value.name.firstName} joined team ${foundUser.value.team.teamName} as ${ foundUser.value.role }.`
          };
        }
      }

      const newKey = inviteTokenGenerator.sign({
        userId: foundUser.value._id,
        email: foundUser.value.email,
        team: foundUser.value.team.teamName,
        role: role
      });

      // Generate a new JWT based on user ID
      await User.findByIdAndUpdate({
          _id: foundUser.value._id
        }, {
          userKey: newKey
        })
        .populate('team', 'teamName')
        .then(async (user) => {

          user.userKey = newKey;

          if (!await sendEmail(user)) {
            throw {
              type: "response",
              message: "Error sending the email."
            };
          }

        })
        .catch(e => {
          throw (e);
        });

      // Old user, don't append to team
      if (foundUser.lastErrorObject.updatedExisting) {
        throw {
          type: "response",
          message: "success",
          user: foundUser.value
        };
      }

      return foundUser.value;
    })
    .then(async (user) => {

      // Add to team
      await Team
        .findOneAndUpdate({
          _id: teamID
        }, {
          $push: {
            members: user._id
          }
        })
        .catch(e => {
          throw (e)
        });

      // New user created and added to team
      throw {
        type: "response",
        message: "success",
        user: user
      };

    })
    .catch(thrown => {
      if (thrown.type === 'response') {
        res.json({
          data: thrown.message,
          member: thrown.user
        });
      } else {
        res.send(`{"data": "Some error occured."}`);
      }
    });

};

/**
 * @route DELETE /user/{userID}
 * @group User - Endpoints for user actions
 * @summary Deletes user and remove their profile image
 * @param {string} userID.path.required - User's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  200 - success
 * @returns {Error}  default: User deletion failed.
 * @security userKey
 * @produces text/plain text/html
 */
exports.delete_user = function(req, res) {

  User.findOneAndDelete({
      _id: req.params.userID
    })
    .then((user) => {

      if (!user) {
        throw ("Couldn't delete user.");
      }

      try {
        fs.unlinkSync(`public/img/users/${user.image}`, 'utf8');
      } catch (e) {} // Do nothing

      res.send('{"data": "success"}');
    })
    .catch(() => res.send('{"data": "User deletion failed."}'));
}

exports.authenticate_User = async function(req, res, next) {
  try {
    const token = req.headers.authorization.split(" ")[1];

    if (!loginTokenGenerator.verify(token))
      throw ("Authentication failed!");

    User
      .findById(loginTokenGenerator.decode(token).userId || false)
      .then((user) => {
        if (!user)
          throw ("Authentication failed!")

        req.user = user;

        next();
      })
      .catch(() => {
        throw ("Authentication failed!")
      });

  } catch (error) {
    res.status(401).json({
      message: "Authentication failed!"
    });
    return false;
  }

}

exports.grantAccess = function(action, resource, ...attribute) {
  return async (req, res, next) => {
    try {
      const permission = roles.can(req.user.role)[action](resource, attribute);
      if (!permission.granted) {
        res.status(401).json({
          error: "You don't have enough permission to perform this action"
        });

        return false;
      }

      next();
    } catch (error) {
      next(error);
    }
  }
}

/**
 * @route POST /user/register
 * @group User - Endpoints for user actions
 * @summary Registers the user
 * @param {string} token.formData.required - Invitation token
 * @param {string} email.formData.required - User's invited email
 * @param {string} password.formData.required - New password
 * @param {string} firstName.formData.required - First name
 * @param {string} lastName.formData.required - Last name
 * @param {file} userImage.formData.required - User profile image
 * @param {string} firmwareID.path.required - Old ID or 'new firmware'
 * @returns {string}  200 - success
 * @returns {Error}  default: Firmware deletion failed.
 * @produces text/plain text/html
 */
exports.user_registeration = function(req, res) {

  const requestHandler = async function(req) {

    // Verify registration token
    try {

      if (!inviteTokenGenerator.verify(req.body.token || ''))
        throw ("Authentication failed!");

    } catch (error) {
      return "Authentication failed!";
    }

    if (!req.body.email || !req.body.password || !req.body.firstName || !req.body.lastName) {
      return "All fields are required.";
    }

    req.token = inviteTokenGenerator.decode(req.body.token || '');

    if (req.token.email != req.body.email) {
      return "Authentication failed!";
    }

    req.fileID = shortid.generate() + '.' + req.fileExtension;

    let returnVal = "Some error occured";

    await new Promise((resolve, reject) => {
      fs.exists(`public/img/users/${req.fileID}`, function(exists) {

        // Generate a new file
        if (exists) {
          req.fileID = shortid.generate() + '.' + req.fileExtension;
        }

        returnVal = true;
        resolve()
      });

    });

    return returnVal;
  };

  const updateDB = function() {

    // search if team exists already
    User.findOneAndUpdate({
        _id: req.token.userId,
        email: req.token.email,
        userKey: req.body.token
      }, {
        name: {
          firstName: req.body.firstName,
          lastName: req.body.lastName
        },
        image: req.fileID,
        password: req.body.password
      })
      .populate('team', 'secret')
      .then((user) => {

        if (user === null) {
          res.send(`{"data": "User already registered."}`);
          return false;
        }

        res.send(`{"data": "success", "secret": "${user.team.secret}"}`);
      })
      .catch(
        () => res.send({
          "data": "Some error occured."
        })
      );

  };

  upload(req, res, {
        fileName: 'userImage',
        directory: 'public/img/users',
        allowedSize: 1024 * 1024, // 1 MB
        allowedFileTypes: ['png', 'jpeg', 'jpg'],
        allowedMimeTypes: ['image/jpeg', 'image/jpg', 'image/png']
      },
      requestHandler
    )
    .then(() => {
      updateDB();
    })
    .catch(() => {});

}
