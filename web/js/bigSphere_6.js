//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/three.min.js",
"js/async.js",
"js/Detector.js",
"js/pixastic.custom.js",
"js/OculusRiftEffect_2.js",
"js/postprocessing/EffectComposer.js",
"js/postprocessing/RenderPass.js",
"js/postprocessing/ShaderPass.js",
"js/postprocessing/MaskPass.js",
"js/shaders/CopyShader.js"], function(){
	var renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.autoClear = false;
	document.body.appendChild( renderer.domElement );
	var camera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	var scene	= new THREE.Scene();
	var mesh = [];
	var onRenderFcts= [];

	var oOculusRift = new THREE.OculusRiftEffect( renderer );
		
	//////////////////////////////////////////////////////////////////////////////////
	//		add star field							//
	//////////////////////////////////////////////////////////////////////////////////
	var iImageLoaded = 0;
	var iNumberPhi = 4;
	var iNumberThe = 2;
	var img = new Image();

	img.onload = function() {
		async.series([ 
			function(callback){
				for (var i = 0; i < iNumberPhi; i++) {
					for (var j = 0; j < iNumberThe; j++){
						Pixastic.process(img, "crop", 
							{
								rect : {
									left : i*img.width/iNumberPhi,
									top : j*img.height/iNumberThe,
									width : img.width/iNumberPhi,
									height : img.height/iNumberThe-j-1
								}
							},
							function(newImage) {
								// newImage is the new canvas/image element
								var geometry  = new THREE.SphereGeometry(100, 64, 48, i*Math.PI*2/iNumberPhi, Math.PI*2/iNumberPhi, j*Math.PI/iNumberThe, Math.PI/iNumberThe);
								var material  = new THREE.MeshBasicMaterial({
									side: THREE.FrontSide,
									map: THREE.ImageUtils.loadTexture(newImage.toDataURL(), new THREE.UVMapping(), function(){iImageLoaded++;})
								})
								mesh.push(new THREE.Mesh(geometry, material));
							}
						);
					}
				}
				mesh.forEach(function(oEachMesh){
					oEachMesh.scale.x = -1;
					oEachMesh.scale.y = 1;
					oEachMesh.scale.z = 1;
					scene.add(oEachMesh)
				})
				callback();},
			function(callback){
				oOculusRift.setHMD( scene, camera );
				callback();},
			function(callback){
				//////////////////////////////////////////////////////////////////////////////////
				//		Camera Controls							//
				//////////////////////////////////////////////////////////////////////////////////
				var mouse	= {x : 0, y : 0}
				document.addEventListener('mousemove', function(event){
					mouse.x	= (event.clientX / window.innerWidth ) - 0.5
					mouse.y	= (event.clientY / window.innerHeight) - 0.5
				}, false)
				onRenderFcts.push(function(delta, now){
					//camera.lookAt(new THREE.Vector3(mouse.x,-mouse.y,-1))
					mesh.forEach(function(oEachMesh){
						oEachMesh.rotation.y += .002*mouse.x;
						oEachMesh.rotation.x += .002*mouse.y;
					})
				})
				callback();
			},
			function(callback){ 
				//////////////////////////////////////////////////////////////////////////////////
				//		render the scene						//
				//////////////////////////////////////////////////////////////////////////////////
				onRenderFcts.push(function(){
					oOculusRift.render();
				})
				//////////////////////////////////////////////////////////////////////////////////
				//		Windows Resize							//
				//////////////////////////////////////////////////////////////////////////////////
/* 				window.addEventListener( 'resize', function(event){
					oLeftCamera.aspect = window.innerWidth / (2*window.innerHeight);
					oLeftCamera.updateProjectionMatrix();
					oRightCamera.aspect = window.innerWidth / (2*window.innerHeight);
					oRightCamera.updateProjectionMatrix();
					oLeftComposer.renderer.setViewport( 0, 0, window.innerWidth/2, window.innerHeight );
					oRightComposer.renderer.setViewport( window.innerWidth/2, 0, window.innerWidth/2, window.innerHeight );
				}, false ); */
				
				//////////////////////////////////////////////////////////////////////////////////
				//		loop runner							//
				//////////////////////////////////////////////////////////////////////////////////
				var lastTimeMsec= null
				requestAnimationFrame(function animate(nowMsec){
					// keep looping
					requestAnimationFrame( animate );
					// measure time
					lastTimeMsec	= lastTimeMsec || nowMsec-1000/60
					var deltaMsec	= Math.min(200, nowMsec - lastTimeMsec)
					lastTimeMsec	= nowMsec
			/* 		if (iImageLoaded == iNumberPhi*iNumberThe) {
						alert(img.width);
						iImageLoaded = 0;
					} */
					// call each update function
					onRenderFcts.forEach(function(onRenderFct){
						onRenderFct(deltaMsec/1000, nowMsec/1000)
					})
				})
				callback();
			}
		]);
	}
	//document.body.appendChild(img);
	img.src = "Land_shallow_topo_alpha_2048.png";//"Big_ben_equirectangular.jpg";"14087020332_1221918a9e_o.jpg""Land_shallow_topo_alpha_2048.png"

})