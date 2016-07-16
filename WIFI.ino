
void WIFIAP_Client() {
  WiFi.mode(WIFI_AP_STA);
  //WiFi.begin(ssid, password);
  Serial.print(_ssid);
  WiFi.begin(_ssid.c_str(), _password.c_str());
  WiFi.softAP(_ssidAP.c_str(), _passwordAP.c_str());

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED && i < 50) {
    delay(500);
    i++;
    Serial.print(".");
  }
}
