/**
 * @file Az AllUsers osztály tagfüggvényeinek a definíciói.
 */
#include "memtrace.h"

#include "AllUsers.h"
//#define MEMTRACE

/**
 * A paraméterként megadott név alapján ellenőrzi, hogy létezik-e ilyen nevű felhasználó.
 * @param name a keresett személy neve.
 * @return létezik-e ilyen nevű felhasználó.
 */
 bool AllUsers::contains(const std::string& name)
{
    for (size_t i = 0; i < num; i++)
    {
        if (name == all[i]->getName())
        {
            return true;
        }
    }
    return false;
}
/**
 * A paraméterként megadott TAJ szám alapján ellenőrzi, hogy létezik-e ilyen TAJ számú/jelszavú felhasználó.
 * @param ID a keresett személy azonosítója.
 * @return létezik-e ilyen jelszavú/TAJ számú felhasználó.
 */
bool AllUsers::containsID(const std::string& ID)
{
    for (size_t i = 0; i < num; i++)
    {
        if (ID == all[i]->getPassword().getter())
        {
            return true;
        }
    }
    return false;
}
/**
 * A paraméterként átvett felhasználót hozzáadja a felhasználók tömbjéhez.
 * @param l a hozzáadandó felhasználó.
 */
void AllUsers::addUser(User *l)
{
    num++;
    User **helper = new User *[num];

    for (size_t i = 0; i < num - 1; i++)
    {
        helper[i] = all[i];
    }
    helper[num - 1] = l;

    delete[] all;
    all = helper;

}

/**
 * A paraméterként kapott felhasználót megkeresi.
 * @param name a keresett profil neve.
 * @return kapott névhez tartozó profilra mutató pointer vagy nullptr.
 */
User *AllUsers::getUser(const std::string &name)
{
    for (size_t i = 0; i < num; i++)
    {
        if (name == all[i]->getName())
        {
            return all[i];
        }
    }
    return nullptr;
}

/**
 * File-ba kiíráshoz előállít egy stringet a tartalmából, melyet később majd vissza lehet olvasni.
 * @return stringbe írt tartalom.
 */
std::string AllUsers::exporter()
{
    std::string output = "AllUsers\n";
    for(size_t i = 0; i < num; i++)
    {
        output += all[i]->exporter();
    }
    output += "end\n";
    return output;
}

/**
 * @return a tárolt felhasználók száma.
 */
int AllUsers::getNum() const
{
    return num;
}



