var express = require('express');
var router = express.Router();

var mysql      = require('mysql');
var connection = mysql.createConnection({
	host     : 'localhost',
	port	 : '3306',
	user     : 'sanf',
	password : '123456',
	database: 'PANA'
});

connection.connect();

/* GET home page. */
router.get('/', function(req, res) {
	res.sendFile("./public/index.html");
	//res.render('index', { title: 'Express' });
});

router.get('/image/:imageId', function(req, res) {
	if (connection.threadId) {
		connection.query('SELECT url FROM image WHERE ' + 'id=' + req.params.imageId.toString(),function(err, rows, fields) {
			if (err) {
				res.send();
				throw err;
			} else if (rows.length !== 0) {
				res.send(rows[0].url);
				console.log('The image url is: ', rows[0].url);
			} else if (rows.length === 0) {
				res.send();
				console.log('Image is not found in database.');
			}
		});
	} else {
		res.send('images/Earthmap720x360_grid.jpg');
	}
});

module.exports = router;
