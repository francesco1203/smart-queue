#include "Arduino.h"
#include "SensorPIR.h"        //header che stiamo implementando


/*COSTRUTTORI*/
SensorPIR::SensorPIR(int signalPin){
    if(signalPin >= 0 && signalPin <= 35){ //pin valido 
        attachedSignalPin = signalPin;
        pinMode(signalPin, INPUT);
    }
}

/*METODI PUBBLICI*/
    /*metodi d'accesso*/
    int SensorPIR::getAttachedSignalPin(){return attachedSignalPin;}

    bool SensorPIR::detectedMovement()
    {
        return digitalRead(attachedSignalPin) == HIGH;
        //restituisce 1 solo se signal pin è alto, cioè ha rilevato movimento
    }
    

    /*metodi d'aggiornamento*/
   