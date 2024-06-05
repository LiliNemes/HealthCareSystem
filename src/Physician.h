/**
 * @file A Physician osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_PHYSICIAN_H)
#define _PHYSICIAN_H
//#define MEMTRACE

#include <ostream>
#include <iostream>
#include <stdexcept>

#include "memtrace.h"

#include "User.h"
#include "AllUsers.h"
#include "Calendar.h"

class Patient;

/**
 * A háziorvost megvalósító osztály.
 */
class Physician : public User
{
protected:
	int numOfPatients; /**< páciensek darabszáma. */
	Patient** patients; /**< páciensekre mutatókat tároló dinamikus tömb. */
public:
    /**
     * Konstruktor.
     * @param n string név.
     * @param p Password jelszó.
     */
    Physician(const std::string &n, Password p) : User(n, p), numOfPatients(0)
    {
        patients=new Patient* [0];
    }

    /**
    * Exportálásért felelős függvény.
    * @return a file-ba kiírandó szöveg tartalom.
    */
	std::string exporter() override;

    /**
     * Létrehoz egy beteg-profilt, azt az összes profil és a saját betegei közé adja.
     * @param taj a beteg (leendő) jelszava.
     * @param name a beteg (leendő) neve.
     * @param users az összes profilt tároló heterogén kollekció, ebbe is bele kell tegye a függvény az új Patientet.
     */
    void addPatient(const std::string& taj,const std::string& name, AllUsers& users);
    /**
     * A paraméterként kapott string segítségével kiválasztja az egyik betegét, különböző műveleteket hajthat végre rajta (a lehetőségek a paraméterként lapott ostreamre íródhatnak).
     * @param taj annak a felhasználónak a TAJszáma/jelszava, akivel a műveleteket végre lehet hajtani.
     * @param os ide íródnak a függvény által kiírt dolgok.
     */
	void care(const std::string& taj, std::ostream& os);
    /**
     * Kiírja az orvos betegeit a paraméterként kapott ostreamre.
     * @param os ide ír a függvény.
     */
    void showPatients(std::ostream& os) const;
    /**
     * Már létező páciens hozzáadása a háziorvoshoz.
     * Az állapot file-ból történő visszaállításánál van rá szükség.
     * @param pPatient az eltárolandó páciens.
     */
    void addExistingPatient(Patient *pPatient);
    /**
     * Destruktor
     */
    ~Physician()
    {
        delete[] patients;
    }
};

#endif  //_PHYSICIAN_H
