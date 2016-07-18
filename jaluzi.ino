#include <ESP8266WiFi.h>        //Содержится в пакете
#include <ESP8266WebServer.h>   //Содержится в пакете
#include <ESP8266SSDP.h>        //Содержится в пакете
#include <FS.h>                 //Содержится в пакете
#include <time.h>               //Содержится в пакете
#include <Servo.h>              //Содержится в пакете
#include <Ticker.h>             //Содержится в пакете
#include <ArduinoJson.h>


// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
// Для файловой системы
File fsUploadFile;
// Для сервопривода
Servo myservo;
// Для тикера
Ticker tickerSetLow;
Ticker tickerAlert;

// Кнопка управления
#define Tach0 0

// Сервопривод на ноге
#define servo_pin 2

// Определяем переменные
String _ssid     = ""; // Для хранения SSID
String _password = ""; // Для хранения пароля сети
String _ssidAP = "Zaluzi01";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа
String XML;              // формирование XML
String SSDP_Name = "jalousie";      // SSDP
String TimeUp = "08:00:00";      // время открытия
String TimeDown = "21:00:00";    // время закрытия
int timezone = 3;        // часовой пояс GTM
int Led1 = 12;           // индикатор движения вверх
int Led2 = 13;           // индикатор движения вниз
float TimeServo = 10.0;  // Время вращения
int revolutions = 90;    // Скорость вращения
int kolibr = 90; // Колибруем серву

volatile int chaing = LOW;
volatile int chaing1 = LOW;
int state0 = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(Tach0, INPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  Serial.println("");
  // Параметры памяти ESP справочно можно закаментировать
  CheckFlashConfig();
  // Включаем работу с файловой системой
  FS_init();
  // Загружаем настройки из файла
  loadConfig();
  // Подключаем сервомотор
  myservo.attach(servo_pin);
  // Кнопка будет работать по прерыванию
  attachInterrupt(Tach0, Tach_0, FALLING);
  //Запускаем WIFI
  WIFIAP_Client();
  //настраиваем HTTP интерфейс
  HTTP_init();
  Serial.println("HTTP Ready!");
  //запускаем SSDP сервис
  SSDP_init();
  Serial.println("SSDP Ready!");
  // Включаем время из сети
  Time_init(timezone);
  // Будет выполняться каждую секунду проверяя будильники
  tickerAlert.attach(1, alert);
}

void loop()
{
  HTTP.handleClient();
  delay(1);
  if (chaing && !chaing1) {
    noInterrupts();
    switch (state0) {

      case 0:
        MotorUp();
        break;
      case 1:
        MotorDown();
        break;
    }
    interrupts();
  }
}
// Вызывается каждую секунду в обход основного циклу.
void alert() {
  if (TimeUp.compareTo(XmlTime()) == 0) {
    MotorUp();
  }
  if (TimeDown.compareTo(XmlTime()) == 0) {
    MotorDown();
  }
}

