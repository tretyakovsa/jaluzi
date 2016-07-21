// Выполняется при нажатии на кнопку
void Tach_0() {
  static unsigned long millis_prev;
  // Устроняем дребезг контакта
  if (millis() - 100 > millis_prev) {
    chaing = 1; // Выстовляем признак нажатия кнопки
  }
  millis_prev = millis();
}

void MotorUp() {
  digitalWrite(Led1, HIGH);
  digitalWrite(Led2, LOW);
  tickerSetLow.attach(TimeServo2, setUp, 0);
  Serial.println("Up");
  myservo.write(kolibr+speed);
  chaing = LOW;
  chaing1 = 1;
}
void MotorDown() {
  digitalWrite(Led2, HIGH);
  digitalWrite(Led1, LOW);
  tickerSetLow.attach(TimeServo, setDown, 0);
  Serial.println("Down");
  myservo.write(kolibr-speed);
  chaing = LOW;
  chaing1 = 1;
}

void setUp(int state) {
  tickerSetLow.detach();
  digitalWrite(Led1, state);
  state0 = !state0;
  chaing = LOW;
  chaing1 = 0;
  myservo.write(kolibr);
}
void setDown(int state) {
  tickerSetLow.detach();
  digitalWrite(Led2, state);
  state0 = !state0;
  chaing = LOW;
  chaing1 = 0;
  myservo.write(kolibr);
}
