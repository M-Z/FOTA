'use strict';

const mongoose = require('mongoose');

const StatisticsSchema = new mongoose.Schema({
  downloadRequest: {
    succeed: {
      type: Number,
      default: 0
    },
    failed: {
      type: Number,
      default: 0
    },
    unknown: {
      type: Number,
      default: 0
    }
  },
  versionRequest: {
    type: Number,
    default: 0
  }
});

module.exports = mongoose.model('Statistics', StatisticsSchema);
