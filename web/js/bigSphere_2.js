//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require(["js/three.min.js","js/Detector.js","js/pixastic.custom.js"], function(){
	var renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
	//var renderer	= new THREE.WebGLRenderer();
	renderer.setSize( window.innerWidth, window.innerHeight );
	document.body.appendChild( renderer.domElement );

	var onRenderFcts= [];
	var scene	= new THREE.Scene();
	var camera	= new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.01, 1000 );
	//camera.position.z = 1.5;
	camera.position.set(0,0,0);
	camera.up = new THREE.Vector3(0,1,0);
	camera.lookAt(new THREE.Vector3(0,0,-1));

	//var light	= new THREE.AmbientLight( 0x888888 )
	//scene.add( light )
	// var light	= new THREE.DirectionalLight( 'white', 1)
	// light.position.set(5,5,5)
	// light.target.position.set( 0, 0, 0 )
	// scene.add( light )

/* 	var light	= new THREE.DirectionalLight( 0xcccccc, 1 )
	light.position.set(5,3,5)
	scene.add( light ) */

	//////////////////////////////////////////////////////////////////////////////////
	//		add an object and make it move					//
	//////////////////////////////////////////////////////////////////////////////////	
	/*
	var earthMesh	= THREEx.Planets.createEarth()
	scene.add(earthMesh)
	onRenderFcts.push(function(delta, now){
		earthMesh.rotateY( 1/32 * delta )
	})

	var cloudMesh	= THREEx.Planets.createEarthCloud()
	scene.add(cloudMesh)
	onRenderFcts.push(function(delta, now){
		cloudMesh.rotateY( 1/16 * delta )
	})
	*/

	//////////////////////////////////////////////////////////////////////////////////
	//		define vertex and fragment shaders							//
	//////////////////////////////////////////////////////////////////////////////////


		
	//////////////////////////////////////////////////////////////////////////////////
	//		add star field							//
	//////////////////////////////////////////////////////////////////////////////////
	var iImageLoaded = 0;
	var mesh = [];
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
						// var material  = new THREE.MeshBasicMaterial({
							// side: THREE.FrontSide,
							// map: THREE.ImageUtils.loadTexture(newImage.toDataURL(), new THREE.UVMapping(), function(){iImageLoaded++;})
						// })
						var sVertexShader = '#ifdef GL_ES\n' +
							'precision highp float;\n' +
							'#endif\n' +
							' varying vec2 vUv;' +
							' void main() {' +
							'    vUv = uv;' +
							'    vec3 newPosition1 = position * 100.0 / position.z;' +
							'    vec3 newPosition2 = newPosition1 * (1.0 + 0.3 * newPosition1.x * newPosition1.x * newPosition1.y * newPosition1.y;' +
							'    vec3 newPosition3 = newPosition2 * 100.0 / length(newPosition2);' +
							'    gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);' +
							' }';
						var sFragmentShader = '#ifdef GL_ES\n' +
							'precision highp float;\n' +
							'#endif\n' +
							' varying vec2 vUv;' +
							' uniform sampler2D texture;' +
							' void main() {' +
							'    vec4 color = texture2D( texture, vUv );' +
							'    gl_FragColor = color;' +
							' }';
						var uniforms = {
							texture: { type: "t", value: THREE.ImageUtils.loadTexture(newImage.toDataURL()) }
						};
						var material = new THREE.ShaderMaterial({
							side: THREE.FrontSide,
							uniforms: uniforms,
							attributes: [],
							vertexShader: document.getElementById('vertexshader').innerHTML,
							fragmentShader: document.getElementById('fragmentshader').innerHTML,
							transparent: true
						});
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
	}
	//document.body.appendChild(img);
	img.src = "14087020332_1221918a9e_o.jpg";//"Big_ben_equirectangular.jpg";

	// var uniforms = {
		// texture: { type: "t", value: THREE.ImageUtils.loadTexture('14087020332_1221918a9e_o.jpg') }
	// };
	// var oMaterialShader = new THREE.ShaderMaterial({
		// uniforms: uniforms,
		// vertexShader: sVertexShader
	// });

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
			oEachMesh.rotation.y += .02*mouse.x;
			oEachMesh.rotation.x += .02*mouse.y;
		})
	})

	var touch	= {x : 0, y : 0}
	var touch_start	= {x : 0, y : 0}
	document.addEventListener('touchstart', function(event){
		touch_start.x	= (event.changedTouches[0].clientX / window.innerWidth ) - 0.5
		touch_start.y	= (event.changedTouches[0].clientY / window.innerHeight) - 0.5
	}, false)
	document.addEventListener('touchmove', function(event){
		touch.x	= ((event.changedTouches[0].clientX - touch_start.x )/ window.innerWidth ) * 30 * 3.14159 / 180
		touch.y	= ((event.changedTouches[0].clientY - touch_start.y ) / window.innerHeight) * 30 * 3.14159 / 180
	}, false)
	onRenderFcts.push(function(delta, now){
		camera.rotation.x -= touch.y
		camera.rotation.y += touch.x
	})
	
	//////////////////////////////////////////////////////////////////////////////////
	//		Windows Resize							//
	//////////////////////////////////////////////////////////////////////////////////
	window.addEventListener( 'resize', function(event){
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize( window.innerWidth, window.innerHeight );
	}, false );
	
	//////////////////////////////////////////////////////////////////////////////////
	//		render the scene						//
	//////////////////////////////////////////////////////////////////////////////////
	onRenderFcts.push(function(){
		renderer.render( scene, camera );		
	})
	
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
		if (iImageLoaded == iNumberPhi*iNumberThe) {
			alert(img.width);
			iImageLoaded = 0;
		}
		// call each update function
		onRenderFcts.forEach(function(onRenderFct){
			onRenderFct(deltaMsec/1000, nowMsec/1000)
		})
	})
})