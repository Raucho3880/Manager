#include <Arduino.h>


// extern int Sensores; 
// extern StaticJsonDocument JsonDoc;

void WebDoc_Sensado() {
// Elementos[1].Valor=analogRead(PIN_A0);
// Elementos[0].Valor=analogRead(PIN_A0) * FactorVCC * 2;
    JsonDoc["Cantidad"] = Sensores;

    for (int i = 0; i < Sensores; i++) {

       JsonDoc[Elementos[i].Nombre]["Valor"] = Elementos[i].Valor;
//       JsonDoc[i]["Nombre"] = Elementos[i].Nombre;
//       JsonDoc[i]["Valor"] = Elementos[i].Valor;


    }


//  JsonDoc[Elementos[0].Nombre]["Valor"] = Elementos[0].Valor;
//  JsonDoc[Elementos[1].Nombre]["Valor"] = Elementos[1].Valor;
  }

void Web_getSensores() {
// /service/hostStatus
Serial.println("Pasa por peticion datos sensado : /service/getSensores");
deserializeJson(JsonDoc,"{}"); // Vacia cualquier cosa que exista
WebDoc_Sensado(); 
serializeJson(JsonDoc, Buffer);  // LO convierte a string.. 
WebServer.send(200,"application/json", Buffer);

}


