'use strict'

const router = require('express').Router();
const swaggerUi = require('swagger-ui-express');

const {
  isCelebrate
} = require('celebrate');

// register API routes
require('./user.routes')(router);
require('./team.routes')(router);
require('./vehicle.routes')(router);
require('./firmware.routes')(router);
require('./statistics.routes')(router);

router.use(
  (error, req, res, next) => {

    // It's likely a client-side problem
    if (isCelebrate(error)) {
      return res.send(error.joi.message);
    }
    console.log(error);
    //otherwise, it's probably a server-side problem.
    return res.status(404).send("Some error occured.");
  },
  function(req, res) {
    res.status(404).send({
      error: `Endpoint: '${req.originalUrl}' not found.`
    });
  });

module.exports = router;
