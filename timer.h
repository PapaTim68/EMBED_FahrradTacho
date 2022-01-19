/*
 * timer.h:
 * Timersteuerung
 * fuer die Musterloesung zu Laboraufgabe 5
 * (Implementation des Fahrradtachometers)
 *
 * Jan Bredereke, 2011-2021.
 */

#ifndef TIMER_H
#define TIMER_H

/* Initialisiere den Hardware-Timer auf Ticks alle 20 ms. */
void timerInit(void);

/* Warte auf den naechsten Timer-Tick. */
void timerWait4Tick(void);

#endif
