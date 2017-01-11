#include <ESP8266WiFi.h>        //Содержится в пакете
#include <ESP8266WebServer.h>   //Содержится в пакете
#include <ESP8266SSDP.h>        //Содержится в пакете
#include <FS.h>                 //Содержится в пакете
#include <time.h>               //Содержится в пакете
#include <Servo.h>              //Содержится в пакете
#include <Ticker.h>             //Содержится в пакете
#include <WiFiUdp.h>            //Содержится в пакете
#include <ESP8266HTTPUpdateServer.h> //Содержится в пакете
#include <ESP8266httpUpdate.h>
#include <DNSServer.h>          //Содержится в пакете
#include <ArduinoJson.h>
// Настройки DNS сервера и адреса точки в режиме AP
const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 4, 1);
DNSServer dnsServer;
// Web интерфейс для устройства
ESP8266WebServer HTTP(80);
ESP8266HTTPUpdateServer httpUpdater;
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

//Сенсор вращения
#define turnSensor_pin 14

// Определяем переменные
// Количество модулей в устройстве
int a = 1;
String module[]={"jalousie-motor"};
//,"sonoff","rbg"};

// Определяем строку для json config
String jsonConfig = "";

String _ssid     = "WiFi"; // Для хранения SSID
String _password = "Pass"; // Для хранения пароля сети
String _ssidAP = "Zaluzi03";   // SSID AP точки доступа
String _passwordAP = ""; // пароль точки доступа
String SSDP_Name = "jalousie";      // SSDP
String TimeUp = "08:00:00";      // время открытия
String TimeDown = "21:00:00";    // время закрытия
// Переменные для обнаружения модулей
String Devices = "";            // Поиск IP адресов устройств в сети
String DevicesList = "";            // IP адреса устройств в сети
String Language ="ru";  // язык web интерфейса
String Lang = "";  // файлы языка web интерфейса
int timezone = 3;        // часовой пояс GTM
int Led1 = 12;           // индикатор движения вверх
int Led2 = 13;           // индикатор движения вниз
float TimeServo1 = 10.0;  // Время вращения
float TimeServo2 = 10.0;  // Время вращения
int speed = 90;    // Скорость вращения
int calibration = 90; // Колибруем серву
int turn = 7; //Количество оборотов
int turnSensor = 0;

String kolibrTime = "03:00:00"; // Время колибровки часов
volatile int chaingtime = LOW;
volatile int chaing = LOW;
volatile int chaing1 = LOW;
int state0 = 0;
unsigned int localPort = 2390;
unsigned int ssdpPort = 1900;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup() {
 Serial.begin(115200);
 pinMode(turnSensor_pin, INPUT);
 pinMode(Tach0, INPUT);
 pinMode(Led1, OUTPUT);
 pinMode(Led2, OUTPUT);
 Serial.println("");
 // Включаем работу с файловой системой
 FS_init();
 // Загружаем настройки из файла
 loadConfig();
 // Подключаем сервомотор
 myservo.attach(servo_pin);
 //myservo.write(calibration);
 // Кнопка будет работать по прерыванию
 attachInterrupt(Tach0, Tach_0, FALLING);
 // Сенсор будет работать по прерыванию
 attachInterrupt(turnSensor_pin, turn_0, FALLING);
 //Запускаем WIFI
 WIFIAP_Client();
 // Закускаем UDP
 udp.begin(localPort);
 //udp.beginMulticast(WiFi.localIP(), ssdpAdress1, ssdpPort);
 Serial.print("Local port: ");
 Serial.println(udp.localPort());
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

void loop() {
 dnsServer.processNextRequest();
 delay(1);
 HTTP.handleClient();
 delay(1);
 handleUDP();
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
 if (chaingtime) {
  Time_init(timezone);
  chaingtime=0;
 }
}

// Вызывается каждую секунду в обход основного циклу.
void alert() {
 String Time=XmlTime();
 if (TimeUp.compareTo(Time) == 0) {
  MotorUp();
 }
 if (TimeDown.compareTo(Time) == 0) {
  MotorDown();
 }
 if (kolibrTime.compareTo(Time) == 0) {
  chaingtime=1;
 }
}
