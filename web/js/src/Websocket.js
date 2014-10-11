/** 
* @author fangong
* input: 
* output: HMD mesh quaternion picture
*/ 

PANA.Websocket = (function () {
	var socket;
	return function(config) {
		var reconnectTimeout 	= null;
		var retryOnDisconnect 	= true;
		var websocketAddress 	= config.hasOwnProperty("address") 			? config["address"] 		: "localhost";
		var websocketPort 		= config.hasOwnProperty("port") 			? config["port"] 			: 9002;
		var retryInterval 		= config.hasOwnProperty("retryInterval") 	? config["retryInterval"] 	: 1;

		// Display metrics, set to defaults from the dev kit hardware
		var displayMetrics = {
			FOV 					: 125.871,

			hScreenSize				: 0.14976,
			vScreenSize				: 0.0935,
			vScreenCenter			: 0.0935 / 2,

			eyeToScreenDistance		: 0.041,

			lensSeparationDistance	: 0.067,
			interpupillaryDistance	: 0.0675,

			hResolution				: 1280,
			vResolution				: 720,
		}
		
		var socketURL = "ws://" + websocketAddress + ":" + websocketPort + "/";

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
		
		var imagePath = {
			path: 'Land_shallow_topo_2048.jpg',
			processed: false
		};
		var mesh = {
			IndexCount: 6,
			ScreenPosNDC: [-1, 1, 1, 1, -1, -1, 1, -1],
			TimeWarpFactor: [1, 1, 1, 1],
			VignetteFactor: [1, 1, 1, 1],
			TanEyeAnglesR: [0, 1, 1, 1, 0, 0, 1, 0],
			TanEyeAnglesG: [0, 1, 1, 1, 0, 0, 1, 0],
			TanEyeAnglesB: [0, 1, 1, 1, 0, 0, 1, 0],
			pIndexData: [0, 1, 2, 2, 1, 3],
			processed: false
		};
		var eyeInfo = {
			right: {
				eyeToSourceUVscale: new THREE.Vector2(1.0,1.0),
				eyeToSourceUVoffset: new THREE.Vector2(0.0,0.0),
				eyeRotationStart: new THREE.Matrix4(),
				eyeRotationEnd: new THREE.Matrix4()
			},
			left: {
				eyeToSourceUVscale: new THREE.Vector2(1.0,1.0),
				eyeToSourceUVoffset: new THREE.Vector2(0.0,0.0),
				eyeRotationStart: new THREE.Matrix4(),
				eyeRotationEnd: new THREE.Matrix4()
			}
		};

		var quaternion = new THREE.Quaternion();
		var mouse	= {x : 0, y : 0}; //closure variable
		document.addEventListener('mousemove', function(event){
			mouse.x	= ((event.clientX / window.innerWidth ) - 0.5 ) * 2;
			mouse.y	= - ((event.clientY / window.innerHeight) - 0.5) * 2;
		}, false);
		this.mouse = mouse;
		
		var config, acceleration; //enclosure variables
		socket.onmessage = function(msg) {
			
			var data = JSON.parse( msg.data );

			var message = data["m"];

			switch(message){
				case "config" :
			/* 		displayMetrics.hScreenSize				= data["screenSize"][0];
					displayMetrics.vScreenSize				= data["screenSize"][1];
					displayMetrics.vScreenCenter			= data["screenSize"][1] / 2;

					displayMetrics.eyeToScreenDistance		= data["eyeToScreen"];

					displayMetrics.lensSeparationDistance	= data["lensDistance"];
					displayMetrics.interpupillaryDistance	= data["interpupillaryDistance"];

					displayMetrics.hResolution				= data["screenResolution"][0];
					displayMetrics.vResolution				= data["screenResolution"][1];

					displayMetrics.distortionK				= [ data["distortion"][0], data["distortion"][1], data["distortion"][2], data["distortion"][3] ];

					displayMetrics.FOV						= data["fov"]; */
					config.name						= data["name"]
				break;

				// For backwards compatability with the bridge application.
				case "orientation":
					if(data["o"] && (data["o"].length == 4)) {
						quaternion.x = Number(data["o"][1]);
						quaternion.y = Number(data["o"][2]);
						quaternion.z = Number(data["o"][3]);
						quaternion.w = Number(data["o"][0]);
					}
				break;

				case "acceleration":
					if(data["a"] && (data["a"].length == 3)) {			
						acceleration.x = Number(data["a"][0]);
						acceleration.y = Number(data["a"][1]);
						acceleration.z = Number(data["a"][2]);
					}
				break;

				case "mesh":
					mesh.ScreenPosNDC = data["ScreenPosNDC"];
					mesh.TimeWarpFactor = data["TimeWarpFactor"];
					mesh.VignetteFactor = data["VignetteFactor"];
					mesh.TanEyeAnglesR = data["TanEyeAnglesR"];
					mesh.TanEyeAnglesG = data["TanEyeAnglesG"];
					mesh.TanEyeAnglesB = data["TanEyeAnglesB"];
					mesh.pIndexData = data["pIndexData"];
					mesh.VertexCount = data["VertexCount"];
					mesh.IndexCount = data["IndexCount"];
				break;

				case "image":
					imagePath.path = data["path"];
				break;
				
				default:
					console.log("PANA.Websocket: unknown message received from server: " + msg.data);
					socket.close();
				break;
			}

		}
		this.config = config;
		this.quaternion = quaternion;
		this.acceleration = acceleration;
		this.mesh = mesh;
		this.imagePath = imagePath;
		this.eyeInfo = eyeInfo;
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
		this.quaternion.setFromEuler(new THREE.Euler(theta2, theta1, 0, 'YXZ')); //intrinsic Euler angles; 'theta2' is for X
	}
};