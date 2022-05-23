var express = require('express');
var exphbs = require('express-handlebars')

var peopleData = require('./peopleData.json')

var port = process.env.PORT || 8000;
var app = express();

// tells it that we're using .handlebars as our templating engine
app.engine('handlebars', exphbs.engine({ defaultLayout: null }))
app.set('view engine', 'handlebars')

//npm install --save-dev nodemon
//npm run dev
//Check package.json to see what I changed

app.use(express.static('public'));

app.get('/people', function (req, res, next) {
  res.status(200).sendFile(__dirname + '/public/people.html');
});

// var availablePeople = [
//   'luke',
//   'leia',
//   'rey',
//   'finn',
//   'r2d2'
// ];

app.get('/people/:person', function (req, res, next) {
  var person = req.params.person.toLowerCase();
  var personData = peopleData[person]
  if (personData) {
    res.status(200).render('photoPage', personData)
  } else {
    next()
  }


  // res.status(200).render('photoPage', {
  //   renderTitleContainer: true,
  //   name: "Princess Leia",
  //   photos: [
  //     {
  //       url: "http://placekitten.com/480/480?image=1",
  //       caption: "Leia as a cat #1"
  //     },

  //     {
  //       url: "http://placekitten.com/480/480?image=2",
  //       caption: "Leia as a cat #2"
  //     },

  //     {
  //       url: "http://placekitten.com/480/480?image=3",
  //       caption: "Leia as a cat #3"
  //     }
  //   ]
  // })
  // if (availablePeople.indexOf(person) >= 0) {
  //   res.status(200).sendFile(
  //     __dirname + '/public/people/' + person + '.html'
  //   );
  // } else {
  //   next();
  // }
});

app.get("*", function (req, res, next) {
  res.status(404).sendFile(__dirname + '/public/404.html');
});

app.listen(port, function (err) {
  if (err) {
    throw err;
  }
  console.log("== Server listening on port", port);
});
