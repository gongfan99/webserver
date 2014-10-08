/** 
* @author fangong
* input: quaternion
* output: camera
*/ 

PANA.PerspCamera = function (side) {
	this.camera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	this.camera.up = new THREE.Vector3(0,1,0);
	this.camera.lookAt = new THREE.Vector3(0,0,-1);
	if (side == 'left') {
		this.camera.position.set(-0.5,0,0);
	} else {
		this.camera.position.set(0.5,0,0);
	}
};

PANA.PerspCamera.prototype = {
	contructor: PANA.PerspCamera,
	process: function () {
		this.camera.quaternion = this.quaternion;
		this.camera.updateMatrix();
	}
};