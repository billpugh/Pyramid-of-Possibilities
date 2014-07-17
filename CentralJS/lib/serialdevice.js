require('../lib/globals.js');

var SerialPort = require("serialport").SerialPort;



function SerialDevice(info) {

	var deviceInfo = info;
	var serialPort = new SerialPort(info.port, {
		baudrate: 57600
	}, false);
	var opened = false;

	var open = function() {

		if ( opened ) {
			Logger.warn('already open');
			return;
		}
		serialPort.open(function (error) {
			opened = true;
			if ( error ) {
				Logger.error('Failed to open device'+deviceInfo.port+', Error='+error);
				// TODO: handle error
			}

			serialPort.on('error', function(error) {
				Logger.info('error=',error);
			});

			serialPort.on('data', function(data) {
				Logger.info('Group '+info.group+ " received: " + data);
			});
		});
	};

	var write = function (data) {
		if ( opened ) {
			Logger.info('Writing "'+data+'" to device '+deviceInfo.port);
			serialPort.write(data);
		}
	};

	return {
		open: open,
		write: write
	};
}

// Export this file as a module
module.exports = SerialDevice;
