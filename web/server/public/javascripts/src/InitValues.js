PANA.InitValues = (function () {
	var mesh = {};
	var tempGeo = new THREE.PlaneGeometry( 2, 2, 64, 64 );
	var vertex_posi = new Array(4225*2);
	var uv_posi = new Array(4225*2);
	var vignette =  new Array(4225);
	for( var v = 0; v < 4225; v++ ) {
		vertex_posi[ v * 2 + 0 ] = tempGeo.vertices[v].x;
		vertex_posi[ v * 2 + 1 ] = tempGeo.vertices[v].y;
		uv_posi[ v * 2 + 0 ] = tempGeo.vertices[v].x;
		uv_posi[ v * 2 + 1 ] = tempGeo.vertices[v].y;
		vignette[ v ] =  Math.exp(-tempGeo.vertices[v].length());
	}
	var position_index = new Array(24576);
	for( v = 0; v < 24576/3; v++ ) {
		position_index[ v * 3 + 0 ] = tempGeo.faces[v].a;
		position_index[ v * 3 + 1 ] = tempGeo.faces[v].b;
		position_index[ v * 3 + 2 ] = tempGeo.faces[v].c;
	}
	mesh.right = {
		IndexCount: 24576,
		VertexCount: 4225,
		ScreenPosNDC: vertex_posi,
		TimeWarpFactor: Array.apply(null, Array(4225)).map(function() { return 1.0 }),
		VignetteFactor: vignette,
		TanEyeAnglesR: uv_posi,
		TanEyeAnglesG: uv_posi,
		TanEyeAnglesB: uv_posi,
		pIndexData: position_index,
		processed: false
	};
	mesh.left = {
		IndexCount: 24576,
		VertexCount: 4225,
		ScreenPosNDC: vertex_posi,
		TimeWarpFactor: Array.apply(null, Array(4225)).map(function() { return 1.0 }),
		VignetteFactor: vignette,
		TanEyeAnglesR: uv_posi,
		TanEyeAnglesG: uv_posi,
		TanEyeAnglesB: uv_posi,
		pIndexData: position_index,
		processed: false
	};
	return {
		OcuInf: {
			OculusInit: {
				processed: {
					aspect: {
						left: false,
						right: false
					},
					resolution: false,
					FOV: {
						left: false,
						right: false
					},
					meshData: {
						left: false,
						right: false
					},
					RenderTargetSize: {
						left: false,
						right: false
					},
					UVScaleOffset: {
						left: false,
						right: false
					}
				},
				aspect: {
					left: 1.0*1182/1461,
					right: 1.0*1182/1461
				},
				resolution: [1920, 1080],
				FOV: {
					left: [1.32929,1.32929,1.05866,1.09237],
					right: [1.32929,1.32929,1.05866,1.09237]
				},
				meshData: {
					left: mesh.left,
					right: mesh.right
				},
				RenderTargetSize: {
					left: [1182,1461],
					right: [1182,1461]
				},
				UVScaleOffset: {
					left: {
						Scale: [0.464895,0.376142],
						Offset: [0.492164,0.5]
					},
					right: {
						Scale: [0.464895,0.376142],
						Offset: [0.492164,0.5]
					}
				}
			},
			OculusUpdate: {
				processed: {
					timeWarpMatrices: {
						left: false,
						right: false
					},
					Orientation: false,
					Position: false
				},
				timeWarpMatrices: {
					left: {
						Start: [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1],
						End: [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]
					},
					right: {
						Start: [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1],
						End: [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1]
					}
				},
				Orientation: [0,0,0,1],
				Position: [0,0,0]
			},
			Image: {
				processed: false,
				id: "1",
				url: 'images/Earthmap720x360_grid.jpg'
			}
		}
	};
})();