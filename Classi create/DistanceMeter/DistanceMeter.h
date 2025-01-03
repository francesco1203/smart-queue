#ifndef DISTANCEMETER_H
#define DISTANCEMETER_H

#include "Arduino.h"

/*convenzione:
*/


class DistanceMeter{
    public:

        /*COSTRUTTORI*/
        DistanceMeter(int trigPin, int echoPin);

        /*METODI PUBBLICI*/
          /*metodi d'accesso*/
          int getAttachedTrigPin();
          int getAttachedEchoPin();
          float measureDistance();
          bool detectedMovement();      //rilevato movimento
          bool detectedPresence();      //rilevata presenza

          /*metodi d'aggiornamento*/
         

          /*VARIABILI STATIC*/
          static float thresholdSensitivityDistance;  //metri
          static float thresholdSensitivityTime;      //secondi

          /*METODI STATIC*/
          static void setThresholdSensitivityDistance(float newTreshold);
          static void setThresholdSensitivityTime(float newTreshold);
          

    private:
        /*ATTRIBUTI*/
        int attachedTrigPin=-1;
        int attachedEchoPin=-1;

        bool presenceFlag = false;
  
};

#endif
