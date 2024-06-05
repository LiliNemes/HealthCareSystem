/**
 * @file A vezérlő függvények deklarációi.
 */
 
#ifndef NHF_CONTROLLER_H
#define NHF_CONTROLLER_H
//#define MEMTRACE

#include <string>
#include <iostream>
#include <fstream>

#include "memtrace.h"

#include "AllUsers.h"
#include "AllSpecialists.h"


/**
 * A háziorvosként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg, ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void physician_sign_in (AllUsers& Users);

/**
 * A páciensként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg, ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 * @param Specialists az sszes szakorvosi profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void patient_sign_in (AllUsers& Users, AllSpecialists& Specialists);

/**
 * A szakorvosként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg,ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 * @param Specialists az sszes szakorvosi profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void specialist_sign_in (AllUsers& Users, AllSpecialists& Specialists);

/**
 * A paraméterként megadott string segítségével beolvassa a rendszer állapotát.
 * @param allUsers a felhasználókat tároló objektum.
 * @param allSpecialists a szakorvosokat tároló objektum.
 * @param file a beolvasandó file elérési útja.
 */
 void import_state(AllUsers& allUsers, AllSpecialists& allSpecialists, const std::string& file);

/**
 * A fileba kiírás vezérléséért felelős függvény.
 * @param users a felhasználókat tároló objektum.
 * @param specialists a szakorvosokat tároló objektum.
 */
void export_state(AllUsers& users);
#endif //NHF_CONTROLLER_H
