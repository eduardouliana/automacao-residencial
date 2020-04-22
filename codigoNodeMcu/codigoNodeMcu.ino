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

// Variáveis para ler do Firebase
String statusPorta = "";
String statusLuzes = "";
String statusPortaANT = "";
String statusLuzesANT = "";

void setup() {
  Serial.begin(9600);
  delay(1000);
  
  // Define os pinos como saída
  pinMode(pinoPorta, OUTPUT);
  pinMode(pinoLuzes, OUTPUT);           

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
  
  // Caso queira gravar dados no firebase
  //Firebase.setString("LED_STATUS", "OFF");
}

void loop() {
  // Lê o status do Firebase
  statusPortaANT = statusPorta;
  statusLuzesANT = statusLuzes;
  statusPorta = Firebase.getString("STATUS_PORTA");
  statusLuzes = Firebase.getString("STATUS_LUZES");

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
