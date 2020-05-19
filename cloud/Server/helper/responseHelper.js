const mongoose = require('mongoose');
const Team = mongoose.model('Team');
const Statistics = mongoose.model('Statistics');
const sockets = require('./sockets');

module.exports = async function feedbackHandler(feedbackItem = {
  commandString: null,
  commandOutput: null,
  firmwareID: null,
  incrementField: null,
  res: null,
  sendRequest: null
}) {
  let teams = [];
  await Team.find({
      firmware: feedbackItem.firmwareID
    })
    .lean()
    .populate({
      path: 'firmware',
      match: {
        _id: feedbackItem.firmwareID
      },
      populate: {
        path: 'statistics'
      }
    })
    .then(DBteams => {
      teams = DBteams;
    })
    .catch((e) => {
      feedbackItem.sendRequest = "Some error occured.";
    });

  // Update stats data if supplied
  if (teams.length > 0 && feedbackItem.incrementField) {

    await Statistics.updateOne({
      _id: teams[0].firmware[0].statistics._id
    }, {
      $inc: {
        [feedbackItem.incrementField]: 1
      }
    })

  }

  // Send results to websocket
  if (feedbackItem.commandString && feedbackItem.commandOutput) {
    sockets.sendToTerminal({
      receipients: teams.map(team => team.teamName),
      body: {
        event: 'command',
        data: {
          string: feedbackItem.commandString,
          output: feedbackItem.commandOutput
        }
      }
    });
  }

  // Send HTTP response
  if (feedbackItem.sendRequest && feedbackItem.res) {
    feedbackItem.res.send(feedbackItem.sendRequest);
  }

}
