//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/three.min.js",
"js/async.js",
"js/Detector.js",
"js/pixastic.custom.js",
"js/postprocessing/EffectComposer.js",
"js/postprocessing/RenderPass.js",
"js/postprocessing/ShaderPass.js",
"js/postprocessing/MaskPass.js",
"js/shaders/CopyShader.js"], function(){
	var renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight );
	renderer.autoClear = false;
	var scene	= new THREE.Scene();
	var mesh = [];
	var onRenderFcts= [];
	var oLeftComposer = new THREE.EffectComposer( Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer() );
	var oRightComposer = new THREE.EffectComposer( Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer() );
	var oLeftCamera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	var oRightCamera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	var oCreateMesh = function(mesh, scene){

	}
	
	var oCreateComposer = function(sLeftRight, composer, scene, camera){
		var fPupilaryDist = 10.0;
		camera.up = new THREE.Vector3(0,1,0);
		if (sLeftRight == "left") {
			//renderer.setViewport( 0, 0, window.innerWidth, window.innerHeight );
			//renderer.setViewport( 0, 0, window.innerWidth/2, window.innerHeight );
			camera.position.set(-fPupilaryDist/2,0,0);
			camera.lookAt(new THREE.Vector3(-fPupilaryDist/2,0,-1));
			var oPostproShader =  {
				uniforms: {
					"tDiffuse": { type: "t", value: null },
					"LensCenter": { type: "v2", value: new THREE.Vector2( 0.5, 0.5 ) },
					"ScreenCenter": { type: "v2", value: new THREE.Vector2( 0.5, 0.5 ) },
					"Scale": { type: "v2", value: new THREE.Vector2( 0.95, 0.95 ) },
					"ScaleIn": { type: "v2", value: new THREE.Vector2( 1.0, 1.0 ) },
					"HmdWarpParam": { type: "v4", value: new THREE.Vector4( 1.0, 0.2, 0.2, 0.001 ) },
				},
				vertexShader: document.getElementById('vertexshader').innerHTML,
				fragmentShader: document.getElementById('fragmentshader').innerHTML
			};
		} else {
			//renderer.setViewport( window.innerWidth/2, 0, window.innerWidth/2, window.innerHeight );
			camera.position.set(fPupilaryDist/2,0,0);
			camera.lookAt(new THREE.Vector3(fPupilaryDist/2,0,-1));
			var oPostproShader =  {
				uniforms: {
					"tDiffuse": { type: "t", value: null },
					"LensCenter": { type: "v2", value: new THREE.Vector2( 0.5, 0.5 ) },
					"ScreenCenter": { type: "v2", value: new THREE.Vector2( 0.5, 0.5 ) },
					"Scale": { type: "v2", value: new THREE.Vector2( 0.95, 0.95 ) },
					"ScaleIn": { type: "v2", value: new THREE.Vector2( 1.0, 1.0 ) },
					"HmdWarpParam": { type: "v4", value: new THREE.Vector4( 1.0, 0.2, 0.2, 0.001 ) },
				},
				vertexShader: document.getElementById('vertexshader').innerHTML,
				fragmentShader: document.getElementById('fragmentshader').innerHTML
			};
		}
		
		document.body.appendChild( renderer.domElement );

		// postprocessing
		//var width = window.innerWidth || 1;
		//var height = window.innerHeight || 1;
		var parameters = { minFilter: THREE.LinearFilter, magFilter: THREE.LinearFilter, format: THREE.RGBFormat, stencilBuffer: false };
		renderTarget = new THREE.WebGLRenderTarget( window.innerWidth/2, window.innerHeight, parameters);

		//composer = new THREE.EffectComposer( renderer, renderTarget );
		composer.renderer = renderer;
		composer.reset(renderTarget);
		composer.addPass( new THREE.RenderPass( scene, camera ) );
		
		var oOculusDistortionCorrection = new THREE.ShaderPass( oPostproShader );
		//oOculusDistortionCorrection.uniforms[ 'amount' ].value = 4;
		oOculusDistortionCorrection.renderToScreen = true;
		composer.addPass( oOculusDistortionCorrection );

	}

	
	//////////////////////////////////////////////////////////////////////////////////
	//		add star field							//
	//////////////////////////////////////////////////////////////////////////////////
	var iImageLoaded = 0;
	var iNumberPhi = 4;
	var iNumberThe = 2;
	var img = new Image();

	img.onload = function() {
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

		async.series([ 
			function(callback){ oCreateComposer("left", oLeftComposer, scene, oLeftCamera); callback();},
			function(callback){ oCreateComposer("right", oRightComposer, scene, oRightCamera); callback();},
			function(callback){
				onRenderFcts.push(function(delta, now){
					mesh.forEach(function(oEachMesh){
						oEachMesh.rotation.y += .0005*0;
					})
				})
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
					//renderer.render( scene, camera );
					oLeftComposer.renderer.setViewport( 0, 0, window.innerWidth/2, window.innerHeight );
					oLeftComposer.render();
					oRightComposer.renderer.setViewport( window.innerWidth/2, 0, window.innerWidth/2, window.innerHeight );
					oRightComposer.render();
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
	img.src = "14087020332_1221918a9e_o.jpg";//"Big_ben_equirectangular.jpg";"14087020332_1221918a9e_o.jpg""Land_shallow_topo_alpha_2048.png"

})