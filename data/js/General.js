//
// var Base="http://192.168.0.51"; 
var Base="."; 


 
var getJSON = function(url, callback) {

    var xmlhttprequest = new XMLHttpRequest();
    xmlhttprequest.open('GET', url, true);
    xmlhttprequest.responseType = 'json';

    xmlhttprequest.onload = function() {

        var status = xmlhttprequest.status;

        if (status == 200) {
            callback(null, xmlhttprequest.response);
        } else {
            callback(status, xmlhttprequest.response);
        }
    };

    xmlhttprequest.send();
};






function Accion(pName,pTarget) {
  document.getElementById("Titulo").innerHTML="Titulo Principal";  
  var aMsg=document.getElementById("Msg"); 

    var aText=document.getElementById("DatoBase"); 

    var injText="<table>";
  if ( pName == "MuetroDatos" ) {
    aMsg.innerHTML="Loading data..."; 

    getJSON(Base + pTarget,  function(err, data) {

        if (err != null) {
            console.error(err);
            aMsg.innerHTML="Inconvenientes en con la consula"; 
        } else {

            injText+="<tr><td>SSID</td><td>" + data.WIFI.SSID + "</td></tr>";   
            injText+="<tr><td>IP</td><td>" + data.WIFI.IP + "</td></tr>";   
            injText+="<tr><td>RSSI</td><td>" + data.WIFI.RSSI + "</td></tr>";   
            injText+="<tr><td>hostname</td><td>" + data.WIFI.hostname + "</td></tr>";   


          injText+="</table>";   
          aText.innerHTML=injText;
        }
      console.log(data);
      aMsg.innerHTML="Datos refrescados"; 
    });



 
    pName=""; 
    } 



  if (pName) {
    alert("La opcion:" + pName + " es incorrecta" ); 
  }

}