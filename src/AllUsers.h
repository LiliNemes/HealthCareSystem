/**
 * @file Az AllUsers osztály tagfüggvényeinek deklarációi.
 */

#if !defined(_ALLUSERS_H)
#define _ALLUSERS_H
//#define MEMTRACE

#include "memtrace.h"

#include "User.h"

/**
 * A felhasználókra mutatókat tároló heterogén kollekció.
 */
class AllUsers
{
private:
	User** all; /**< A felhasználók mutatóit tároló, dinamikusan lefoglalt heterogén kollekció. */
	size_t num; /**< A tárolt felhasználók száma */
public:
    /**
	 * Paraméter nélküli konstruktor
	 */
    AllUsers() {
        num = 0;
        all = new User *[0];
    }
	/**
	 * A paraméterként megadott név alapján ellenőrzi, hogy létezik-e ilyen nevű felhasználó.
	 * @param name a keresett személy neve.
	 * @return létezik-e ilyen nevű felhasználó.
	 */
    bool contains(const std::string& name);
    /**
	 * A paraméterként megadott TAJ szám alapján ellenőrzi, hogy létezik-e ilyen TAJ számú felhasználó.
	 * @param ID a keresett személy TAJ száma.
	 * @return létezik-e ilyen TAJ számú/jelszavú felhasználó.
	 */
    bool containsID(const std::string& ID);
    /**
     * A paraméterként átvett felhasználót hozzáadja a felhasználók tömbjéhez.
     * @param l a hozzáadandó felhasználó.
     */
	void addUser(User *l);

    /**
     * A paraméterként kapott felhasználót megkeresi.
     * @param name a keresett profil neve.
     * @return kapott névhez tartozó profilra mutató pointer vagy nullptr.
     */
	User* getUser(const std::string& name);

    /**
     * File-ba kiíráshoz előállít egy stringet a tartalmából, melyet később majd vissza lehet olvasni.
     * @return stringbe írt tartalom.
     */
	std::string exporter ();

    /**
     * @return a tárolt felhasználók száma.
     */
    int getNum() const;

    /**
     * Destruktor, nem csak a dinamikusan foglalt tömböt szabadítja fel, hanem a benne tárolt pointereket is.
     */
    ~AllUsers()
    {
        for(size_t i=0; i<num; i++)
            delete all[i];
        delete[] all;
    }
};

#endif  //_ALLUSERS_H
