#include "Arduino.h"
#include "Buzzer.h"        //header che stiamo implementando


/*COSTRUTTORI*/
Buzzer::Buzzer(int pin){
    if(pin >= 0 && pin <= 35){ //pin valido 
        attachedPin=pin;
        pinMode(pin, OUTPUT);
        digitalWrite(attachedPin, LOW);
    }
}

/*METODI PUBBLICI*/
    /*metodi d'accesso*/
    int Buzzer::getAttachedPin(){return attachedPin;}

    /*metodi d'aggiornamento, funzionamento*/

    void Buzzer::turnOn(){
        if(attachedPin!=-1){    //funzionante
            digitalWrite(attachedPin, HIGH);
        }        
    }

    void Buzzer::turnOff(){
        if(attachedPin!=-1){    //funzionante
            digitalWrite(attachedPin, LOW);
        }        
    }
