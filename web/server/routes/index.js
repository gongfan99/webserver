var express = require('express');
var router = express.Router();

var mysql      = require('mysql');
var connection = mysql.createConnection({
	host     : 'localhost',
	user     : 'me',
	password : 'secret'
});

connection.connect();



/* GET home page. */
router.get('/', function(req, res) {
	res.sendFile("./public/index.html");
	//res.render('index', { title: 'Express' });
});

router.get('/image/:imageId', function(req, res) {
	connection.query('SELECT path FROM image', function(err, rows, fields) {
		if (err) throw err;
		console.log('The image path is: ', rows[0].path);
		res.send(rows[0].path);
	});
});

module.exports = router;
