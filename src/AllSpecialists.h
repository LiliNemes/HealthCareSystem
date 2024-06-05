/**
 * @file Az AllSpecialists osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_ALLSPECIALISTS_H)
#define _ALLSPECIALISTS_H
//#define MEMTRACE

#include "memtrace.h"

#include "Specialist.h"

/**
 * A szakorvosokat tároló osztály.
 */
class AllSpecialists
{
private:

	Specialist** allSps; /**< Szakorvosok mutatóit tároló dinamikusan foglalt tömb. */

	size_t num; /**< Tárolt szakorvosok száma. */
public:
    /**
     * Konstruktor. Paraméter nélküli.
     */
    AllSpecialists()
    {
        num=0;
        allSps=new Specialist*[num];
    }
    /**
     * A paraméterként kapott szakorvosra mutató pointert hozzáadja a Specialist*-okat tároló allSps tömbhöz.
     * @param sp A tömbhöz hozzáadandó szakorvosra mutató pointer.
     */
    void addSpecialist(Specialist* sp);
    /**
     * A paraméterként megadott típusú szakorvosok tömbjével tér vissza.
     * A szakorvosokat a Specialist::getType függvénye segítségével válogatja ki.
     * A dinamikusan foglalt tömb végjeles: utolsó eleme mindig nullpointer.
     * @param t milyen típusú szakorvosokkal térjen vissza
     * @return az adott típusú szakorvosok végjeles tömbje.
     */
	Specialist** filterType(int t);

    /**
     * Destruktor.Felszabadítja a dinamikusan foglalt allSps tömböt.
     */
    ~AllSpecialists()
    {
        delete[] allSps;
    }
};

#endif  //_ALLSPECIALISTS_H
