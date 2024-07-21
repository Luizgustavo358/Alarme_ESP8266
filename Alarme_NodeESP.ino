#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// botoes
#define BTN_LEFT  D3
#define BTN_UP    D4
#define BTN_DOWN  D5
#define BTN_RIGHT D6
#define BTN_OK    D7
#define BTN_CANC  D8

// configuracao do LCD
int colunas = 16;
int linhas  = 2;

// estados dos botoes
int btnLeftState  = 0;
int btnUpState    = 0;
int btnDownState  = 0;
int btnRightState = 0;
int btnOkState    = 0;
int btnCancState  = 0;

// botoes pressionados
bool btnLeftPressed  = false;
bool btnUpPressed    = false;
bool btnDownPressed  = false;
bool btnRightPressed = false;
bool btnOkPressed    = false;
bool btnCancPressed  = false;

// NTP Server
const char* NTP_SERVER = "pool.ntp.org";
const int timeZone = -3;

WiFiUDP Udp;
unsigned int localPort = 8888;  // Porta local a ser usada para a conexao UDP

IPAddress ntpServerIP;

// inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, colunas, linhas);

// prototipo funcoes externas
extern void criaIcones();
extern void conectaNaInternet();
extern void configNTP();
extern void telaPrincipal();
extern void telaAlarme();

// prototipo icones
extern byte Sound[8], Bell[8], Speaker[8], 
            Plus[8], Minus[8], Relogio[8], 
            Relogio1[8], Relogio2[8],
            Relogio3[8], Relogio4[8];

void ligaLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void setup() {
  Serial.begin(115200);
  delay(10);

  ligaLCD();
  conectaNaInternet();
  configNTP();
  criaIcones();

  // inicializando os botoes
  pinMode(BTN_LEFT,  INPUT);
  pinMode(BTN_UP,    INPUT);
  pinMode(BTN_DOWN,  INPUT);
  pinMode(BTN_RIGHT, INPUT);
  pinMode(BTN_OK,    INPUT);
  pinMode(BTN_CANC,  INPUT);

  // mostra a tela de data e hora
  if(timeStatus() != timeNotSet) {
    telaPrincipal();
  }
}

void loop() {
  lcd.noCursor();

  // le o estado dos botoes
  btnOkState   = digitalRead(BTN_OK);
  btnCancState = digitalRead(BTN_CANC);

  if(btnOkState == HIGH) {
    btnOkPressed   = true;
    btnCancPressed = false;
  } else if(btnCancState == HIGH) {
    btnOkPressed   = false;
    btnCancPressed = true;
  }

  if(btnOkPressed) {
    // horario e data
    if(timeStatus() != timeNotSet) {
      telaPrincipal();
    }
  } else if(btnCancPressed) {
    // alarme
    telaAlarme();
  } else {
    // horario e data
    if(timeStatus() != timeNotSet) {
      telaPrincipal();
    }
  }

  delay(1000);
}
