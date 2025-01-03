#ifndef Buzzer_H
#define Buzzer_H

#include "Arduino.h"

/*convenzione: se pin = -1, il componente non è stato integrato bene
               (ad esempio, se attaccato ad un pin non valido)*/


class Buzzer{
    public:
        /*COSTRUTTORI*/
        Buzzer(int pin);

        /*METODI PUBBLICI*/
          /*metodi d'accesso*/
          int getAttachedPin();

          /*metodi d'aggiornamento, funzionamento*/
          void turnOn();
          void turnOff();


    private:
        /*ATTRIBUTI*/
        int attachedPin=-1;
};

#endif