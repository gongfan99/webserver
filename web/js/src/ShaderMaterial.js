/** 
* @author fangong
* input: renderTarget
* output: ShaderMaterial
*/ 

PANA.ShaderMaterial = function () {
	this.ShaderMaterial = new THREE.ShaderMaterial( {
		uniforms: {
			"tDiffuse": { type: "t", value: this.renderTarget },
			"scale": { type: "v2", value: new THREE.Vector2(1.0,1.0) },
			"scaleIn": { type: "v2", value: new THREE.Vector2(1.0,1.0) },
			"lensCenter": { type: "v2", value: new THREE.Vector2(0.0,0.0) },
			"hmdWarpParam": { type: "v4", value: new THREE.Vector4(1.0,0.0,0.0,0.0) },
			"chromAbParam": { type: "v4", value: new THREE.Vector4(1.0,0.0,0.0,0.0) }
		},
		attributes: {
			"TimeWarpFactor": { type: "f", value: new THREE.Vector2(0.0,0.0) },
			"VignetteFactor": { type: "f", value: new THREE.Vector4(1.0,0.0,0.0,0.0) },		"TanEyeAnglesR": { type: "v2", value: renderTarget },
			"TanEyeAnglesG": { type: "v2", value: new THREE.Vector2(1.0,1.0) },
			"TanEyeAnglesB": { type: "v2", value: new THREE.Vector2(1.0,1.0) }
		},
		vertexShader: [
			"varying vec2 vUv;",
			"void main() {",
			" vUv = uv;",
			"	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );",
			"}"
		].join("\n"),
		fragmentShader: [
			"uniform vec2 scale;",
			"uniform vec2 scaleIn;",
			"uniform vec2 lensCenter;",
			"uniform vec4 hmdWarpParam;",
			'uniform vec4 chromAbParam;',
			"uniform sampler2D texid;",
			"varying vec2 vUv;",
			"void main()",
			"{",
			"  vec2 uv = (vUv*2.0)-1.0;", // range from [0,1] to [-1,1]
			"  vec2 theta = (uv-lensCenter)*scaleIn;",
			"  float rSq = theta.x*theta.x + theta.y*theta.y;",
			"  vec2 rvector = theta*(hmdWarpParam.x + hmdWarpParam.y*rSq + hmdWarpParam.z*rSq*rSq + hmdWarpParam.w*rSq*rSq*rSq);",
			'  vec2 rBlue = rvector * (chromAbParam.z + chromAbParam.w * rSq);',
			"  vec2 tcBlue = (lensCenter + scale * rBlue);",
			"  tcBlue = (tcBlue+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  if (any(bvec2(clamp(tcBlue, vec2(0.0,0.0), vec2(1.0,1.0))-tcBlue))) {",
			"    gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);",
			"    return;}",
			"  vec2 tcGreen = lensCenter + scale * rvector;",
			"  tcGreen = (tcGreen+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  vec2 rRed = rvector * (chromAbParam.x + chromAbParam.y * rSq);",
			"  vec2 tcRed = lensCenter + scale * rRed;",
			"  tcRed = (tcRed+1.0)/2.0;", // range from [-1,1] to [0,1]
			"  gl_FragColor = vec4(texture2D(texid, tcRed).r, texture2D(texid, tcGreen).g, texture2D(texid, tcBlue).b, 1);",
			"}"
		].join("\n")
	} );
};

PANA.ShaderMaterial.prototype = {
	contructor: PANA.ShaderMaterial
};