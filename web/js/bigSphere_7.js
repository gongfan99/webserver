//http://learningthreejs.com/blog/2013/09/16/how-to-make-the-earth-in-webgl/
//http://blog.thematicmapping.org/2014/01/photo-spheres-with-threejs.html
require([
"js/three.min.js",
"js/async.js",
"js/Detector.js",
"js/pixastic.custom.js",
"js/OculusRiftEffect_2.js",
"js/postprocessing/EffectComposer.js",
"js/postprocessing/RenderPass.js",
"js/postprocessing/ShaderPass.js",
"js/postprocessing/MaskPass.js",
"js/shaders/CopyShader.js"], function(){
	var xx = THREE.Math.radToDeg(Math.PI);
	console.log(xx);
})