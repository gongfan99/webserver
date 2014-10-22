PANA.InitValues = (function () {
	return {
		OcuInf: {
 			//OculusInit: {}, //OculusInit data will be got from Websocket server.
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
				path: "Land_shallow_topo_2048.jpg"
			}
		}
	};
})();