require('../lib/globals.js');

var SerialDevice = require('../lib/serialdevice.js');
var SerialPortModule = require("serialport");


function createDevices(devices) {
	var newDevices = [];
	_.each(devices, function(deviceInfo) {
		Logger.info('Making device'+deviceInfo.port);
		var newDevice = SerialDevice(deviceInfo);
		newDevices.push(newDevice);
	});
	return newDevices;
}

function SerialManager() {

	var devices;
	var metaDevices;

	var openAll = function () {
		_.each(devices, function(device) {
			device.open();
		});
	};
	var listPorts = function () {
		SerialPortModule.list(function (err, ports) {
			ports.forEach(function(port) {
				Logger.info(port.comName + ' / '+ port.pnpId + ' / '+ port.manufacturer);
			});
		});
	};
	var sendCommandToPlatform = function (group, platform, command) {
		device = devices[group];
		if ( !device ) {
			Logger.error('no device to send command');
			return;
		}
		device.write("I command platform#"+platform+" to: "+command);
	};

	return {
		run: function() {
			devices = createDevices(metaDevices);
			Logger.info('serial manager running');
			openAll();
		},
		setDevices: function(deviceMetaArray) {
			metaDevices = deviceMetaArray;
		},
		listPorts: listPorts,
		sendCommandToPlatform : sendCommandToPlatform
	};
}

// Export this file as a module
module.exports = new SerialManager();