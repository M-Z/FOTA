'use strict';

const Team = require('mongoose').model('Team');

/**
 * Returns the number of failed and succeeded requests made by vehicles
 * as well as the number of version requests.
 * @route GET /statistics/{firmwareID}
 * @group Firmware - End points for team leaders and developers
 * @summary Returns the firmware's statistics
 * @param {string} firmwareID.path.required - Firmware's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  200 - Firmware's statistics
 * @returns {Error}  default - {error: "Error message."}
 * @security userKey
 * @produces application/json
 */
exports.read_statistics = function(req, res) {

  const teamQuery = (req.user.role === 'Admin') ? {} : {
    _id: req.user.team._id
  };

  Team
    .findOne(teamQuery, 'firmware -_id')
    .lean()
    .populate({
      path: 'firmware',
      select: 'statistics',
      match: {
        _id: req.params.firmwareId
      },
      populate: {
        path: 'statistics',
        select: "-_id",
      }
    })
    .then(response => {

      if (!response ||
        response.firmware.length == 0 ||
        !response.firmware[0].statistics) {
        throw ('Firmware error.')
      }

      res.json(response.firmware[0].statistics);
    }).catch((err) => {

      res.status(404).json({
        error: "Firmware not found."
      });
    });
}
