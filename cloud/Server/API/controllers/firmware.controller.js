'use strict';

const Firmware = require('mongoose').model('Firmware');
const Team = require('mongoose').model('Team');
const Statistics = require('mongoose').model('Statistics');
const User = require('mongoose').model('User');
const fs = require('fs');
const crypto = require('crypto');
const config = require('../../config/config.js');
const shortid = require('shortid');
const {
  sendFeedback,
  hashFile,
  upload,
  totp
} = require('../../helper');

/**
 * Vehicle's username and password to use the API's features
 * @typedef vehicleCredentials
 * @property {string} vehicleName.required - username of requesting vehicle - eg: fota user
 * @property {string} password.required - password of requesting vehicle - eg: 123
 */

/**
 * Optional parameters for firmware download
 * @typedef firmwareOptions
 * @property {string} vehicleName.required - username of requesting vehicle - eg: fota user
 * @property {string} password.required - Password of requesting vehicle - eg: 123
 * @property {string} bytes - Number of bytes to divide the whole hex file into. - eg: 200
 * @property {enum} hashType - Hashing algorithm to use.
 *
 * - default: sha256
 * - Available hashes on the server:
 * - eg: sha256,md5,DSA,DSA-SHA,DSA-SHA1,DSA-SHA1-old,RSA-MD4,RSA-MD5,RSA-MDC2,RSA-RIPEMD160,RSA-SHA,RSA-SHA1,RSA-SHA1-2,RSA-SHA224,RSA-SHA256,RSA-SHA384,RSA-SHA512,dsaEncryption,dsaWithSHA,dsaWithSHA1,dss1,ecdsa-with-SHA1,md4,md4WithRSAEncryption,md5WithRSAEncryption,mdc2,mdc2WithRSA,ripemd,ripemd160,ripemd160WithRSA,rmd160,sha,sha1,sha1WithRSAEncryption,sha224,sha224WithRSAEncryption,sha256WithRSAEncryption,sha384,sha384WithRSAEncryption,sha512,sha512WithRSAEncryption,shaWithRSAEncryption,ssl2-md5,ssl3-md5,ssl3-sha1,whirlpool
 */

/**
 * @route GET /firmwares
 * @group Vehicle - End points for vehicle interaction
 * @deprecated true
 * @summary Returns all the firmwares on the server
 * @returns {string}  default - Returns a detailed list of firmwares
 * @produces text/plain text/html
 */

/**
 * Called from the vehicle to the API with the vehicle's credentials
 * to get a specific firmware semantic version (in the form of "vXX.XX.XX")
 * @route POST /firmware/v/{firmwareID}
 * @group Vehicle - End points for vehicle interaction
 * @summary Returns the firmware's semantic version
 * @param {vehicleCredentials.model} body.body.required - Vehicle's credentials
 * @param {string} firmwareID.path.required - Firmware's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  default - Firmware's semantic version
 * @produces text/plain text/html
 */
exports.get_firmware_version = function(req, res) {

  // Search for the specified ID
  Firmware.findById(req.params.firmwareID, function(err, firmware) {

    if (err || firmware === null) {

      return sendFeedback({
        firmwareID: firmware ? firmware._id : null,
        incrementField: "versionRequest",
        commandString: `Getting firmware [version] with ID ${req.params.firmwareID}`,
        commandOutput: "Firmware not found.",
        res: res,
        sendRequest: "Firmware not found."
      });

    }

    const version = `v${firmware.version.major}.${firmware.version.minor}.${firmware.version.patch}`;

    sendFeedback({
      firmwareID: firmware._id,
      incrementField: "versionRequest",
      commandString: `Getting firmware [version] with ID ${req.params.firmwareID}`,
      commandOutput: `Returned: ${version}`,
      res: res,
      sendRequest: version
    });

  });

};

/**
 * Called from the vehicle to the API with the vehicle's credentials to get the firmware's hashed hex data followed by the hex data itself. Each divided by n-chunks
 * @route POST /firmware/get/{firmwareID}
 * @group Vehicle - End points for vehicle interaction
 * @summary Returns the firmware's hash followed by hex data. Each divided by n-chunks
 * @param {firmwareOptions.model} body.body - Vehicle's credentials and download options
 * @param {string} firmwareID.path.required - Firmware's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  default - n chunks of hashes followed by the hex file content
 * @produces text/plain text/html
 */
exports.read_firmware_file = function(req, res) {

  // Searches for the file
  Firmware.findById(req.params.firmwareID, async function(err, firmware) {

    if (err || firmware === null) {

      return sendFeedback({
        firmwareID: firmware ? firmware._id : null,
        incrementField: "downloadRequest.unknown",
        commandString: `Getting firmware [file] with ID ${req.params.firmwareID}`,
        commandOutput: 'Firmware not found.',
        res: res,
        sendRequest: "Firmware not found."
      });

    }

    // Read from rootFolder/fileName
    fs.readFile(`${config.rootFolder}/${firmware.location}`, 'utf8', async function(err, contents) {

      if (err || !contents) {

        return sendFeedback({
          firmwareID: firmware._id,
          incrementField: "downloadRequest.failed",
          commandString: `Getting firmware [file] with ID ${req.params.firmwareID}`,
          commandOutput: 'Firmware file not found on the server',
          res: res,
          sendRequest: "Firmware file not found on the server"
        });

      }

      sendFeedback({
        firmwareID: firmware._id,
        incrementField: "downloadRequest.succeed",
        commandString: `Getting firmware [file] with ID ${req.params.firmwareID}`,
        commandOutput: `Returned firmware ${ firmware.location }.hex`,
        res: res,

        // Generate file Hash
        sendRequest: hashFile({
          contents: contents,
          re: `[^]{1,${ req.body.bytes }}`,
          hashType: req.body.hashType || config.hashType
        })
      });

    });
  });
};

/**
 * @route DELETE /firmware/delete/{firmwareID}
 * @group Firmware - End points for team leaders and developers
 * @summary Deletes firmware and remove its file
 * @param {string} firmwareID.path.required - Firmware's unique ID - eg: 5e9274770bfe6bc0f0e8d947
 * @returns {string}  200 - success
 * @returns {Error}  default: Firmware deletion failed.
 * @security userKey
 * @produces text/plain text/html
 */
exports.delete_firmware_file = function(req, res) {

  Firmware.findOneAndDelete({
      _id: req.params.firmwareID
    })
    .then(async (firmware) => {

      fs.unlinkSync(`${config.rootFolder}/${firmware.location}`, 'utf8');

      // Delete reference to firmware
      await Team.updateOne({
        firmware: firmware._id
      }, {
        $pull: {
          firmware: firmware._id
        }
      });

      await Statistics.deleteOne({
        _id: firmware.statistics
      });

      sendFeedback({
        commandString: `Deleting firmware with ID ${req.params.firmwareID}`,
        commandOutput: `Firmware deleted successfully!`,
        res: res,
        sendRequest: '{"data": "success"}'
      });
    })
    .catch((er) => {
      sendFeedback({
        commandString: `Deleting firmware with ID ${req.params.firmwareID}`,
        commandOutput: `Firmware deleting failed!`,
        res: res,
        sendRequest: '{"data": "Firmware deletion failed."}'
      });
    });
}

/**
 * @route POST /firmware/update
 * @group Firmware - End points for team leaders and developers
 * @summary Creates or updates a new firmware
 * @param {string} version.formData.required - Firmware's Version v1.1.0
 * @param {string} name.formData.required - Firmware's name like: GSM Module
 * @param {string} comment.formData - Optional comments
 * @param {number} otp.formData.required - OTP of the team
 * @param {file} hexFile.formData.required - The .hex file
 * @param {string} firmwareID.path.required - Old ID or 'new firmware'
 * @returns {string}  200 - success
 * @returns {Error}  default: Firmware deletion failed.
 * @security userKey
 * @consumes application/x-www-form-urlencoded
 * @produces text/plain text/html
 */
exports.update_firmware_file = function(req, res) {

  const updateDB = function() {
    const versionParts = req.body.version ? req.body.version.substr(1).split('.') : false,
      updatedData = {};
    updatedData.name = req.body.name;
    updatedData.version = {
      major: versionParts[0],
      minor: versionParts[1],
      patch: versionParts[2]
    };

    // Append comment is exists
    if (req.body.comment) {
      updatedData.comment = req.body.comment;
    }

    updatedData.location = req.fileID;

    // create a new firmware file
    if (req.params.firmwareID == 'newFirmware') {
      new Firmware(updatedData)
        .save()
        .then(newFirmware => {
          req.params.firmwareID = newFirmware._id;
          return newFirmware._id;
        })
        .then(async (newFirmwareID) => {

          // Add the new firmware to the team
          await Team.updateOne({
            _id: req.user.team._id
          }, {
            $push: {
              firmware: newFirmwareID
            }
          });

          // Append user uploads
          await User.updateOne({
            _id: req.user._id
          }, {
            $inc: {
              uploads: 1
            }
          });

        })
        .then(() => res.send('{"data": "success"}'))
        .catch(() => res.send('{"data": "Error adding firmware to DB."}'));

    } else {

      // Check if firmware is the same and update otherwise
      Firmware.findOne({
          _id: req.params.firmwareID
        }).then(firmware => {

          // update firmware data info
          firmware
            .updateOne(updatedData)
            .then(() => res.send('{"data": "success"}'))
            .catch(() => res.send('{"data": "Error adding firmware to DB."}'));

        })
        .catch(() => res.send("Error uploading file."));
    }

  };

  const requestHandler = async function(req) {
    const versionParts = req.body.version ? req.body.version.substr(1).split('.') : false;

    if (req.body.name == undefined) {
      return "Firmware name required.";
    }

    if (req.body.OTP == undefined) {
      return "OTP is required.";
    } else if (req.body.OTP.length != 6) {
      return "Invalid OTP.";
    }

    // Check if correct versioning format and user uploaded a file
    if (versionParts.length != 3 || req.body.version == undefined) {
      return "Firmware version required.";
    }

    let returnVal = "Some error occured";

    await Team.findOne({
        _id: req.user.team._id
      }).then(async (team) => {

        if (!team) {
          returnVal = "Team not found.";
          return false;
        }

        // Firmware exists and Version didn't change
        if (await !totp.verifyTOTP(req.body.OTP, team.secret)) {
          returnVal = "Incorrect OTP.";
          return false;
        }

        returnVal = true;
      })
      .catch((err) => {
        console.log(err);
        returnVal = 'Some error occured.';
      });

    if (returnVal === true && req.params.firmwareID == 'newFirmware') {
      req.fileID = shortid.generate() + '.hex';

      await new Promise((resolve, reject) => {
        fs.exists(`${config.rootFolder}/${req.fileID}`, function(exists) {

          // Generate a new file
          if (exists) {
            req.fileID = shortid.generate();
          }

          returnVal = true;
          resolve(true);
        });
      });

    } else if (returnVal === true) {
      // Check if firmware is the same and update otherwise
      await Firmware.findById(req.params.firmwareID)
        .then(firmware => {

          if (!firmware) {
            returnVal = "Firmware not found.";
            return false;
          }

          // Firmware exists and Version didn't change
          if (`v${firmware.version.major}.${firmware.version.minor}.${firmware.version.patch}` == req.body.version) {
            returnVal = "Firmware [version] didn't change.";
            return false;
          }

          req.fileID = firmware.location;
          returnVal = true;
        });

    }

    return returnVal;
  }

  upload(req, res, {
        fileName: 'hexFile',
        allowedFileTypes: ['hex'],
        allowedMimeTypes: ['text/plain']
      },
      requestHandler
    )
    .then(() => {
      updateDB();
    })
    .catch(() => {});
}
