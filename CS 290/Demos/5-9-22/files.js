var fs = require('fs')

//asynchronous
fs.readFile('./lib/circle.js', 'utf8', function (err, data) {
    if (err) {
        throw err
    } else {
        console.log('== file contents:', data)
    }
})

//readFileSync for synchronous

var four = 2 + 2
console.log(' == four:', four)