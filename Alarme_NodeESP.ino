#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define BTN_DIR  D5
#define BTN_MEIO D6
#define BTN_ESQ  D7

int colunas = 16;
int linhas  = 2;

int btnDirState  = 0;
int btnMeioState = 0;
int btnEsqState  = 0;

bool btnDirPressed = false;
bool btnMeioPressed = false;
bool btnEsqPressed = false;

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
  pinMode(BTN_ESQ,  INPUT);
  pinMode(BTN_MEIO, INPUT);
  pinMode(BTN_DIR,  INPUT);

  // mostra a tela de data e hora
  if(timeStatus() != timeNotSet) {
    telaPrincipal();
  }
}

void loop() {
  // le o estado dos botoes
  btnDirState  = digitalRead(BTN_DIR);
  btnMeioState = digitalRead(BTN_MEIO);
  btnEsqState  = digitalRead(BTN_ESQ);

  if(btnEsqState == HIGH) {
    btnDirPressed = false;
    btnMeioPressed = false;
    btnEsqPressed = true;
  } else if(btnMeioState == HIGH) {
    btnDirPressed = false;
    btnMeioPressed = true;
    btnEsqPressed = false;
  } else if(btnDirState == HIGH) {
    btnDirPressed = true;
    btnMeioPressed = false;
    btnEsqPressed = false;
  }

  if(btnEsqPressed) {
    // horario e data
    if(timeStatus() != timeNotSet) {
      telaPrincipal();
    }
  } else if(btnMeioPressed) {
    // alarme
    telaAlarme();
  } else if(btnDirPressed) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("IP:");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  } else {
    // horario e data
    if(timeStatus() != timeNotSet) {
      telaPrincipal();
    }
  }

  delay(1000);
}
