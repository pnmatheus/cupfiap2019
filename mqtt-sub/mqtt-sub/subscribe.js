// subscribe de mqtt
const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883')
var mensagem = '';


client.on('connect', () => {
    client.subscribe('teste/fiap')
  })

  client.on('message', (topic, message) => {
    mensagem = message;
    console.log('received message %s %s', topic, mensagem)
  })