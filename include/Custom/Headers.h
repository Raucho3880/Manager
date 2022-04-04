// Defino las constantes a emplear.
#define C_HTTP_PORT 80


/*

 Datos asociado al NTP, sincronizacion de la hora del ESP.
*/ 
#define C_NTP_UTC_OFSET -3*3600
#define C_NTP_REFRESH_INTERVAL  1*(1000*60*60) 


/*
 Buffers de trabajo, 
*/ 
StaticJsonDocument<2000> JsonDoc;
char Buffer[2048]; 
char WK100[100]; 