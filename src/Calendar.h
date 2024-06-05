/**
 * @file A Calendar osztály tagfüggvvényeinek a deklarációi.
 */

#if !defined(_CALENDAR_H)
#define _CALENDAR_H
//#define MEMTRACE

#include <string>
#include <stdexcept>
#include <iostream>

#include "memtrace.h"

#include "Day.h"

/**
 * Naptár osztály egy hónap bejegyzett eseményei tárolására.
 */
class Calendar
{
private:
	Day days [31]; /**< A napok tömbje. */
public:
    /**
     * Paraméter nélküli konstruktor, mely nullákkal tölti fel a kalendárt.
     */
    Calendar()
    {
        for(int i=0; i<31; i++)
        {
            days[i]=Day();
        }
    }
    /**
     * /Kiírja a paraméterként kapott ostreamre a naptárat úgy, hogy a naptárban szereplő 31 napra
     * meghívja a Day osztály print függvényét.
     * @param os paraméterként kapott ostream.
     */
	void print(std::ostream& os);
    /**
     * Időpont hozzáadása a naptárhoz.
     * @param day a nap száma, 1 és 31 közötti egész szám.
     * @param section napszak, 1 és 4 közötti egész szám.
     * @param who a szakorvos neve.
     */
	void addEvent(int day, int section, const std::string& who);
    /**
     * Exportálásért felelős függvény.
     * @return a file-ba kiírandó szöveg tartalom.
     */
	std::string exporter();
    /**
     * Destruktor
     */
    ~Calendar() = default;
};

#endif  //_CALENDAR_H
