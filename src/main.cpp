/**
 * @file A program belépési pontja.
 */
#include "memtrace.h"

#include "menu.h"
#include "test.h"

//#define MEMTRACE


/**
 * A program belépési pontja.
 * @return kilépési kód.
 */
int main() {

#ifdef CPORTA
    test_main();
#endif
#ifndef CPORTA
    menu();
#endif
    return 0;
}
