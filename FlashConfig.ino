bool loadConfig() {
  File configFile = SPIFFS.open("/config.json", "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();
  if (size > 1024) {
    Serial.println("Config file size is too large");
    return false;
  }

  // Выделим буфер для хранения содержимого файла.
  std::unique_ptr<char[]> buf(new char[size]);

  // Мы не используем строку здесь, потому что библиотека Arduino Json требует ввода
  // буфер, чтобы быть изменчивым. Если вы не используете ArduinoJson, вы можете также
  // использование configFile.readString вместо этого.
  configFile.readBytes(buf.get(), size);

  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(buf.get());

  if (!json.success()) {
    Serial.println("Failed to parse config file");
    return false;
  }
  String ssidAP = json["ssidAPName"];
  _ssidAP = ssidAP;
  String passwordAP = json["ssidAPPassword"];
  _passwordAP = passwordAP;

  timezone = json["timezone"];

  speed = json["speed"];
  kolibr = json["kolibr"];

  String SSDPName = json["SSDPName"];
  SSDP_Name = SSDPName;
  String ssid = json["ssidName"];
  _ssid = ssid;
  String password = json["ssidPassword"];
  _password = password;
  String _TimeUp = json["TimeUp"];
  TimeUp = _TimeUp;
  String _TimeDown = json["TimeDown"];
  TimeDown = _TimeDown;

  TimeServo = json["TimeServo"];
  TimeServo2 = json["TimeServo2"];

  String lang = json["Lang"];
  Language = lang;
  return true;
}

bool saveConfig() {
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["SSDPName"] = SSDP_Name;
  json["kolibr"] = kolibr;
  json["ssidAPName"] = _ssidAP;
  json["ssidAPPassword"] = _passwordAP;
  json["ssidName"] = _ssid;
  json["ssidPassword"] = _password;
  json["timezone"] = timezone;
  json["speed"] = speed;
  json["TimeUp"] = TimeUp;
  json["TimeDown"] = TimeDown;
  json["TimeServo"] = TimeServo;
  json["TimeServo2"] = TimeServo2;
  json["Lang"] = Language;
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}
