//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/async.js",
"js/Detector.js",
"js/three.min.js",
"js/pixastic.custom.js",
"js/stats.min.js",
"js/src/PANA.js",
"js/src/Websocket.js",
"js/src/ImageSource.js",
"js/src/Quaternion.js",
"js/src/PerspCamera.js",
"js/src/Scene1.js",
"js/src/Renderer.js",
"js/src/PlaneGeometry.js"], function(){
	var name = document.getElementById("name");
	var orientation = document.getElementById("orientation");
	var qrcode = document.getElementById("qrcode");
	name.textContent = "I am here";
	orientation.textContent = "I am here";
	qrcode.textContent = "reserved for QR code";

/* 	window.onbeforeunload = function () {
		return "Do you really want to close?";
	}; */

	var stats = new Stats();
	stats.domElement.style.position = 'absolute';
	stats.domElement.style.top = '0px';
	stats.domElement.style.left = window.innerWidth*3/4 + 'px';
	document.body.appendChild( stats.domElement );

	var websocket, imagesource, scene1, quaternion, rightcamera, rightrenderer, leftrenderer;
	var vec = new THREE.Vector3( 0, 0, -1 );
	var quatValue;
	//imagesource = new PANA.ImageSource();
	async.series([
		function(callback){
			websocket = new PANA.Websocket({});
			imagesource = new PANA.ImageSource(); //scene1.process will build the scene after the image is loaded.
			scene1 = new PANA.Scene1();
			quaternion = new PANA.Quaternion();
			rightcamera = new PANA.PerspCamera('right');
			leftcamera = new PANA.PerspCamera('left');
			rightrenderer = new PANA.Renderer('right', true);
			leftrenderer = new PANA.Renderer('left', true);
			planegeometry = new PANA.PlaneGeometry();
			console.log(imagesource.status);
			callback();
		},

		function(callback){
			imagesource.imagePath = websocket.imagePath;
			scene1.status = imagesource.status;
			scene1.image = imagesource.image;
			rightcamera.quaternion = quaternion.quaternion;
			leftcamera.quaternion = quaternion.quaternion;
			rightrenderer.scene = scene1.scene;
			rightrenderer.camera = rightcamera.camera;
			leftrenderer.scene = scene1.scene;
			leftrenderer.camera = leftcamera.camera;
			planegeometry.mesh = websocket.mesh;
			callback();
		},
		
		function(callback){		
			requestAnimationFrame(function animate(){
				// keep looping
				requestAnimationFrame( animate );
				quaternion.process();

				name.textContent = 'xy: '+quaternion.mouse.x.toString()+" "+quaternion.mouse.y.toString();
				
				quatValue = leftrenderer.camera.quaternion;
				orientation.textContent = 'wxyz: '+quatValue.w.toString()+" "+quatValue.x.toString()+" "+quatValue.y.toString()+" "+quatValue.z.toString();
				
				vec.set(0, 0, -1);
				vec.applyQuaternion(quatValue);
				qrcode.textContent = 'xyz: '+vec.x.toString()+" "+vec.y.toString()+" "+vec.z.toString();
				
				imagesource.process();
				scene1.process();
				quaternion.process();
				rightcamera.process();
				leftcamera.process();
				rightrenderer.process(); //'true' means render to screen
				leftrenderer.process();
				planegeometry.process();
				stats.update();
			});
			callback();
		}
	]);
});