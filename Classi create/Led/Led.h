#ifndef Led_H
#define Led_H

#include "Arduino.h"

/*convenzione: se pin = -1, il componente non è stato integrato bene
               (ad esempio, se attaccato ad un pin non valido)*/


class Led{
    public:
        /*COSTRUTTORI*/
        Led(int pin);

        /*METODI PUBBLICI*/
          /*metodi d'accesso*/
          int getAttachedPin();
          bool getState();

          /*metodi d'aggiornamento, funzionamento*/
          void turnOn();
          void turnOff();
          void lampeggia(int millTime);


    private:
        /*ATTRIBUTI*/
        int attachedPin=-1;
        bool state=LOW;
};

#endif
