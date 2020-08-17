const ws = require('ws');
const config = require('../config/config');
const sockets = {};
var internalConnectionReady = false;

class Clients {

  constructor() {
    this.clientList = {};
  }

  clientsLength() {
    return Object.keys(this.clientList).length;
  }

  saveClient(ID, client) {
    this.clientList[ID] = client;
  }

  deleteClient(ID) {
    delete this.clientList[ID];
  }
}

var token = false;

const runClientWebsocket = function(jwtToken = '', message = false) {
  const client = new ws(
    'wss://localhost:' + config.https_port + '/' + jwtToken, {
      rejectUnauthorized: false // Self-signed problem refer to https://stackoverflow.com/questions/44243503/standalone-nodejs-client-connects-to-a-self-signed-websocket-wss
    }
  );

  client.on('error', function(error) {
    console.log(error);
    console.log("Couldn't connect to internal WebSocket.");
  });

  client.on('close', function(error) {
    console.log("Connection to internal WebSocket closed.");
  });

  // Connected to websocket
  client.on('open', function(connection) {
    internalConnectionReady = client;

    if (message) {
      client.send(JSON.stringify(message));
    }

  });

  client.on('message', function(msg) {
    console.log("Internal got: " + msg);
  });
}

sockets.init = function(jwtToken) {
  token = jwtToken; // Store token if needed for reconnection

  const wsServer = new ws.Server({
    noServer: true
  });

  const clients = new Clients(); // Connected clients
  const maxConnectedClients = 10; // Maximum number of connected clients

  // Client credentials accepted
  wsServer.on('connection', function(connection, request, clientID) {

    // Received a message from the internal websocker
    if (clientID == 'internal websocket') {
      console.log("INTERNAL CLIENT CONNECTED");

      connection.on('message', function(message) {
        const keys = Object.keys(clients.clientList);
        const received = JSON.parse(message);

        // All subsribed parties
        for (const client of keys) {
          // Intended receiver
          if (received.receipients.includes(client) || received.receipients.length == 0) {
            clients.clientList[client].send(JSON.stringify(received.body));
          }
        }

      });
      return;
    }

    // Check if maximum number of clients reached or already connected
    if (clients.clientsLength() >= maxConnectedClients) {
      return false;
    }

    console.log("NEW CLIENT: " + clientID + " CONNECTED");

    clients.saveClient(clientID, connection);

    // Remove from connected clients
    connection.on('close', function(reasonCode, description) {
      clients.deleteClient(clientID);
    });
  });

  wsServer.on('error', () => console.log('Websocket Server Error'));

  runClientWebsocket(jwtToken);

  return wsServer;
}

sockets.sendToTerminal = function(message) {

  // WS client connection
  if (internalConnectionReady) {
    internalConnectionReady.send(JSON.stringify(message));
  } else {
    runClientWebsocket(token, JSON.stringify(message));
  }

}

module.exports = sockets;
