/** 
* @author fangong
* input: image
* output: scene
*/ 

PANA.Scene1 = function () {
	var img = this.image;
	var iNumberPhi = 4;
	var iNumberThe = 2;
	this.scene = new THREE.Scene();
	
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
						map: THREE.ImageUtils.loadTexture(newImage.toDataURL(), new THREE.UVMapping(), function(){})
					})
					var mesh = new THREE.Mesh(geometry, material));
					mesh.scale.x = -1;
					mesh.scale.y = 1;
					mesh.scale.z = 1;
					this.scene.add(mesh);
				}
			);
		}
	}
};

PANA.Scene1.prototype = {
	contructor: PANA.Scene1,
	process: function () {}
};