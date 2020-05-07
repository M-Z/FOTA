'use strict';
const {
  Joi,
  celebrate
} = require('celebrate');

const vehicleCredentialsSchema = {
  body: Joi.object().keys({

    vehicleName: Joi.string()
      .pattern(new RegExp('^[a-zA-Z0-9 ]*$'))
      .required()
      .error((errors) => {
        switch (errors[0].code) {
          case ('string.pattern.base'):
            return new Error("Invalid vehicle name");
          default:
            return new Error("Vehicle name is required");
        }
      }),

    password: Joi.string()
      .required()
      // .pattern(new RegExp('^(((?=.*[a-z])(?=.*[A-Z]))|((?=.*[a-z])(?=.*[0-9]))|((?=.*[A-Z])(?=.*[0-9])))(?=.{6,})'))
      .error((error) => {
        switch (error[0].code) {
          case 'string.pattern.base':
            return new Error('Incorrect Vehicle password supplied');
          default:
            return new Error('Vehicle password is required');
        }
      }),

    hashType: Joi.string()
      .optional()
      .valid(...require('../../config/config').supportedHashes)
      .error(new Error('Unsupported hash type')),

    bytes: Joi.number()
      .min(200)
      .max(102400)
      .optional()
      .error((errors) => {
        switch (errors[0].code) {
          case ('number.base'):
            return new Error("Invalid bytes field");
          case ('number.min'):
            return new Error("Paritions can't be less than 200 bytes");
          case ('number.max'):
            return new Error("Paritions can't be more than 102400 bytes");
        }
      }),
  })
};

module.exports = function(router) {

  const vehicle = require('../controllers/vehicle.controller');

  router.post('/firmware/v/:firmwareId',
    celebrate(vehicleCredentialsSchema),
    vehicle.authenticate_vehicle
  );

  router.post('/firmware/get/:firmwareId',
    celebrate(vehicleCredentialsSchema),
    vehicle.authenticate_vehicle
  );

}
