var http = require('http')

var server = http.createServer(function (req, res) {
    console.log("== A request was received")
    console.log('  - req.method:', req.method)
    console.log('  - req.url:', req.url)
    console.log('  - req.headers:', req.headers)

    res.statusCode = 200
    res.setHeader('Content-Type', 'text/html')

    if (req.url === '/cats') {
        res.write('<html>')
        res.write('<body>')
        res.write('<h1>Hello!</h1>')
        res.write('</body>')
        res.write('</html>')
    }

    res.end()
})

server.listen(8001, function () {
    console.log('== Server is listening on port 8001')
})