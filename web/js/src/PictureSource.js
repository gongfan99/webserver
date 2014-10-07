/** 
* @author fangong 
*/ 

PANA.PictureSource = function () {
	this.image = new Image();

	this.image.onload = function() {
		this.loaded = true;
	};

	image.src = "Land_shallow_topo_alpha_2048.png";//"Big_ben_equirectangular.jpg";"14087020332_1221918a9e_o.jpg""Land_shallow_topo_alpha_2048.png"
};

PANA.PictureSource.prototype = {
	contructor: PANA.PictureSource,
	process: function () {}
};