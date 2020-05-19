const jwt = require('jsonwebtoken');

function TokenGenerator(options) {

  this.secretOrPublicKey = options.pub;
  this.secretOrPrivateKey = options.priv;

  if (options.passphrase) {
    this.secretOrPrivateKey = {
      key: options.priv,
      passphrase: options.passphrase
    };
  }

  this.options = options.options; //algorithm + keyid + noTimestamp + expiresIn + notBefore
}

TokenGenerator.prototype.sign = function(payload, signOptions) {
  const jwtSignOptions = Object.assign({}, signOptions, this.options); // Append options
  return jwt.sign(payload, this.secretOrPrivateKey, jwtSignOptions);
}

TokenGenerator.prototype.verify = function(token, verifyOptions) {
  const jwtVerifyOptions = Object.assign({}, verifyOptions, this.options); // Append options
  return jwt.verify(token, this.secretOrPublicKey, jwtVerifyOptions);
}

// refreshOptions.verify = options you would use with verify function
// refreshOptions.jwtid = contains the id for the new token
TokenGenerator.prototype.refresh = function(token, refreshOptions = {}) {
  const payload = jwt.verify(token, this.secretOrPublicKey, refreshOptions.verify);
  delete payload.iat;
  delete payload.exp;
  delete payload.nbf;
  delete payload.jti; // We are generating a new token, if you are using jwtid during signing, pass it in refreshOptions
  const jwtSignOptions = Object.assign({}, this.options, refreshOptions);
  // The first signing converted all needed options into claims, they are already in the payload
  return jwt.sign(payload, this.secretOrPrivateKey, jwtSignOptions);
}

TokenGenerator.prototype.decode = function(payload, decodeOptions) {
  const jwtDecodeOptions = Object.assign({}, decodeOptions, this.options); // Append options
  return jwt.decode(payload, jwtDecodeOptions);
}

module.exports = TokenGenerator;
