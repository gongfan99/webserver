//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/OculusBridge.js",
"js/async.js"], function(){
	var bridge = new OculusBridge({
		"onOrientationUpdate" : function(quatValues) {
			giantSquid.quaternion.set(quatValues.x, quatValues.y, quatValues.z, quatValues.w);
		}
	});

	bridge.connect();
})