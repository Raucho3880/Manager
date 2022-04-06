// Funciones WEB...

void Web_SendFile(fs::FS &fs, const char * Filename) {


WebServer.setContentLength(CONTENT_LENGTH_UNKNOWN);

// char *lFilename = strdup(Filename); 
strcpy(WK100, Filename);


MatchState ms;
ms.Target (WK100);  // set its address


// Serial.println(WK100 ); 
bool HeaderOK=false; 

if ( ms.Match ("%phtml$") ) {
  WebServer.send ( 200, "text/html", " ");
//  Serial.println("Encuentra html"); 
  HeaderOK=true; 
  }

if ( ms.Match ("%pcss$") ) {
  WebServer.send ( 200, "text/css", " ");
//  Serial.println("Encuentra css"); 
  HeaderOK=true; 
  }

if ( ms.Match ("%pico$") ) {
  WebServer.send ( 200, "image/x-icon", "");
//  Serial.println("Encuentra css"); 
  HeaderOK=true; 
  }



if ( ! HeaderOK ) {
  WebServer.send ( 200, "text/txt", " ");
  Serial.println("No encuentra nada"); 
  HeaderOK=true; 
}






if (fs.exists(Filename) ) {
  
  File file = fs.open(Filename,"r");

    while(file.available()){


     String line = file.readStringUntil('\n');
     WebServer.sendContent(line);
//     Serial.println(line);
     }
  WebServer.sendContent("");  
  file.close();  
//   Serial.println("Devuelvo pagina web");
  } else {

   Serial.println("No se encuentra el archivo solicitado"); 
  }

    
}




void WebServer_RootPath() {
  Web_SendFile(LittleFS,"index.html"); 
 }



void WebServer_NotFount() {



// https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WebServer/README.rst


// Serial.println(   WebServer._currentUri()    );
// Serial.println(   WebServer.uri() ); 

if (  LittleFS.exists( WebServer.uri()) ) {
  String File=String(WebServer.uri());  
  char s[30];
  File.toCharArray(s  , 30);  
  Web_SendFile(LittleFS,s); 
  return;
//  Serial.println(   s ); 
    
  }

if (  WebServer.args() > 0 )   {
  Serial.println(   WebServer.args() );  
  for (int i = 0; i < WebServer.args(); i++) {
    Serial.println( "Argumento:" + String(WebServer.argName(i))  +  ", valor:"  +   String(WebServer.arg(i))  );  
//     Serial.println(   WebServer.arg(i) );   
    }
  }



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


 if ( LittleFS.info(fs_info) ) {
   JsonDoc["FS"]["totalBytes"] = fs_info.totalBytes ; 
   JsonDoc["FS"]["usedBytes"] = fs_info.usedBytes ; 
   }


}



void Web_hostStatus() {
// /service/hostStatus
Serial.println("Pasa por peticion web...Web_hostStatus : /service/hostStatus");



deserializeJson(JsonDoc,"{}"); // Vacia cualquier cosa que exista
ESP_NodeData(); 
serializeJson(JsonDoc, Buffer);  // LO convierte a string.. 
WebServer.send(200,"application/json", Buffer);




}