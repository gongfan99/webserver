/** 
* @author fangong
* input: 
* output: camera
*/ 

PANA.OrthoCamera = function () {
	this.camera = new THREE.OrthographicCamera( -1, 1, 1, -1, 0.1, 1000 );
	this.camera.position.z = 1;
	this.camera.up = new THREE.Vector3(0,1,0);
	this.camera.lookAt = new THREE.Vector3(0,0,-1);
};

PANA.OrthoCamera.prototype = {
	contructor: PANA.OrthoCamera,
	process: function () {}
};