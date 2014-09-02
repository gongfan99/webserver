//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/OculusBridge.js",
"js/async.js"], function(){
	var div = document.getElementById("textDiv");
	div.textContent = "I am here";

	window.onbeforeunload = function () {
		bridge.disconnect();
		return "Do you really want to close?";
	};

	var bridge = new OculusBridge({
		"onOrientationUpdate" : function(quatValues) {
			//giantSquid.quaternion.set(quatValues.x, quatValues.y, quatValues.z, quatValues.w);
			div.textContent = quatValues.w.toString()+" "+quatValues.x.toString()+" "+quatValues.y.toString()+" "+quatValues.z.toString();
		}
	});

	bridge.connect();
})