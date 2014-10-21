/** 
* @author fangong
* input: 
* output: OcuInf
*/ 

PANA.Websocket = function() {
	var socketURL = "ws://localhost:9002/";

	console.log("PANA.Websocket: attempting to connect " + socketURL);
	// attempt to open the socket connection
	var socket = new WebSocket(socketURL);
	this.socket = socket;

	// hook up websocket events //
	socket.onopen = function(){
		console.log("PANA.Websocket: connected!")
	}

	socket.onclose = function() {
		console.log("PANA.Websocket: disconnected.");
	}

	socket.onerror = function(e){
		console.log("PANA.Websocket: socket error.");
	}

	this.OcuInf = PANA.InitValues.OcuInf;
	this.internalUse = {rcvArray: [], socketTime: [], startTime: 0, costTime: 0, sendNumber: 0};
	socket.onmessage = (function(OcuInf, internalUse) {
		return function(msg) {
			var data = JSON.parse( msg.data );
			for ( key in data ) {
				if ( key !== "OculusUpdate" ) {
					OcuInf[key] = data[key];
				} else  {
					internalUse.rcvArray[data[key]["sendNumber"]] = data[key];
				}
			}
		}
	})(this.OcuInf, this.internalUse);

/* 		this.mouse = {x : 0, y : 0};
	document.addEventListener('mousemove', (function(mouse){
		return function(event){
			mouse.x	= ((event.clientX / window.innerWidth ) - 0.5 ) * 2;
			mouse.y	= - ((event.clientY / window.innerHeight) - 0.5) * 2;
		}
	})(this.mouse),	false);
	this.quaternion = new THREE.Quaternion(); */
};

PANA.Websocket.prototype = {
	contructor: PANA.Websocket,
	send: (function () { //send request to websocket server to get Oculus orientation
		//var sendTimes = 0;
		return function () {
			if (this.socket.readyState === 1) {
				this.internalUse.rcvArray[this.internalUse.sendNumber] = undefined;
				this.socket.send(this.internalUse.sendNumber.toString());
			}
		};
	})(),
	process: function () {
/* 		var x = this.mouse.x;
		var y = this.mouse.y;
		var t = Math.sqrt( x * x + y * y );
		if ( t > 0.99 ) { //scale x, y below unit circle
			x = x * 0.99 / t;
			y = y * 0.99 / t;
		}
		var z = -Math.sqrt(1-x*x-y*y);
		var theta1 = Math.atan(x/z);
		var theta2 = Math.asin(y);
		var q = this.quaternion;
		q.setFromEuler(new THREE.Euler(theta2, theta1, 0, 'YXZ')); //intrinsic Euler angles; 'theta2' is for X
		this.OcuInf["OculusUpdate"]["Orientation"] = [q.x, q.y, q.z, q.w]; */
		for (var i = 0; i < 20; i++) { //check if the Oculus orientation is received
			if (this.internalUse.rcvArray[this.internalUse.sendNumber - i] !== undefined) {
				this.OcuInf["OculusUpdate"] = this.internalUse.rcvArray[(this.internalUse.sendNumber-i+20)%20];
				if ( i !== 0 ) {
					console.log("No. " + this.internalUse.sendNumber.toString() + " is needed but we only received up to No." + ((this.internalUse.sendNumber-i+20)%20).toString() + ".");
				}
				break;
			}
		}
		this.internalUse.sendNumber++;
		this.internalUse.sendNumber %= 20;
	}
};