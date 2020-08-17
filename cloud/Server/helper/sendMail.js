const handlebars = require('handlebars');
const fs = require('fs');
const config = require('../config/config');

const transport = require('nodemailer').createTransport({
  host: "elalameya.net",
  port: 465,
  auth: {
    user: "fota@elalameya.net",
    pass: "hv8F6#S$NeMnrjdkCtH"
  },
  secure: true
});

const readHTMLFile = function(path) {
  return new Promise((resolve, reject) => {

    fs.readFile(path, {
      encoding: 'utf-8'
    }, function(err, html) {
      if (err) {
        throw err;
        reject(err);
      } else {
        resolve(html);
      }
    });

  });
};

const sendEmail = async function(user) {
  if (!user) return false;

  let state = false;

  // Read HTML template file
  await readHTMLFile('./src/assets/emails/invite/invite.html')
    .then(html => {

      const template = handlebars.compile(html);

      const replacements = {
        guest_name: user.email,
        guest_team: user.team.teamName,
        invitation_link: user.userKey,
        base_url: config.base_url
      };

      const message = {
        from: 'FOTA <fota@elalameya.net>', // Sender address
        to: user.email, // List of recipients
        subject: `You've been invited to ${ user.team.teamName } team!`, // Subject line
        html: template(replacements)
      };

      return message;
    })
    .then(async (message) => {

      await new Promise((resolve, reject) => {

          transport.sendMail(message, function(err, response) {
            if (err) resolve(false);

            resolve(true);
          });

        })
        .then(
          sent => state = sent
        );

    })
    .catch((e) => {console.log(e);});

  return state;
}

module.exports = sendEmail;
