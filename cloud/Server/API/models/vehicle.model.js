'use strict';

const mongoose = require('mongoose');
const bcrypt = require('bcryptjs');

const config = require('../../config/config');

const VehicleSchema = new mongoose.Schema({
  vehicleName: {
    type: String,
    required: true
  },
  password: {
    type: String,
    required: true
  },
  hashType: {
    type: String,
    enum: config.supportedHashes,
    default: config.hashType
  },
  publicKey: {
    type: String,
    required: true
  }
});

// Encrypt password on every save (middleware)
VehicleSchema.pre("save", function(next) {
  var vehicle = this;

  // only hash the password if it has been modified (or is new)
  if (!vehicle.isModified('password')) return next();

  // generate a salt
  bcrypt.genSalt(config.saltWorkFactor, function(err, salt) {
    if (err) return next(err);

    // hash the password using our new salt
    bcrypt.hash(vehicle.password, salt, function(err, hash) {
      if (err) return next(err);

      // override the cleartext password with the hashed one
      vehicle.password = hash;
      next();
    });
  });

});

// Hash new password and compare with saved hash
VehicleSchema.methods.comparePassword = function(candidatePassword, cb) {
  bcrypt.compare(candidatePassword, this.password, function(err, isMatch) {
    if (err) return cb(err);
    cb(null, isMatch);
  });
};

module.exports = mongoose.model('Vehicle', VehicleSchema);
