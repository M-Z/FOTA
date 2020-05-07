const mongoose = require('mongoose');
const util = require('util');
const debug = require('debug')('API:index');
const config = require('./config');

// DB collection models
require('../API/models');

// connect to mongo db
mongoose.connect(config.mongo.host + ':' + config.mongo.port + '/' + config.mongo.db, {
  keepAlive: 1,
  useNewUrlParser: true,
  useUnifiedTopology: true,
  useFindAndModify: false
});

mongoose.connection.on(
  'error',
  () => {
    throw new Error('Unable to connect to DataBase.');
  }
);
