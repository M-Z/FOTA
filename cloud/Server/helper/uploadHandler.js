const multer = require("multer");

const config = require('../config/config'); // Root foler
const mmm = require('mmmagic');
const Magic = mmm.Magic;
const fs = require('fs');
const magic = new Magic(mmm.MAGIC_MIME_TYPE);

module.exports = async function(
  req,
  res,
  options,
  requestHandler = () => {
    return true
  } // Function to call when request is parsed
) {

  return new Promise((resolve, reject) => {
    const defaults = {
      fileName: false, // File name to intercept in form data
      allowedMimeTypes: [],
      allowedFileTypes: [],
      directory: config.rootFolder,
      allowedSize: 128 * 1024 // default to 128kBs
    };

    const uploadedFile = Object.assign({}, defaults, options);

    if (!uploadedFile.fileName) {
      reject("File name field is required.");
      return false;
    }

    if (uploadedFile.allowedFileTypes.length == 0) {
      reject("Allowed file types are required.");
      return false;
    }

    let fileIntercepted = false; // file uploaded correctly from font-end

    // Store directly to disk
    const storage = multer.diskStorage({
      destination: function(req, file, cb) {
        cb(null, "./quarantine/");
      },
      filename: function(req, file, cb) {
        (req.fileID) ? cb(null, req.fileID): cb("Invalid file name", false);
      }
    });

    const validateFile = async function(req, file, cb) {
      const fileExtension = file ? file.originalname.split('.') : false;

      fileIntercepted = true; // Multer intercepted a file

      // Check file extension
      if (
        !file ||
        fileExtension.length != 2 ||
        !uploadedFile.allowedFileTypes.includes(fileExtension[1])
      ) {
        cb("Invalid file uploaded.", false);
        return false;
      }

      req.fileExtension = fileExtension[1];
      const handledRequest = await requestHandler(req);

      if (handledRequest === true) {
        cb(null, true);
      } else {
        cb(handledRequest, false);
      }

    }

    const upload = multer({
        storage: storage,
        fileFilter: validateFile,
        limits: {
          fileSize: uploadedFile.allowedSize,
          files: 1
        }
      })
      .single(uploadedFile.fileName);

    // Multer upload handler
    upload(req, res, function(response) {

      if (response instanceof multer.MulterError) {

        // A Multer error occurred when uploading.
        if (response.code == 'LIMIT_FILE_SIZE') {
          res.send(`{"data":"${response.message} maximum is ${ uploadedFile.allowedSize >= 1024 * 1024 ? uploadedFile.allowedSize / (1024 * 1024) + 'MBs' : uploadedFile.allowedSize + 'KBs'  }"}`);
        } else {
          res.send('{"data":"' + response.message + '"}');
        }

        reject(response);
        return false;
      } else if (response) {
        // An unknown error occurred when uploading.
        res: res.send(`{"data":"${response}"}`);
        reject(response);
        return false;
      } else if (!fileIntercepted) {
        // Check if file could be parsed by Multer
        res.send('{"data": "No file uploaded."}');
        reject('No file uploaded');
        return false;
      }

      // Check magic bytes
      magic.detectFile('./quarantine/' + req.fileID, function(err, mimeType) {

        if (err || !uploadedFile.allowedMimeTypes.includes(mimeType)) {
          // An unknown error occurred when uploading.
          res.send(`{"data":"Only '${ uploadedFile.allowedFileTypes.join("', '") }' file formats are allowed."}`);

          if (!err) {
            fs.unlinkSync('quarantine/' + req.fileID);
          }

          reject(err);
          return false;
        }

        // Move file to the intended directory
        move(
          'quarantine/' + req.fileID,
          `${uploadedFile.directory}/${req.fileID}`,
          (err) => {

            if (err) {

              // An unknown error occurred when uploading
              res.send(`{"data":"An unknown error occurred when uploading."}`);

              reject(err);
              return false;
            }

            resolve(true);
          });

      }); // Magic bytes

    }); // Upload function

  });
}

const move = function(oldPath, newPath, callback) {

  fs.rename(oldPath, newPath, function(err) {

    if (err) {
      if (err.code === 'EXDEV') {
        copy();
      } else {
        callback(err);
      }

      return;
    }

    callback();
  });

  function copy() {
    var readStream = fs.createReadStream(oldPath);
    var writeStream = fs.createWriteStream(newPath);

    readStream.on('error', callback);
    writeStream.on('error', callback);

    readStream.on('close', function() {
      fs.unlink(oldPath, callback);
    });

    readStream.pipe(writeStream);
  }
}
