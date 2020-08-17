module.exports = {
  TokenGenerator: require('./jwtHandler'),
  sendFeedback: require('./responseHelper'),
  hashFile: require('./hashFile'),
  sockets: require('./sockets'),
  roles: require('./roles').roles,
  upload: require('./uploadHandler'),
  sendEmail: require('./sendMail'),
  totp: require('./totp'),
}
