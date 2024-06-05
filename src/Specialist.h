/**
 * @file A Specialist osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_SPECIALIST_H)
#define _SPECIALIST_H
//#define MEMTRACE

#include <stdexcept>

#include "memtrace.h"

#include "Physician.h"
#include "Calendar.h"


class Patient;

/**
 * Szakorvost megvalósító osztály.
 */
class Specialist : public Physician{
private:
    int type; /**< a szakorvos típusát jelölő egész szám. */
	Calendar cal; /**< a szakorvos naptárja, melyben a páciensek foglalt időpontjai találhatók. */
public:
    /**
     * Konstruktor
     * @param n név (name)
     * @param p jelszó (password)
     * @param a kalendár (appointments)
     * @param t típus (type)
     */
    Specialist(const std::string &n, Password p, Calendar a, int t) : Physician(n, p), type(t), cal(a) {}

    /**
     * A szakorvos páciensei közé adódik egy beteg ha időpontot kér tőle. A szakorvos egy dinamikus tömbben tárolja a pácienseire mutató pointereket.
     * Ehhez a tömbhöz adódik hozzá a paraméterként kapott pointer.
     * Maga a hozzáadás egy új, kibővített tömb létrehozásából, az előző tömb törléséből áll.
     * @param p a hozzáadandó páciensre mutató pointer.
     */
    void addPatients(Patient* p);

    /**
     * TAJ szám alapján kiválasztott beteggel (vagyis a rá mutató pointerrel) tér vissza.
     * A Specialist patient pointereket tároló patients tömbjén végigmegy, ha az adott páciens tajszáma (=jelszava) egyezik a megadottal visszatér egy rá mutató pointerrel.
     * Amennyiben nincs egyezés, kivételt dob.
     * @param taj a keresett páciens tajszáma stringként.
     * @return a keresett páciensre mutató pointer.
     */
	Patient* getPatient(const std::string& taj);

    /**
     * A felhasználó által kiválasztott, paraméterként átadott időpontra beírja a beteg tajszámát.
     * Ugyanakkor beírja a paraméterként megadott páciens kalendárjába ugyanarra az időpontra a szakorvos nevét.
     * Meghívja a Specialist kalendárjára az addEvent függvényt, a páciensre a newAppointment függvényt.
     * @param day int, a megadott nap száma (1-31).
     * @param section int, a napon belül megadott szekció száma (1-4).
     * @param who a beírandó páciensre mutató pointer.
     */
	void refreshCalendar(int day, int section, Patient* who);

    /**
     * Exportálásért felelős függvény.
     * @return a file-ba kiírandó szöveg tartalom.
     */
	std::string exporter();

    /**
     * A Specialist kalendárjának kiírására szolgáló függvény. Meghívja a Calendar print függvényét.
     * @param os ostream&, ahová a függvény kiírja a kalendárt.
     */
	void printCalendar(std::ostream& os);

    /**
    * A szakorvos típusának lekérdezésére szolgál.
    * @return szakorvos típusa.
    */
	int getType() const;

};

#endif  //_SPECIALIST_H
