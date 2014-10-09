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
	this.mouse = mouse;
};

PANA.Quaternion.prototype = {
	contructor: PANA.Quaternion,
	process: function () {
		var x = this.mouse.x;
		var y = this.mouse.y;
		var z = -Math.sqrt(0.25-x*x-y*y);
		var theta1 = Math.atan(x/z);
		var theta2 = Math.asin(y);
		//this.quaternion.setFromEuler(new THREE.Euler(theta2, theta1, 0, 'XYZ')); //intrinsic Euler angles
		this.quaternion.setFromEuler(new THREE.Euler(theta2, theta1, 0, 'YXZ')); //intrinsic Euler angles
	}
};