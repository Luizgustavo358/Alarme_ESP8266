extern LiquidCrystal_I2C lcd;

// WiFi
const char* ssid = "SSID";
const char* password = "PASSWORD";

byte Wifi1[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b10000,
	0b00000
};

byte Wifi2[8] = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11000,
	0b00100,
	0b10100,
	0b00000
};

byte Wifi3[8] = {
	0b00000,
	0b00000,
	0b11100,
	0b00010,
	0b11001,
	0b00101,
	0b10101,
	0b00000
};

void conectaNaInternet() {
  int i = 12;

  WiFi.begin(ssid, password);

  Serial.print("Conectando a Rede: ");
  Serial.println(ssid);

  // nome do wifi
  lcd.setCursor(0, 0);
  lcd.print(ssid);

  // criando icone do wifi
  lcd.createChar(0, Wifi1);
  lcd.createChar(1, Wifi2);
  lcd.createChar(2, Wifi3);

  lcd.setCursor(2, 1);
  lcd.print("Conectando");

  while(WiFi.status() != WL_CONNECTED) {
    delay(500);

    // icone do wifi
    lcd.setCursor(0, 1);
    lcd.write(0);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.write(1);
    delay(500);
    lcd.setCursor(0, 1);
    lcd.write(2);
    delay(500);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Finalmente");
  lcd.setCursor(0, 1);
  lcd.print("Conectado!");
  Serial.println("WiFi conectado");
  Serial.println("Endereço IP: ");
  Serial.println(WiFi.localIP());

  delay(1000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("IP:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());

  delay(1000);
}