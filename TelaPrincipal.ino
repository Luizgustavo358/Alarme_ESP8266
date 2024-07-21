extern LiquidCrystal_I2C lcd;

void telaPrincipal() {
  char buffer[20];
  time_t time = now();

  lcd.clear();

  Serial.println("Tela Principal");
  
  // icone relogio
  lcd.setCursor(0, 0);
  lcd.write(2);
  lcd.setCursor(1, 0);
  lcd.write(3);
  lcd.setCursor(0, 1);
  lcd.write(4);
  lcd.setCursor(1, 1);
  lcd.write(5);

  // hora
  lcd.setCursor(3, 0);
  lcd.print("Hora: ");
  sprintf(buffer, "%02d:%02d", hour(time), minute(time));
  lcd.setCursor(9, 0);
  lcd.print(buffer);

  lcd.setCursor(15, 0);

  // icone de manha/noite
  if(hour(time) > 12) {
    lcd.write(7);
  } else {
    lcd.write(6);
  }

  // data
  sprintf(buffer, "%02d/%02d/%02d", day(time), month(time), year(time));
  lcd.setCursor(3, 1);
  lcd.print(buffer);
}