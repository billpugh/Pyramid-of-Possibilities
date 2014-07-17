var Winston = require('winston');
require('../lib/globals.js');

/*************
* Map our logger levels to the real logger.
* @note this lets us switch loggers w/o changing our source code
*/

/****************
* Global Vars
****************/

// var FORCE_DEBUG = false;

/****************
* Config!
****************/

var config = {
  levels: {
    debug: 0,
    info: 1,
    warn: 2,
    alert: 3,
    error: 4
  },
  colors: {
    debug: 'grey',
    info: 'green',
    warn: 'yellow',
    alert: 'cyan',
    error: 'red'
  }
};

// set minimum logging level by OS type
// Mac OSX gets debug (probably local),
var minimumLevel =  'debug';

module.exports = new (Winston.Logger)({
  transports: [
    new (Winston.transports.Console)({
      level: minimumLevel,
      colorize: true,
      timestamp: true
    })
  ],
  levels: config.levels,
  colors: config.colors
});

module.exports.FileLogger = new (Winston.Logger)({
  transports: [
    new (Winston.transports.Console)({
      level: minimumLevel,
      colorize: true,
      timestamp: true
    }),
    new (Winston.transports.File)({
      filename: 'bots.log',
      level: minimumLevel,
      colorize: true,
      timestamp: true
    })
  ],
  levels: config.levels,
  colors: config.colors
});