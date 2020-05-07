'use strict';

const mongoose = require('mongoose');
const Statistics = mongoose.model("Statistics");
const Team = mongoose.model("Team");

const FirmwareSchema = new mongoose.Schema({
  name: {
    type: String,
    required: true
  },
  /*
   *   Semantic Versioning
   *   Given a version number MAJOR.MINOR.PATCH, increment the:
   *     MAJOR version when you make incompatible API changes,
   *     MINOR version when you add functionality in a backwards compatible manner, and
   *     PATCH version when you make backwards compatible bug fixes.
   */
  version: {
    major: {
      type: Number,
      required: true,
      default: 0
    },
    minor: {
      type: Number,
      required: true,
      default: 0
    },
    patch: {
      type: Number,
      required: true,
      default: 1
    }
  },
  location: {
    type: String,
    required: true
  },
  comment: {
    type: String
  },
  statistics: {
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Statistics'
  }
});

// Add new firmware statistics
FirmwareSchema.pre("save", function(next) {
  const Firmware = this;

  // Create a statistics for the new firmware
  new Statistics().save().then(created => {
    Firmware.statistics = created._id;
    next();
  });

});

module.exports = mongoose.model('Firmware', FirmwareSchema);
