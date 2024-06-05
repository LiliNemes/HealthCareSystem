/**
 * @file A tesztelő függvény deklarációja.
 */

#ifndef NHF_TEST_H
#define NHF_TEST_H

#include <iostream>

#include "memtrace.h"

#include "AllUsers.h"
#include "Physician.h"
#include "Specialist.h"
#include "AllSpecialists.h"
#include "Patient.h"
#include "controller.h"
#include "menu.h"
#include "gtest_lite.h"

//#define MEMTRACE

//a tesztelést végző függvény
void test_main();
#endif //NHF_TEST_H
