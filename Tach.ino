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
  //      analogWrite(Led1, 256);
  //    } else{
  //      analogWrite(Led2, 256);
  //    }
  //  }
  }
  millis_prev = millis();
}

void MotorUp() {
  if (state0 == 0) {
    pinMode(servo_pin, OUTPUT);
    digitalWrite(Led1, HIGH);
    digitalWrite(Led2, LOW);
   // tickerSetLow.attach(TimeServo2, setUp, 0);
    Serial.println("Up");
   // attachInterrupt(turnSensor_pin, turn_0, FALLING );
    myservo.write(calibration + speed);
   // state0 = 1;
    turnSensor=0;
      chaing = 0;
    //chaing1 = 1;
  }
}

void MotorDown() {
  if (state0 == 1) {
    pinMode(servo_pin, OUTPUT);
    digitalWrite(Led2, HIGH);
    digitalWrite(Led1, LOW);
   // tickerSetLow.attach(TimeServo1, setDown, 0);
    Serial.println("Down");
   // attachInterrupt(turnSensor_pin, turn_0, FALLING );
    myservo.write(calibration - speed);
    //state0 = 0;
    turnSensor=0;
      chaing = 0;
   // chaing1 = 1;
  }
}

void setUp(int state) {
  tickerSetLow.detach();
 // detachInterrupt(turnSensor_pin);
  //analogWrite(Led1, 0);
  digitalWrite(Led2, LOW);
  digitalWrite(Led1, LOW);
  state0 = !state0;
 // chaing = 0;
 // chaing1 = 0;
  myservo.write(calibration);
  digitalWrite(servo_pin, LOW);
  pinMode(servo_pin, INPUT);
}

void setDown(int state) {
  tickerSetLow.detach();
 // detachInterrupt(turnSensor_pin);
  //analogWrite(Led2, 0);
  digitalWrite(Led2, LOW);
  digitalWrite(Led1, LOW);
  state0 = !state0;
  //chaing = 0;
  //chaing1 = 0;
  myservo.write(calibration);
  digitalWrite(servo_pin, LOW);
  pinMode(servo_pin, INPUT);
}
