'use strict';

const {
  Joi,
  celebrate
} = require('celebrate');

module.exports = function(router) {

  const stats = require('../controllers/statistics.controller');

  router.get('/statistics/:firmwareId',
    celebrate({
      params: Joi.object().keys({

        firmwareId: Joi.string()
          .required()
          .alphanum()
          .min(10)
          .error(new Error('{"data":"Invalid firmware ID"}'))
      })
    }),
    stats.read_statistics);

}
