//------------------------------------------
// Меняет флаг для запуска сервопривода
void MotorActiv() {
  chaing = 1;
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Сохраняет все настройки в файле
void handle_saveConfig() {
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Время вращения сервопривода
void handle_TimeServo() {
  TimeServo = HTTP.arg("t").toInt();
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Установка времянной зоны
void handle_TimeZone() {
  timezone = HTTP.arg("timezone").toInt();
  Time_init(timezone);
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Установка параметров сети
void handle_Set_Ssid() {
  _ssid = HTTP.arg("ssid");
  _password = HTTP.arg("password");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Установка параметров точки доступа
void handle_Set_Ssidap() {
  _ssidAP = HTTP.arg("ssidAP");
  _passwordAP = HTTP.arg("passwordAP");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
// Время из сети
void handle_Time() {
  Time_init(timezone);
  HTTP.send(200, "text/plain", "OK");
}
// Установка скорости вращения
void handle_Revolutions() {
  revolutions = HTTP.arg("revolutions").toInt();
  saveConfig();
   HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
//Задать время открытия
void handle_Time_Up() {
  TimeUp = HTTP.arg("open");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//------------------------------------------
//Задать время закрытия
void handle_Time_Down() {
  TimeDown = HTTP.arg("close");
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}
//----------------------------------
//Задать время закрытия
void handlekolibr() {
  kolibr = HTTP.arg("kolibr").toInt();
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void HTTP_init(void) {

  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SSPI) и выше
  //update();

  HTTP.on("/Motor", MotorActiv);            // запуск мотора напровление храниться в переменной
  HTTP.on("/Timeservo", handle_TimeServo);  // установка времени вращения сервопривода
  HTTP.on("/TimeZone", handle_TimeZone);    // Установка времянной зоны
  HTTP.on("/Time", handle_Time);            // Синхронизировать время из сети
  HTTP.on("/TimeUp", handle_Time_Up);       // Установить время открытия
  HTTP.on("/TimeDown", handle_Time_Down);   // Установить время закрытия
  HTTP.on("/ssid", handle_Set_Ssid);        // Установить имя и пароль роутера
  HTTP.on("/ssidap", handle_Set_Ssidap);    // Установить имя и пароль для точки доступа
  HTTP.on("/revolutions", handle_Revolutions); // Установить скорость вращения сервопривода
  HTTP.on("/Save", handle_saveConfig);      // Сохранить настройки в файл
  HTTP.on("/configxml", handleConfigXML);   // формирование config_xml страницы для передачи данных в web интерфейс
  HTTP.on("/kolibr", handlekolibr);   // колибруем серву
  // Запускаем HTTP сервер
  HTTP.begin();
}


// Получение текущего времени
String XmlTime(void) {
  String Time = ""; // Строка для результатов времени
  int i = 0; // Здесь будем хранить позицию первого символа :
  time_t now = time(nullptr); // получаем времяс помощью библиотеки time.h
  Time += ctime(&now); // Преобразуем время в строку формата
  i = Time.indexOf(":"); //Ишем позицию первого символа :
  Time = Time.substring(i - 2, i + 6); // Выделяем из строки 2 символа перед символом : и 6 символов после
  return Time; // Возврашаем полученное время
}

void handleConfigXML() {
  XML = "<?xml version='1.0'?>";
  XML += "<Donnees>";
  // Имы SSDP
  XML += "<SSDP>";
  XML += SSDP_Name;
  XML += "</SSDP>";
  // Имя сети
  XML += "<ssid>";
  XML += _ssid;
  XML += "</ssid>";
  // Пароль сети
  XML += "<password>";
   if (_password == NULL) {
    XML += " ";
      }
  else {
    XML += _password;
  }
  XML += "</password>";
  // Имя точки доступа
  XML += "<ssidAP>";
  XML += _ssidAP;
  XML += "</ssidAP>";
  // Пароль точки доступа
  XML += "<passwordAP>";
  if (_passwordAP == NULL) {
    XML += " ";
      }
  else {
    XML += _passwordAP;
  }
  XML += "</passwordAP>";
  // Времянная зона
  XML += "<timezone>";
  XML += timezone;
  XML += "</timezone>";
  // Скорость вращения
  XML += "<revolutions>";
  XML += revolutions;
  XML += "</revolutions>";
  //  Время врашения
  XML += "<timeservo>";
  XML += TimeServo;
  XML += "</timeservo>";
  // Время открытия
  XML += "<TimeUp>";
  XML += TimeUp;
  XML += "</TimeUp>";
  // Время закрытия
  XML += "<TimeDown>";
  XML += TimeDown;
  XML += "</TimeDown>";
  // Текущее время
  XML += "<time>";
  XML += XmlTime();
  XML += "</time>";
  // Колибруе серву
  XML += "<kolibr>";
  XML += kolibr;
  XML += "</kolibr>";
  XML += "</Donnees>";
  HTTP.send(200, "text/xml", XML);
}



