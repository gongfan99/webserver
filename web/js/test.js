//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/OculusBridge.js",
"js/async.js",
"js/three.min.js",
"js/src/PANA.js",
"js/src/Quaternion.js"], function(){
	var name = document.getElementById("name");
	var orientation = document.getElementById("orientation");
	var qrcode = document.getElementById("qrcode");
	name.textContent = "I am here";
	orientation.textContent = "I am here";
	qrcode.textContent = "reserved for QR code";

/* 	window.onbeforeunload = function () {
		bridge.disconnect();
		return "Do you really want to close?";
	};

	var bridge = new OculusBridge({
		"onConfigUpdate" : function(displayMetrics) {
			//giantSquid.quaternion.set(quatValues.x, quatValues.y, quatValues.z, quatValues.w);
			name.textContent = displayMetrics.name;
		},
		"onOrientationUpdate" : function(quatValues) {
			//giantSquid.quaternion.set(quatValues.x, quatValues.y, quatValues.z, quatValues.w);
			orientation.textContent = quatValues.w.toString()+" "+quatValues.x.toString()+" "+quatValues.y.toString()+" "+quatValues.z.toString();
		}
	});

	bridge.connect(); */
	
	var quaternion = new PANA.Quaternion();
	requestAnimationFrame(function animate(){
		// keep looping
		requestAnimationFrame( animate );
		quaternion.process();

		name.textContent = 'xy: '+quaternion.mouse.x.toString()+" "+quaternion.mouse.y.toString();

		orientation.textContent = 'wxyz: '+quaternion.quaternion.w.toString()+" "+quaternion.quaternion.x.toString()+" "+quaternion.quaternion.y.toString()+" "+quaternion.quaternion.z.toString();
	});

});