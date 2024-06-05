/**
 * @file A User osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "User.h"

//#define MEMTRACE

/**
 * Getter a jelszónak.
 * @return a felhasználóhoz tartozó jelszóval
 */
 Password User::getPassword()
{
    return passW;
}

/**
 * Getter a névnek.
 * @return a profilhoz tartozó név.
 */
std::string User::getName()
{
    return name;
}



