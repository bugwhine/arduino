var keypress = require('keypress');
var btSerial = new (require('bluetooth-serial-port')).BluetoothSerialPort();

btSerial.on('found', function(address, name) {
	console.log("found " + name + " @ " + address);
	btSerial.findSerialPortChannel(address, function(channel) {
		console.log('Serial port on channel '+channel);
		btSerial.connect(address, channel, function() {
			console.log('connected');

			btSerial.write(new Buffer('my data', 'utf-8'), function(err, bytesWritten) {
				if (err) console.log(err);
			});

		}, function () {
			console.log('cannot connect');
		});

		// close the connection when you're ready
		btSerial.close();
	}, function() {
		console.log('found nothing');
	});
});

btSerial.on('failure', function(err) {
	console.log(err.toString());
});

btSerial.on('data', function(buffer) {
	console.log('Received: Size of data buf = ' + buffer.length);
	console.log(buffer.toString('utf-8'));
});

// make `process.stdin` begin emitting "keypress" events
keypress(process.stdin);

// listen for the "keypress" event
process.stdin.on('keypress', function (ch, key) {
//  console.log('got "keypress"', key);
  if (key) {
		switch (key.name) {
			case 'q' :
				console.log("closing btSerial");
				btSerial.close();
				process.stdin.setRawMode(false);
				console.log("exit");
				process.exit();
				break;
			case 'up' :
				btSerial.write(new Buffer("u1", 'utf-8'), function(err, bytesWritten) {
					console.log("u1");
					if (err) console.log(err);
				});
				break;
			case 'down' :
				btSerial.write(new Buffer("d1", 'utf-8'), function(err, bytesWritten) {
					console.log("d1");
					if (err) console.log(err);
				});
				break;
			case 'left' :
				btSerial.write(new Buffer("l1", 'utf-8'), function(err, bytesWritten) {
					console.log("l1");
					if (err) console.log(err);
				});
				break;
			case 'right' :
				btSerial.write(new Buffer("r1", 'utf-8'), function(err, bytesWritten) {
					console.log("r1");
					if (err) console.log(err);
				});
				break;
		}
	}
});

console.log('inquire');
btSerial.inquire();
process.stdin.setRawMode(true);
process.stdin.resume();
