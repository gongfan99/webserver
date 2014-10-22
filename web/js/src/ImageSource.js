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
		var http = new XMLHttpRequest();
		return function () {
			if ( this.OcuInf["Image"] && !this.OcuInf["Image"]["processed"] && (previouspath != this.OcuInf["Image"]["path"]) ) {
				http.open("HEAD", "./image/" + this.OcuInf["Image"]["path"], false);
				http.send();
				if ( http.status !== 404 ) {
					previouspath = this.OcuInf["Image"]["path"];
					this.image.src = "./image/" + this.OcuInf["Image"]["path"];
					console.log('PANA.ImageSource: loading...'+this.OcuInf["Image"]["path"]);
					this.OcuInf["Image"]["processed"] = true;
				}
			}
		};
	})()
};