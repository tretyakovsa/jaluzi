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

  // загружаем файл конфигурации в глобальную переменную
  jsonConfig = configFile.readString();
  Serial.println(jsonConfig);
  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(jsonConfig);
  _ssidAP = root["ssidAPName"].as<String>();
  _passwordAP = root["ssidAPPassword"].as<String>();
  timezone = root["timezone"];
  SSDP_Name = root["SSDPName"].as<String>();
  _ssid = root["ssidName"].as<String>();
  _password = root["ssidPassword"].as<String>();
  Language = root["Lang"].as<String>();
  DDNS = root["DDNS"].as<String>();
  DDNSName = root["DDNSName"].as<String>();

  speed = root["speed"];
  calibration = root["calibration"];
  turn = root["turn"];
  TimeUp = root["TimeUp"].as<String>();
  TimeDown = root["TimeDown"].as<String>();
  TimeServo1 = root["TimeServo1"];
  TimeServo2 = root["TimeServo2"];
  return true;
}





bool saveConfig() {
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.parseObject(jsonConfig);
  json["SSDPName"] = SSDP_Name;
  json["calibration"] = calibration;
  json["ssidAPName"] = _ssidAP;
  json["ssidAPPassword"] = _passwordAP;
  json["ssidName"] = _ssid;
  json["ssidPassword"] = _password;
  json["timezone"] = timezone;
  json["DDNSName"] = DDNSName;
  json["DDNSPort"] = DDNSPort;
  json["Lang"] = Language;
  json["speed"] = speed;
  json["turn"] = turn;
  json["TimeUp"] = TimeUp;
  json["TimeDown"] = TimeDown;
  json["TimeServo1"] = TimeServo1;
  json["TimeServo2"] = TimeServo2;
  json["DDNS"] = DDNS;
  File configFile = SPIFFS.open("/config.json", "w");
  if (!configFile) {
    //Serial.println("Failed to open config file for writing");
    return false;
  }

  json.printTo(configFile);
  return true;
}






