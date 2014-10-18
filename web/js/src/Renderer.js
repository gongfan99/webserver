/** 
* @author fangong
* input: scene camera OcuInf
* output: renderTarget or (to screen)
*/ 

PANA.Renderer = (function () {
	var renderer; //static member
	function onWindowResize(){
		renderer.setSize( window.innerWidth, window.innerHeight );
	}
	window.addEventListener( 'resize', onWindowResize, false );
	return function ( toScreen, side ) {
		this.toScreen = toScreen;
		if ( !this.toScreen ) {
			this.side = side;
		}

		//Screen resolution of Oculus DK2
		var ResWidth = 1920;
		var ResHeight = 1080;

		if (renderer == undefined) {
			renderer = Detector.webgl ? new THREE.WebGLRenderer() : new THREE.CanvasRenderer();
			renderer.setSize( ResWidth, ResHeight ); //set canvas size
			renderer.autoClear = false;
			document.body.appendChild( renderer.domElement ); //add canvas only once
		}
		this.renderer = renderer;

		if ( !this.toScreen ) {
			var RTParams = { minFilter: THREE.LinearFilter, magFilter: THREE.NearestFilter, format: THREE.RGBAFormat };
			this.renderTarget = new THREE.WebGLRenderTarget( ResWidth/2, ResHeight, RTParams );
		}
	};
})();

PANA.Renderer.prototype = {
	contructor: PANA.Renderer,
	process: function () {
		var r;

		if ( this.toScreen && !this.OcuInf["OculusInit"]["processed"]["resolution"] ) {
			r = this.OcuInf["OculusInit"]["resolution"];
			this.renderer.setSize( r[0]/10, r[1]/10 ); //set canvas size
			this.OcuInf["OculusInit"]["processed"]["resolution"] = true;
		}

		if ( !this.toScreen && !this.OcuInf["OculusInit"]["processed"]["RenderTargetSize"][this.side] ) {
			r = this.OcuInf["OculusInit"]["RenderTargetSize"][this.side];
			this.renderTarget.setSize( r[0], r[1] ); //set render target size
			this.OcuInf["OculusInit"]["processed"]["RenderTargetSize"][this.side] = true;
		}

		if (this.toScreen) {
			this.renderer.render( this.scene, this.camera );
		} else {
			this.renderer.render( this.scene, this.camera, this.renderTarget, true );
		};
	}
};