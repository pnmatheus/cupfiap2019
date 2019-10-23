//biblitecas  
#include<Servo.h> 
#include<SoftwareSerial.h>

SoftwareSerial SUART(2, 3); //SRX  = DPin-2; STX = DPin-3

//defines
#define analogUmi A0
#define analogDist A1
#define SERVO_1 11
#define SERVO_2 10
#define nivel 7

//pinos
Servo s1;
Servo s2;

//variaveis globais
int pos;
String distancia;
float valorVolts; 
String estadoNivel;
String UmidadePercentual;

//prototipos
String leDistancia(void);
String leituraNivel(void);
String leUmidade(void);
void ref1();
void ref2();
void ref3();
void ref4();
void ref5();

String leUmidade(void) {
  int valorUmi = analogRead(analogUmi);
  
  UmidadePercentual = 100 * ((1023-(float)valorUmi) / 1023);
  //SUART.print("Umidade Percentual: ");
  //SUART.print(UmidadePercentual);
  //SUART.println("%");
  return UmidadePercentual;
}

String leituraNivel(void) {
  int estadoNivel = digitalRead(nivel);
  String estado = "";
  if(estadoNivel == 1){
    //UART.println("Barragem cheia");
    return "1";
  } else {
    //SUART.println("Barragem em nivel normal!");
    return "0";
  }
}
String leDistancia(void) {
  
  //Obtenção do valor em Volts através da formula ( valorAnalógico * (5/1023)
   valorVolts = analogRead(analogDist) * 0.0048828125; 

   distancia = 26*pow(valorVolts, -1); //equação de acordo com a grafico do datasheet

   return distancia;
}

void ref1() {
  for (pos = 100; pos > 75; pos--){
    s1.write(pos);
    delay(15);
  }
  for (pos = 100; pos > 79; pos--) {
    s2.write(pos);
    delay(15);
  }

  SUART.print("1");
  SUART.print(";");
  SUART.print(leDistancia());
  SUART.print(";"); 
  SUART.print(leituraNivel());
  SUART.print(";"); 
  SUART.print(leUmidade()); 
  SUART.print(";"); 
  delay(3000);
  
  //volta para o posição inicial
    for (pos = 75; pos < 100; pos++){
    s1.write(pos);
    delay(15);
  }
  for (pos = 79; pos < 100; pos++) {
    s2.write(pos);
    delay(15);
  }
}

void ref2() {
  for (pos = 90; pos < 115; pos++) {
    s1.write(pos);
    delay(15);
  }
  for (pos = 100; pos > 67; pos--) {
    s2.write(pos);
    delay(15);
  }
  
    //medição
    SUART.print("2");
    SUART.print(";");
    SUART.print(leDistancia());
    SUART.print(";"); 
    SUART.print(leituraNivel());
    SUART.print(";"); 
    SUART.print(leUmidade()); 
    SUART.print(";"); 
    delay(3000);
  
    //volta para o posição inicial
  for (pos = 115; pos > 88; pos--){
    s1.write(pos);
    delay(15);
  }
  for (pos = 67; pos < 100; pos++) {
    s2.write(pos);
    delay(15);
  }
}

void ref3() {
    //medição
    SUART.print("3");
    SUART.print(";");
    SUART.print(leDistancia());
    SUART.print(";"); 
    SUART.print(leituraNivel());
    SUART.print(";"); 
    SUART.print(leUmidade()); 
    SUART.print(";"); 
    delay(3000);
}

void ref4() {
  for (pos = 100; pos > 75; pos--) {
    s1.write(pos);
    delay(15);
  }
  for (pos = 100; pos < 124; pos++) {
    s2.write(pos);
    delay(15);
  }
  //medição
  SUART.print("4");
  SUART.print(";");
  SUART.print(leDistancia());
  SUART.print(";"); 
  SUART.print(leituraNivel());
  SUART.print(";"); 
  SUART.print(leUmidade()); 
  SUART.print(";");
  delay(3000);
  
   //volta para o posição inicial
  for (pos = 75; pos < 100; pos++) {
    s1.write(pos);
    delay(15);
  }
  for (pos = 124; pos > 100; pos--) {
    s2.write(pos);
    delay(15);
  }
}

void ref5() {
  for (pos = 90; pos < 112; pos++) {
    s1.write(pos);
    delay(15);
  }
  for (pos = 100; pos < 130; pos++) {
    s2.write(pos);
    delay(15);
  }
    //medição
  SUART.print("5");
  SUART.print(";");
  SUART.print(leDistancia());
  SUART.print(";"); 
  SUART.print(leituraNivel());
  SUART.print(";"); 
  SUART.print(leUmidade()); 
  SUART.print(";");
  delay(3000);
  
    //volta para o posição inicial
  for (pos = 112; pos > 100; pos--){
    s1.write(pos);
    delay(15);
  }
  for (pos = 130; pos > 100; pos--) {
    s2.write(pos);
    delay(15);
  }
}

void setup() {
  Serial.begin(115200);
  SUART.begin(115200);
  pinMode(nivel, INPUT);
  pinMode(analogDist, INPUT);
  pinMode(analogUmi, INPUT);
  s1.attach(SERVO_1);
  s2.attach(SERVO_2);
  s1.write(100);
  s2.write(100);
}

void loop() {
  ref1();
  delay(500);
  ref2();
  delay(500);
  ref3();
  delay(500);
  ref4();
  delay(500);
  ref5();
  delay(500);
}
