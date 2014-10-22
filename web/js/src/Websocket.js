/** 
* @author fangong
* input: 
* output: OcuInf
*/ 

PANA.Websocket = function() {
	this.OcuInf = {};
	if ( "PANAOculusInit" in sessionStorage ) {
		this.OcuInf["OculusInit"] = JSON.parse(sessionStorage.getItem("PANAOculusInit"));
		console.log("PANA.Websocket: PANAOculusInit found in Local Storage.");
	}

	var socketURL = "ws://localhost:9002/";
	console.log("PANA.Websocket: attempting to connect " + socketURL);
	var socket = new WebSocket(socketURL);
	this.socket = socket;

	// hook up websocket events //
	socket.onopen = function(){
		console.log("PANA.Websocket: connected!");
		if ( !("PANAOculusInit" in sessionStorage) ) {
			socket.send("OculusInit");
		}
	}

	socket.onclose = function() {
		console.log("PANA.Websocket: disconnected.");
	}

	socket.onerror = function(e){
		console.log("PANA.Websocket: socket error.");
	}

	this.internalUse = {rcvArray: [], socketTime: [], startTime: 0, costTime: 0, sendNumber: 0};
	socket.onmessage = (function(OcuInf, internalUse) {
		return function(msg) {
			var data = JSON.parse( msg.data );
			for ( key in data ) {
				if ( key === "OculusInit" ) {
					OcuInf[key] = data[key];
					sessionStorage.setItem("PANAOculusInit", JSON.stringify(data[key]));
					console.log("PANA.Websocket: PANAOculusInit saved to Local Storage.");
				} else if ( key === "OculusUpdate" ) {					
					internalUse.rcvArray[data[key]["sendNumber"]] = data[key];
				} else {
					OcuInf[key] = data[key];
				}
			}
		}
	})(this.OcuInf, this.internalUse);

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
		//this.OcuInf["OculusUpdate"]["Orientation"] = [q.x, q.y, q.z, q.w];
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