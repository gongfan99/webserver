var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
	res.sendFile("./public/index.html");
	//res.render('index', { title: 'Express' });
});

router.get('/image/:imageId', function(req, res) {
  res.send("imageId is set to " + req.param("imageId"));
});

module.exports = router;
