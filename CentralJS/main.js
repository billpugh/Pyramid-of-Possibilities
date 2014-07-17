require('./lib/globals.js');
var express = require('express');
var app = express();
var SerialManager = require('./lib/serialmanager.js');



// Serial Port Manager

SerialManager.listPorts();		// Show list of ports for debug sake.
SerialManager.setDevices([
	{
		"group":1,
		"platforms":1,
		"port": "/dev/tty.usbserial-A603IU64"
	}
]);
SerialManager.run();



// HTTP API Manager

app.get('/test', function(req, res) {
    Logger.info('responding to test...');
    SerialManager.sendCommandToPlatform(0,0,"Turn it up!");
    res.send({ok: 'ok'});
});
var port = 3003;
app.listen(port);
Logger.info('HTTP Server Listening on port '+port+'...');
