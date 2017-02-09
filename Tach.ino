// Выполняется при нажатии на кнопку
void Tach_0() {
  static unsigned long millis_prev;
  // Устроняем дребезг контакта
  if (millis() - 300 > millis_prev) {
    chaing = 1; // Выстовляем признак нажатия кнопки
  }
  millis_prev = millis();
}

// Выполняется при вращение сенсора
void turn_0() {
  static unsigned long millis_prev;
  // Устроняем дребезг контакта
  if (millis() - 300 > millis_prev) {
    turnSensor++; // счетчик поличества оборотов
    if (turnSensor == turn) {     //Останавливаем
      turnSensor=0;
      if (state0 == 0){
        tickerSetLow.attach(1, setUp, 0);
      }
      if (state0 == 1){
        tickerSetLow.attach(1, setDown, 0);
      }
    }
  //  if (turnSensor == turn-1) {     //замедляем скорость
  //    if (state0){
  //      analogWrite(LED1_PIN, 256);
  //    } else{
  //      analogWrite(LED2_PIN, 256);
  //    }
  //  }
  }
  millis_prev = millis();
}

void MotorUp() {
  if (state0 == 0) {
    pinMode(SERVO_PIN, OUTPUT);
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
   // tickerSetLow.attach(timeServo2, setUp, 0);
    Serial.println("Up");
   // attachInterrupt(TURNSENSOR_PIN, turn_0, FALLING );
    myservo.write(calibration + speed);
   // state0 = 1;
    turnSensor=0;
      chaing = 0;
    //chaing1 = 1;
  }
}

void MotorDown() {
  if (state0 == 1) {
    pinMode(SERVO_PIN, OUTPUT);
    digitalWrite(LED2_PIN, HIGH);
    digitalWrite(LED1_PIN, LOW);
   // tickerSetLow.attach(timeServo1, setDown, 0);
    Serial.println("Down");
   // attachInterrupt(TURNSENSOR_PIN, turn_0, FALLING );
    myservo.write(calibration - speed);
    //state0 = 0;
    turnSensor=0;
      chaing = 0;
   // chaing1 = 1;
  }
}

void setUp(int state) {
  tickerSetLow.detach();
 // detachInterrupt(TURNSENSOR_PIN);
  //analogWrite(LED1_PIN, 0);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  state0 = !state0;
 // chaing = 0;
 // chaing1 = 0;
  myservo.write(calibration);
  digitalWrite(SERVO_PIN, LOW);
  pinMode(SERVO_PIN, INPUT);
}

void setDown(int state) {
  tickerSetLow.detach();
 // detachInterrupt(TURNSENSOR_PIN);
  //analogWrite(LED2_PIN, 0);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED1_PIN, LOW);
  state0 = !state0;
  //chaing = 0;
  //chaing1 = 0;
  myservo.write(calibration);
  digitalWrite(SERVO_PIN, LOW);
  pinMode(SERVO_PIN, INPUT);
}
