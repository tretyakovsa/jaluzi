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
// Время вращения сервопривода
void handle_TimeServo2() {
  TimeServo2 = HTTP.arg("t").toInt();
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
  String Time=XmlTime();
  HTTP.send(200, "text/plain", "Время синхронизовано: "+Time);
}
// Установка скорости вращения
void handle_speed() {
  speed = HTTP.arg("speed").toInt();
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
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  update();

  HTTP.on("/Motor", MotorActiv);            // запуск мотора напровление храниться в переменной
  HTTP.on("/Timeservo", handle_TimeServo);  // установка времени вращения сервопривода
  HTTP.on("/Timeservo2", handle_TimeServo2);  // установка времени вращения сервопривода
  HTTP.on("/TimeZone", handle_TimeZone);    // Установка времянной зоны
  HTTP.on("/Time", handle_Time);            // Синхронизировать время из сети
  HTTP.on("/TimeUp", handle_Time_Up);       // Установить время открытия
  HTTP.on("/TimeDown", handle_Time_Down);   // Установить время закрытия
  HTTP.on("/ssid", handle_Set_Ssid);        // Установить имя и пароль роутера
  HTTP.on("/ssidap", handle_Set_Ssidap);    // Установить имя и пароль для точки доступа
  HTTP.on("/speed", handle_speed);          // Установить скорость вращения сервопривода
  HTTP.on("/Save", handle_saveConfig);      // Сохранить настройки в файл
  HTTP.on("/config.xml", handleConfigXML);   // формирование config_xml страницы для передачи данных в web интерфейс
  HTTP.on("/kolibr", handlekolibr);         // колибруем серву
  HTTP.on("/block", block);                 // Блок для device.htm
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
  } else {
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
  } else {
    XML += _passwordAP;
  }
  XML += "</passwordAP>";
  // Времянная зона
  XML += "<timezone>";
  XML += timezone;
  XML += "</timezone>";
  // Скорость вращения
  XML += "<speed>";
  XML += speed;
  XML += "</speed>";
  //  Время врашения
  XML += "<timeservo>";
  XML += TimeServo;
  XML += "</timeservo>";
  //  Время врашения
  XML += "<timeservo2>";
  XML += TimeServo2;
  XML += "</timeservo2>";
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
  // Статус жалюзи
  XML += "<state>";
  XML += state0;
  XML += "</state>";
  XML += "</Donnees>";
  HTTP.send(200, "text/xml", XML);
}

void block() {
  XML = "<div class=\"block col-md-5\">";
  XML += "<h5>";
  XML += SSDP_Name;
  XML += "</h5>";
  XML += "<div class=\"alert alert-dismissible alert-warning\"><b>Обратите внимание</b>";
  XML += "<br>Время закрытия: ";
  XML += TimeUp;
  XML += "<br>Время открытия: ";
  XML += TimeDown;
  XML += "</div>";
  XML += "<input class=\"btn btn-block btn-lg btn-primary\" value=\"Открыть/закрыть жалюзи\" onclick=\"ajax('";
  XML += WiFi.localIP().toString();
  XML += "/Motor', this);\" type=\"submit\">";
  XML += "<hr>";
  XML += "<div class=\"alert alert-dismissible alert-info\">Изменить конфигурацию устройсва вы можете на странице управления</div>";
  XML += "<a class=\"btn btn-block btn-default\" href=\"http://";
  XML += WiFi.localIP().toString();
  XML += "\">Страница управления</a>";
  XML += "</div>";
  HTTP.send(200, "text/plain", XML);
}

