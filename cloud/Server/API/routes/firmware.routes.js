'use strict';

const {
  Joi,
  celebrate
} = require('celebrate');

const firmwareSchema = {
  params: Joi.object().keys({

    firmwareID: Joi.string()
      .required()
      .alphanum()
      .min(10)
      .error(new Error('Invalid firmware ID'))
  })
}

module.exports = function(router) {

  const firmware = require('../controllers/firmware.controller');

  router.post('/firmware/v/:firmwareID',
    celebrate(firmwareSchema),
    firmware.get_firmware_version
  );

  router.post('/firmware/get/:firmwareID',
    celebrate(firmwareSchema),
    firmware.read_firmware_file
  );

  router.post('/firmware/update/:firmwareID',
    celebrate(firmwareSchema),
    firmware.update_firmware_file
  );
  router.delete('/firmware/delete/:firmwareID',
    celebrate(firmwareSchema),
    firmware.delete_firmware_file
  );

}
