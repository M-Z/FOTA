const crypto = require('crypto');
const base32 = require('hi-base32');
const {
  generateHOTP
} = require('./hotp');

const generateSecret = function(length = 20) {
  const randomBuffer = crypto.randomBytes(length);
  return base32.encode(randomBuffer).replace(/=/g, '');
}

/*
 * This is an implementation of Time-Based One Time Password (TOTP) algorithm
 * specified in RFC 6238 (https://tools.ietf.org/html/rfc6238)
 */
const generateTOTP = function(secret, window = 0, timeStepInSeconds = 30, initialTime = 0, otpLength = 6) {
  if (!secret) {
    throw new Error('Secret is required');
  }

  const currentTime = Date.now();
  const timeStep = timeStepInSeconds * 1000;
  const counter = Math.floor((currentTime - initialTime) / timeStep);
  return generateHOTP(secret, counter + window, otpLength);
}

/*
 * This function verifies the validity of OTP (token) entered by the user
 * from the Google Authenticator app.
 * The secret passed here as argument must match with the secret in the
 * authenticator app.
 */
const verifyTOTP = function(token, secret, window = 1) {
  try {
    token = parseInt(token, 10);

    if (isNaN(token)) {
      throw new Error();
    }
  } catch (e) {
    return false;
  }

  if (Math.abs(+window) > 10) {
    console.error('Window size is too large');
    return false;
  }

  for (let errorWindow = -window; errorWindow <= +window; errorWindow++) {
    const totp = generateTOTP(secret, errorWindow);
    if (token === totp) {
      return true;
    }
  }

  return false;
}

module.exports = {
  generateSecret,
  verifyTOTP,
  generateTOTP
}
