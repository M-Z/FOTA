const express = require('express');
const helmet = require('helmet');
const bodyParser = require('body-parser');
const cookieParser = require('cookie-parser');
const securityTxt = require('express-security-txt')
const path = require('path');
const config = require('./config');
const Celebrate = require('celebrate');
const {
  errors
} = Celebrate;

const app = express();

app.use(
  helmet(),
  helmet.contentSecurityPolicy({
    directives: {
      defaultSrc: ["'self'"],
      scriptSrc: [
	"'self'",
	"'sha256-WKuDZ/JEhPqWVB/Q/9NHi/rWHSoQaxYVDHZ/s8d3Kfw='"
      ],
      styleSrc: [
        "'self'",
        'https://stackpath.bootstrapcdn.com',
        'https://fonts.googleapis.com',
        "'unsafe-inline'"
      ],
      fontSrc: [
	"'self'",
	'fonts.gstatic.com',
	"data:"
      ],
      connectSrc: ["'self'"],
      imgSrc: [
	"'self'",
	"data:",
	"https://online.swagger.io"
      ],
      frameAncestors: ["'none'"],
      upgradeInsecureRequests: true
    }
  }),
  bodyParser.json(), // content-type: application/json
  bodyParser.urlencoded({
    extended: true // content-type: application/x-www-form-urlencoded
  }),
  cookieParser(),
  securityTxt.setup({
    _prefixComment: 'Want to report anything?',
    contact: [{
        comment: 'You can try posting here on our repo',
        value: 'https://github.com/Mario-Medhat/FOTA'
      },
      {
        comment: 'Contact me directly instead?',
        value: 'mailto:mario_medhat@outlook.com',
      }
    ],
    preferredLanguages: 'en, ar',
    _postfixComment: 'Thanks!'
  }) // security.txt proposed standard
);

// Serve Angular UI distribution files
app.use(
  express.static(
    path.join(__dirname, '../../dist')
  )
);

// Serve static public files
app.use('/static',
  express.static(
    path.join(__dirname, '../../public')
  )
);

// API docs
const expressSwagger = require('express-swagger-generator')(app);

expressSwagger({
  swaggerDefinition: {
    info: {
      description: 'Firmware over-the-air graduation project `2020`',
      title: 'FOTA',
      version: '1.0.0',
      contact: {
        name: 'FOTA Team',
        email: "mario_medhat@outlook.com",
        url: 'https://github.com/Mario-Medhat/FOTA'
      },
      license: {
        name: "Apache 2.0",
        url: "http://www.apache.org/licenses/LICENSE-2.0.html"
      }
    },
    host: '34.65.7.33',
    basePath: '/API',
    consumes: [
      "application/json",
      "application/x-www-form-urlencoded"
    ],
    produces: [
      "application/json",
      "text/plain",
      "text/html"
    ],
    schemes: ['https'],
    securityDefinitions: {
      userKey: {
        type: "apiKey",
        name: 'Authorization',
        in: 'header',
        description: "For front-end interactions with the API, this key is needed",
      }
    }
  },
  route: {
    url: '/API',
    docs: '/api-docs.json'
  },
  basedir: __dirname, //app absolute path
  files: ['../API/controllers/*.js'] //Path to the API handle folder
});

// API endpoints
app.use('/API',
  require('cors')({
    origin: [
      "https://localhost:4200",
      "https://34.65.7.33"
    ],
    credentials: true
  }),
  require('../API/routes/index.router')
);

// Catch all other routes and return the index file
app.get('*', (req, res) => {
  res.sendFile(path.join(__dirname, '../../dist/index.html'));
});

// Last fallback if Front-end didn't catch the 404
app.use(function(req, res) {
  res.status(404).send({
    url: req.originalUrl + ' not found.'
  });
});

// Bad requests
app.use(function(e, req, res, next) {
  console.log(e);
  res.status(400).send("Unhandled request.");
});

module.exports = app;
