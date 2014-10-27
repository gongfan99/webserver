/** 
* @author fangong 
* input: OcuInf
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
		var previouspath = null;
		return function () {
			if ( this.OcuInf["Image"] && this.OcuInf["Image"]["url"] && !this.OcuInf["Image"]["processed"] && (previouspath != this.OcuInf["Image"]["url"]) ) {
				previouspath = this.OcuInf["Image"]["url"];
				this.image.src = this.OcuInf["Image"]["url"];
				console.log('PANA.ImageSource: loading...'+this.OcuInf["Image"]["url"]);
				this.OcuInf["Image"]["processed"] = true;
			}
		};
	})()
};