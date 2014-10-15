/** 
* @author fangong
* input: mesh
* output: geometry
*/ 

PANA.PlaneGeometry = function () {
	this.geometry = new THREE.BufferGeometry();
	this.geometry.dynamic = true;

	var IndexCount = 24576;
	this.positions = new Float32Array( IndexCount * 3 );
	this.TimeWarpFactor = new Float32Array( IndexCount );
	this.VignetteFactor = new Float32Array( IndexCount );
	this.texCoord0 = new Float32Array( IndexCount * 2 );
	this.texCoord1 = new Float32Array( IndexCount * 2 );
	this.texCoord2 = new Float32Array( IndexCount * 2 );
	
	this.geometry.addAttribute( 'position', new THREE.BufferAttribute( this.positions, 3 ) );
	this.geometry.addAttribute( 'timewarpLerpFactor', new THREE.BufferAttribute( this.TimeWarpFactor, 1 ) );
	this.geometry.addAttribute( 'vignette', new THREE.BufferAttribute( this.VignetteFactor, 1 ) );
	this.geometry.addAttribute( 'texCoord0', new THREE.BufferAttribute( this.texCoord0, 2 ) );
	this.geometry.addAttribute( 'texCoord1', new THREE.BufferAttribute( this.texCoord1, 2 ) );
	this.geometry.addAttribute( 'texCoord2', new THREE.BufferAttribute( this.texCoord2, 2 ) );
};

PANA.PlaneGeometry.prototype = {
	contructor: PANA.PlaneGeometry,
	process: function () {
		if ( !this.mesh.processed ) {
			var mesh = this.mesh;
			for( var v = 0; v < mesh.IndexCount; v++ ) {
				this.positions[ v * 3 + 0 ] = mesh.ScreenPosNDC[ mesh.pIndexData[ v ] * 2 + 0 ];
				this.positions[ v * 3 + 1 ] = mesh.ScreenPosNDC[ mesh.pIndexData[ v ] * 2 + 1 ];
				this.positions[ v * 3 + 2 ] = 0.0;
				
				this.TimeWarpFactor[v] = mesh.TimeWarpFactor[ mesh.pIndexData[ v ] ];
				this.VignetteFactor[v] = mesh.VignetteFactor[ mesh.pIndexData[ v ] ];

				this.texCoord0[ v * 2 + 0 ] = mesh.TanEyeAnglesR[ mesh.pIndexData[ v ] * 2 + 0 ] / 2 + 0.5;
				this.texCoord0[ v * 2 + 1 ] = 1 - ( mesh.TanEyeAnglesR[ mesh.pIndexData[ v ] * 2 + 1 ] / 2 + 0.5 ); //"1-y" is to convert DirectX coordinates to WebGL coordinates. The data from Oculus SDK is for DirectX.
				this.texCoord1[ v * 2 + 0 ] = mesh.TanEyeAnglesG[ mesh.pIndexData[ v ] * 2 + 0 ] / 2 + 0.5;
				this.texCoord1[ v * 2 + 1 ] = 1 - ( mesh.TanEyeAnglesG[ mesh.pIndexData[ v ] * 2 + 1 ] / 2 + 0.5 );
				this.texCoord2[ v * 2 + 0 ] = mesh.TanEyeAnglesB[ mesh.pIndexData[ v ] * 2 + 0 ] / 2 + 0.5;
				this.texCoord2[ v * 2 + 1 ] = 1 - ( mesh.TanEyeAnglesB[ mesh.pIndexData[ v ] * 2 + 1 ] / 2 + 0.5 );
			}

			for ( var key in this.geometry.attributes ) {
				this.geometry.attributes[ key ].needsUpdate = true;
			}

			this.mesh.processed = true;
			console.log("PANA.PlaneGeometry: geometry created.");
		}
	}
};