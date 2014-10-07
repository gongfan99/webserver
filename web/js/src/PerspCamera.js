/** 
* @author fangong
* input: 
* output: camera
*/ 

PANA.PerspCamera = function () {
	this.camera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	this.camera.up = new THREE.Vector3(0,1,0);
};

PANA.PerspCamera.prototype = {
	contructor: PANA.PerspCamera,
	process: function () {}
};