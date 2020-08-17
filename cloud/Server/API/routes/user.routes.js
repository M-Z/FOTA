'use strict';
const {
  Joi,
  celebrate
} = require('celebrate');

const requestHeaderSchema = {
  headers: Joi.object().keys({
    authorization: Joi.string()
      .required()
      .pattern(/^Bearer\s[a-zA-Z0-9-_.]+/)
      .error(new Error('{"data": "No authorization supplied"}'))
  }).unknown(true) // Allow other headers to propagate
};

module.exports = function(router) {

  const user = require('../controllers/user.controller');

  router.post('/user/login',
    celebrate({
      body: Joi.object().keys({

        username: Joi.string()
          .required()
          .error(new Error('{"error": "Invalid E-mail."}')),

        password: Joi.string()
          .required()
          .error(new Error('{"error": "Invalid password."}'))
      })
    }),
    user.login_User
  );

  router.post('/user/add',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('createAny', 'profile'),
    celebrate({
      body: Joi.object().keys({

        email: Joi.string()
          .email({
            minDomainSegments: 2,
            tlds: {
              allow: ['com', 'net']
            }
          })
          .max(256)
          .required()
          .error(new Error('{"data": "Invalid user e-mail."}')),

        role: Joi.string()
          .valid('Leader', 'Developer')
          .required()
          .pattern(new RegExp('^(((?=.*[a-z])(?=.*[A-Z]))|((?=.*[a-z])(?=.*[0-9]))|((?=.*[A-Z])(?=.*[0-9])))(?=.{6,})'))
          .error(new Error('{"data": "Invalid role supplied."}')),

        teamID: Joi.string()
          .required()
          .alphanum()
          .min(10)
          .error(new Error('{"data": "Invalid team supplied."}')),

      })
    }),
    user.add_User
  );

  router.post('/user/refreshToken',
    user.refreshToken
  );

  router.post('/user/logout',
    user.logout
  );

  router.delete('/user/:userID',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('deleteAny', 'profile'),
    celebrate({
      query: Joi.object().keys({

        userID: Joi.string()
          .alphanum()
          .min(10)
          .error(new Error('{"data":"Invalid firmware ID"}'))
      })
    }),
    user.delete_user
  );

  router.post('/user/register',
    user.user_registeration
  );

  // Protect team routes
  router.get('/teams',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('readAny', 'team')
  );

  // Any logged in user can see his team's firmwares
  router.get('/team/firmwares',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('readOwn', 'team')
  );

  router.get(
    '/team/:teamID',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('readOwn', 'team'),
  );

  router.post('/team/',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('createAny', 'team'),
  );

  router.delete(
    '/team/:teamID',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('deleteAny', 'team')
  );

  // Protect firmware routes
  router.post('/firmware/update/:firmwareId',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('updateOwn', 'team', 'firmware')
  );

  router.delete('/firmware/delete/:firmwareID',
    celebrate(requestHeaderSchema),
    user.authenticate_User,
    user.grantAccess('deleteOwn', 'team', 'firmware')
  );

  // Protect statistics route
  router.get('/statistics/:firmwareId',
    celebrate(requestHeaderSchema),
    user.authenticate_User
  );

}
