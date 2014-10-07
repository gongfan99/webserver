/** 
* @author fangong 
* input: OculusBridge
* output: quaternion
*/

PANA.ImageSource = function () {
	this.image = new Image();

	this.image.onload = function() {
		this.loaded = true;
	};

	image.src = "Land_shallow_topo_alpha_2048.png";//"Big_ben_equirectangular.jpg";"14087020332_1221918a9e_o.jpg""Land_shallow_topo_alpha_2048.png"
};

PANA.ImageSource.prototype = {
	contructor: PANA.ImageSource,
	process: function () {}
};