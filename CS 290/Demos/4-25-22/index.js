console.log ("Hellowo, world!")

console.log("====================")
console.log("=== Variables")
console.log("====================\n")

var n = 16
console.log("=== n:", n)
console.log("typeof(n):", typeof(n))

n = "This is a string"
console.log("=== n:", n)
console.log("typeof(n):", typeof(n))

console.log("====================")
console.log("=== Numbers")
console.log("====================\n")

var n1 = 4
var n2 = 8.0

//these will just be "numbers", so all integers and floats are numbers
console.log("typeof(n1):", typeof(n1))
console.log("typeof(n2):", typeof(n2))
console.log("== n2 / n1: ", n2 / n1)

console.log("====================")
console.log("=== Comparisons")
console.log("====================\n")

var twoNum = 2
var threeNum = 3
var twoStr = "2"
console.log("== twoNum == threeNum:", twoNum == threeNum)
console.log("== twoNum == twoStr:", twoNum == twoStr)
console.log("== twoNum === twoStr:", twoNum === twoStr) //Strict equality operator
/* There's also inequality and strict inequality operators like you'd expect */

console.log("====================")
console.log("=== Strings")
console.log("====================\n")

var greeting = "'Hello',"
var name = 'CS "290"' // "" and '' mean the same thing
var longStr = greeting + " " + name

console.log(longStr)
console.log("This is a number:", 123)
console.log("name[1]:", name[1])
name[1] = 'x'
console.log("name[1]", name[1])

decatholon = "decatholon"
console.log("decatholon.indexOf('cat'):", decatholon.indexOf('cat'))

affection = "I love dogs"
console.log("affection.replace('dog', 'cat')", affection.replace('dog', 'cat'))

console.log("====================")
console.log("=== Functions")
console.log("====================\n")

function YouABitch() {
    console.log("Inside you!")
}

YouABitch()

function sum(a = 0, b = 0, c = 0) {
    return a + b + c
}

function higherOrderFn(fnArg) {
    console.log("Inside higherOrderFn:", fnArg)
    fnArg()
}

console.log(sum(23, 23, 23))
console.log(sum("23", "23", 23))

//functions are just data types so you can store and pass them
higherOrderFn(function() {
    console.log("This is an anonymous function")
})

console.log("====================")
console.log("=== Array")
console.log("====================\n")

var array = [23, 23, 23]

array.forEach(function (elem, idx) {
    console.log(" - elem:", elem, " - idx:", idx)
})