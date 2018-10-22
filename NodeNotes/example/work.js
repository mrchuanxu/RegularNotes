// var http = require('http');
// http.createServer(function (req, res) {
//   res.writeHead(200, {
//     'Content-Type': 'text/plain'
//   });
//   res.end('hello,world');
// }).listen(Math.round(1 + Math.random() * 1000), '127.0.0.1');
// var n = 1;
// search:while(true){
//   n+=1;
//   for(var i = 2; i<= Math.sqrt(n); i+=1)
//       if(n%i == 0)
//           continue search;
//   postMessage(n);
// }
var http = require('http');
var server = http.createServer(function(req,res){
  res.writeHead(200,{'Content-Type':'text/plain'});
  res.end('handled by child,pid is'+process.pid + '\n');
});
process.on('message',function(m,tcp){
  if(m === 'server'){
    tcp.on('connection',function(socket){
      server.emit('connection',socket);
    });
  }
});
