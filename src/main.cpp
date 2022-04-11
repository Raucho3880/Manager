#include <Arduino.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <Regexp.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
// ADC_MODE(ADC_VCC); //vcc read
/*
Subsistema de riego
  */ 

#include <LittleFS.h>
FSInfo fs_info;
#define FLASH_MAP_SETUP_CONFIG(FLASH_MAP_OTA_FS) // Scetch:1M, OTA:1M, FS:2M 
// FLASH_MAP_MAX_FS  // Scetch:1M, OTA:1M, FS:2M 
// FLASH_MAP_NO_FS



//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

// =========================================
#include <Ticker.h>
Ticker flipper;
// =========================================
#include "ArduinoOTA.h"

// =========================================
#include <Custom/Headers.h>
// =========================================

ESP8266WebServer WebServer(C_HTTP_PORT); 
// =========================================
/*
  Esta seccion depende del los sensores empleados. 

  Primero las librerias, luego las variables, luego las funciones. 

  Estas deben configuarse segun los sensores empleados. 
 */ 
#include <Sensado/Variables_sensado.h>
#include <Sensado/TomoMedicion.h>


// You can specify the time server pool and the offset, (in seconds)
// additionally you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", C_NTP_UTC_OFSET,C_NTP_REFRESH_INTERVAL);

#include <Custom/Funciones_Comunes.h>

#include <Custom/Funciones_WebHandlers.h>

#include <Sensado/MuestroDatosSensado.h>






void setup() {
    // put your setup code here, to run once:


Elementos[0].Nombre="SensorA"; 
Elementos[0].Valor=2; 
Elementos[1].Nombre="Elementos"; 
Elementos[1].Valor=sizeof(Elementos) ; 




    Serial.begin(115200);
    delay(200); 

 Serial.println(""); 
 Serial.println("Inicia la setup....."); 

  pinMode(LED_BUILTIN, OUTPUT);


    flipper.attach(0.3, onTick_ChageLed);

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
// wifiManager.resetSettings();


/* 
WiFi.disconnect();
wifiManager.resetSettings();
ESP.eraseConfig();
ESP.reset();
ESP.restart();
 */ 




    //set custom ip for portal
    //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

/*  Setup custom parms*/ 

wifiManager.setCustomHeadElement("<style>html{filter: invert(100%); -webkit-filter: invert(100%);}</style>");

WiFiManagerParameter custom_text("<p>Texto agregado</p>");
wifiManager.addParameter(&custom_text);  // agrega texto debajo de las Wifis escaneadas...

// const char* menu[] = {"wifi"};
// wifiManager.setMenu(menu,1);




    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();

    
    //if you get here you have connected to the WiFi
    Serial.println("El ESP se ha conectado a la red....");
    flipper.attach(5, onTick_ChageLed);

/*  
  Ahora Habilito OTA
  */ 
  ArduinoOTA.onStart([]() {  // switch off all the PWMs during upgrade
    flipper.attach(0.05, onTick_ChageLed);
  });
  ArduinoOTA.begin();

/*  
  Habilito el FS
  */ 
if ( LittleFS.begin() ) {
 Serial.println("El LittleFS se monto adecuedamente");   
 } else {  
   // Asumo que no esta formateado.... 
   if (  LittleFS.format() ) {
     if ( ! LittleFS.begin() ) {
      Serial.println("*** Fallo el montaje e LittleFS luego del formateo");   
    } 
   }
   else {
    Serial.println("*** Fallo Formateo del lFS");   
   }  
  }



/*  
  Ahora levanto el WebServer.... 
  */
 	
   WebServer.on("/", WebServer_RootPath); 
   WebServer.on("/service/hostStatus.json", Web_hostStatus);
   WebServer.on("/service/getSensores.json", Web_getSensores);


   WebServer.onNotFound(WebServer_NotFount); 
   // Ruteo para URI desconocida
   
   
   WebServer.begin();
   Serial.println("HTTP server started");    
   timeClient.begin();

/* 
Incializacion de sensore
  */ 


TomoMuestras(); 
flipper.attach(60, TomoMuestras);




}

void loop() {
    // put your main code here, to run repeatedly:
   timeClient.update();
   ArduinoOTA.handle();
   WebServer.handleClient();
}