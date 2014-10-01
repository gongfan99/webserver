/**
 * @author troffmo5 / http://github.com/troffmo5
 *
 * Effect to render the scene in stereo 3d side by side with lens distortion.
 * It is written to be used with the Oculus Rift (http://www.oculusvr.com/) but
 * it works also with other HMD using the same technology
 */


THREE.OculusRiftEffect = function ( renderer, options ) {
	// worldFactor indicates how many units is 1 meter
	var worldFactor = (options && options.worldFactor) ? options.worldFactor: 1.0;


	// Specific HMD parameters
	var HMD = (options && options.HMD) ? options.HMD: {
		// Parameters from the Oculus Rift DK1
		hResolution: window.innerWidth,//1280,
		vResolution: window.innerHeight,//800,
		hScreenSize: 0.14976,
		vScreenSize: 0.0936,
		interpupillaryDistance: 0.064,
		lensSeparationDistance: 0.064,
		eyeToScreenDistance: 0.041,
		distortionK : [1.0, 0.22, 0.24, 0.0],
		chromaAbParameter : [1.0, 0, 1.0, 0]
	};


	// Perspective pCamera
	var pCamera = new THREE.PerspectiveCamera(45, window.innerWidth / (2*window.innerHeight), 0.01, 1000 );
	pCamera.up = new THREE.Vector3(0,1,0);


	// pre-render hooks
	this.preLeftRender = function() {};
	this.preRightRender = function() {};


	renderer.autoClear = false;
	var emptyColor = new THREE.Color("black");


	// Render target
	var RTParams = { minFilter: THREE.LinearFilter, magFilter: THREE.NearestFilter, format: THREE.RGBAFormat };
	var renderTarget = new THREE.WebGLRenderTarget( 640, 800, RTParams );
	var oComposer = new THREE.EffectComposer( renderer, renderTarget );
	
	var oPostproShader = {
		uniforms: {
			"tDiffuse": { type: "t", value: null },
			"scale": { type: "v2", value: new THREE.Vector2(1.0,1.0) },
			"scaleIn": { type: "v2", value: new THREE.Vector2(1.0,1.0) },
			"lensCenter": { type: "v2", value: new THREE.Vector2(0.0,0.0) },
			"hmdWarpParam": { type: "v4", value: new THREE.Vector4(1.0,0.0,0.0,0.0) },
			"chromAbParam": { type: "v4", value: new THREE.Vector4(1.0,0.0,0.0,0.0) }
		},
		vertexShader: [
			"varying vec2 vUv;",
			"void main() {",
			" vUv = uv;",
			"	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );",
			"}"
		].join("\n"),
		fragmentShader: [
			"uniform vec2 scale;",
			"uniform vec2 scaleIn;",
			"uniform vec2 lensCenter;",
			"uniform vec4 hmdWarpParam;",
			'uniform vec4 chromAbParam;',
			"uniform sampler2D tDiffuse;",
			"varying vec2 vUv;",
			"void main()",
			"{",
			"  vec2 uv = (vUv*2.0)-1.0;", // range from [0,1] to [-1,1]
			"  vec2 theta = (uv-lensCenter)*scaleIn;",
			"  float rSq = theta.x*theta.x + theta.y*theta.y;",
			"  vec2 rvector = theta*(hmdWarpParam.x + hmdWarpParam.y*rSq + hmdWarpParam.z*rSq*rSq + hmdWarpParam.w*rSq*rSq*rSq);",
			'  vec2 rBlue = rvector * (chromAbParam.z + chromAbParam.w * rSq);',
			"  vec2 tcBlue = (lensCenter + scale * rBlue);",
			"  tcBlue = (tcBlue+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  if (any(bvec2(clamp(tcBlue, vec2(0.0,0.0), vec2(1.0,1.0))-tcBlue))) {",
			"    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);",
			"    return;}",
			"  vec2 tcGreen = lensCenter + scale * rvector;",
			"  tcGreen = (tcGreen+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  vec2 rRed = rvector * (chromAbParam.x + chromAbParam.y * rSq);",
			"  vec2 tcRed = lensCenter + scale * rRed;",
			"  tcRed = (tcRed+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  gl_FragColor = vec4(texture2D(tDiffuse, tcRed).r, texture2D(tDiffuse, tcGreen).g, texture2D(tDiffuse, tcBlue).b, 1);",
			"}"
		].join("\n")
	};


    var left = {}, right = {};
    var distScale = 1.0;
	this.setHMD = function(scene, camera) {
		//HMD = v;
		// Compute aspect ratio and FOV
		var aspect = HMD.hResolution / (2*HMD.vResolution);

		// Fov is normally computed with:
		//   THREE.Math.radToDeg( 2*Math.atan2(HMD.vScreenSize,2*HMD.eyeToScreenDistance) );
		// But with lens distortion it is increased (see Oculus SDK Documentation)
		var r = -1.0 - (4 * (HMD.hScreenSize/4 - HMD.lensSeparationDistance/2) / HMD.hScreenSize);
		distScale = (HMD.distortionK[0] + HMD.distortionK[1] * Math.pow(r,2) + HMD.distortionK[2] * Math.pow(r,4) + HMD.distortionK[3] * Math.pow(r,6));
		var fov = THREE.Math.radToDeg(2*Math.atan2(HMD.vScreenSize*distScale, 2*HMD.eyeToScreenDistance));

		// Compute pCamera projection matrices
		var proj = (new THREE.Matrix4()).makePerspective( fov, aspect, 0.3, 10000 );
		var h = 4 * (HMD.hScreenSize/4 - HMD.interpupillaryDistance/2) / HMD.hScreenSize;
		left.proj = ((new THREE.Matrix4()).makeTranslation( h, 0.0, 0.0 )).multiply(proj);
		right.proj = ((new THREE.Matrix4()).makeTranslation( -h, 0.0, 0.0 )).multiply(proj);

		// Compute pCamera view matrices
		h = worldFactor * HMD.interpupillaryDistance/2;
		left.view = ((new THREE.Matrix4()).makeTranslation( -h, 0.0, 0.0 )).multiply(camera.matrix);
		right.view = ((new THREE.Matrix4()).makeTranslation( h, 0.0, 0.0 )).multiply(camera.matrix);

		// Compute Viewport
		left.viewport = [0, 0, HMD.hResolution/2, HMD.vResolution];
		right.viewport = [HMD.hResolution/2, 0, HMD.hResolution/2, HMD.vResolution];

		// Distortion shader parameters
		var lensShift = 4 * (HMD.hScreenSize/4 - HMD.lensSeparationDistance/2) / HMD.hScreenSize;
		left.lensCenter = new THREE.Vector2(lensShift, 0.0);
		right.lensCenter = new THREE.Vector2(-lensShift, 0.0);

		oPostproShader.uniforms['hmdWarpParam'].value = new THREE.Vector4(HMD.distortionK[0], HMD.distortionK[1], HMD.distortionK[2], HMD.distortionK[3]);
		oPostproShader.uniforms['chromAbParam'].value = new THREE.Vector4(HMD.chromaAbParameter[0], HMD.chromaAbParameter[1], HMD.chromaAbParameter[2], HMD.chromaAbParameter[3]);
		oPostproShader.uniforms['scaleIn'].value = new THREE.Vector2(1.0,1.0/aspect);
		oPostproShader.uniforms['scale'].value = new THREE.Vector2(1.0/distScale, 1.0*aspect/distScale);

		// Create render target
		renderTarget = new THREE.WebGLRenderTarget( HMD.hResolution*distScale/2, HMD.vResolution*distScale, RTParams );
		oComposer.reset(renderTarget);
		//oPostproShader.uniforms[ "texid" ].value = renderTarget;

		oComposer.addPass( new THREE.RenderPass( scene, pCamera ) );
		var oOculusDistortionCorrection = new THREE.ShaderPass( oPostproShader );
		oOculusDistortionCorrection.renderToScreen = true;
		oComposer.addPass( oOculusDistortionCorrection );

	}	
	this.getHMD = function() {return HMD};

	//this.setHMD(HMD);	

	this.setSize = function ( width, height ) {
		left.viewport = [width/2 - HMD.hResolution/2, height/2 - HMD.vResolution/2, HMD.hResolution/2, HMD.vResolution];
		right.viewport = [width/2, height/2 - HMD.vResolution/2, HMD.hResolution/2, HMD.vResolution];

		oComposer.renderer.setSize( width, height );
	};


	this.render = function () {

		// Render left
/* 		oComposer.passes[0].camera.position.set(-HMD.interpupillaryDistance/2,0,0);
		oComposer.passes[0].camera.lookAt(new THREE.Vector3(-HMD.interpupillaryDistance/2,0,-1)); */
		//if (oComposer.passes[0].camera.matrixAutoUpdate) oComposer.passes[0].camera.updateMatrix();
		oComposer.passes[0].camera.projectionMatrix.copy(left.proj);
		oComposer.passes[0].camera.matrix.copy(left.view);
		oComposer.passes[0].camera.matrixWorldNeedsUpdate = true;
		oComposer.passes[1].material.uniforms['lensCenter'].value = left.lensCenter;
		oComposer.renderer.setViewport( left.viewport[0], left.viewport[1], left.viewport[2], left.viewport[3] );
		oComposer.render();

		// Render right
		oComposer.passes[0].camera.projectionMatrix.copy(right.proj);
		oComposer.passes[0].camera.projectionMatrix.copy(right.proj);
		oComposer.passes[0].camera.matrix.copy(right.view);
		oComposer.passes[0].camera.matrixWorldNeedsUpdate = true;
		oComposer.passes[1].material.uniforms['lensCenter'].value = right.lensCenter;
		oComposer.renderer.setViewport( right.viewport[0], right.viewport[1], right.viewport[2], right.viewport[3] );
		oComposer.render();
	};
	
};
