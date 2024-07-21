extern LiquidCrystal_I2C lcd;

void telaAlarme() {
  time_t time = now();
  char buffer[20];

  Serial.println("Tela Alarme");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(2, 0);
  lcd.print("Alarme");

  lcd.setCursor(0, 1);
  sprintf(buffer, "%02d:%02d %02d/%02d/%02d", hour(time), minute(time), day(time), month(time), year(time));
  lcd.print(buffer);

  lcd.setCursor(0, 1);
  lcd.cursor();
}