var express = require('express')
var app = express()

app.use((req, res, next) => {
    console.log("== Request Received")
    console.log("  - Method:", req.method)
    console.log("  - Headers:", req.headers)
    console.log("  - Url:", req.url)

    next()
})

// Does something
//app.use(express.static(__dirname + '/public'))

app.get('/about/people', (req, res, next) => {
    //res.status(200)
    res.status(200).send("<h1>About People</h1>")
})

app.get(['/', '/home'], (req, res, next) => {
    res.status(200).send("<h1>Home</h1>")
})

app.get('/dictionary/:word/:tense', (req, res, next) => {
    var word = req.params.word
    var tense = req.params.tense

    res.status(200).send("<h1>Definition for '" + word + "'</h1>")
})

// app.post(
// app.delete()
// app.patch()

// * acts as wildcard
// has to go at end or else it will always be loaded
app.get('*', (req, res, next) => {
    res.status(404).send('<h1>404</h1>')
})

app.listen(8001, function () {
    console.log('>> Server listening on port 8001.')
})