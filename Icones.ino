extern LiquidCrystal_I2C lcd;

byte Sound[8] = {
  0b00001,
  0b00011,
  0b00101,
  0b01001,
  0b01001,
  0b01011,
  0b11011,
  0b11000
};

byte Bell[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b00000,
  0b00100,
  0b00000
};

byte Relogio1[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00111,
  0b01000,
  0b10001,
  0b10001,
  0b10001
};

byte Relogio2[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b11000,
  0b00100,
  0b00010,
  0b00010,
  0b11010
};

byte Relogio3[8] = {
  0b10000,
  0b10000,
  0b01000,
  0b00111,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte Relogio4[8] = {
  0b00010,
  0b00010,
  0b00100,
  0b11000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
};

byte Sol[8] = {
	0b00100,
	0b10101,
	0b01110,
	0b11111,
	0b01110,
	0b10101,
	0b00100,
	0b00000
};

byte Lua[8] = {
	0b11100,
	0b01110,
	0b00111,
	0b00111,
	0b00111,
	0b01110,
	0b11100,
	0b00000
};

void criaIcones() {
  lcd.createChar(0, Sound);
  lcd.createChar(1, Bell);
  lcd.createChar(2, Relogio1);
  lcd.createChar(3, Relogio2);
  lcd.createChar(4, Relogio3);
  lcd.createChar(5, Relogio4);
  lcd.createChar(6, Sol);
  lcd.createChar(7, Lua);
}