var fs = require('fs')
var express = require('express')
var exphbs = require('express-handlebars')

var peopleData = require('./peopleData.json')

var app = express()
var port = process.env.PORT || 8000

app.engine('handlebars', exphbs.engine({ defaultLayout: 'main' }))
app.set('view engine', 'handlebars')

app.use(express.json())

app.use(express.static('public'))

app.get('/', function (req, res, next) {
  res.status(200).render('homePage')
})

app.get('/people', function (req, res, next) {
  res.status(200).render('peoplePage', {
    people: peopleData
  })
})

app.get('/people/:person', function (req, res, next) {
  var person = req.params.person.toLowerCase()
  if (peopleData[person]) {
    res.status(200).render('photoPage', peopleData[person])
  } else {
    next()
  }
})

app.post('/people/:person/addPhoto', function (req, res, next) {
  var person = req.params.person.toLowerCase()
  if (peopleData[person]) {
    console.log("  - req.body:", req.body)
    if (req.body && req.body.url && req.body.caption) {
      peopleData[person].photos.push({
        caption: req.body.caption,
        url: req.body.url
      })
      console.log("  - peopleData[" + person + "]:", peopleData[person])
      fs.writeFile(
        "./peopleData.json",
        JSON.stringify(peopleData, null, 2),
        function (err) {
          if (!err) {
            res.status(200).send()
          } else {
            res.status(500).send("Error: error saving photo card")
          }
        }
      )
    } else {
      res.status(400).send("Error: request body needs a 'url' and 'caption'")
    }
  } else {
    next()
  }
})

app.get('*', function (req, res, next) {
  res.status(404).render('404', {
    page: req.url
  })
})

app.listen(port, function () {
  console.log("== Server listening on port", port)
})
