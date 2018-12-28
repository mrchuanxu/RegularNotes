let net = require('net');

let client = net.createConnection(
    {   
        host:'10.7.1.235',
        port: 1024 
    },
    (socket) => {
        //'connect' listener
        console.log('成功连接到TCP服务器...');
        console.log(socket)
        client.write('这条消息来自于客户端...!\r\n');
      }
)
client.on('error',err=>{
    console.log('连接失败')
})
client.on('data', (data) => {
    console.log('客户端收到了消息：'+ data.toString());
    client.end();
  });
  client.on('end', () => {
    console.log('disconnected from server');
  });


