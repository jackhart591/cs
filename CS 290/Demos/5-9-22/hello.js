console.log('Hello World!')

console.log('== proces.env.USER:', process.env.USER)
console.log("== process.env.SOME_ENV_VAR:", process.env.SOME_ENV_VAR)

console.log("== __dirname:", __dirname)

var circle = require('./lib/circle')
console.log("== circle:", circle)
console.log("== circle.area(5):", circle.area(5))
console.log("== circle.circumference(5):", circle.circumference(5))