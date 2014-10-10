/** 
* @author fangong
* input: mesh
* output: geometry
*/ 

PANA.PlaneGeometry = function () {
	this.geometry = new THREE.BufferGeometry();
};

PANA.PlaneGeometry.prototype = {
	contructor: PANA.PlaneGeometry,
	process: function () {
		if ( !this.mesh.processed ) {
			var mesh = this.mesh;
			var positions = new Float32Array( mesh.IndexCount * 2 );
			var TimeWarpFactor = new Float32Array( mesh.IndexCount );
			var VignetteFactor = new Float32Array( mesh.IndexCount );
			var TanEyeAnglesR = new Float32Array( mesh.IndexCount * 2 );
			var TanEyeAnglesG = new Float32Array( mesh.IndexCount * 2 );
			var TanEyeAnglesB = new Float32Array( mesh.IndexCount * 2 );

			for( var v = 0; v < mesh.IndexCount; v++ ) {
				positions[ v * 2 + 0 ] = mesh.ScreenPosNDC[ mesh.pIndexData[ v ] * 2 + 0 ];
				positions[ v * 2 + 1 ] = mesh.ScreenPosNDC[ mesh.pIndexData[ v ] * 2 + 1 ];
				
				TimeWarpFactor[v] = mesh.TimeWarpFactor[ mesh.pIndexData[ v ] ];
				VignetteFactor[v] = mesh.VignetteFactor[ mesh.pIndexData[ v ] ];

				TanEyeAnglesR[ v * 2 + 0 ] = mesh.TanEyeAnglesR[ mesh.pIndexData[ v ] * 2 + 0 ];
				TanEyeAnglesR[ v * 2 + 1 ] = mesh.TanEyeAnglesR[ mesh.pIndexData[ v ] * 2 + 1 ];
				TanEyeAnglesG[ v * 2 + 0 ] = mesh.TanEyeAnglesG[ mesh.pIndexData[ v ] * 2 + 0 ];
				TanEyeAnglesG[ v * 2 + 1 ] = mesh.TanEyeAnglesG[ mesh.pIndexData[ v ] * 2 + 1 ];
				TanEyeAnglesB[ v * 2 + 0 ] = mesh.TanEyeAnglesB[ mesh.pIndexData[ v ] * 2 + 0 ];
				TanEyeAnglesB[ v * 2 + 1 ] = mesh.TanEyeAnglesB[ mesh.pIndexData[ v ] * 2 + 1 ];
			}

			this.geometry.addAttribute( 'position', new THREE.BufferAttribute( positions, 2 ) );
			this.geometry.addAttribute( 'TimeWarpFactor', new THREE.BufferAttribute( TimeWarpFactor, 1 ) );
			this.geometry.addAttribute( 'VignetteFactor', new THREE.BufferAttribute( VignetteFactor, 1 ) );
			this.geometry.addAttribute( 'TanEyeAnglesR', new THREE.BufferAttribute( TanEyeAnglesR, 2 ) );
			this.geometry.addAttribute( 'TanEyeAnglesG', new THREE.BufferAttribute( TanEyeAnglesG, 2 ) );
			this.geometry.addAttribute( 'TanEyeAnglesB', new THREE.BufferAttribute( TanEyeAnglesB, 2 ) );
			
			this.mesh.processed = true;
		}
	}
};