/**
 * @file A User osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_USER_H)
#define _USER_H
//#define MEMTRACE

#include "memtrace.h"

#include "Password.h"

/**
 * Absztrakt alaposztály.
 */
class User
{
protected:
	std::string name; /**< a felhasználó neve. */
	Password passW; /**< a felhasználó jelszava. */
public:
    /**
     * Konstruktor.
     * @param n felhasználó neve.
     * @param p felhasználó jelszava.
     */
    User(const std::string& n, Password p)
    {
        name=n;
        passW=p;
    }
    /**
     * Getter a jelszónak.
     * @return a felhasználóhoz tartozó jelszóval
     */
	Password getPassword();

	/**
	 * Exportálásért felelős függvény.
	 */
    virtual std::string exporter()=0;

	/**
	 * Getter a névnek.
	 * @return a profilhoz tartozó név.
	 */
    std::string getName();

    /**
     * Destruktor
     */
    virtual ~User(){}
};

#endif  //_USER_H
