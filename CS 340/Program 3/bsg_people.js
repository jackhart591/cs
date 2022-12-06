var express = require('express');
var mysql = require('./dbcon.js');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 8000);

app.get('/',function(req,res,next){
  let empResults = [];
  let projResults = [];
  
  mysql.pool.query('SELECT * FROM EMPLOYEE', function(err, rows, fields) {
    for(let i = 0; i < rows.length; i++) {
      empResults[i] = rows[i];
    }
  
    mysql.pool.query('SELECT * FROM PROJECT', function(err, rows, fields) {
      for (let i = 0; i < rows.length; i++) {
        projResults[i] = rows[i];
      }

      res.render('displayTable',{data: empResults, projects: projResults});
    });
  });
});

app.get('/filter/:project', function (req, res) {
  let empResults = [];
  let projResults = [];
  
  mysql.pool.query(`SELECT * FROM EMPLOYEE INNER JOIN WORKS_ON ON Ssn=Essn WHERE ${req.params.project}=Pno`, function(err, rows, fields) {
    for(let i = 0; i < rows.length; i++) {
      empResults[i] = rows[i];
    }
  
    mysql.pool.query('SELECT * FROM PROJECT', function(err, rows, fields) {
      for (let i = 0; i < rows.length; i++) {
        projResults[i] = rows[i];
      }

      res.status(200).render('displayTable',{data: empResults, projects: projResults});
    });
  });
})

app.use(express.static('public'))

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

// mysql.pool.query(`SELECT * FROM EMPLOYEE INNER JOIN WORKS_ON ON Ssn=Essn WHERE ${filterDD.value}=Pno`, function (err, rows, fields) {
//   for(let i = 0; i < rows.length; i++) {
//     empResults[i] = rows[i];
//   }
  
//   location.reload()
// })