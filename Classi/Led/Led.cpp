#include "Arduino.h"
#include "Led.h"        //header che stiamo implementando


/*COSTRUTTORI*/
Led::Led(int pin){
    if(pin >= 0 && pin <= 35){ //pin valido 
        attachedPin=pin;
        pinMode(pin, OUTPUT);
    }
}

/*METODI PUBBLICI*/
    /*metodi d'accesso*/
    int Led::getAttachedPin(){return attachedPin;}
    bool Led:: getState(){return state;}

    /*metodi d'aggiornamento, funzionamento*/
    void Led::turnOn(){
        if(attachedPin!=-1){    //funzionante
            state = HIGH;
            digitalWrite(attachedPin, HIGH);
        }        
    }

    void Led::turnOff(){
        if(attachedPin!=-1){    //funzionante
            state = LOW;
            digitalWrite(attachedPin, LOW);
        }        
    }

    void Led::lampeggia(int millTime){
        if(attachedPin!=-1){    //funzionante
            turnOn();
            delay(millTime);
            turnOff();
        }        
    }