/** 
* @author fangong
* input: OcuInf
* output: camera
*/ 

PANA.PerspCamera = function (side) {
	this.side = side;
	this.camera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 100 );
	this.camera.up = new THREE.Vector3(0,1,0);
	this.camera.lookAt = new THREE.Vector3(0,0,-1);
	var IPD = 0.064; //Interpupillary Distance is generally 54 to 72 mm
	if (side == 'left') {
		this.camera.position.set(-IPD/2,0,0);
	} else {
		this.camera.position.set(IPD/2,0,0);
	}
	
	var camera = this.camera;
	function onWindowResize(){
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
	}
	window.addEventListener( 'resize', onWindowResize, false );
};

PANA.PerspCamera.prototype = {
	contructor: PANA.PerspCamera,
	process: function () {
		if ( !this.OcuInf["OculusInit"]["processed"]["aspect"] ) {
			this.camera.aspect = this.OcuInf["OculusInit"]["aspect"];
			this.camera.updateProjectionMatrix();
			this.OcuInf["OculusInit"]["processed"]["aspect"] = true;
		}
		if ( !this.OcuInf["OculusInit"]["processed"]["FOV"][this.side] ) {
			var LeftTan = this.OcuInf["OculusInit"]["FOV"][this.side][2];
			var RightTan = this.OcuInf["OculusInit"]["FOV"][this.side][3];
			this.camera.fov = (Math.atan(LeftTan)+Math.atan(RightTan))*180/Math.PI;
			this.camera.updateProjectionMatrix();
			this.OcuInf["OculusInit"]["processed"]["FOV"][this.side] = true;
		}
		var q = this.OcuInf["OculusUpdate"]["Orientation"];
		this.camera.quaternion.set( q[0], q[1], q[2], q[3] ); //camera.quaternion is not writable so 'copy' has to be used.
/* 		this.camera.updateMatrix();
		this.camera.updateProjectionMatrix(); */
	}
};