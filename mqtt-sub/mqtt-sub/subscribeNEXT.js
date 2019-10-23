// subscribe de mqtt
const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883')
var request = require("request");
var referencia = '';
var distancia = '';
var nivel = '';
var umidade = '';

function relogio(){
  var today = new Date();
  var date = today.getFullYear()+'-'+(today.getMonth()+1)+'-'+today.getDate();
  var time = today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
  var dateTime = date+' '+time;
  return dateTime
}
setInterval(relogio, 1000);


client.on('connect', () => {
    //client.subscribe('teste/fiap')
    client.subscribe('esp/fiap/referencia')
    client.subscribe('esp/fiap/distancia')
    client.subscribe('esp/fiap/nivel')
    client.subscribe('esp/fiap/umidade')
  })

  client.on('message', (topic, message) => {
    if (topic == 'esp/fiap/referencia') {
        options.qs.referencia = message  
        referencia = message;
        console.log('Topico: %s Referencia: %s', topic, referencia)

    } else if (topic == 'esp/fiap/distancia') {
        options.qs.distancia = message
        distancia = message;
        console.log('Topico: %s Distancia: %s', topic, distancia)

    } else if (topic == 'esp/fiap/nivel') {
        options.qs.nivel = message
        nivel = message;
        console.log('Topico: %s Nivel: %s', topic, nivel)

    } else if (topic == 'esp/fiap/umidade') {
        options.qs.umidade_percentual = message
        umidade = message;
        console.log('Topico: %s Umidade: %s', topic, umidade)
        console.log(relogio())
        options.qs.timestamp = relogio()
    
        request(options, function (error, response, body) {
            if (error) throw new Error(error);
          
            console.log(body);
          });
    }
  })

  var options = { method: 'POST',
  url: 'https://projetop2001743368trial.hanatrial.ondemand.com/MQTT_DATA/DadosArduino.xsjs',
  qs: { },
  headers: 
   { 'Postman-Token': 'be651761-09ab-4bf4-bbca-62635adeff8a,20426ddd-4ccb-4506-8eca-c5f6a03006e0',
     'Cache-Control': 'no-cache',
     Authorization: 'Basic c3lzdGVtOlByb2pldG9maWFwMjAxOV8=' } };