/** 
* @author fangong 
* input: imagePath
* output: image
* in/out: loaded
*/

PANA.ImageSource = function () {
	this.imagePath = {};
	this.imagePath.path = this.imagePath.previouspath = "Land_shallow_topo_2048.jpg";

	this.image = new Image();
	var loaded = {
		status: false,
		processed: true
	};
	this.image.onload = function() {
		console.log('image loaded!');
		loaded.status = true;
		loaded.processed = false; //scene will set this flag to true
	};
	this.loaded = loaded;

	this.image.src = this.imagePath.path;//"Big_ben_equirectangular.jpg";"14087020332_1221918a9e_o.jpg""Land_shallow_topo_alpha_2048.png"
	console.log('loading...'+this.imagePath.path);
};

PANA.ImageSource.prototype = {
	contructor: PANA.ImageSource,
	process: function () {
		if ( this.loaded.status && (this.imagePath.previouspath != this.imagePath.path) ) {
			this.imagePath.previouspath = this.imagePath.path;
			this.loaded.status = false;
			this.image.src = this.imagePath.path;
		}
	}
};