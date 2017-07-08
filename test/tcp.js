var net = require('net');

var HOST = '127.0.0.1';
var PORT = 11111;
var cnt = 1;


var client = new net.Socket();
client.connect(PORT, HOST, function() {
    console.log('CONNECTED TO: ' + HOST + ':' + PORT);
    client.write('I am wayne, from NodeJS !');
});

client.on('data', function(data) {
    console.log('DATA: ' + data);
});

client.on('error', function() {
    console.log('error: ' );
    client.destroy();
});

client.on('close', function() {
    console.log('Connection closed');
});

function intervalFunc() {
	data={"url":"","desc":""};
	tmp = ("0" + cnt++).slice(-2);
	data["url"]="http://www.stevenround-birdphotography.com/source/image/puffin-"
		+ tmp +".jpg";
	data["desc"] = "from node js"+tmp 
	client.write(JSON.stringify(data));
	console.log('send data: '+JSON.stringify(data));
}

setInterval(intervalFunc, 2000);
