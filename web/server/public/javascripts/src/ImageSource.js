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
				http.onreadystatechange = (function (self) {
					return	function () {
						if ( http.readyState == 4 && http.status !== 404 ) {
							console.log('PANA.ImageSource: ' + http.responseText);
							previouspath = self.OcuInf["Image"]["path"];
							self.image.src = "./images/" + self.OcuInf["Image"]["path"];
							console.log('PANA.ImageSource: loading...'+self.OcuInf["Image"]["path"]);
							self.OcuInf["Image"]["processed"] = true;
						}
					}
				})(this);
				http.open("GET", "./image/" + this.OcuInf["Image"]["path"], false);
				http.send();
			}
		};
	})()
};