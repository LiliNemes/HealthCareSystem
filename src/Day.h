/**
 * @file A Day osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_DAY_H)
#define _DAY_H
//#define MEMTRACE

#include <stdexcept>
#include <string>
#include <ostream>

#include "memtrace.h"

/**
 * Egy naptárban szereplő napot jelképező osztály.
 */
class Day
{
private:
	std::string sections [4]; /**< A napon belüli időszakok tömbje. */
public:
    /**
     * Konstruktor.
     */
    Day()
    {
        for(int i=0; i<4; i++)
        {
            sections[i]="0";
        }
    }
    /**
     * A nap egy kiválasztott section-jébe beleírja a paraméterként kapott stringet, amennyiben
     * a sectionben 0 szerepel (nem foglal).
     * @param section a megadott section (1-4).
     * * @param who a megadott string.
     */
	void addEvent(int section, const std::string& who);
    /**
    * Exportálásért felelős függvény.
    * @return a file-ba kiírandó szöveg tartalom.
    */
    std::string exporter();
    /**
     * Kiírja a napot section-önként, tabulátorokkal elválasztva a megadott outputstreamre.
     * @param os a megadott outputstream.
     */
    void print(std::ostream& os);
    /**
     * Destruktor.
     */
    ~Day () = default;
};

#endif  //_DAY_H
