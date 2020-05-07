'use strict';

const mongoose = require('mongoose');

const UserSchema = new mongoose.Schema({
  email: {
    type: String,
    required: true,
    set: v => v.toLowerCase()
  },
  name: {
    firstName: {
      type: String,
      set: v => v.charAt(0).toUpperCase() + v.slice(1).toLowerCase()
    },
    lastName: {
      type: String,
      set: v => v.charAt(0).toUpperCase() + v.slice(1).toLowerCase()
    }
  },
  uploads: {
    type: Number,
    default: 0
  },
  joinDate: {
    type: Date,
    default: Date.now
  },
  password: {
    type: String
  },
  image: {
    type: String
  },
  role: {
    type: String,
    required: true,
    default: 'Developer',
    enum: [
      'Developer',
      'Leader',
      'Admin'
    ]
  },
  team: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Team',
  },
  userKey: {
    type: String
  }
}, {
  toObject: {
    virtuals: true
  },
  toJSON: {
    virtuals: true
  }
});

const bcrypt = require('bcryptjs');
const config = require('../../config/config');

// Remove from team
const Team = require('mongoose').model('Team');

UserSchema.pre("findOneAndDelete", function(next) {
  const DeletedUser = this.getQuery();

  Team.updateOne({}, {
      $pull: {
        members: DeletedUser._id
      }
    })
    .then((team) => {
      if (team.nModified < 1) {
        throw ("Couldn't delete User.");
      }

      next();
    })
    .catch(e => next(e));
});

// Encrypt password on every save (middleware)
UserSchema.pre("findOneAndUpdate", function(next) {

  // If password isn't updated
  if (!this._update.password) {
    next();
    return false;
  };

  const User = this;

  // generate a salt
  bcrypt.genSalt(config.saltWorkFactor, function(err, salt) {
    if (err) return next(err);

    // hash the password using our new salt
    bcrypt.hash(User._update.password, salt, async function(err, hash) {
      if (err) next(err);
      // override the cleartext password with the hashed one

      User._update.password = hash;
      User._update.userKey = 'created';

      next();
    });
  });

});

// Hash new password and compare with saved hash
UserSchema.methods.comparePassword = function(candidatePassword) {
  return bcrypt.compare(candidatePassword, this.password);
};

module.exports = mongoose.model('User', UserSchema);
