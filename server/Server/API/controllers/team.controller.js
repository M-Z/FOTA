'use strict';

const Team = require('mongoose').model('Team');
const fs = require("fs");
const shortid = require('shortid');
const {
  upload,
  totp
} = require('../../helper');

/**
 * @route GET /team/{teamID}
 * @group Team - End points for admin to manage teams and users to see their teams
 * @summary Return a specific team
 * @param {string} teamID.path.required - Team's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  200 - success
 * @returns {Error}  default: Team not found.
 * @security userKey
 * @produces application/json
 */
exports.read_team = function(req, res) {
  Team
    .findOne({
      _id: req.params.teamID
    })
    .populate('firmware')
    .populate('members')
    .then(response => {
      if (!response) throw ("Team not found.");
      res.send(response);
    }).catch((err) =>
      res.status(404).json({
        error: "Team not found."
      })
    );
}

/**
 * @route GET /teams/
 * @group Team - End points for admin to manage teams and users to see their teams
 * @summary View all teams
 * @returns {string}  200 - success
 * @returns {Error}  default: No teams found.
 * @security userKey
 * @produces application/json
 */
exports.read_all_teams = function(req, res) {

  Team.find({})
    .populate('firmware')
    .populate('members')
    .then(results => {
      if (!results || results.length < 1)
        throw ("No teams found.");

      res.send(results);
    })
    .catch(err =>
      res.send("No teams found.")
    );
}

/**
 * @route GET /team/firmwares
 * @group Team - End points for admin to manage teams and users to see their teams
 * @summary Gets a list of logged in user team's firmwares
 * @returns {string}  200 - success
 * @returns {Error}  default: [].
 * @security userKey
 * @produces application/json
 */
exports.get_team_firmwares = function(req, res) {
  const findQuery = (req.user.role === 'Admin') ? {} : {
    _id: req.user.team._id
  };

  Team.findOne(findQuery, 'firmware')
    .populate('firmware')
    .then(team => {
      res.send((team) ? team.firmware : "[]");
    });
}

/**
 * @route POST /team/
 * @group Team - End points for admin to manage teams and users to see their teams
 * @summary Add a new team
 * @param {string} teamName.formData.required - Unique team's name
 * @param {string} description.formData.required - Summary for team tasks
 * @param {file} teamLogo.formData.required - A logo for the team
 * @returns {string}  200 - success
 * @returns {Error}  default: Error saving the new team.
 * @security userKey
 * @produces application/json
 */
exports.add_team = function(req, res) {

  const updateDB = function() {

    // Add the new team
    new Team({
      teamName: req.body.teamName,
      description: req.body.teamDescription,
      logo: req.fileID,
      secret: totp.generateSecret()
    }).save(function(err, team) {
      if (err || !team) {
        res.send('{"data": "Error saving the new team."}')
        return false;
      };

      res.json({
        data: "success",
        member: team
      });
    });

  };

  const requestHandler = async function(req) {

    if (req.body.teamName == undefined) {
      return "Team name required.";
    }

    let returnVal = "Some error occured";

    await new Promise((resolve, reject) => {

      // search if team exists already
      Team.find({
        teamName: req.body.teamName
      }, async (err, teams) => {

        // If the team FOUND
        if (err || teams.length !== 0) {
          returnVal = "Team already exists!";
          resolve();
          return false;
        }

        req.fileID = shortid.generate() + '.' + req.fileExtension;

        fs.exists(`public/img/teams/${req.fileID}`, function(exists) {

          // Generate a new file
          if (exists) {
            req.fileID = shortid.generate() + '.' + req.fileExtension;
          }

          returnVal = true;
          resolve();
        });

      });

    });

    return returnVal;
  }

  upload(req, res, {
        fileName: 'teamLogo',
        directory: 'public/img/teams',
        allowedSize: 1024 * 1024, // 1 MB
        allowedFileTypes: ['png', 'jpeg', 'jpg'],
        allowedMimeTypes: ['image/jpeg', 'image/jpg', 'image/png']
      },
      requestHandler
    )
    .then(() => {
      updateDB();
    })
    .catch((e) => {console.log(e);});
}

/**
 * @route DELETE /team/{teamID}
 * @group Team - End points for admin to manage teams and users to see their teams
 * @summary Deletes a team and remove its logo file
 * @param {string} teamID.path.required - Team's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  200 - success
 * @returns {Error}  default: Couldn't delete firmware.
 * @security userKey
 * @produces text/plain text/html
 */
exports.delete_team = function(req, res) {

  Team.findOneAndRemove({
      _id: req.params.teamID
    })
    .then((firmware) => {

      if (!firmware) {
        throw ("Couldn't delete firmware.");
      }

      fs.unlinkSync(`public/img/teams/${firmware.logo}`, 'utf8');
      res.send('{"data": "success"}');
    })
    .catch((er) => res.send('{"data": "Team deletion failed."}'));
}
