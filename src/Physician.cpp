/**
 * @file A Physician osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "Physician.h"
#include "Patient.h"

//#define MEMTRACE

/**
* Exportálásért felelős függvény.
* @return a file-ba kiírandó szöveg tartalom.
*/
std::string Physician::exporter()
{
    std::string ret = "Physician\n";
    ret += name+"\n";
    ret += passW.exporter();

    ret+= "patients:\n";
    for(int i = 0; i < numOfPatients; i++){
        ret+=patients[i]->exporter();
    }

    ret +="end\n";

    return ret;
}

/**
 * Létrehoz egy beteg-profilt, azt az összes profil és a saját betegei közé adja.
 * @param taj a beteg (leendő) jelszava.
 * @param name a beteg (leendő) neve.
 * @param users az összes profilt tároló heterogén kollekció, ebbe is bele kell tegye a függvény az új Patientet.
 */
void Physician::addPatient(const std::string& taj,const std::string& name, AllUsers& users)
{
    Password PatientPass;
    if (!PatientPass.setPassword(taj))
        throw  std::invalid_argument("Couldn't set the password.");

    Calendar c;

    Patient* JohnDoe = new Patient(name,PatientPass, c);
    users.addUser(JohnDoe);
    Patient** helper=new Patient*[numOfPatients+1];
    for(int i=0; i<numOfPatients; i++)
    {
        helper[i]=patients[i];
    }
    helper[numOfPatients]=JohnDoe;
    numOfPatients++;
    delete[] patients;
    patients=helper;
}

/**
 * A paraméterként kapott string segítségével kiválasztja az egyik betegét, különböző műveleteket hajthat végre rajta (a lehetőségek a paraméterként lapott ostreamre íródhatnak).
 * @param taj annak a felhasználónak a TAJszáma/jelszava, akivel a műveleteket végre lehet hajtani.
 * @param os ide íródnak a függvény által kiírt dolgok.
 */
void Physician::care(const std::string& taj, std::ostream& os)
{
    Patient* JaneDoe= nullptr;
    for(int i=0; i<numOfPatients; i++)
    {
        if(patients[i]->getPassword().getter() == taj)
        {
            JaneDoe=patients[i];
        }
    }
    if(JaneDoe== nullptr)
    {
        throw std::invalid_argument("Couldn't find this patient");
    }
    bool exit = false;
    os<<"1. New Refferal"<<std::endl;
    os<<"2. New Prescription"<<std::endl;
    os<<"3. Got Vaccinated"<<std::endl;
    os<<"4. Add Information"<<std::endl;
    os<<"5. Exit"<<std::endl;
    os<<"Which one?"<<std::endl;
    char control;
    while (!exit && std::cin>>control)
    {

            try {
                switch (control) {
                    case '1': {
                        os << "Type of specialist:" << std::endl;
                        os << "1. Otolaryngology" << std::endl;
                        os << "2. Surgery" << std::endl;
                        os << "3. Internal medicine" << std::endl;
                        os << "4. Ophthalmology" << std::endl;
                        int readin = 0;
                        std::cin >> readin;
                        if (readin < 1 || readin > 4) {
                            throw std::invalid_argument("There isn't a specialist type for this code.");
                        }
                        JaneDoe->newRefferal(readin);
                        break;
                    }
                    case '2': {
                        os << "Prescription:" << std::endl;
                        std::string prescription;
                        std::cin >> std::ws;
                        std::getline(std::cin, prescription);
                        JaneDoe->newPrescription(prescription);
                        break;
                    }
                    case '3': {
                        JaneDoe->gotVaccinated();
                        break;
                    }
                    case '4': {
                        os << "Information:" << std::endl;
                        std::string information;
                        std::cin >> std::ws;
                        std::getline(std::cin, information);
                        JaneDoe->newInformation(information);
                        break;
                    }
                    default:
                        exit = true;
                        break;

                }
                if(!exit) {
                    os << "1. New Refferal" << std::endl;
                    os << "2. New Prescription" << std::endl;
                    os << "3. Got Vaccinated" << std::endl;
                    os << "4. Add Information" << std::endl;
                    os << "5. Exit" << std::endl;
                    os << "Which one?" << std::endl;
                }
            }
            catch(std::invalid_argument& e){
                std::cout<<e.what()<<std::endl;
            }

    }
}

/**
 * Kiírja az orvos betegeit a paraméterként kapott ostreamre.
 * @param os ide ír a függvény.
 */
void Physician::showPatients(std::ostream& os) const
{
    for(int i=0; i<numOfPatients; i++)
    {
        os<<patients[i]->getName()<<(std::string)"\t"<< patients[i]->getPassword().getter()<<std::endl;
    }
}

/**
 * Már létező páciens hozzáadása a háziorvoshoz.
 * Az állapot file-ból történő visszaállításánál van rá szükség.
 * @param pPatient az eltárolandó páciens.
 */
void Physician::addExistingPatient(Patient *pPatient) {

    Patient** helper=new Patient*[numOfPatients+1];
    for(int i=0; i<numOfPatients; i++)
    {
        helper[i]=patients[i];
    }
    helper[numOfPatients]=pPatient;
    numOfPatients++;
    delete[] patients;
    patients=helper;
}



