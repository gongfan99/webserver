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
			if ( this.OcuInf["Image"] && this.OcuInf["Image"]["path"] && !this.OcuInf["Image"]["processed"] && (previouspath != this.OcuInf["Image"]["path"]) ) {
				previouspath = this.OcuInf["Image"]["path"];
				this.image.src = self.OcuInf["Image"]["path"];
				console.log('PANA.ImageSource: loading...'+self.OcuInf["Image"]["path"]);
				self.OcuInf["Image"]["processed"] = true;
			}
		};
	})()
};