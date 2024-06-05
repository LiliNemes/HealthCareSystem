/**
 * @file A főmenü függvény definíciója.
 */
#include "memtrace.h"

#include "menu.h"

//#define MEMTRACE

/**
 * A főmenűt kiíró függvény. A controller modulba tartozó függvényeket hív meg attól függően, hogy a felhasználó melyik lehetőséget választja.
 * Itt jön létre a program alapjául szolgálü két heterogén kollekció, az AllUsers és az AllSpecialists.
 * A menü a specifikációnak, egfelelően jön létre, kód beírása alapján lehet váltogatni a funkciókat.
 * Amennyiben nem a felsorolt funkciók egyikét (1-5) írja be a felhasználó, a program kilép a menüből és befejeződik.
 */
int menu()
{
    bool exiter=false;
    char menuPoint = 0;
    AllUsers profiles;
    AllSpecialists specialistProfiles;

    std::cout<<"1. Physician"<<std::endl;
    std::cout<<"2. Patient"<<std::endl;
    std::cout<<"3. Specialist"<<std::endl;
    std::cout<<"4. Import state"<<std::endl;
    std::cout<<"5. Export state"<<std::endl;
    std::cout<<"6. Exit"<<std::endl;

    while(!exiter)
    {
        std::cin>>menuPoint;
        if(std::cin.eof() || std::cin.bad() || std::cin.fail()){
            return -1;
        }
            try {
                switch (menuPoint) {
                    case '1':
                        physician_sign_in(profiles);
                        break;
                    case '2':
                        patient_sign_in(profiles, specialistProfiles);
                        break;
                    case '3':
                        specialist_sign_in(profiles, specialistProfiles);
                        break;
                    case '4': {
                        std::cout << "Filename: ";
                        std::string fileName;
                        std::cin >> fileName;
                        import_state(profiles, specialistProfiles, fileName);
                        break;
                    }
                    case '5':
                        export_state(profiles);
                        break;
                    default:
                        exiter = true;
                        break;
                }
            }
            catch (std::invalid_argument &e) {
                std::cout << e.what() << std::endl;
            }
            catch (std::runtime_error &e) {
                std::cerr << e.what();
                exiter = true;
            }
        if(!exiter) {
            std::cout << "1. Physician" << std::endl;
            std::cout << "2. Patient" << std::endl;
            std::cout << "3. Specialist" << std::endl;
            std::cout << "4. Import state" << std::endl;
            std::cout << "5. Export state" << std::endl;
            std::cout << "6. Exit" << std::endl;
        }
    }
    return 0;
}