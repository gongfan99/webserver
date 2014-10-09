//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/async.js",
"js/Detector.js",
"js/three.min.js",
"js/pixastic.custom.js",
"js/src/PANA.js",
"js/src/ImageSource.js",
"js/src/Quaternion.js",
"js/src/PerspCamera.js",
"js/src/Scene1.js",
"js/src/Renderer.js"], function(){
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

	var vec, imagesource, scene1, quaternion, rightcamera, rightrenderer, leftrenderer;
	vec = new THREE.Vector3( 0, 0, -1 );
	var quatValue;
	imagesource = new PANA.ImageSource();
	var checkedimageloaded = function(){
		if (!(imagesource.loaded && imagesource.loaded.status)) {
			setTimeout(checkedimageloaded, 50);
			return;
		};
		async.series([
			function(callback){
				scene1 = new PANA.Scene1();
				quaternion = new PANA.Quaternion();
				rightcamera = new PANA.PerspCamera('right');
				leftcamera = new PANA.PerspCamera('left');
				rightrenderer = new PANA.Renderer('right');
				leftrenderer = rightrenderer.clone('left');
				console.log(imagesource.loaded);
				callback();
			},

			function(callback){
				scene1.loaded = imagesource.loaded;
				scene1.image = imagesource.image;
				rightcamera.quaternion = quaternion.quaternion;
				leftcamera.quaternion = quaternion.quaternion;
				rightrenderer.scene = scene1.scene;
				rightrenderer.camera = rightcamera.camera;
				leftrenderer.scene = scene1.scene;
				leftrenderer.camera = leftcamera.camera;
				callback();
			},
			
			function(callback){		
				requestAnimationFrame(function animate(){
					// keep looping
					requestAnimationFrame( animate );
					quaternion.process();

					name.textContent = 'xy: '+quaternion.mouse.x.toString()+" "+quaternion.mouse.y.toString();
					
					quatValue = rightrenderer.camera.quaternion;
					orientation.textContent = 'wxyz: '+quatValue.w.toString()+" "+quatValue.x.toString()+" "+quatValue.y.toString()+" "+quatValue.z.toString();
					
					vec.set(0, 0, -1);
					vec.applyQuaternion(quatValue);
					qrcode.textContent = 'xyz: '+vec.x.toString()+" "+vec.y.toString()+" "+vec.z.toString();
					
					imagesource.process();
					scene1.process();
					quaternion.process();
					rightcamera.process();
					leftcamera.process();
					rightrenderer.process(true); //'true' means render to screen
					leftrenderer.process(true);
				});
				callback();
			}
		]);
	};
	checkedimageloaded();
});