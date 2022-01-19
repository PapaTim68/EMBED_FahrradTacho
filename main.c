/*
 * main.c:
 * Hauptprogramm
 * fuer die Musterloesung zu Laboraufgabe 5
 * (Implementation des Fahrradtachometers)
 *
 * Jan Bredereke, 2011-2021.
 */

#include "timer.h"
#include "tacho.h"

void main(void) {
    /* Initialisiere den Hardware-Timer auf Ticks alle 20 ms. */
    timerInit();
    /* Rufe die Initialisierung zur Implementation von SOF auf. */
    tachoInit();
    while(1) {
        /* Warte auf den naechsten Timer-Tick. */
        timerWait4Tick();
        /* Rufe die Implementation von SOF auf. */
        tacho();
    }
}
