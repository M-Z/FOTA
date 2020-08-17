const fs = require('fs');
const path = require("path");

require('./config/mongoose'); // DB connection

const app = require('./config/express');
const {
  TokenGenerator,
  sockets
} = require('./helper');

const config = require('./config/config');

// var proxy = require('express-http-proxy');
// app.use('/proxy', proxy('www.google.com'));

// we will pass our 'app' to 'https' server
const secureServer = require('https')
  .createServer({
      key: fs.readFileSync(path.resolve(config.certficatesPath + '/key.pem'), 'ascii'),
      cert: fs.readFileSync(path.resolve(config.certficatesPath + '/cert.pem'), 'ascii'),
      passphrase: config.certPathPhrase
    },
    app
  );

secureServer.listen(config.https_port, () => {
  console.log('HTTPS Server running on port ' + config.https_port);
});;

// Redirect from http port 80 to https
const http = require('http');
http.createServer(function(req, res) {
  res.writeHead(301, {
    "Location": "https://" + req.headers['host'] + req.url
  });
  res.end();
}).listen(config.http_port);

const tokenGenerator = new TokenGenerator({
  priv: fs.readFileSync('Server/cryptKeys/key.pem'),
  pub: fs.readFileSync('Server/cryptKeys/cert.pem'),
  passphrase: 'PEM pass phrase',
  options: {
    algorithm: 'RS256',
    expiresIn: '60m'
  }
});

// Activate websocket and pass jwt of internal socket
const wsServer = sockets.init(
  tokenGenerator.sign({
    team: {
      teamName: 'internal websocket'
    }
  })
);

const authenticate = function(request, cb) {
  const token = request.url.substring(1);

  if (!tokenGenerator.verify(token)) {
    throw ("Authentication failed!");
  }

  const clientID = tokenGenerator.decode(token).team.teamName;

  if (clientID !== 'internal websocket' && !['https://localhost:4200', 'https://34.65.7.33'].includes(request.headers.origin)) {
    throw ("Incorrect origin!");
  }

  return cb(clientID);
};

// Attach upgrade sent handler to HTTPS server
secureServer.on('upgrade', function upgrade(request, socket, head) {

  // Check origin and authorization
  try {

    authenticate(request, (clientID) => {

      if (!clientID) {
        socket.destroy();
      }

      wsServer.handleUpgrade(request, socket, head, function done(ws) {
        wsServer.emit('connection', ws, request, clientID);
      });
    });

  } catch (e) {
    console.log("Authentication failed.");
    socket.destroy();
    return;
  }
});
