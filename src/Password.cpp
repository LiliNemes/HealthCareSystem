/**
 * @file A Password osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "Password.h"

//#define MEMTRACE

/**
 * A Password osztály konstruktora, mely egy üres sztringet hoz létre.
 */
Password::Password()
{
    pass = "";
}

/**
 * Amennyiben a felhasználó érvényes jelszót adott meg, az lesz pass értéke és a visszatérési érték true.
 * Ha nem, false és a jelszó nem változik.
 * @param p a felhasználó által jelszónak megadott string.
 * @return true, ha jót adott meg, false, ha nem.
 */
bool Password::setPassword(const std::string& p)
{
    if (p.length() == 6 && p!= "111111")
    {
        pass = p;
        return true;
    }
    else
        return false;
}

/**
 * Az == operátor felüldefiniálása, hogy összehasonlítható legyen a felhasználó által beírt string a profilhoz tartozó jelszóval.
 * Visszatérési értéke true ha megegyezik, false ha nem.
 * Ha a felhasználó átal megadott string "111111", akkor a program fájlba írja az adott profilhoz tartozó jelszót.
 * @param p a felhasználó által megadott jelszó (string).
 * @return true, ha jót adott meg, false, ha nem.
 */
bool Password::operator==(const std::string& p)
{

    if(p=="111111")
    {
        std::fstream fs;
        fs.open("password.txt", std::ios_base::out);
        if(fs.is_open()) {
            fs << pass;
            fs.close();
        }
        else
            throw std::runtime_error("Couldn't open jelszo.txt to write password.");
        return false;
    }
    else if(pass == p){
        return true;
    }
    else
        return false;

}

/**
* Exportálásért felelős függvény.
* @return a file-ba kiírandó szöveg tartalom.
*/
std::string Password::exporter()
{
    std::string ret = "Password\n";
    ret += std::string(pass)+"\n";
    ret += "end\n";
    return ret;
}

