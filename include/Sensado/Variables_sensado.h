/*
Aqui colocaremos las estructuras y variables golbales para sensados diversos
 */ 
struct SensorSimple {
  String Nombre; // Identificacion del sensor
  float Valor; // Valor medido 
}; 

// struct SensorSimple sTest;

struct Sensores {
  struct SensorSimple Sensor1; 
  struct SensorSimple Sensor2; 
}; 

struct Sensores sTest;

SensorSimple Elementos[5];
int Sensores=2; 

// float FactorVCC=3.3f/1024.0f;   // Real
float FactorVCC=3.1f/1024.0f;  





