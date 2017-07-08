var nano = require('nanomsg');


// var rep = nano.socket('rep');
var pair = nano.socket('pair');

var addr = 'tcp://127.0.0.1:11111';
var cnt = 1;

pair.connect(addr);

pair.on('data', function (buf) {
  console.log('received response: ', buf.toString());
  // req.close();
});

function intervalFunc() {
	data={"url":"","desc":""};
	tmp = ("0" + cnt++).slice(-2);
	data["url"]="http://www.stevenround-birdphotography.com/source/image/puffin-"
		+ tmp +".jpg";
	data["desc"] = "from node js"+tmp 
	pair.send(JSON.stringify(data));

	console.log('send data: '+JSON.stringify(data));
}

setInterval(intervalFunc, 2000);
