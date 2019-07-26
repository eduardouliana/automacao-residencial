// Biblioteca do Esp8266
#include <ESP8266WiFi.h>
// Biblioteca do firebase
#include <FirebaseArduino.h>
// Biblioteca de conversão de JSON
#include <ArduinoJson.h>

// URL do Firebase SEM o "HTTPS" e SEM A BARRA "/" no final
#define FIREBASE_HOST "*********.firebaseio.com"
// Key do Firebase
#define FIREBASE_AUTH "hLo5v06E**************rdQNYRUvop"
// Nome da rede Wifi
#define WIFI_SSID "CASA_GELADA"
// Senha do Wifi
#define WIFI_PASSWORD "*************"

// Define em qual pino está conectado
int pinoPorta = D6;
int pinoLuzes = D7;

// Pinos para led RGB
int pinoRGBAzul = D1;
int pinoRGBVerde = D2;
int pinoRGBVermelho = D3;

// Variáveis para ler do Firebase
String statusPorta = "";
String statusLuzes = "";
String statusPortaANT = "";
String statusLuzesANT = "";

String corRGB = "";

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  // Define os pinos como saída
  pinMode(pinoPorta, OUTPUT);
  pinMode(pinoLuzes, OUTPUT); 
  // RGB
  pinMode(pinoRGBAzul, OUTPUT);
  pinMode(pinoRGBVerde, OUTPUT);
  pinMode(pinoRGBVermelho, OUTPUT);                

  // Tenta conectar com Wifi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectando com: ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Falha, tentando novamente!");
    delay(500);
  }
  Serial.println();
  Serial.print("Conectado com: ");
  Serial.println(WIFI_SSID);
  Serial.print("IP da placa : ");
  Serial.println(WiFi.localIP()); 
  
  // Conecta com o Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  //Firebase.setString("LED_STATUS", "OFF");
}

void loop() {
  // Lê o status do Firebase
  statusPortaANT = statusPorta;
  statusLuzesANT = statusLuzes;
  statusPorta = Firebase.getString("STATUS_PORTA");
  statusLuzes = Firebase.getString("STATUS_LUZES");

  corRGB = Firebase.getString("COR_RGB");

  // Verifica se é para abrir a porta
  if (statusPorta != statusPortaANT) {  
    if (statusPorta == "ABRIR") {
      abrirPorta();
    } else {
      fecharPorta();
    }
  }
  // Verifica se é para ligar as luzes
  if (statusLuzes != statusLuzesANT) {  
    if (statusLuzes == "LIGAR") {
      ligarLuzes();
    } else {
      desligarLuzes();
    }
  }

  if (corRGB == "VERMELHO") {
    ligarRGBVermelho();
  } else if (corRGB == "AZUL") {
    ligarRGBAzul();
  } else if (corRGB == "VERDE") {
    ligarRGBVerde();
  } else if (corRGB == "AMARELO") {
    ligarRGBAmarelo();
  } else if (corRGB == "ROXO") {
    ligarRGBRoxo();
  } else if (corRGB == "BRANCO") {
    ligarRGBBranco();
  } else if (corRGB == "DESLIGAR") {
    desligarRGB();
  }
}

void abrirPorta() {
  Serial.println("Abrindo porta...");
  digitalWrite(pinoPorta, HIGH);
}

void fecharPorta() {
  Serial.println("Fechando porta...");
  digitalWrite(pinoPorta, LOW);
}

void ligarLuzes() {
  Serial.println("Ligando luzes...");
  digitalWrite(pinoLuzes, HIGH);
}

void desligarLuzes() {
  Serial.println("Desligando luzes...");
  digitalWrite(pinoLuzes, LOW);
}

void ligarRGBVermelho(){
  digitalWrite(pinoRGBAzul, LOW);
  digitalWrite(pinoRGBVerde, LOW);
  digitalWrite(pinoRGBVermelho, HIGH);
}

void ligarRGBAzul(){
  digitalWrite(pinoRGBAzul, HIGH);
  digitalWrite(pinoRGBVerde, LOW);
  digitalWrite(pinoRGBVermelho, LOW);
}

void ligarRGBVerde(){
  digitalWrite(pinoRGBAzul, LOW);
  digitalWrite(pinoRGBVerde, HIGH);
  digitalWrite(pinoRGBVermelho, LOW);
}

void ligarRGBAmarelo(){
  analogWrite(pinoRGBAzul, 0);
  analogWrite(pinoRGBVerde, 50);
  analogWrite(pinoRGBVermelho, 255);
}

void ligarRGBRoxo(){
  analogWrite(pinoRGBAzul, 207);
  analogWrite(pinoRGBVerde, 0);
  analogWrite(pinoRGBVermelho, 255);
}

void ligarRGBBranco(){
  digitalWrite(pinoRGBAzul, HIGH);
  digitalWrite(pinoRGBVerde, HIGH);
  digitalWrite(pinoRGBVermelho, HIGH);
}

void desligarRGB(){
  digitalWrite(pinoRGBAzul, LOW);
  digitalWrite(pinoRGBVerde, LOW);
  digitalWrite(pinoRGBVermelho, LOW);
}
