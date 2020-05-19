const Joi = require('@hapi/joi');

// require and configure dotenv, will load vars in .env in PROCESS.ENV
require('dotenv').config();

// define validation for all the env vars
const envVarsSchema = Joi.object({
    NODE_ENV: Joi.string()
      .valid(
        'development',
        'production',
        'test'
      )
      .default('development'),

    CERT_PATH: Joi.string()
      .when('NODE_ENV', {
        is: Joi.string().equal('development'),
        then: Joi.string().default('D:/Projects/Localhost Certs'),
        otherwise: Joi.required()
      }),

    HTTP_PORT: Joi.string()
      .when('NODE_ENV', {
        is: Joi.string().equal('development'),
        then: Joi.string().default(3000),
        otherwise: Joi.required()
      }),

    HTTPS_PORT: Joi.string()
      .when('NODE_ENV', {
        is: Joi.string().equal('development'),
        then: Joi.string().default(4000),
        otherwise: Joi.required()
      }),

    BASE_URL: Joi.string()
      .when('NODE_ENV', {
        is: Joi.string().equal('development'),
        then: Joi.string().default('https://localhost'),
        otherwise: Joi.required()
      }),

    CERT_PASS_PHRASE: Joi.string()
      .when('NODE_ENV', {
        is: Joi.string().equal('development'),
        then: Joi.string().default('localhost'),
        otherwise: Joi.required()
      }),

    MONGO_HOST: Joi.string().required()
      .description('Mongo DB host url'),

    MONGO_DB: Joi.string().required()
      .description('Mongo DB name'),

    MONGO_PORT: Joi.number()
      .default(27017),

    // Default firmwares directory
    ROOT_HEX_FOLDER: Joi.string().required()
      .description('Folder to store the firmware hex files in.'),

    // Default hash function
    DEFAULT_HASH_ALGORITHM: Joi.string().required()
      .default("sha256"),

    SALT_WORK_FACTOR: Joi.number()
      .default(10)
  })
  .unknown()
  .required();

const {
  error,
  value: envVars
} = envVarsSchema.validate(process.env);

if (error) {
  throw new Error(`Config validation error: ${error.message}`);
}

module.exports = {
  env: envVars.NODE_ENV,
  base_url: envVars.NODE_ENV === 'development' ? 'https://localhost:4000' : envVars.BASE_URL,
  http_port: envVars.NODE_ENV === 'development' ? 3000 : envVars.HTTP_PORT,
  https_port: envVars.NODE_ENV === 'development' ? 4000 : envVars.HTTPS_PORT,
  mongo: {
    host: envVars.MONGO_HOST.replace(/\/?$/, ''), // Remove trailing "/" if exists
    db: envVars.MONGO_DB,
    port: envVars.MONGO_PORT
  },
  certficatesPath: envVars.NODE_ENV === 'development' ? '../../Localhost_Certs' : envVars.CERT_PATH,
  certPathPhrase: envVars.NODE_ENV === 'development' ? 'localhost' : envVars.CERT_PASS_PHRASE,
  rootFolder: envVars.ROOT_HEX_FOLDER.replace(/\/?$/, ''),
  saltWorkFactor: envVars.SALT_WORK_FACTOR,
  hashType: envVars.DEFAULT_HASH_ALGORITHM,
  supportedHashes: [
    'DSA',
    'DSA-SHA',
    'DSA-SHA1',
    'DSA-SHA1-old',
    'RSA-MD4',
    'RSA-MD5',
    'RSA-MDC2',
    'RSA-RIPEMD160',
    'RSA-SHA',
    'RSA-SHA1',
    'RSA-SHA1-2',
    'RSA-SHA224',
    'RSA-SHA256',
    'RSA-SHA384',
    'RSA-SHA512',
    'dsaEncryption',
    'dsaWithSHA',
    'dsaWithSHA1',
    'dss1',
    'ecdsa-with-SHA1',
    'md4',
    'md4WithRSAEncryption',
    'md5',
    'md5WithRSAEncryption',
    'mdc2',
    'mdc2WithRSA',
    'ripemd',
    'ripemd160',
    'ripemd160WithRSA',
    'rmd160',
    'sha',
    'sha1',
    'sha1WithRSAEncryption',
    'sha224',
    'sha224WithRSAEncryption',
    'sha256',
    'sha256WithRSAEncryption',
    'sha384',
    'sha384WithRSAEncryption',
    'sha512',
    'sha512WithRSAEncryption',
    'shaWithRSAEncryption',
    'ssl2-md5',
    'ssl3-md5',
    'ssl3-sha1',
    'whirlpool'
  ]
};
