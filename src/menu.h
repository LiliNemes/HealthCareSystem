/**
 * @file A főmenü függvény deklarációja.
 */

#ifndef NHF_MENU_H
#define NHF_MENU_H
//#define MEMTRACE


#include <iostream>

#include "memtrace.h"

#include "controller.h"
#include "AllUsers.h"
#include "AllSpecialists.h"

/**
 * A főmenűt kiíró függvény. A controller modulba tartozó függvényeket hív meg attól függően, hogy a felhasználó melyik lehetőséget választja.
 * Itt jön létre a program alapjául szolgáló két heterogén kollekció, az AllUsers és az AllSpecialists.
 * A menü a specifikációnak, egfelelően jön létre, kód beírása alapján lehet váltogatni a funkciókat.
 * Amennyiben nem a felsorolt funkciók egyikét (1-5) írja be a felhasználó, a program kilép a menüből és befejeződik.
 * @return hibakód eof esetén, egyébként 0.
 */
int menu();

#endif //NHF_MENU_H

