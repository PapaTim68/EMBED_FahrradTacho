/*
 * tacho.c:
 * Die Implementation von SOF
 * fuer die Loesung zu Laboraufgabe 5 (Implementation des Fahrradtachometers).
 * Dies ist eine Vorlage mit einem Rahmen, der von den Teilnehmern
 * zuende ausgefuellt werden muss.
 *
 * Autor der Vorlage: Jan Bredereke, 2011-2021.
 *
 * Autoren der Loesung: 
 */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Definiere die Namen der Special-Function-Register des C515C-Prozessors. */
#include <REG515C.H>

#include "tacho.h"

/* =========== Konstanten =========== */

/* Die Zeit fuer eine Polling-Periode bzw. fuer einen Umlauf des endlichen
 * Automaten, in Sekunden:
 */
#define POLL_PERIODE 0.020

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* =========== Hardware-Schnittstellen-Definitionen =========== */

/* Eingabeleitungen: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Ausgabeleitungen: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* =========== Lokale Typdefinitionen =========== */

/* Zustandsmenge des Endlichen Automaten fuer die Mode-Klasse: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* =========== Lokale Variablen =========== */

/* (Anmerkung: Der Datentyp "bit" ist eine Erweiterung von Keil
 * gegenueber dem Standard-ANSI-C.)
 */

/* Eingabevariablen: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Bedingungen der aktuellen Runde: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Bedingungen der vorigen Runde: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Ereignisse der aktuellen Runde: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Ausgabevariablen: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Die Variable, die den aktuellen Mode der Mode-Klasse enthaelt: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Die bei Ereignissen gemerkten Zeiten: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Die gezaehlten Hilfswerte: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* Die bei Ereignissen gemerkten gezaehlten Hilfswerte: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

/* =========== Lokale Funktionen =========== */

/* ----------- Hilfsfunktionen ----------- */

/* Die folgenden Hilfsfunktionen sind eng an das Anforderungsdokument 
 * angelehnt. Ihre Bedeutung kann dort nachgeschlagen werden.
 */

static unsigned char fM2hm(unsigned long int meter) {
    return meter / 100;
}

static unsigned char fM2dam(unsigned long int meter) {
    return meter / 10;
}

static unsigned long int fGesamtstreckeMess() {
    return cntUmdrehungIn * RADUMFANG;
}

static unsigned long int fTagesstreckeMess() {
    return (cntUmdrehungIn - cntUmdrehungInLastReset) * RADUMFANG;
}

static unsigned char fVStufenOut(void) {
    unsigned char stufenCurr = 
      (KMH_PRO_MS * RADUMFANG / ((iT - iTLastEUmdrehungIn) * POLL_PERIODE)) / 3;
    if (eUmdrehungIn ) {
        stufenOld = stufenCurr;
    }
    else {
        if (stufenCurr < stufenOld) {
            stufenOld = stufenCurr;
        }
    }
    return stufenOld;
}

static unsigned char fVAnz(void) {
    return ((1 << fVStufenOut()) - 1)^0xff;
}

static unsigned char int2dualOut(unsigned char intWert) {
    return (intWert^0xff) & 0x3f;
}

static unsigned char fGesamtstreckeOut(void) {
    return int2dualOut(fM2hm(fGesamtstreckeMess()))
           | 0x40;
}

static unsigned char fTagesstreckeOut(void) {
    return int2dualOut(fM2dam(fTagesstreckeMess()));
}

/* ----------- Standardfunktionen fuer ein reaktives System ----------- */

/* Lies die Eingabevariablen aus den Eingangsleitungen. */
static void readInputVars(void) {

    /* HIER EIGENE LOESUNG EINSETZEN. */

    return;
}

/* Berechne den neuen Zustand und die Ausgabevariablen aus den
 * eingelesenen und nun unveraenderlichen Eingabevariablen. */
static void computeOutputVars(void) {
    /* HIER EIGENE LOESUNG EINSETZEN. */

    /* Zustandsuebergangsfunktion: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

    /* Ausgabefunktion: */

    /* HIER EIGENE LOESUNG EINSETZEN. */

    return;
}

/* Schreibe die Ausgabevariablen auf die Ausgabeleitungen. */
static void writeOutputVars(void) {

    /* HIER EIGENE LOESUNG EINSETZEN. */

    return;
}

/* =========== Exportierte Funktionen =========== */

/* Die Implementation von SOF. */
void tacho(void) {
    /* Diese Funktion wird von der Timer-Interrupt-Steuerung alle 
     * POLL_PERIODE aufgerufen. */

    readInputVars();
    computeOutputVars();
    writeOutputVars();

    return;
}

/* Die Initialisierung zur Implementation von SOF. */
void tachoInit(void) {

    /* HIER EIGENE LOESUNG EINSETZEN. */

    return;
}
