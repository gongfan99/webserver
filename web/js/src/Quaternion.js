/** 
* @author fangong 
* input: OculusBridge
* output: quaternion
*/ 

PANA.Quaternion = function () {
	this.quaternion = new THREE.Quaternion();
	//this.quaternion.set( 0, 0, 0, 1 ); //xyzw
	
	var mouse	= {x : 0, y : 0}; //closure variable
	document.addEventListener('mousemove', function(event){
		mouse.x	= (event.clientX / window.innerWidth ) - 0.5;
		mouse.y	= -((event.clientY / window.innerHeight) - 0.5);
		//console.log(mouse.x, mouse.y);
	}, false);

	this.u = new THREE.Vector3( 0, 0, 1 );
	this.v = new THREE.Vector3();
	this.axis = new THREE.Vector3();
	this.mouse = mouse;
};

PANA.Quaternion.prototype = {
	contructor: PANA.Quaternion,
	process: function () {
		var x = this.mouse.x;
		var y = this.mouse.y;
		this.v.set( x, y, Math.sqrt(0.25-x*x-y*y) );
		this.axis.crossVectors( this.u, this.v );
		this.axis.normalize();
		var cosTheta = this.u.dot(this.v)/(this.u.length() * this.v.length());
		var cosHalfTheta = Math.sqrt(( 1 + cosTheta ) / 2);
		var sinHalfTheta = Math.sqrt(( 1 - cosTheta ) / 2);
		this.quaternion.set( this.axis.x * sinHalfTheta, this.axis.y * sinHalfTheta, this.axis.z * sinHalfTheta, cosHalfTheta ); //xyzw
	}
};