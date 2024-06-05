/**
 * @file A Specialist osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "Specialist.h"
#include "Patient.h"

//#define MEMTRACE

/**
 * A szakorvos páciensei közé adódik egy beteg ha időpontot kér tőle. A szakorvos egy dinamikus tömbben tárolja a pácienseire mutató pointereket.
 * Ehhez a tömbhöz adódik hozzá a paraméterként kapott pointer.
 * Maga a hozzáadás egy új, kibővített tömb létrehozásából, az előző tömb törléséből áll.
 * @param p a hozzáadandó páciensre mutató pointer.
 */
void Specialist::addPatients(Patient* p)
{
    numOfPatients++;
    Patient** helper=new Patient*[numOfPatients];
    for(int i=0; i<numOfPatients-1; i++)
    {
        helper[i]=patients[i];
    }
    helper[numOfPatients-1]=p;
    delete[] patients;
    patients=helper;
}

/**
 * TAJ szám alapján kiválasztott beteggel (vagyis a rá mutató pointerrel) tér vissza.
 * A Specialist patient pointereket tároló patients tömbjén végigmegy, ha az adott páciens tajszáma (=jelszava) egyezik a megadottal visszatér egy rá mutató pointerrel.
 * Amennyiben nincs egyezés, kivételt dob.
 * @param taj a keresett páciens tajszáma stringként.
 * @return a keresett páciensre mutató pointer.
 */
Patient* Specialist::getPatient(const std::string& taj)
{
    for(int i=0; i<numOfPatients; i++)
    {
        if (patients[i]->getPassword().getter() == taj)
            return patients[i];
    }
    throw std::invalid_argument("Invalid ID!");

}

/**
 * A felhasználó által kiválasztott, paraméterként átadott időpontra beírja a beteg tajszámát.
 * Ugyanakkor beírja a paraméterként megadott páciens kalendárjába ugyanarra az időpontra a szakorvos nevét.
 * Meghívja a Specialist kalendárjára az addEvent függvényt, a páciensre a newAppointment függvényt.
 * @param day int, a megadott nap száma (1-31).
 * @param section int, a napon belül megadott szekció száma (1-4).
 * @param who a beírandó páciensre mutató pointer.
 */
void Specialist::refreshCalendar(int day, int section, Patient* who)
{
    if(day< 0 || day > 30 || section < 0 || section > 3)
        throw std::invalid_argument("Bad date format!");
    cal.addEvent(day, section, who->getPassword().getter());
    who->newAppointment(day, section, this->getName());
}

/**
* Exportálásért felelős függvény.
* @return a file-ba kiírandó szöveg tartalom.
*/
std::string Specialist::exporter()
{
    std::string ret = "Specialist\n";
    ret += name+"\n";
    ret += passW.exporter();
    ret += std::to_string(type)+"\n";
    ret += cal.exporter();

    ret+= "patients:\n";
    for(int i = 0; i < numOfPatients; i++){
        ret+=patients[i]->exporter();
    }

    ret +="end\n";

    return ret;
}

/**
 * A Specialist kalendárjának kiírására szolgáló függvény. Meghívja a Calendar print függvényét.
 * @param os ostream&, ahová a függvény kiírja a kalendárt.
 */
void Specialist::printCalendar(std::ostream& os)
{
    cal.print(os);
}

/**
 * A szakorvos típusának lekérdezésére szolgál.
 * @return szakorvos típusa.
 */
int Specialist::getType() const
{
    return type;
}

