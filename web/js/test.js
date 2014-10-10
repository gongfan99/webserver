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
	var rightmaterial, leftmaterial, rightscene, leftscene, rightrenderer2, leftrenderer2;
	var renderer;
	var vec = new THREE.Vector3( 0, 0, -1 );
	var quatValue;

	async.series([
		function(callback){
			websocket = new PANA.Websocket({});
			imagesource = new PANA.ImageSource(); //scene1.process will build the scene after the image is loaded.
			scene1 = new PANA.Scene1();
			
			rightcamera = new PANA.PerspCamera('right');
			leftcamera = new PANA.PerspCamera('left');
			
			//rightrenderer1 = new PANA.Renderer('right', false);
			//leftrenderer1 = new PANA.Renderer('left', false);

			planegeometry = new PANA.PlaneGeometry();

			rightmaterial = new PANA.ShaderMaterial();
			leftmaterial = new PANA.ShaderMaterial();
			
			rightscene = new THREE.Scene();
			leftscene = new THREE.Scene(); //very simple so unnecessary to write a wrapper object
			
			oCamera = new PANA.OrthoCamera();
			
			//rightrenderer2 = new PANA.Renderer('right', true);
			//leftrenderer2 = new PANA.Renderer('left', true);
			console.log(imagesource.status);
			callback();
		},

		function(callback){
			imagesource.imagePath = websocket.imagePath;
			
			scene1.status = imagesource.status;
			scene1.image = imagesource.image;
			
			rightcamera.quaternion = websocket.quaternion;
			leftcamera.quaternion = websocket.quaternion;
			
/* 			rightrenderer1.scene = scene1.scene;
			rightrenderer1.camera = rightcamera.camera;
			leftrenderer1.scene = scene1.scene;
			leftrenderer1.camera = leftcamera.camera; */
			
			planegeometry.mesh = websocket.mesh;

			rightmaterial.renderTarget = THREE.ImageUtils.loadTexture('Land_shallow_topo_2048.jpg');//rightrenderer1.renderTarget;
			leftmaterial.renderTarget = rightmaterial.renderTarget;//leftrenderer1.renderTarget;
			rightmaterial.eyeInfo = websocket.eyeInfo.right;
			leftmaterial.eyeInfo = websocket.eyeInfo.left;

			rightscene.add(new THREE.Mesh(planegeometry.geometry, 
			//new THREE.MeshBasicMaterial( {color: 0xffff00, side: THREE.DoubleSide} )
			new THREE.ShaderMaterial( {	
				vertexShader: 'void main() {\n\tgl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );\n}',
				fragmentShader: 'void main() {\n\tgl_FragColor = vec4( 1.0, 0.0, 0.0, 1.0 );\n}',
				side: THREE.DoubleSide } )
			));
			renderer = new THREE.WebGLRenderer({ antialias:true, alpha: true });
			renderer.setSize( window.innerWidth/10, window.innerHeight/10 );
			document.body.appendChild( renderer.domElement );
			//leftscene.add(new THREE.Mesh(planegeometry.geometry, leftmaterial.material));
			
/* 			rightrenderer2.scene = rightscene;
			rightrenderer2.camera = oCamera.camera; */
			//leftrenderer2.scene = rightscene; //set to rightscene to avoid a bug
			//leftrenderer2.camera = oCamera.camera;
			callback();
		},
		
		function(callback){		
			requestAnimationFrame(function animate(){
				// keep looping
				requestAnimationFrame( animate );

				name.textContent = 'xy: '+websocket.mouse.x.toString()+" "+websocket.mouse.y.toString();
				
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
/* 				rightrenderer1.process();
				leftrenderer1.process(); */
				planegeometry.process();
				rightmaterial.process();
				leftmaterial.process();
				oCamera.process(); //empty process
				//rightrenderer2.process();
				//leftrenderer2.process();
				renderer.render( rightscene, oCamera.camera );
				stats.update();
			});
			callback();
		}
	]);
});