#include "Arduino.h"
#include "LedRGB.h"        //header che stiamo implementando


/*COSTRUTTORI*/
LedRGB::LedRGB(int redPin, int greenPin, int bluePin){
    if(redPin >= 0 && redPin <= 35){ //pin valido 
        attachedRedPin = redPin;
        pinMode(redPin, OUTPUT);
    }

    if(greenPin >= 0 && greenPin <= 35){ //pin valido 
        attachedGreenPin = greenPin;
        pinMode(greenPin, OUTPUT);
    }

    if(bluePin >= 0 && bluePin <= 35){ //pin valido 
        attachedBluePin = bluePin;
        pinMode(bluePin, OUTPUT);
    }
}

/*METODI PUBBLICI*/
    /*metodi d'accesso*/
    int LedRGB::getAttachedRedPin(){return attachedRedPin;}
    int LedRGB::getAttachedGreenPin(){return attachedGreenPin;}
    int LedRGB::getAttachedBluePin(){return attachedBluePin;}
    char LedRGB::getActualColor(){return actualColor;}

    /*metodi d'aggiornamento, funzionamento*/
    
    void LedRGB::setActualColor(char color){

        switch(color){

            case 'r':
                setRed(HIGH);
                setGreen(LOW);
                setBlue(LOW);
            break;

            case 'g':
                setRed(LOW);
                setGreen(HIGH);
                setBlue(LOW);
            break;

            case 'b':
                setRed(LOW);
                setGreen(LOW);
                setBlue(HIGH);
            break;

            case 'y':
                setRed(HIGH);
                setGreen(HIGH);
                setBlue(LOW);
            break;

            default:    //colore non valido -> spegne
                setRed(LOW);
                setGreen(LOW);
                setBlue(LOW);
        }

        actualColor = color;
    }

    void LedRGB::turnOff(){setActualColor('/');}

    void LedRGB::lampeggia(char color, int millTime){
        switch(color){

            case 'r':
                setGreen(LOW);
                setBlue(LOW);
                setRed(HIGH);
                delay(millTime);
                setRed(LOW);
            break;

            case 'g':
                setRed(LOW);
                setBlue(LOW);
                setGreen(HIGH);
                delay(millTime);
                setGreen(LOW);
            break;

            case 'b':
                setRed(LOW);
                setGreen(LOW);
                setBlue(HIGH);
                delay(millTime);
                setBlue(LOW);
            break;

            default:    //colore non valido
                setRed(LOW);
                setGreen(LOW);
                setBlue(LOW);
        }

        actualColor = 'L';
    }

/*METODI PRIVATI*/
void LedRGB::setRed(int lowOrHigh){
    if(attachedRedPin >= 1 && attachedRedPin <= 35) //pin valido 
        digitalWrite(attachedRedPin, lowOrHigh);
}

void LedRGB::setGreen(int lowOrHigh){
    if(attachedGreenPin >= 1 && attachedGreenPin <= 35) //pin valido 
        digitalWrite(attachedGreenPin, lowOrHigh);
}

void LedRGB::setBlue(int lowOrHigh){
    if(attachedBluePin >= 1 && attachedBluePin <= 35) //pin valido 
        digitalWrite(attachedBluePin, lowOrHigh);
}
