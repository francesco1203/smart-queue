#ifndef LedRGB_H
#define LedRGB_H

#include "Arduino.h"

/*convenzione:

    se pin = -1, il componente non è stato integrato bene
    (ad esempio, se attaccato ad un pin non valido)

    se actualColor = 'L' vuol dire lampeggio in corso
               
    COLORI DISPONIBILI:
    -r = red
    -g = green
    -b = blue
    -y = yellow
*/


class LedRGB{
    public:
        /*COSTRUTTORI*/
        LedRGB(int redPin, int greenPin, int bluePin);

        /*METODI PUBBLICI*/
          /*metodi d'accesso*/
          int getAttachedRedPin();
          int getAttachedGreenPin();
          int getAttachedBluePin();
          char getActualColor();

          /*metodi d'aggiornamento, funzionamento*/
          void setActualColor(char color);
          void lampeggia(char color, int millTime);
          void turnOff();


    private:
        /*ATTRIBUTI*/
        int attachedRedPin=-1;
        int attachedGreenPin=-1;
        int attachedBluePin=-1;
        char actualColor='/';

        /*METODI PRIVATI*/
        void setRed(int lowOrHigh);
        void setGreen(int lowOrHigh);
        void setBlue(int lowOrHigh);
};

#endif
