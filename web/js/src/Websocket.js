/** 
* @author fangong
* input: 
* output: HMD mesh quaternion picture
*/ 

PANA.Websocket = (function () {
	var socket;
	return function() {
		var socketURL = "ws://localhost:9002/";

		console.log("PANA.Websocket: attempting to connect " + socketURL);
		// attempt to open the socket connection
		socket = new WebSocket(socketURL);

		// hook up websocket events //
		socket.onopen = function(){
			console.log("PANA.Websocket: connected!")
			socket.send("Here's some text that the server is urgently awaiting!");
		}

		socket.onclose = function() {
			//socket.close();
			console.log("PANA.Websocket: close.");
/* 			window.setTimeout( function(){
				socket = new WebSocket(socketURL);
				console.log("PANA.Websocket: attempting to connect " + socketURL);
			}, 2000 ); */
		}

		socket.onerror = function(e){
			console.log("PANA.Websocket: socket error.");
		}

		this.OcuInf = PANA.InitValues.OcuInf;
		socket.onmessage = (function(OcuInf) {
			return function(msg) {
				var data = JSON.parse( msg.data );
				for ( key in data ) {
					OcuInf[key] = data[key];
				}
			}
		})(this.OcuInf);

		this.mouse = {x : 0, y : 0};
		document.addEventListener('mousemove', (function(mouse){
			return function(event){
				mouse.x	= ((event.clientX / window.innerWidth ) - 0.5 ) * 2;
				mouse.y	= - ((event.clientY / window.innerHeight) - 0.5) * 2;
			}
		})(this.mouse),	false);
		this.quaternion = new THREE.Quaternion();
	}
})();

PANA.Websocket.prototype = {
	contructor: PANA.Websocket,
	process: function () {
		var x = this.mouse.x;
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
		this.OcuInf["OculusUpdate"]["Orientation"] = [q.x, q.y, q.z, q.w];
	}
};