#include "AudioSampling.h"
#include <arduinoFFT.h>

int gBandValues[NUM_BANDS];

int bandValues[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
double vReal[SAMPLES];
double vImag[SAMPLES];
arduinoFFT FFT = arduinoFFT(vReal, vImag, SAMPLES, SAMPLING_FREQ);
unsigned int sampling_period_us = round(1000000 * (1.0 / SAMPLING_FREQ));
unsigned long newTime;

void sampleTask(void* parameter) {

    //Serial.println("1");
	for (;;) {
        //Sample the data
        for (int i = 0; i < NUM_BANDS; i++) {
            bandValues[i] = 0;
        }
        //Serial.println("2");
        // Sample the audio pin
        for (int i = 0; i < SAMPLES; i++) {
            newTime = micros();
            vReal[i] = analogRead(AUDIO_IN_PIN); // A conversion takes about 9.7uS on an ESP32
            vImag[i] = 0;
            //Serial.println("3");
            //yield();
            while ((micros() - newTime) < sampling_period_us) { /* chill */ }
        }
        //Serial.println("4");
        // Compute FFT
        FFT.DCRemoval();
        FFT.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
        FFT.Compute(FFT_FORWARD);
        FFT.ComplexToMagnitude();

        // Analyse FFT results
        for (int i = 2; i < (SAMPLES / 2); i++) {       // Don't use sample 0 and only first SAMPLES/2 are usable. Each array element represents a frequency bin and its value the amplitude.
            if (vReal[i] > NOISE) {                    // Add a crude noise filter

            /*8 bands, 12kHz top band
              if (i<=3 )           bandValues[0]  += (int)vReal[i];
              if (i>3   && i<=6  ) bandValues[1]  += (int)vReal[i];
              if (i>6   && i<=13 ) bandValues[2]  += (int)vReal[i];
              if (i>13  && i<=27 ) bandValues[3]  += (int)vReal[i];
              if (i>27  && i<=55 ) bandValues[4]  += (int)vReal[i];
              if (i>55  && i<=112) bandValues[5]  += (int)vReal[i];
              if (i>112 && i<=229) bandValues[6]  += (int)vReal[i];
              if (i>229          ) bandValues[7]  += (int)vReal[i];*/

              //16 bands, 12kHz top band
                if (i <= 2)           bandValues[0] += (int)vReal[i];
                if (i > 2 && i <= 3) bandValues[1] += (int)vReal[i];
                if (i > 3 && i <= 5) bandValues[2] += (int)vReal[i];
                if (i > 5 && i <= 7) bandValues[3] += (int)vReal[i];
                if (i > 7 && i <= 9) bandValues[4] += (int)vReal[i];
                if (i > 9 && i <= 13) bandValues[5] += (int)vReal[i];
                if (i > 13 && i <= 18) bandValues[6] += (int)vReal[i];
                if (i > 18 && i <= 25) bandValues[7] += (int)vReal[i];
                if (i > 25 && i <= 36) bandValues[8] += (int)vReal[i];
                if (i > 36 && i <= 50) bandValues[9] += (int)vReal[i];
                if (i > 50 && i <= 69) bandValues[10] += (int)vReal[i];
                if (i > 69 && i <= 97) bandValues[11] += (int)vReal[i];
                if (i > 97 && i <= 135) bandValues[12] += (int)vReal[i];
                if (i > 135 && i <= 189) bandValues[13] += (int)vReal[i];
                if (i > 189 && i <= 264) bandValues[14] += (int)vReal[i];
                if (i > 264) bandValues[15] += (int)vReal[i];
            }
        }
        
        //ToDo Send the data to the handler
        //Take lock
        //Copy and inform new measurements have arrived
        //Give Lock
	}
}