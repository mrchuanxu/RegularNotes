// var fork = require('child_process').fork;
// var cpus = require('os').cpus();
// for(var i = 0;i<cpus.length;i++){
//   fork('./work.js');
// }

// var worker = new Worker('./work.js');
// worker.onmessage = function(event){
//   document.getElementById('result').textContent = event.data;
// }

var child = require('child_process');
var child1 = child.fork('./work.js');
var child2 = child.fork('./work.js');
var server = require('net').createServer();
// server.on('connection',function(socket){
//   socket.end('handled by parent\n');
// });
server.listen(1337,function(){
  console.log("listen:1337");
  child2.send('server',server);
  child1.send('server',server);
  server.close();
});
