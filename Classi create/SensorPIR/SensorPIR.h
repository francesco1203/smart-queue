#ifndef SENSORPIR_H
#define SENSORPIR_H

#include "Arduino.h"

/*convenzione:
*/


class SensorPIR{
    public:
        /*COSTRUTTORI*/
        SensorPIR(int signalPin);

        /*METODI PUBBLICI*/
          /*metodi d'accesso*/
          int getAttachedSignalPin();
          bool detectedMovement();      //rilevato movimenti

          /*metodi d'aggiornamento*/

    private:
        /*ATTRIBUTI*/
        int attachedSignalPin=-1;
        
};

#endif
