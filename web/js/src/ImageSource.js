/** 
* @author fangong 
* input: imagePath
* output: image
* in/out: status
*/

PANA.ImageSource = function () {
	this.image = new Image();
	var status = { processed: true };
	this.image.onload = function() {
		console.log('PANA.ImageSource: image loaded!');
		status.processed = false; //to trigger scene1.process
	};
	this.status = status;
};

PANA.ImageSource.prototype = {
	contructor: PANA.ImageSource,
	process: (function () {
		var previouspath;
		return function () {
			if ( (!this.imagePath.processed) && (previouspath != this.imagePath.path) ) {
				previouspath = this.imagePath.path;
				this.image.src = this.imagePath.path;
				console.log('PANA.ImageSource: loading...'+this.imagePath.path);
				this.imagePath.processed = true;
			}
		};
	})()
};