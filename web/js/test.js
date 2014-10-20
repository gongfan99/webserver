//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/async.js",
"js/Detector.js",
"js/three.js",
"js/pixastic.custom.js",
"js/stats.min.js",
"js/src/PANA.js",
"js/src/InitValues.js",
"js/src/Websocket.js",
"js/src/ImageSource.js",
"js/src/PerspCamera.js",
"js/src/Scene1.js",
"js/src/Renderer.js",
"js/src/PlaneGeometry.js",
"js/src/ShaderMaterial.js",
"js/src/OrthoCamera.js"], function(){
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

	var websocket, imagesource, scene1, quaternion, rightcamera, rightrenderer1, leftrenderer1;
	var rightmaterial, leftmaterial, rightscene, leftscene, renderer2, leftrenderer2;
	var renderer;
	var vec = new THREE.Vector3( 0, 0, -1 );
	var quatValue, startTime;

	async.series([
		function(callback){
			websocket = new PANA.Websocket();
			imagesource = new PANA.ImageSource(); //scene1.process will build the scene after the image is loaded.
			scene1 = new PANA.Scene1();
			
			rightcamera = new PANA.PerspCamera("right");
			leftcamera = new PANA.PerspCamera("left");
			
			rightrenderer1 = new PANA.Renderer(false, "right"); //false means not to render to screen
			leftrenderer1 = new PANA.Renderer(false, "left");

			rightplanegeometry = new PANA.PlaneGeometry("right");
			leftplanegeometry = new PANA.PlaneGeometry("left");

			rightmaterial = new PANA.ShaderMaterial("right");
			leftmaterial = new PANA.ShaderMaterial("left");
			
			scene2 = new THREE.Scene(); //very simple so unnecessary to write a wrapper object
			
			oCamera = new PANA.OrthoCamera();
			
			renderer2 = new PANA.Renderer(true);

			callback();
		},

		function(callback){
			imagesource.OcuInf = websocket.OcuInf;
			
			scene1.status = imagesource.status;
			scene1.image = imagesource.image;
			
			rightcamera.OcuInf = websocket.OcuInf;
			leftcamera.OcuInf = websocket.OcuInf;
			
			rightrenderer1.OcuInf = websocket.OcuInf;
			rightrenderer1.scene = scene1.scene;
			rightrenderer1.camera = rightcamera.camera;
			leftrenderer1.OcuInf = websocket.OcuInf;
			leftrenderer1.scene = scene1.scene;
			leftrenderer1.camera = leftcamera.camera;

			rightplanegeometry.OcuInf = websocket.OcuInf;
			leftplanegeometry.OcuInf = websocket.OcuInf;

			rightmaterial.renderTarget = rightrenderer1.renderTarget;
			leftmaterial.renderTarget = leftrenderer1.renderTarget;
			rightmaterial.OcuInf = websocket.OcuInf;
			leftmaterial.OcuInf = websocket.OcuInf;

			scene2.add(new THREE.Mesh(rightplanegeometry.geometry, rightmaterial.material));
			scene2.add(new THREE.Mesh(leftplanegeometry.geometry, leftmaterial.material));

			renderer2.OcuInf = websocket.OcuInf;
			renderer2.scene = scene2;
			renderer2.camera = oCamera.camera;

			callback();
		},
		
		function(callback){		
			requestAnimationFrame(function animate(){
				// keep looping
				requestAnimationFrame( animate );

				//name.textContent = 'xy: '+websocket.mouse.x.toString()+" "+websocket.mouse.y.toString();
				name.textContent = "cost Time: "+websocket.test.costTime.toString()+" ms";
				
				quatValue = websocket.quaternion;
				orientation.textContent = 'wxyz: '+quatValue.w.toString()+" "+quatValue.x.toString()+" "+quatValue.y.toString()+" "+quatValue.z.toString();
				
				vec.set(0, 0, -1);
				vec.applyQuaternion(quatValue);
				qrcode.textContent = 'xyz: '+vec.x.toString()+" "+vec.y.toString()+" "+vec.z.toString();

				websocket.process();
				imagesource.process();
				scene1.process();
				rightcamera.process();
				leftcamera.process();



				rightrenderer1.process();
				leftrenderer1.process();
				rightplanegeometry.process();
				leftplanegeometry.process();
				rightmaterial.process();
				leftmaterial.process();
				oCamera.process(); //empty process
				renderer2.process();
				stats.update();
				websocket.send();
			});
			callback();
		}
	]);
});