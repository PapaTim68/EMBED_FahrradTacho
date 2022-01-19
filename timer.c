/*
 * timer.c:
 * Timersteuerung
 * fuer die Musterloesung zu Laboraufgabe 5
 * (Implementation des Fahrradtachometers)
 *
 * Jan Bredereke, 2011-2021.
 */

/* Definiere die Namen der Special-Function-Register des C515C-Prozessors. */
#include <REG515C.H>

#include "timer.h"

/* =========== Konstanten =========== */

/* Nummer des Interrupts von Timer 1. */
#define INTR_TIMER1 3

/* Berechne die Anzahl der Zaehlschritte bis zum naechsten Interrupt: */

/* Frequenz des Uhr-Interrupts: 50 Hz, entsprechend 20 ms Periodendauer
   Frequenz des Systemtakts: 10.000.000 Hz
   Vorteiler fuer Zeitgeber: 6
   (Anmerkung: beim Mikrocontroller 8051 ist der Vorteiler 12)
   Anzahl der Zaehlschritte bis zum naechsten Interrupt:
   ((10.000.000 Hz / 6) / 50 Hz) = 33.333,333...
 */
#define ZAEHL_BIS_INTR 33333

/* Anzahl der Zaehlschritte, die waehrend der Dauer der
   Interruptverarbeitung ausfallen (experimentell ermittelt).
 */
#define ZAEHL_AUSFALL 9

/* Anzahl der zu zaehlenden Zaehlschritte. */
#define ZAEHL_SCHRITTE (ZAEHL_BIS_INTR - ZAEHL_AUSFALL)

/* Startwert fuer den Zahler, der noch die zu zaehlenden Zaehlschritte
   vom Ueberlaufen entfernt ist. */
#define ZAEHL_START (0x10000 - ZAEHL_SCHRITTE)

/* =========== Lokale Variablen =========== */

/* (Anmerkung: Der Datentyp "bit" ist eine Erweiterung von Keil
 * gegenueber dem Standard-ANSI-C.)
 */

/* Flag, das von der Interrupt-Routine jedes Mal auf 1 gesetzt wird. */
static bit lTimerTick;

/* =========== Exportierte Funktionen =========== */

/* Initialisiere den Hardware-Timer auf Ticks alle 20 ms. */
void timerInit(void) {
    /* Initialisiere Timer 1 des C515C als 16-Bit-Zeitgeber mit
    Ausloesung von Interrupts. */

    /* Setze Timer-Modus:
     * Untere 4 Bit: Timer 0, hier egal.
     * Obere 4 Bit: Timer 1 (von links nach rechts):
     *   Gate=0: Aeussere Freigabe ist deaktiviert.
     *   C//T=0: Interner Takt.
     *   M1=0, M0=1: Mode 1, 16-Bit-Zaehler/Zeitgeber ohne Reload.
     */
    TMOD = 0x10;

    /* Lade Startwert in Timer 1. */
    TL1 = ZAEHL_START;
    TH1 = ZAEHL_START >> 8;

    /* Setze Timer 1 auf hoechste Prioritaet 3, alles andere auf
     * niedrigste Prioritaet 0. */
    IP0 = 0x080;
    IP1 = 0x080;

    /* Interrupt fuer Timer 1 freigeben. */
    ET1 = 1;

    /* Interrupts grundsaetzlich freigeben ("ea" wird auch "eal"
     * genannt).
     */
    EAL = 1;

    /* Setze das Timer-Tick-Flag zurueck. */
    lTimerTick = 0;

    /* Takt fuer Timer 1 freigeben ("run"). */
    TR1 = 1;

    return;
}

/* Warte auf den naechsten Timer-Tick. */
void timerWait4Tick(void) {
    /* Warte auf 0/1-Flanke. */
    while (!lTimerTick) {};

    /* Setze das Timer-Tick-Flag zurueck. */
    lTimerTick = 0;

    return;
}

/* =========== Lokale Funktionen =========== */

void timerIntr() interrupt INTR_TIMER1 {
    /* Die Ausfuehrungszeit fuer diesen ersten Teil der Interrupt-Routine 
     * muss bei der Berechnung der Laufzeit des Timers beruecksichtigt 
     * werden.
     */

    /* Halte Timer 1 an, um neue Werte einzuschreiben. */
    TR1 = 0;

    /* Lade Startwert in Timer 1. */
    TL1 = ZAEHL_START;
    TH1 = ZAEHL_START >> 8;

    /* Starte Timer 1 wieder. */
    TR1 = 1;

    /* Der Rest dieser Interrupt-Routine ist nicht mehr so zeitkritisch. */

    /* Setze das Timer-Tick-Flag. */
    lTimerTick = 1;

    return;
}
