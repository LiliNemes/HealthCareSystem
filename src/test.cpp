/**
 * @file A tesztelő függvény megvalósítása.
 */
#include "memtrace.h"

#include "test.h"

//#define MEMTRACE


/**
 * A tesztelést megvalósító függvény.
 */
void test_main()
{
    AllUsers users;
    AllSpecialists specialists;

    import_state(users, specialists, "in.txt");

    int e = menu();
    /*
     * bemenet:
     * 1
     * Ex Lample
     * 012345
     * 3
     * 8
     */
    if(e == -1){
         std::cout<<"EOF, bye!";
         return;
     }

    //A Password osztályhoz tartozó tesztesetek
    Password test;

    bool res = test.setPassword("111111");
    EXPECT_FALSE( res);

    res = test.setPassword("234567");
    EXPECT_TRUE( res);


    //Háziorvos létrehozása, tesztesetek melyek a háziorvos képességeire vonatkoznak
    std::string name = "George";
    Physician* george = new Physician(name, test);
    users.addUser(george);

    std::string pass2 = "345671";
    EXPECT_NO_THROW(george->addPatient(pass2,  "Ella", users));
    std::stringstream st;
    george->showPatients(st);
    EXPECT_EQ(st.str(), "Ella\t"+pass2+"\n");


    Patient* ella = dynamic_cast<Patient *>(users.getUser("Ella"));


    //1. Funkció - beutaló
    EXPECT_NO_THROW(george->care(ella->getPassword().getter(), std::cout));
    /*
     * bemenet:
     * 1
     * 4
     * 5
     */

    //2. Funkció - Recept felírása
    std::string presc="Nurofen";
    ella->newPrescription(presc);
    ella->getPrescription();
    /*
     * bemenet:
     * y
     */

    //3. Funkció - oltottság megjelölése
     ella->gotVaccinated();
     ella->getVaccinationInformation();
     /*
      * bemenet:
      * y
      */


    //4. Funkció - Megjegyzés írása
    ella->newInformation("Surgery is needed");

    std::string name2="Anna";
    Password passwordAnna;
    std::string pass3 = "223344";
    passwordAnna.setPassword(pass3);
    Calendar cAnna;
    Specialist* anna=new Specialist(name2,passwordAnna, cAnna, 4);
    users.addUser(anna);
    specialists.addSpecialist(anna);

    //Rossz jelszavak ellenőrzése
    EXPECT_NO_THROW(patient_sign_in(users, specialists));
    /*
     * bemenet:
     * Ella
     * 345670
     * 22
     * 3456789
     * 345671
     * 5
     */



    //Belépés betegként
    //1. menüponthoz kapcsolódó függvények
    EXPECT_NO_THROW(ella->chooseRefferals(specialists, std::cout));
    /*
     * bemenet:
     * 4
     * 1
     */

    //2. Menüpont
    //később a Specialist során


    //3. Menüpont
    //Physician tesztelése során már ellenőrizve lett

    //4. Menüpont
    //Physician tesztelése során már ellenőrizve lett


    //Szakorvos
    //1. menüpont

    EXPECT_THROW(specialist_sign_in(users, specialists), std::invalid_argument&);
    /*
     * bemenet:
     * Bar Kiraly
     * 223344
     */

    EXPECT_NO_THROW(specialist_sign_in(users, specialists));
    /*
     * bemenet:
     * Anna
     * 223344
     * 1
     * 345671
     * 3
     * 2
     */
    ella->printAppointments(std::cout);



    //2. menüpont
    ella->newInformation("Surgery successfully done.");


    //export_state(users);
}