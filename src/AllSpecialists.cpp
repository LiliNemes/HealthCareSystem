/**
 * @file Az Allspecialist osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "AllSpecialists.h"
//#define MEMTRACE

/**
 * A paraméterként kapott szakorvosra mutató pointert hozzáadja a Specialist*-okat tároló allSps tömbhöz.
 * @param sp A tömbhöz hozzáadandó szakorvosra mutató pointer.
 */
void AllSpecialists::addSpecialist(Specialist* sp)
{
    num++;
    Specialist** helper=new Specialist*[num];
    for(size_t i=0; i<num-1; i++)
    {
        helper[i]=allSps[i];
    }
    helper[num-1]=sp;
    delete[] allSps;
    allSps=helper;
}

/**
 * A paraméterként megadott típusú szakorvosok tömbjével tér vissza.
 * A szakorvosokat a Specialist::getType függvénye segítségével válogatja ki.
 * A dinamikusan foglalt tömb végjeles: utolsó eleme mindig nullpointer.
 * @param t milyen típusú szakorvosokkal térjen vissza
 * @return az adott típusú szakorvosok végjeles tömbje.
 */
Specialist** AllSpecialists::filterType(int t)
{
    size_t size=0;
    for(size_t i=0; i<num; i++)
    {
        if(allSps[i]->getType()==t)
            size++;
    }
    Specialist** thisType=new Specialist*[size+1];
    int g=0;
    for(size_t i=0; i<num; i++)
    {
        if(allSps[i]->getType()==t)
        {
            thisType[g]=allSps[i];
            g++;
        }
    }
    thisType[size] = nullptr;
    return thisType;
}



