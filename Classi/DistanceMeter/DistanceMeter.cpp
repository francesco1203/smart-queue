#include "Arduino.h"
#include "DistanceMeter.h"        //header che stiamo implementando


/*etichette-costanti di classe*/
#define MAX_DISTANCE 5.0    //5 m massima distanza misurabile
#define SOUND_SPEED 340     //340 m/s velocità del suono

float const TIME_OUT = 2* MAX_DISTANCE / SOUND_SPEED * 1000000;
//tempo massimo di attesa in microsecondi per il ritorno dell'echo

float thresholdSensitivityDistance = 1.0;



/*COSTRUTTORI*/
DistanceMeter::DistanceMeter(int trigPin, int echoPin){
    if(trigPin >= 1 && trigPin <= 35 &&
       echoPin >= 1 && echoPin <= 35 &&
       trigPin != echoPin)                  //pin validi
    { 
        attachedTrigPin = trigPin;
        pinMode(trigPin, OUTPUT);
        digitalWrite(trigPin, LOW);

        attachedEchoPin = echoPin;
        pinMode(echoPin, INPUT);
    }
}

/*METODI PUBBLICI*/
    /*metodi d'accesso*/
    int DistanceMeter::getAttachedTrigPin(){return attachedTrigPin;}
    int DistanceMeter::getAttachedEchoPin(){return attachedEchoPin;}

    float DistanceMeter::measureDistance()
    {
        digitalWrite(attachedTrigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(attachedTrigPin, LOW);

        float pingTime = (float) pulseIn(attachedEchoPin, HIGH, TIME_OUT) / 1000000; //tempo di rimbalzo in sec
        return pingTime * SOUND_SPEED /2;
    }

    bool DistanceMeter::detectedPresence()
    {
        float m = measureDistance();

        //debug
        //Serial.print("Misura: ");
        //Serial.println(m);
        
        return (m <= thresholdSensitivityDistance);
            
    }

    bool DistanceMeter::detectedMovement()
    {
        bool risultato = false;

        if(!presenceFlag && detectedPresence())
            presenceFlag=true;

        if(presenceFlag && !detectedPresence()){
            presenceFlag = false;
            risultato = true;
        }

        return risultato;
    }
    

    /*metodi d'aggiornamento*/
   

    /*VARIABILI STATIC*/
    float DistanceMeter:: thresholdSensitivityDistance = 1.0;  //metri
    float DistanceMeter:: thresholdSensitivityTime = 0.5;      //secondi


    /*METODI STATIC*/
    void DistanceMeter::setThresholdSensitivityDistance(float newTreshold){thresholdSensitivityDistance=newTreshold;}
    void DistanceMeter::setThresholdSensitivityTime(float newTreshold){thresholdSensitivityTime=newTreshold;}
    