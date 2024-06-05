/**
 * @file A Patient osztály tagfüggvényeinek definíciói.
 */
#include "memtrace.h"

#include "Patient.h"

//#define MEMTRACE

/**
 * Bejelöli, hogy egy beteg megkapta az oltást.
 */
void Patient::gotVaccinated()
{
    vaccination=true;
}

/**
 * Szakorvoshoz beutalót adó függvény. A beutalók tömbjéhez hozzáadódik.
 * @param n a célzott szakorvos típusa.
 */
void Patient::newRefferal(int n)
{
    numOfRefferals++;
    int* helper=new int[numOfRefferals];
    for(size_t i=0; i<numOfRefferals-1; i++)
        helper[i]=refferals[i];
    helper[numOfRefferals-1]=n;
    delete[] refferals;
    refferals=helper;
}

/**
 * Recept írható fel vele.
 * @param p a recept szövege.
 */
void Patient::newPrescription(const std::string& p)
{
    numOfPrescriptions++;
    std::string* helper=new std::string [numOfPrescriptions];
    for(size_t i=0; i<numOfPrescriptions-1; i++)
        helper[i]=prescriptions[i];
    helper[numOfPrescriptions-1]=p+"\n";
    delete[] prescriptions;
    prescriptions=helper;
}
/**
 * Megjegyzés adható vele a beteg profiljához.
 * @param I a hozzáadandó információ.
 */
void Patient::newInformation(const std::string& I)
{
    numOfAdditional++;
    std::string* helper=new std::string [numOfAdditional];
    for(size_t i=0; i<numOfAdditional-1; i++)
        helper[i]=additionalInformation[i];
    helper[numOfAdditional-1]=I+"\n";
    delete[] additionalInformation;
    additionalInformation=helper;
}

/**
 * A beteg ezzel megtekinti, hogy van-e számára felírt recept.
 * Amennyiben van, azt a függvény file-ba exportálja.
 */
void Patient::getPrescription()
{
    if(numOfPrescriptions > 0){
        std::cout<<"Your prescriptions are:\n";
        for(size_t i = 0; i < numOfPrescriptions; i++){
            std::cout<<std::to_string(i)+") "<<prescriptions[i];
        }
        std::cout<<"\nWould you like to save them in a file? (prescriptions.txt) (y/n): ";
        char c;
        std::cin>>c;
        if(c == 'y'){
            std::fstream fs;
            fs.open("prescriptions.txt", std::ios_base::out);
            if(fs.is_open()) {
                for (size_t i = 0; i < numOfPrescriptions; i++) {
                    fs << std::to_string(i) + ") " << prescriptions[i];
                }

                fs.close();
                std::cout<<"Your prescriptions have been exported.\n";
            }
            else
                throw std::runtime_error("Couldn't open file to write.");
        }
        else
            std::cout<<"Your prescriptions haven't been exported.\n";
    }
    else
        std::cout<<"You don't have any precriptions yet.\n";
}

/**
 * A beteg megtekintheti, hogy megkapta-e az oltást.
 * Eportálhatja az oltási igazolványát file-ba.
 */
void Patient::getVaccinationInformation()
{
    if(vaccination){
        std::cout<<"You have already got a vaccination.\n";
    }
    else
        std::cout<<"You haven't got any vaccination yet.\n";

    std::cout<<"\nWould you like to save this information in a file? (vaccination.txt) (y/n): ";
    char c;
    std::cin>>c;
    if(c == 'y'){
        std::fstream fs;
        fs.open("vaccination.txt", std::ios_base::out);
        if(fs.is_open()) {
            if (vaccination)
                fs << name << " has already got the vaccine.";
            else
                fs << name << " hasn't got any vaccination yet.";

            fs.close();
            std::cout<<"Your vaccination has been exported.\n";
        }
        else
            throw std::runtime_error("Couldn't open file to write.");

    }
    else
        std::cout<<"Your vaccination hasn't been exported.\n";
}

/**
 * A függvény kiírja a páciens háziorvosoktól kapott beutalóit.
 * Minden beutalóhoz kiírja a paraméterként kapott ostreamre az adott szakterületen dolgozó orvosok neveit.
 * @param list Az összes szakorvos listája, melyből a függvény a filterType függvény segítségével válogat.
 * @param os ide ír a függvény .
 */
void Patient::chooseRefferals(AllSpecialists& list, std::ostream& os)
{
    Specialist** otolaryngologyst = nullptr;
    Specialist** surgents = nullptr;
    Specialist** medicinists = nullptr;
    Specialist** ophthalmologyst = nullptr;
    bool availableRefferals[4] = {false, false, false, false};
    os<<"0 Exit"<<std::endl;
    for(size_t i=0; i<numOfRefferals; i++)
    {
        if(refferals[i]==1)
        {
            os<<"1. Otolaryngology"<<std::endl;
            otolaryngologyst = list.filterType(1);
            for(int z=0; otolaryngologyst[z]!= nullptr; z++)
            {
                os<<" "<<z+1<<" "<<otolaryngologyst[z]->getName()<<std::endl;
            }
            availableRefferals[0] = true;
        }
        if(refferals[i]==2)
        {
            os<<"2. Surgery"<<std::endl;
            surgents = list.filterType(2);
            for(int z=0; surgents[z]!= nullptr; z++)
            {
                os<<" "<<z+1<<" "<<surgents[z]->getName()<<std::endl;
            }
            availableRefferals[1] = true;
        }
        if(refferals[i]==3)
        {
            os<<"3. Internal medicine"<<std::endl;
            medicinists = list.filterType(3);
            for(int z=0; medicinists[z]!= nullptr; z++)
            {
                os<<" "<<z+1<<" "<<medicinists[z]->getName()<<std::endl;
            }
            availableRefferals[2] = true;
        }
        if(refferals[i]==4)
        {
            os<<"4. Ophthalmology"<<std::endl;
            ophthalmologyst = list.filterType(4);
            for(int z=0; ophthalmologyst[z]!= nullptr; z++)
            {
                os<<" "<<z+1<<" "<<ophthalmologyst[z]->getName()<<std::endl;
            }
            availableRefferals[3] = true;
        }
    }
    os<<"Type:"<<std::endl;
    int type;
    std::cin>>type;
    os<<"Person:";
    int person;
    std::cin>>person;
    if(type==1 && availableRefferals[0])
    {
        otolaryngologyst[person-1]->addPatients(this);
    }
    else if(type==2 && availableRefferals[1])
    {
        surgents[person-1]->addPatients(this);
    }
    else if(type==3 && availableRefferals[2])
    {
        medicinists[person-1]->addPatients(this);
    }
    else if(type==4 && availableRefferals[3])
    {
        ophthalmologyst[person-1]->addPatients(this);
    }
    else
        throw std::invalid_argument("Invalid refferal type!");

    if(ophthalmologyst != nullptr)
        delete[] ophthalmologyst;
    if(otolaryngologyst != nullptr)
        delete[] otolaryngologyst;
    if(surgents != nullptr)
        delete[] surgents;
    if(medicinists != nullptr)
        delete[] medicinists;

}

/**
 * Kiírja a beteg kalendárját (meghívja a kalendár print függvényét).
 * @param os  ostream, ide ír a függvény.
 */
void Patient::printAppointments(std::ostream& os)
{
    appointments.print(os);
}

/**
 *  Új szakorvosi időpont adható a beteg kalendárjába.
 *  Meghívja a kalendár addEvent függvényét.
 * @param day melyik napra (1-31).
 * @param sec a nap melyik szekciójába (1-4).
 * @param who string, a szakorvos neve.
 */
void Patient::newAppointment(int day, int sec, const std::string& who)
{
    appointments.addEvent(day, sec, who);
}

/**
* Exportálásért felelős függvény.
* @return a file-ba kiírandó szöveg tartalom.
*/
std::string Patient::exporter()
{
    std::string ret = "Patient\n";
    ret += name+"\n";
    ret += passW.exporter();
    ret += appointments.exporter();

    ret += std::to_string(vaccination)+"\n";
    ret += "refferals:\n";
    for(size_t i = 0; i < numOfRefferals; i++)
    {
        ret += std::to_string(refferals[i])+"\n";
    }
    ret += "prescriptions:\n";
    for(size_t i = 0; i < numOfPrescriptions; i++)
    {
        ret += prescriptions[i];
        ret += "end\n";
    }

    ret += "informations:\n";
    for(size_t i = 0; i < numOfAdditional; i++)
    {
        ret += additionalInformation[i]+"\n";
        ret+= "end\n";
    }

    ret+= "end\n";

    return ret;
}



