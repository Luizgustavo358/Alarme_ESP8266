extern LiquidCrystal_I2C lcd;

void telaAlarme() {
  Serial.println("Tela Alarme");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(2, 0);
  lcd.print("Alarme");
}