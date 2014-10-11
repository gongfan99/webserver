/** 
* @author fangong
* input: renderTarget eyeInfo
* output: ShaderMaterial
*/ 

PANA.ShaderMaterial = function () {
	this.material = new THREE.ShaderMaterial( {
		uniforms: {
			"texture0": { type: "t", value: null },
			"eyeToSourceUVscale": { type: "v2", value: new THREE.Vector2() },
			"eyeToSourceUVoffset": { type: "v2", value: new THREE.Vector2() },
			"eyeRotationStart": { type: "m4", value: new THREE.Matrix4() },
			"eyeRotationEnd": { type: "m4", value: new THREE.Matrix4() }
		},
		attributes: {
			"timewarpLerpFactor": { type: "f", value: 1.0 },
			"vignette": { type: "f", value: 1.0 },
			"texCoord0": { type: "v2", value: new THREE.Vector2() },
			"texCoord1": { type: "v2", value: new THREE.Vector2() },
			"texCoord2": { type: "v2", value: new THREE.Vector2() }
		},
		vertexShader: [
			"attribute float timewarpLerpFactor;",
			"attribute float vignette;",
			"attribute vec2 texCoord0;",
			"attribute vec2 texCoord1;",
			"attribute vec2 texCoord2;",
			"",
			"uniform vec2 eyeToSourceUVscale;",
			"uniform vec2 eyeToSourceUVoffset;",
			"uniform mat4 eyeRotationStart;",
			"uniform mat4 eyeRotationEnd;",
			"",
			"varying vec2 oTexCoord0;",
			"varying vec2 oTexCoord1;",
			"varying vec2 oTexCoord2;",
			"varying float oVignette;",
			"",
			"vec2 timeWarpTexCoord(in vec2 texCoord, in mat4 rotMat) {",
				"vec3 transformed = (rotMat * vec4(texCoord.xy, 1.0, 1.0)).xyz;",
				"vec2 flattened = transformed.xy / transformed.z;",
				"return eyeToSourceUVscale * flattened + eyeToSourceUVoffset;",
			"}",
			"",
			"void main() {",
			"	mat4 lerpedEyeRot = eyeRotationStart * (1.0 - timewarpLerpFactor) + eyeRotationEnd * timewarpLerpFactor;",
			"	oTexCoord0 = timeWarpTexCoord(texCoord0, lerpedEyeRot);",
			"	oTexCoord1 = timeWarpTexCoord(texCoord1, lerpedEyeRot);",
			"	oTexCoord2 = timeWarpTexCoord(texCoord2, lerpedEyeRot);",
			"	gl_Position = vec4(position, 1.0);",
			"	oVignette = vignette;",
			"}"
		].join("\n"),
		fragmentShader: [
			"uniform sampler2D texture0;",
			"",
			"varying vec2 oTexCoord0;",
			"varying vec2 oTexCoord1;",
			"varying vec2 oTexCoord2;",
			"varying float oVignette;",
			"",
			"void main() {",
			"	float r = texture2D(texture0, oTexCoord0).r;",
			"	float g = texture2D(texture0, oTexCoord1).g;",
			"	float b = texture2D(texture0, oTexCoord2).b;",
			"	gl_FragColor = vec4(r, g, b, 1) * oVignette;",
			"}"
		].join("\n"),
		side: THREE.DoubleSide,
		transparent: true
	} );
/* 	this.material = new THREE.ShaderMaterial( {
		uniforms: {},
		attributes: {
		},
		vertexShader: [
			"void main() {",
			"	gl_Position = vec4(position, 1.0);",
			"}"
		].join("\n"),
		fragmentShader: [
			"void main() {",
			"	gl_FragColor = vec4(1.0, 0.2, 0.2, 1.0);",
			"}"
		].join("\n"),
		side: THREE.DoubleSide,
		transparent: true
	} ); */
};

PANA.ShaderMaterial.prototype = {
	contructor: PANA.ShaderMaterial,
	process: function () {
		this.material.uniforms['texture0'].value = this.renderTarget;
		this.material.uniforms['eyeToSourceUVscale'].value = this.eyeInfo.eyeToSourceUVscale;
		this.material.uniforms['eyeToSourceUVoffset'].value = this.eyeInfo.eyeToSourceUVoffset;
		this.material.uniforms['eyeRotationStart'].value = this.eyeInfo.eyeRotationStart;
		this.material.uniforms['eyeRotationEnd'].value = this.eyeInfo.eyeRotationEnd;
	}
};