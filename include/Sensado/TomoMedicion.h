// 

void TomoMuestras() {


Elementos[0].Nombre="VCC"; 
Elementos[0].Valor=analogRead(PIN_A0) * FactorVCC * 2;
// analogRead(A0)
Serial.println("Tomo muestras sensado"); 
Elementos[0].Valor++; 

}