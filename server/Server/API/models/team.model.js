'use strict';

const mongoose = require('mongoose');

const TeamSchema = new mongoose.Schema({
  teamName: {
    type: String,
    required: true
  },
  description: {
    type: String
  },
  members: [{
    type: mongoose.Schema.Types.ObjectId,
    ref: 'User'
  }],
  logo: {
    type: String,
    required: true
  },
  secret: {
    type: String,
    required: true
  },
  joinDate: {
    type: Date,
    default: Date.now
  },
  firmware: [{
    type: mongoose.Schema.Types.ObjectId,
    ref: 'Firmware',
  }]
}, {
  toObject: {
    virtuals: true
  },
  toJSON: {
    virtuals: true
  }
});

module.exports = mongoose.model('Team', TeamSchema);
