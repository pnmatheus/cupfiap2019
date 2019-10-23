// subscribe de mqtt
const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883')

var request = require("request");
var mensagem = '';

client.on('connect', () => {
    client.subscribe('teste/fiap')
  })

  client.on('message', (topic, message) => {
    mensagem = message;
    console.log('received message %s %s', topic, mensagem)
    options.qs.menssagem = mensagem;
    request(options, function (error, response, body) {
        options.qs = mensagem;
        if (error) throw new Error(error);
      
        console.log(body);
      });
  })

var options = { method: 'POST',
  url: 'https://databasetestenop2001657401tria.hanatrial.ondemand.com/teste-mensagens/teste.xsjs',
  qs: { },
  headers: 
   { 'Postman-Token': 'fb0bb737-c7f7-4f15-9ac3-fab19e44af8a,0e57bdcc-fb99-430c-98cb-61672f3c4cc3',
     'Cache-Control': 'no-cache',
     Authorization: 'Basic c3lzdGVtOlByb2pldG9maWFwMjAxOV8=' } };