/** 
* @author fangong 
* input: OculusBridge
* output: quaternion
*/ 

PANA.Quaternion = function () {
	this.quaternion = new THREE.Quaternion();
	
	var mouse	= {x : 0, y : 0}; //closure variable
	document.addEventListener('mousemove', function(event){
		mouse.x	= ((event.clientX / window.innerWidth ) - 0.5 ) * 2;
		mouse.y	= - ((event.clientY / window.innerHeight) - 0.5) * 2;
	}, false);
	this.mouse = mouse;
};

PANA.Quaternion.prototype = {
	contructor: PANA.Quaternion,
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