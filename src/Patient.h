/**
 * @file A Patient osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_PATIENT_H)
#define _PATIENT_H
//#define MEMTRACE

#include <ostream>
#include <iostream>

#include "memtrace.h"

#include "User.h"
#include "Calendar.h"
#include "AllSpecialists.h"


/**
 * Pácienst megvalósító osztály.
 */
class Patient : public User
{
private:
	bool vaccination; /**< oltottság. */
	int* refferals; /**< beutalókat tároló dinamikus tömb. */
	size_t numOfRefferals; /**< tárolt beutalók darabszáma. */
	std::string* prescriptions; /**< dinamikusan tárolt receptek. */
	size_t numOfPrescriptions; /**< tárolt receptek darabszáma */
	std::string* additionalInformation; /**< dinamikusan tárolt egyéb információk a pácienssel kapcsolatban. */
	size_t numOfAdditional; /**< dinamikusan tárolt egyéb információk darabszáma. */
	Calendar appointments; /**< naptár, melyben a lefoglalt időpontok szerepelnek. */
public:
    /**
     * Konstruktor.
     * @param Name string név
     * @param pass Password jelszó.
     * @param a Calendar kalendár.
     */
    Patient(const std::string& Name, Password pass, Calendar a) : User(Name, pass)
    {
        vaccination= false;
        numOfRefferals=0;
        refferals=new int[0];
        numOfPrescriptions=0;
        prescriptions=new std::string[0];
        numOfAdditional=0;
        additionalInformation=new std::string[0];
        appointments=a;
    }
    /**
     * Bejelöli, hogy egy beteg megkapta az oltást.
     */
	void gotVaccinated();
    /**
     * Szakorvoshoz beutalót adó függvény. A beutalók tömbjéhez hozzáadódik.
     * @param n a célzott szakorvos típusa.
     */
	void newRefferal(int n);
    /**
     * Recept írható fel vele.
     * @param p a recept szövege.
     */
	void newPrescription(const std::string& p);
    /**
     * Megjegyzés adható vele a beteg profiljához.
     * @param I a hozzáadandó információ.
     */
	void newInformation(const std::string& I);
    /**
     * A beteg ezzel megtekinti, hogy van-e számára felírt recept.
     * Amennyiben van, azt a függvény file-ba exportálja.
     */
	void getPrescription();
    /**
     * A beteg megtekintheti, hogy megkapta-e az oltást.
     * Eportálhatja az oltási igazolványát file-ba.
     */
    void getVaccinationInformation();
    /**
     * A függvény kiírja a páciens háziorvosoktól kapott beutalóit.
     * Minden beutalóhoz kiírja a paraméterként kapott ostreamre az adott szakterületen dolgozó orvosok neveit.
     * @param list Az összes szakorvos listája, melyből a függvény a filterType függvény segítségével válogat.
     * @param os ide ír a függvény .
     */
    void chooseRefferals(AllSpecialists& list, std::ostream& os);
    /**
     * Kiírja a beteg kalendárját (meghívja a kalendár print függvényét).
     * @param os  ostream, ide ír a függvény.
     */
    void printAppointments(std::ostream& os);
    /**
     *  Új szakorvosi időpont adható a beteg kalendárjába.
     *  Meghívja a kalendár addEvent függvényét.
     * @param day melyik napra (1-31).
     * @param sec a nap melyik szekciójába (1-4).
     * @param who string, a szakorvos neve.
     */
    void newAppointment(int day, int sec, const std::string& who);

    /**
    * Exportálásért felelős függvény.
    * @return a file-ba kiírandó szöveg tartalom.
    */
	std::string exporter() override;
    /**
     * Destruktor. Megszünteti a dinamikusan létrehozott attribútumait.
     */
    ~Patient() override
    {
        delete[] refferals;
        delete[] prescriptions;
        delete[] additionalInformation;
    };


};

#endif  //_PATIENT_H
