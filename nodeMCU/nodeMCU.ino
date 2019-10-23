/*
 * Projeto: Recepção de leituras analógicas pela serial e envio das mesmas por MQTT
 * Autor: FilipeFlop e Pedro Bertoleti
 * Data: Janeiro/2018
 */
#include<SoftwareSerial.h>
#include <ESP8266WiFi.h> // Importa a Biblioteca ESP8266WiFi
#include <PubSubClient.h> // Importa a Biblioteca PubSubClien
 
//defines:
//defines de id mqtt e tópicos para publicação e subscribe
#define TOPICO_REF   "esp/fiap/referencia"
#define TOPICO_DIST   "esp/fiap/distancia"
#define TOPICO_NIV   "esp/fiap/nivel"
#define TOPICO_UMI   "esp/fiap/umidade"

#define ID_MQTT  "NodeMCU-FIAP-NEXT"
 
// WIFI
const char* SSID = ""; // SSID / nome da rede WI-FI que deseja se conectar
const char* PASSWORD = ""; // Senha da rede WI-FI que deseja se conectar
  
// MQTT
const char* BROKER_MQTT = ""; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT
 
//Variáveis e objetos globais
WiFiClient espClient; // Cria o objeto espClient
PubSubClient MQTT(espClient); // Instancia o Cliente MQTT passando o objeto espClient
String referencia;
String distancia;
String nivel;
String umidade;
char ref[20];
char dist[20];
char niv[20];
char umi[20];

SoftwareSerial SUART(4, 5); //SRX=Dpin-D2; STX-DPin-D1

//Prototypes
void initSerial(void);
void initWiFi(void);
void initMQTT(void);
void reconectWiFi(void); 
void VerificaConexoesWiFIEMQTT(void);
bool VerificaSeHaInformacaoNaSerial(void);
void EnviaInformacoesMQTT(void);
 
/*
 * Implementações
 */
 
//Função: inicializa e conecta-se na rede WI-FI desejada
void initWiFi() 
{
    delay(10);
    reconectWiFi();
}
  
//Função: inicializa parâmetros de conexão MQTT(endereço do broker e porta)
void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
}
 
//Função: reconecta-se ao broker MQTT (caso ainda não esteja conectado ou em caso de a conexão cair)
void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        if (MQTT.connect(ID_MQTT)) 
          break;
        else
        {
            //aguarda 2 segundos e tenta se conectar novamente.
            delay(2000);
        }
    }
}
  
//Função: reconecta-se ao WiFi
void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
        delay(100);  
}
 
 
 
//Função: verifica o estado das conexões WiFI e ao broker MQTT. 
//        Em caso de desconexão (qualquer uma das duas), a conexão é refeita.
void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}
 
//Função: verifica se há informações sendo recebidas na serial.
bool VerificaSeHaInformacaoNaSerial(void)
{
  byte n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0)
  {
    referencia = SUART.readStringUntil(';');
    referencia.toCharArray(ref, 50);
    distancia = SUART.readStringUntil(';');
    distancia.toCharArray(dist, 50);
    nivel = SUART.readStringUntil(';');
    nivel.toCharArray(niv, 50);
    umidade = SUART.readStringUntil(';');
    umidade.toCharArray(umi, 50);
    return true;
  }
}
 
//Função: envia informações recebidas pela serial por MQTT
//Parâmetros: nenhum
//Retorno: nenhum
void EnviaInformacoesMQTT(void)
{
  MQTT.publish(TOPICO_REF, ref);
  MQTT.publish(TOPICO_DIST, dist);
  MQTT.publish(TOPICO_NIV, niv);
  MQTT.publish(TOPICO_UMI, umi);
}
 
void setup() 
{
    Serial.begin(115200);
    SUART.begin(115200);
    initWiFi();
    initMQTT();
}
 
void loop() 
{
  //garante funcionamento das conexões WiFi e ao broker MQTT
  VerificaConexoesWiFIEMQTT();
   
  //se recebeu informações pela serial, as envia por MQTT
  if (VerificaSeHaInformacaoNaSerial() == true)
    EnviaInformacoesMQTT();
 
  //keep=alive do MQTT
  MQTT.loop();  
}
