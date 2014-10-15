/** 
* @author fangong
* input: scene camera
* output: renderTarget or (to screen)
*/ 

PANA.Renderer = (function () {
	var renderer; //static member
	return function (toScreen) {
		this.toScreen = toScreen;
		
		// temperarily put here; should point to OculusBridge eventually
		var HMD = {
			// Parameters from the Oculus Rift DK1
			hResolution: window.innerWidth/6,//1280,
			vResolution: window.innerHeight/6,//800,
			hScreenSize: 0.14976,
			vScreenSize: 0.0936,
			interpupillaryDistance: 0.064,
			lensSeparationDistance: 0.064,
			eyeToScreenDistance: 0.041
		};
		var distScale = 1.0;

		if (renderer == undefined) {
			renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
			renderer.setSize( HMD.hResolution, HMD.vResolution ); //set canvas size
			renderer.autoClear = false;
			document.body.appendChild( renderer.domElement ); //add canvas only once
		}
		this.renderer = renderer;

/* 		this.viewport = [0, 0, HMD.hResolution/2, HMD.vResolution];
		this.viewport[0] = ( side == 'left' ) ? 0 : HMD.hResolution/2; */

		if ( !this.toScreen ) {
			var RTParams = { minFilter: THREE.LinearFilter, magFilter: THREE.NearestFilter, format: THREE.RGBAFormat };
			this.renderTarget = new THREE.WebGLRenderTarget( HMD.hResolution*distScale/2, HMD.vResolution*distScale, RTParams );
		}
	};
})();

PANA.Renderer.prototype = {
	contructor: PANA.Renderer,
	process: function () {
		if (this.toScreen) {
			//this.renderer.setViewport(this.viewport[0], this.viewport[1], this.viewport[2], this.viewport[3]);
			this.renderer.render( this.scene, this.camera );
		} else {
			this.renderer.render( this.scene, this.camera, this.renderTarget, true );
		};
	}
};