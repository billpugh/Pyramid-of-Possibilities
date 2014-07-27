require('../lib/globals.js');

var SerialPort = require("serialport").SerialPort;

// in ms
var TIME_PER_WINDOW = 100;

function platformForTimeDifference(diff) {
	return 0;	// todo;
}
function addBytesToBuffer(buffer, data)
{
	return data;		// todo
}


function SerialDevice(info) {

	var deviceInfo = info;
	var serialPort = new SerialPort(info.port, {
		baudrate: 57600
	}, false);
	var opened = false;
	var busy = false;
	var dateOfWrite;
	var messageId = 0;
	var countPlatforms = info.platforms;
	var responses = {};

	var cleanupAfterCloseOrErrorEvent = function() {
		opened = false;
	};

	var clearBuffers = function () {
		responses = {};
	};

	var printBuffers = function () {
		// todo
	};

	var finishedWaiting = function() {
		// todo: what if connection closed while waiting?
		Logger.info('Wait over.');
		busy = false;

		printBuffers();
		clearBuffers();
	};

	var waitForResponses = function() {
		var timeToWait = TIME_PER_WINDOW * (countPlatforms + 1);		// add 1 for central's window
		Logger.info('Wait '+timeToWait+'ms...');
		setTimeout(function() {
			finishedWaiting();
		}, timeToWait);
	};

	var receivedData = function (data) {
		var now = new Date();
		var time_diff = now - dateOfWrite;
		var platformKey = platformForTimeDifference(time_diff) + "";

		// append the data to the platform's buffer. All buffers stored in a hash
		responses[platformKey] = addBytesToBuffer(platforms[platformKey], data);

		// Logger.info('Group '+info.group+ " received " + data);
		Logger.info('Response from Group '+info.group+ ", Platform " + platformKey);
	};

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

			// close & error
			serialPort.on('error', function(error) {
				Logger.info('error=',error);
				cleanupAfterCloseOrErrorEvent();
			});
			serialPort.on('close', function(error) {
				Logger.info('error=',error);
				cleanupAfterCloseOrErrorEvent();
			});

			serialPort.on('data', function(data) {
				receivedData(data);
			});

		});
	};

	var write = function (data) {
		if ( opened && !busy ) {
			
			Logger.info('Writing "'+data+'" to device '+deviceInfo.port);

			busy = true;
			dateOfWrite = new Date();

			serialPort.write(data);

			var drainStart = new Date();
			
			Logger.info('Calling drain...');
			serialPort.drain(function() {		// Now data has "left the pipe"
				timeToDrain = new Date() - drainStart;
				Logger.info('Drain finished ('+timeToDrain+'ms)');
				waitForResponses();
			});

		} // TODO: else can't write because busy or close. if busy.. we drop this command on groound which might not be what we want
	};

	return {
		open: open,
		write: write
	};
}

// Export this file as a module
module.exports = SerialDevice;
