var express = require('express');
var mysql = require('./dbcon.js');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 8000);

app.get('/',function(req,res,next){
  var context = {};
  let empResults = [];

  mysql.pool.query('SELECT * FROM EMPLOYEE', function(err, rows, fields) {
//	context.results = JSON.stringify(rows);

    console.log(typeof(rows));

    for(let i = 0; i < rows.length; i++) {
      empResults[i] = rows[i];
    }

	res.render('displayTable',{data: empResults});
	});

});

app.use(function(req,res){
  res.status(404);
  res.render('404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.status(500);
  res.render('500');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
