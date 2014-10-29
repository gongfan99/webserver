//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
requirejs.config({
	paths: {
        "InitValues": "src/InitValues",
        "three": "three.min"
    },
    shim: {
        'InitValues': {
            deps: ['three']
        }
	}
});

require([
"javascripts/src/PANA.js",
"three",
"javascripts/async.js",
"javascripts/Detector.js",
"javascripts/pixastic.custom.js",
"javascripts/stats.min.js",
"javascripts/src/Websocket.js",
"javascripts/src/ImageSource.js",
"javascripts/src/PerspCamera.js",
"javascripts/src/Scene1.js",
"javascripts/src/Renderer.js",
"javascripts/src/PlaneGeometry.js",
"javascripts/src/ShaderMaterial.js",
"javascripts/src/OrthoCamera.js",
"InitValues"], function(){
/* 	var name = document.getElementById("name");
	var orientation = document.getElementById("orientation");
	var qrcode = document.getElementById("qrcode");
	name.textContent = "I am here";
	orientation.textContent = "I am here";
	qrcode.textContent = "reserved for QR code"; */

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

	async.series([
		function(callback){
			websocket = new PANA.Websocket();
			imagesource = new PANA.ImageSource(); //scene1.process will build the scene after the image is loaded.
			scene1 = new PANA.Scene1();
			
			rightcamera = new PANA.PerspCamera("right");
			leftcamera = new PANA.PerspCamera("left");
			
			rightrenderer1 = new PANA.Renderer(false, "right"); //not to render to screen
			leftrenderer1 = new PANA.Renderer(false, "left");

			rightplanegeometry = new PANA.PlaneGeometry("right");
			leftplanegeometry = new PANA.PlaneGeometry("left");

			rightmaterial = new PANA.ShaderMaterial("right");
			leftmaterial = new PANA.ShaderMaterial("left");
			
			scene2 = new THREE.Scene(); //simple so unnecessary to write a wrapper object
			
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
/* 			var array2 = [];
			var startTime2 = 0;
			var vec = new THREE.Vector3( 0, 0, -1 );
			var quatValue; */
			requestAnimationFrame(function animate(){
				// keep looping
				requestAnimationFrame( animate );

/* 				name.textContent = "cost Time: "+websocket.internalUse.costTime.toString()+" ms";
				
				quatValue = websocket.quaternion;
				orientation.textContent = 'wxyz: '+quatValue.w.toString()+" "+quatValue.x.toString()+" "+quatValue.y.toString()+" "+quatValue.z.toString();
				
				vec.set(0, 0, -1);
				vec.applyQuaternion(quatValue);
				qrcode.textContent = 'xyz: '+vec.x.toString()+" "+vec.y.toString()+" "+vec.z.toString();

				array2.push(performance.now() - startTime2);
				if (array2.length === 20){
					console.log(array2);
				} */
	
				imagesource.process();
				scene1.process();
				websocket.process(); //Update Oculus orientation
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
				websocket.send(); //send request to websocket server to get Oculus orientation
/* 				startTime2 = performance.now(); */
			});
			callback();
		}
	]);
});