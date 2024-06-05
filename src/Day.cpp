/**
 * @file A Day osztály tagfüggvényeinek definíciói.
 */

#include "memtrace.h"

#include "Day.h"

//#define MEMTRACE

/**
 * A nap egy kiválasztott section-jébe beleírja a paraméterként kapott stringet, amennyiben
 * a sectionben 0 szerepel (nem foglal).
 * @param section a megadott section (1-4).
 * @param who a megadott string.
 */
void Day::addEvent(int i, const std::string& who)
{
    if(sections[i]!="0")
        throw std::invalid_argument("This section is already preserved.");
    else
        sections[i] = who;
}

/**
 * Exportálásért felelős függvény.
 * @return a file-ba kiírandó szöveg tartalom.
 */
std::string Day::exporter()
{
    std::string ret;
    
    for(int j = 0; j < 4; j++)
    {
        if(sections[j] != "0")
        {
            ret += std::to_string(j)+":"+sections[j]+"\n";
        }
    }
    
    return ret;
}

/**
 * Kiírja a napot section-önként, tabulátorokkal elválasztva a megadott outputstreamre.
 * @param os a megadott outputstream.
 */
 void Day::print(std::ostream& os)
{
    for (int i = 0; i < 4; i++)
        os << sections[i] << (std::string) "\t";
    os<<std::endl;
}

