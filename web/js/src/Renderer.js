/** 
* @author fangong
* input: scene camera
* output: renderTarget or (to screen)
*/ 

PANA.Renderer = function () {
	// temperarily put here; should point to OculusBridge eventually
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
	var distScale = 1.0;

	this.renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
	this.renderer.setSize( HMD.hResolution, HMD.vResolution );
	this.renderer.autoClear = false;
	document.body.appendChild( this.renderer.domElement );

	var RTParams = { minFilter: THREE.LinearFilter, magFilter: THREE.NearestFilter, format: THREE.RGBAFormat };
	this.renderTarget = new THREE.WebGLRenderTarget( HMD.hResolution*distScale/2, HMD.vResolution*distScale, RTParams );
};

PANA.Renderer.prototype = {
	contructor: PANA.Renderer,
	process: function () {
		//this.renderer.render( this.scene, this.camera, this.renderTarget, true );
		this.renderer.render( this.scene, this.camera );
	}
	clone: function () {
		var renderer = new PANA.Renderer();
		renderer.renderer = this.renderer; //share the renderer
		renderer.renderTarget = this.renderTarget.clone();
	}
};