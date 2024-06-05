/**
 * @file A Password osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_PASSWORD_H)
#define _PASSWORD_H
//#define MEMTRACE

#include <string>
#include <fstream>
#include <stdexcept>

#include "memtrace.h"

/**
 * Jelszót kezelő osztály.
 */
class Password
{
	std::string pass; /**< A jelszó maga. */
public:
    /**
     * A Password osztály konstruktora, mely egy üres sztringet hoz létre.
     */
    Password();
    /**
     * Magával a string formájú jelszóval tér vissza.
     * @return a jelszó (pass).
     */
    std::string getter ()
    {
        return pass;
    }
    /**
     * Amennyiben a felhasználó érvényes jelszót adott meg, az lesz pass értéke és a visszatérési érték true.
     * Ha nem, false és a jelszó nem változik.
     * @param p a felhasználó által jelszónak megadott string.
     * @return true, ha jót adott meg, false, ha nem.
     */
	bool setPassword(const std::string& p);
    /**
     * Az == operátor felüldefiniálása, hogy összehasonlítható legyen a felhasználó által beírt string a profilhoz tartozó jelszóval.
     * Visszatérési értéke true ha megegyezik, false ha nem.
     * Ha a felhasználó átal megadott string "111111", akkor a program fájlba írja az adott profilhoz tartoó jelszót.
     * @param p a felhasználó által megadott jelszó (string).
     * @return true, ha jót adott meg, false, ha nem.
     */
	bool operator==(const std::string& p);
    /**
     * Exportálásért felelős függvény.
     * @return a file-ba kiírandó szöveg tartalom.
     */
    std::string exporter();
    /**
     * Destruktor
     */
    ~Password() = default;
};

#endif  //_PASSWORD_H
