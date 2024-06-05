/**
 * @file A Calendar osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "Calendar.h"

//#define MEMTRACE

/**
 * /Kiírja a paraméterként kapott ostreamre a naptárat úgy, hogy a naptárban szereplő 31 napra
 * meghívja a Day osztály print függvényét.
 * @param os paraméterként kapott ostream.
 */
void Calendar::print(std::ostream& os)
{
    for(int i=0; i<31; i++)
    {
        os<<i<<"\t";
        days[i].print(os);
    }
}

/**
 * Időpont hozzáadása a naptárhoz.
 * @param day a nap száma, 1 és 31 közötti egész szám.
 * @param section napszak, 1 és 4 közötti egész szám.
 * @param who a szakorvos neve.
 */
void Calendar::addEvent(int day, int section, const std::string& who)
{
    try
    {
        days[day].addEvent(section, who);
    }
    catch(std::invalid_argument& e){
        std::cout<<e.what()<<std::endl;
    }
}

/**
* Exportálásért felelős függvény.
* @return a file-ba kiírandó szöveg tartalom.
*/
std::string Calendar::exporter()
{
    std::string ret = "Calendar\n";

    ret += "events:\n";
    for(int i=0; i<31; i++)
    {
        std::string tmp = days[i].exporter();
        if(!tmp.empty()) {
            ret+= std::to_string(i+1)+":"+tmp;
        }
    }

    ret += "end\n";

    return ret;
}

