/** 
* @author fangong
* input: 
* output: HMD mesh quaternion picture
*/ 

PANA.Websocket = function(config) {
	var reconnectTimeout 	= null;
	var retryOnDisconnect 	= true;
	var websocketAddress 	= config.hasOwnProperty("address") 			? config["address"] 		: "localhost";
	var websocketPort 		= config.hasOwnProperty("port") 			? config["port"] 			: 9002;
	var retryInterval 		= config.hasOwnProperty("retryInterval") 	? config["retryInterval"] 	: 1;
	var debugEnabled		= config.hasOwnProperty("debug") 			? config["debug"] 			: true;

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

		distortionK				: [1, .22, .24, 0],
		chromaAbParameter		: [0.996, -0.004, 1.014, 0]
	}

	var debug = function(message){
		if(debugEnabled){
			console.log("PANA.Websocket: " + message);
		}
	}
	
	var socketURL = "ws://" + websocketAddress + ":" + websocketPort + "/";
	
	// attempt to open the socket connection
	this.socket = new WebSocket(socketURL); 

	debug("Attempting to connect: " + socketURL);

	// hook up websocket events //
	this.socket.onopen = function(){
		debug("Connected!")
		this.socket.send("Here's some text that the server is urgently awaiting!");
	}

	this.socket.onerror = function(e){
		debug("Socket error.");
	}
	
	this.socket.onmessage = function(msg) {
		
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
				this.config.name						= data["name"]
			break;

			// For backwards compatability with the bridge application.
			case "orientation":
				if(data["o"] && (data["o"].length == 4)) {
					this.quaternion.x = Number(data["o"][1]);
					this.quaternion.y = Number(data["o"][2]);
					this.quaternion.z = Number(data["o"][3]);
					this.quaternion.w = Number(data["o"][0]);
				}
			break;

			case "acceleration":
				if(data["a"] && (data["a"].length == 3)) {			
					this.acceleration.x = Number(data["a"][0]);
					this.acceleration.y = Number(data["a"][1]);
					this.acceleration.z = Number(data["a"][2]);
				}
			break;

			case "mesh":
				this.mesh.ScreenPosNDC = data["ScreenPosNDC"];
				this.mesh.TimeWarpFactor = data["TimeWarpFactor"];
				this.mesh.VignetteFactor = data["VignetteFactor"];
				this.mesh.TanEyeAnglesR = data["TanEyeAnglesR"];
				this.mesh.TanEyeAnglesG = data["TanEyeAnglesG"];
				this.mesh.TanEyeAnglesB = data["TanEyeAnglesB"];
				this.mesh.pIndexData = data["pIndexData"];
				this.mesh.VertexCount = data["VertexCount"];
				this.mesh.IndexCount = data["IndexCount"];
			break;

			case "image":
				this.image.path = data["path"];
			break;
			
			default:
				debug("Unknown message received from server: " + msg.data);
				disconnect();
			break;
		}

	}

	this.socket.onclose = function() {
		this.socket.close();
	}
};

PANA.Websocket.prototype = {
	contructor: PANA.Websocket,
	process: function () {}
};