'use strict';

const {
  Joi,
  celebrate
} = require('celebrate');

const teamIDSchema = {
  params: Joi.object().keys({

    teamID: Joi.string()
      .required()
      .alphanum()
      .min(10)
      .error(new Error('{"data": "Invalid Team ID"}'))
  })
};

module.exports = function(router) {

  const team = require('../controllers/team.controller');

  router.get('/teams/', team.read_all_teams);

  router.get('/team/firmwares',
    team.get_team_firmwares
  );

  router.post('/team/', team.add_team);

  router.get('/team/:teamID',
    celebrate(teamIDSchema),
    team.read_team
  );

  router.delete('/team/:teamID',
    celebrate(teamIDSchema),
    team.delete_team
  );

}
