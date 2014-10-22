/** 
* @author fangong
* input: renderTarget OcuInf
* output: ShaderMaterial
*/ 

PANA.ShaderMaterial = function (side) {
	this.side = side;
	this.material = new THREE.ShaderMaterial( {
		uniforms: {
			texture0: { type: "t", value: null },
			eyeToSourceUVscale: { type: "v2", value: new THREE.Vector2() },
			eyeToSourceUVoffset: { type: "v2", value: new THREE.Vector2() },
			eyeRotationStart: { type: "m4", value: new THREE.Matrix4() },
			eyeRotationEnd: { type: "m4", value: new THREE.Matrix4() }
		},
		attributes: {
			timewarpLerpFactor: { type: "f", value: 1.0 },
			vignette: { type: "f", value: 1.0 },
			texCoord0: { type: "v2", value: new THREE.Vector2() },
			texCoord1: { type: "v2", value: new THREE.Vector2() },
			texCoord2: { type: "v2", value: new THREE.Vector2() }
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
				"vec2 result = eyeToSourceUVscale * flattened + eyeToSourceUVoffset;",
				"return vec2(result.x, 1.0-result.y);", //"1-y" is to convert DirectX coordinates to WebGL coordinates. The data from Oculus SDK is for DirectX.
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
};

PANA.ShaderMaterial.prototype = {
	contructor: PANA.ShaderMaterial,
	process: function () {
		var m;
		this.material.uniforms['texture0'].value = this.renderTarget;

		if ( this.OcuInf["OculusInit"] && !this.OcuInf["OculusInit"]["processed"]["UVScaleOffset"][this.side] ) {
			this.material.uniforms['eyeToSourceUVscale'].value.fromArray( this.OcuInf["OculusInit"]["UVScaleOffset"][this.side]["Scale"] );
			this.material.uniforms['eyeToSourceUVoffset'].value.fromArray( this.OcuInf["OculusInit"]["UVScaleOffset"][this.side]["Offset"] );
			this.OcuInf["OculusInit"]["processed"]["UVScaleOffset"][this.side] = true;
		}

		if ( this.OcuInf["OculusUpdate"] && !this.OcuInf["OculusUpdate"]["processed"]["timeWarpMatrices"][this.side] ) {
			m = this.OcuInf["OculusUpdate"]["timeWarpMatrices"][this.side]["Start"];
			this.material.uniforms['eyeRotationStart'].value.set(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
			m = this.OcuInf["OculusUpdate"]["timeWarpMatrices"][this.side]["End"];
			this.material.uniforms['eyeRotationEnd'].value.set(m[0],m[1],m[2],m[3],m[4],m[5],m[6],m[7],m[8],m[9],m[10],m[11],m[12],m[13],m[14],m[15]);
			this.OcuInf["OculusUpdate"]["processed"]["timeWarpMatrices"][this.side] = true;
		}
	}
};