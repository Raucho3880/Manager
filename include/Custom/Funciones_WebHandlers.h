// Funciones WEB...


void WebServer_NotFount() {

Serial.println("Pasa por peticion web..."); 




WebServer.send(404, "text/plain", "No puedo procesar el pedido");
 
}


void ESP_NodeData() {
  JsonDoc["WIFI"]["MACADDRS"] = WiFi.macAddress();
  JsonDoc["WIFI"]["SSID"] = WiFi.SSID(); 
  JsonDoc["WIFI"]["RSSI"] = WiFi.RSSI(); 
  JsonDoc["WIFI"]["IP"] = WiFi.localIP();
  JsonDoc["WIFI"]["hostname"] = WiFi.hostname();

  JsonDoc["ESP"]["FreeHeap"] = ESP.getFreeHeap();
  JsonDoc["ESP"]["HeapFragmentation"] = ESP.getHeapFragmentation();
  JsonDoc["ESP"]["MaxFreeBlockSize"] = ESP.getMaxFreeBlockSize();
  JsonDoc["ESP"]["CoreVersion"] = ESP.getCoreVersion();
  JsonDoc["ESP"]["SdkVersion"] = ESP.getSdkVersion();
  JsonDoc["ESP"]["SketchSize"] = ESP.getSketchSize();
  JsonDoc["ESP"]["FreeSketchSpace"] = ESP.getFreeSketchSpace();
  JsonDoc["ESP"]["FlashChipId"] = (uint32_t)ESP.getFlashChipId();
  sprintf(WK100, "%0x",  (uint32_t)ESP.getFlashChipId());  
  JsonDoc["ESP"]["FlashChipIdX"] = WK100;

  JsonDoc["ESP"]["FlashChipSize"] = ESP.getFlashChipSize();
  JsonDoc["ESP"]["FlashChipRealSize"] = ESP.getFlashChipRealSize();
  
  JsonDoc["BUILD"]["DATE"] = __DATE__ ;
  JsonDoc["BUILD"]["TIME"] = __TIME__ ;

  JsonDoc["CURRENT"]["Time"] = timeClient.getFormattedTime(); // 
  JsonDoc["CURRENT"]["DATE"] = timeClient.getDay(); //
  unsigned long epochTime = timeClient.getEpochTime(); //
  JsonDoc["CURRENT"]["epochTime"] = epochTime; 
  sprintf(WK100, "%04u/%02u/%02u",  year(epochTime),month(epochTime),day(epochTime)  ); 
  JsonDoc["CURRENT"]["Date"] = WK100; 

}



void Web_hostStatus() {
// /service/hostStatus
Serial.println("Pasa por peticion web...Web_hostStatus : /service/hostStatus");



deserializeJson(JsonDoc,"{}"); // Vacia cualquier cosa que exista
ESP_NodeData(); 
serializeJson(JsonDoc, Buffer);  // LO convierte a string.. 
WebServer.send(200,"application/json", Buffer);
      
}