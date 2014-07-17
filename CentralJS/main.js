require('./lib/globals.js');
var express = require('express');
var app = express();
var SerialManager = require('./lib/serialmanager.js');



////////////////////////////////////
// Serial Port Manager
////////////////////////////////////

/**
The SerialManager manages the serial ports.
*/

SerialManager.listPorts();		// Show list of ports for debug sake.

// Tell the manager how many USB devices it is managing, the number of platforms per group, and the group id.
SerialManager.setDevices([
	{
		"group":0,
		"platforms":1,
		"port": "/dev/tty.usbserial-A603IU64"
	},
	{
		"group":1,
		"platforms":1,
		"port": "/dev/tty.usbmodem33311"
	}
]);

// Start running the serial monitor on all USB ports.
SerialManager.run();


////////////////////////////////////
// HTTP API Manager
////////////////////////////////////

/*
 This represents our HTTP server and API. 
 Each endpoint is designated by it's path (for example /test) and it's RESTful method (GET, POST, etc).
 On your local machine, you could use a web browser to visit localhost:3003/test and it would send
 a command to group 0, platform 0.
 A web app can be built using this API in pure HTML, CSS and client-side Javascript.
 */

app.get('/test', function(req, res) {
    Logger.info('responding to test...');
    SerialManager.sendCommandToPlatform(0,0,"Turn it up!");
    res.send({ok: 'ok'});
});
var port = 3003;
app.listen(port);
Logger.info('HTTP Server Listening on port '+port+'...');
