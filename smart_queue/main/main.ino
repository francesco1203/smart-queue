
/*Classi e Librerie*/
  /*mie classi*/
  #include <DistanceMeter.h>
  #include <Led.h>
  #include <SensorPIR.h>
  #include <LedRGB.h>
  #include <Buzzer.h>

  /*mie librerie*/
  #include "Arduino.h"
  #include <WiFi.h>
  #include <WiFiClient.h>
  #include <HTTPClient.h>
  #include <String.h>



/*etichette*/
  #define TIME_LAMP 500   //tempo di lampeggio dei led in millisecondi

  const char *ssid     = "realme";              //Enter the router name
  const char *password = "napoli1926";          //Enter the router password

  const char* scriptGetThreshold = "http://192.168.56.98/smart_queue/getCardinalityThreshold.php";
  const char* scriptSetOccupation = "http://192.168.56.98/smart_queue/setOccupation.php";
  const char* scriptSetAllarmDB = "http://192.168.56.98/smart_queue/setAllarmDB.php";
  const char* scriptGetAllarmActivation = "http://192.168.56.98/smart_queue/getAllarmActivation.php";
  const char* scriptGetActualMinutes = "http://192.168.56.98/smart_queue/getActualMinutes.php";
  const char* scriptSetHourVisitorsDB = "http://192.168.56.98/smart_queue/setHourVisitorsDB.php";


/*objects*/
  /*components*/
  Led Lout(25);
  Led Lin(4);
  LedRGB RGB(26, 27, 14);
  DistanceMeter DM(5, 18);
  SensorPIR PIR(13);
  Buzzer B(12);

  

/*variabili*/
  int peoplePresence = 0;             //presenza attuale
  int cardinalityThreshold;           //occupazione massima da non superare
  int peopleThisHour = 0;             //totale visitatori quest'ora

  int startTime, endTime;             //tempi di inizio e fine del suono dell'allarme (per calcolare durata allarme)

  bool allarmActivationOn;            //accende o spegne definitivamente l'allarme (può entrare chiunque)
  bool allarmStateOn = false;         //stato attuale dell'allarme (relativo al se sta suonando o no)

  int actual_min;
  bool FLAG_ALREADYREAD = false;      //è alto se min = 0 ma ha già inviato la richiesta di aggiornare i DB
                                      /*serve a mandare la richiesta una volta solta sul minuto 0*/


/*funzioni*/
  void gestioneLedRGB();                
  void allarmGeneration();
  void allarmStop();
  String timeFormat();                      //formatta da secondi a stringa di time

  String get_from_server(const char* serverName);
  void send_to_server(String getData, const char* serverName);


void setup() {
  Serial.begin(9600);

  //connessione wi-fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  { 
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  /*inizializzazione delle variabili dai salvataggi*/
  cardinalityThreshold = get_from_server(scriptGetThreshold).toInt();
  allarmActivationOn = get_from_server(scriptGetAllarmActivation).toInt();
  actual_min = get_from_server(scriptGetActualMinutes).toInt();
}


void loop() {

  /*rilevazione ingresso*/
  if(DM.detectedMovement())
  {
    //Serial.print("Trovato che entra!!");
    Lin.lampeggia(TIME_LAMP);
    peoplePresence++;
    peopleThisHour++;

    //riporta al server l'occupazione attuale
    send_to_server(String(peoplePresence), scriptSetOccupation);
  }
  
  /*rilevazione uscita*/
  if(PIR.detectedMovement() && peoplePresence > 0) //movimento in uscita
  {
    //Serial.print("Trovato che esce!!");
    peoplePresence--;
    Lout.lampeggia(TIME_LAMP);
    
    //riporta al server l'occupazione attuale
    send_to_server(String(peoplePresence), scriptSetOccupation);
  }


  /*gestione degli allarmi*/
  if(allarmActivationOn)  //gestisco gli allarmi se non sono totalmente disattivati dalla dashboard
  {
    /*gestione generazione allarme*/
    if(!allarmStateOn && peoplePresence > cardinalityThreshold)
      allarmGeneration();
    
    if(allarmStateOn && peoplePresence <= cardinalityThreshold)
      allarmStop();


    /*gestisce il semaforo*/
    gestioneLedRGB();
  }
  else
  {
    RGB.turnOff();  //spengo il semaforo

    if(allarmStateOn) //caso limite: utente disattava allarme durante allarme in corso.
      allarmStop();
  }


  /*aggiornamento grafici*/
  if(actual_min == 0 && !FLAG_ALREADYREAD)
  {
    send_to_server(String(peopleThisHour), scriptSetHourVisitorsDB);
    peopleThisHour = 0;


    FLAG_ALREADYREAD = true;                         //flag di avvenuta lettura della presenza oraria, lo metto a true
  }
  else if(FLAG_ALREADYREAD && actual_min != 0){
       FLAG_ALREADYREAD = false;                     //lo rimetto a false per il prossimo controllo
  }
   



  /*aggiornamento variabili dalla dashboard*/
  cardinalityThreshold = get_from_server(scriptGetThreshold).toInt();
  allarmActivationOn = get_from_server(scriptGetAllarmActivation).toInt();
  actual_min = get_from_server(scriptGetActualMinutes).toInt();



  delay(1000);
}


/*metodi*/
void gestioneLedRGB(){ //gestisce semaforo quando allarme è acceso

  if (allarmStateOn)                                        //superato capienza, allarme in corso
    RGB.lampeggia('r', TIME_LAMP);
  else if(peoplePresence == cardinalityThreshold)            //equagliato capienza
    RGB.setActualColor('r');
  else if((float)peoplePresence >= (0.8*cardinalityThreshold)) //sto sopra 80% capienza
    RGB.setActualColor('y'); 
  else                                                         //sto tranquillo
    RGB.setActualColor('g');
}


void allarmGeneration(){
  B.turnOn();                           //buzzer comincia a suonare
  startTime = round(millis() / 1000);

  allarmStateOn = true;
}


void allarmStop(){
  B.turnOff();
  endTime = round(millis() / 1000);

  send_to_server(timeFormat(), scriptSetAllarmDB);  //aggiorna il DB degli allarmi e la pagina con la tabella

  allarmStateOn = false;
}


String timeFormat(){
  int last = endTime - startTime;   //numero di secondi di durata dell'allarme

  int h =  floor ((float) last / 3600),
      m =  floor ((float)(last - h*3600) /60),
      s =  floor ((float)(last - h*3600 - m*60));

  
  String orario = ""; //format hh:mm:ss

  /*nel caso h, m o s <10 per rispettare il formato aggiungo uno 0*/
  
  if(h<10) orario +="0";
  orario = orario + h + ":";
  
  if(m<10) orario +="0";
  orario = orario + m + ":";

  if(s<10) orario +="0";
  orario +=s;

  return orario;
}


String get_from_server(const char* serverName){
  String threshold;
  if(WiFi.status()== WL_CONNECTED){
      threshold = httpGETRequest(serverName);
      //Serial.println("The threshold is: "+threshold);
  }   else 
  {
    Serial.println("Error in WiFi connection");
  }
  return threshold;
  
}

String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = ""; 
  
  if (httpResponseCode>0) {
    //Serial.print("HTTP Response code: ");
    //Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}

void send_to_server(String getData, const char* serverName) {

  String url = String(serverName) + "?value=" + getData;

  HTTPClient http;    
  if (WiFi.status() == WL_CONNECTED) 
  { //Check WiFi connection status
    http.begin(url);              
    //http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header
    int httpCode = http.GET();   
    //Serial.println(httpCode);   //Print HTTP return code
    http.end();  //Close connection
    //Serial.println(getData);
  }
  else 
  {
    Serial.println("Error in WiFi connection");
  }

}


/*COMMENTI/REQUISITI SECONDARI

Led rosso si accende a capienza massima ed oltre
Led giallo si accende all'80% della capienza
Led verde altrimenti

I led singoli lampeggiano al passaggio di una persona

Buzzer si accende con l'allarme (superata capienza massima)*/
