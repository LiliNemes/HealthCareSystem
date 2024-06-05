/**
 * @file A vezérlőfüggvények definíciói.
 */
#include "memtrace.h"

#include "controller.h"
#include "Patient.h"

//#define MEMTRACE
//#define DEBUG

/**
 * A háziorvosként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg, ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void physician_sign_in (AllUsers& Users)
{
    std::cout<<"name:"<<std::endl;
    std::string physicianName;
    std::cin >> std::ws;
    std::getline(std::cin,physicianName);

    std::cout<<"password (in case of forgotten password press 111111!):"<<std::endl;
    std::string inputPassword;
    std::cin>>inputPassword;

    Physician* JaneDoe;
    if(Users.contains(physicianName))
    {
        JaneDoe= dynamic_cast<Physician *>(Users.getUser(physicianName));
        bool isItOk=false;
        while(!isItOk)
        {
            try{
                isItOk=JaneDoe->getPassword()==inputPassword;
            }
            catch(std::runtime_error& e){
                std::cerr<<e.what()<<" So you need to find out your password on your own.\n";
                isItOk = false;
            }
            if(!isItOk)
            {
                std::cout<<"password: "<<std::endl;
                std::cin>>inputPassword;
            }
        }
    }
    else
    {
        if(Users.containsID(inputPassword))
        {
            throw std::invalid_argument("Existing ID (password) !");
        }
        Password physicianPassword;
        bool isItOk=false;
        while(!isItOk)
        {
            isItOk=physicianPassword.setPassword(inputPassword);
            if(!isItOk)
            {
                std::cout<<"password: "<<std::endl;
                std::cin>>inputPassword;
            }
        }
        JaneDoe= new Physician(physicianName, physicianPassword);
        Users.addUser(JaneDoe);
    }
    bool exit=false;
    std::cout<<"1. Admittance"<<std::endl;
    std::cout<<"2. Care activity"<<std::endl;
    std::cout<<"3. Exit"<<std::endl;
    char choice;
    while(!exit && std::cin>>choice)
    {
        switch(choice)
        {
            case '1':
            {
                std::cout << "Name: " << std::endl;
                std::string PatientName;

                std::cin >> std::ws;
                std::getline(std::cin, PatientName);
                std::cout << "Patient ID: " << std::endl;
                std::string PatientID;
                std::cin >> PatientID;
                if (!Users.contains(PatientName) && !Users.containsID(PatientID))
                {
                    try
                    {
                        JaneDoe->addPatient(PatientID, PatientName, Users);
                    }
                    catch(std::invalid_argument& e)
                    {
                        std::cout<<e.what()<<std::endl;
                    }
                }
                else
                {
                    std::cout<<"This profile already exists!"<<std::endl;
                }
                break;
            }
            case '2':
            {
                std::stringstream st;
                JaneDoe->showPatients(st);
                if(st.str().empty())
                    break;
                else
                    std::cout<<st.str();
                std::cout << "Patient ID:" << std::endl;
                std::string PatientID;
                std::cin >> PatientID;
                try{
                    JaneDoe->care(PatientID, std::cout);
                }
                catch(std::invalid_argument& e){
                    std::cout<<e.what()<<std::endl;
                }
            }
                break;
            default:
                exit=true;
                break;

        }
        if(!exit) {
            std::cout << "1. Admittance" << std::endl;
            std::cout << "2. Care activity" << std::endl;
            std::cout << "3. Exit" << std::endl;
        }
    }
}

/**
 * A páciensként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg, ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 * @param Specialists az sszes szakorvosi profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void patient_sign_in (AllUsers& Users, AllSpecialists& Specialists)
{
    std::cout<<"name: "<<std::endl;
    std::string PatientName;
    std::cin >> std::ws;
    std::getline(std::cin,PatientName);

    Patient* JohnDoe;
    JohnDoe=dynamic_cast<Patient* > (Users.getUser(PatientName));
    if(JohnDoe== nullptr)
        throw std::invalid_argument("Non-existing patient!");
    bool isItOk=false;

    std::cout<<"password (in case of forgotten password press 111111!):"<<std::endl;
    std::string inputPassword;
    std::cin>>inputPassword;

    while(!isItOk)
    {
        try {
            isItOk = JohnDoe->getPassword() == inputPassword;
        }
        catch(std::runtime_error& e){
            std::cerr<<e.what()<<" So you need to find out your password on your own.\n";
            isItOk = false;
        }
        if(!isItOk)
        {
            std::cout<<"password:"<<std::endl;
            std::cin>>inputPassword;
        }
    }
    bool exit=false;
    std::cout<<"1. Refferals"<<std::endl;
    std::cout<<"2. Appointments"<<std::endl;
    std::cout<<"3. Prescriptions"<<std::endl;
    std::cout<<"4. Vaccination"<<std::endl;
    std::cout<<"5. Exit"<<std::endl;
    char choice;
    while(!exit && std::cin>>choice)
    {

        try {
            switch (choice) {
                case '1': {
                    JohnDoe->chooseRefferals(Specialists, std::cout);
                    break;
                }
                case '2': {
                    JohnDoe->printAppointments(std::cout);
                    break;
                }
                case '3': {
                    JohnDoe->getPrescription();
                    break;
                }
                case '4': {
                    JohnDoe->getVaccinationInformation();
                    break;
                }
                default:
                    exit = true;
                    break;

            }
            if(!exit){
                std::cout<<"1. Refferals"<<std::endl;
                std::cout<<"2. Appointments"<<std::endl;
                std::cout<<"3. Prescriptions"<<std::endl;
                std::cout<<"4. Vaccination"<<std::endl;
                std::cout<<"5. Exit"<<std::endl;
            }
        }
        catch(std::runtime_error& e)
        {
            exit = true;
            std::cerr<<e.what();
        }
    }


}

/**
 * A szakorvosként történő belépést, cselekmény-végrehajtást vezérli, kontrollálja.
 * A menu() függvény hívja meg,ő hív meg további függvényeket.
 * @param Users az összes profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 * @param Specialists az sszes szakorvosi profilt tartalmazó heterogén kollekció, a menüben lett létrehozva.
 */
void specialist_sign_in (AllUsers& Users, AllSpecialists& Specialists)
{
    std::cout<<"name: "<<std::endl;
    std::string specialistName;
    std::cin >> std::ws;
    std::getline(std::cin,specialistName);
    std::cout<<"password (in case of forgotten password press 111111!):"<<std::endl;
    std::string inputPassword;
    std::cin>>inputPassword;
    Specialist* JaneDoe;
    if(Users.contains(specialistName))
    {
        JaneDoe= dynamic_cast<Specialist *>(Users.getUser(specialistName));
        bool isItOk=false;
        while(!isItOk)
        {
            try
            {
                isItOk=JaneDoe->getPassword()==inputPassword;
            }
            catch(std::runtime_error& e){
                std::cerr<<e.what()<<" So you need to find out your password on your own.\n";
                isItOk = false;
            }
            if(!isItOk)
            {
                std::cout<<"password: "<<std::endl;
                std::cin>>inputPassword;
            }
        }

    }
    else
    {
        if(Users.containsID(inputPassword))
        {
            throw std::invalid_argument("Existing ID (password) !");
        }
        Password specialistPassword;
        bool isItOk=false;
        while(!isItOk)
        {
            isItOk=specialistPassword.setPassword(inputPassword);
            if(!isItOk)
            {
                std::cout<<"password: "<<std::endl;
                std::cin>>inputPassword;
            }
        }
        std::cout<<"Departments:"<<std::endl;
        std::cout<<"\t1. Otolaryngology\n \t2. Surgery\n \t3. Internal medicine\n \t4. Ophthalmology"<<std::endl;
        std::cout<<"Specialist type: "<<std::endl;
        int type;
        std::cin>>type;
        Calendar cal;
        JaneDoe= new Specialist(specialistName, specialistPassword, cal, type);
        Users.addUser(JaneDoe);
        Specialists.addSpecialist(JaneDoe);

    }
    bool exit=false;
    std::cout<<"1. Give appointment"<<std::endl;
    std::cout<<"2. Add Information"<<std::endl;
    std::cout<<"3. Exit"<<std::endl;
    char choice;
    while(!exit && std::cin>>choice)
    {
        try
        {
            switch(choice)
            {
                case '1':
                {
                    JaneDoe->showPatients(std::cout);
                    std::string whichPatient;
                    std::cout<<"Which patient?"<<std::endl;
                    std::cin >> std::ws;
                    std::getline(std::cin,whichPatient);
                    Patient* JohnDoe=JaneDoe->getPatient(whichPatient);
                    JaneDoe->printCalendar(std::cout);
                    std::cout<<"Day:"<<std::endl;
                    int Day;
                    std::cin>>Day;
                    std::cout<<"Section:"<<std::endl;
                    int Section;
                    std::cin>>Section;
                    JaneDoe->refreshCalendar(Day-1, Section-1, JohnDoe);
                    break;
                }
                case '2':
                {
                    JaneDoe->showPatients(std::cout);
                    std::string whichPatient;
                    std::cout<<"Which patient?"<<std::endl;
                    std::cin >> std::ws;
                    std::getline(std::cin,whichPatient);
                    Patient* JohnDoe;
                    JohnDoe=JaneDoe->getPatient(whichPatient);
                    std::cout<<"Additional information:"<<std::endl;
                    std::string AdditionalInformation;
                    std::cin >> std::ws;
                    std::getline(std::cin,AdditionalInformation);
                    JohnDoe->newInformation(AdditionalInformation);
                    break;
                }
                default:
                {
                    exit=true;
                    break;
                }
            }
            if(!exit){
                std::cout<<"1. Give appointment"<<std::endl;
                std::cout<<"2. Add Information"<<std::endl;
                std::cout<<"3. Exit"<<std::endl;
            }
        }
        catch(std::invalid_argument& e){
            std::cout<<e.what()<<std::endl;
        }
    }
}

/**
 * Egy esemény beolvasása egy sor szövegből és hozzáadása a naptárhoz.
 * @param s a sor szöveg, melyből beolvasunk.
 * @param c a naptár, amibe az eseményt beírjuk.
 */
void addEvent(std::string s, Calendar& c)
{
#ifdef DEBUG
    std::cout<<"Reading Event"<<std::endl;
#endif
    size_t pos1 = s.find(':');
    if(pos1 == s.npos)
        throw std::domain_error("Error in the syntax of the file: Calendar -> : is missing from Day format!");
    int day = std::stoi(s.substr(0,pos1))-1;
    s = s.substr(pos1+1);

    size_t pos2 = s.find(':');
    if(pos2 == s.npos)
        throw std::domain_error("Error in the syntax of the file: Calendar -> : is missing from Day format!");
    int sect = std::stoi(s.substr(0,pos2))-1;
    s = s.substr(pos2+1);

    c.addEvent(day, sect, s);
}

/**
 * Jelszó beolvasása egy file alapú adatfolyamból.
 * @param fs az adatfolyam, amiből olvasunk.
 * @param line az aktuálisan kiolvasott sor.
 * @return a létrehozott jelszó.
 */
Password readPassword(std::fstream& fs, std::string& line){
#ifdef DEBUG
    std::cout<<"Reading Password"<<std::endl;
#endif
    Password password;
    if(line == "Password"){
        std::getline(fs, line);
        password.setPassword(line);
        std::getline(fs, line);
        if(line!= "end")
            throw std::domain_error("Error in the syntax of the file: Patient.Password.end != "+line);
    }
    else
        throw std::domain_error("Error in the syntax of the file: Patient.Password != "+line);

    return password;
}

/**
 * Naptár beolvasása egy file alapú adatfolyamból.
 * @param fs az adatfolyam, amiből olvasunk.
 * @param line az aktuálisan kiolvasott sor.
 * @return a létrehozott naptár.
 */
Calendar readCalendar(std::fstream& fs, std::string& line)
{
#ifdef DEBUG
    std::cout<<"Reading Calendar"<<std::endl;
#endif
    Calendar c;
    if(line == "Calendar")
    {
        std::getline(fs, line);
        if(line == "events:")
        {
            std::getline(fs, line);
            while(line != "end")
            {
                addEvent(line, c);
                std::getline(fs, line);
            }
        }
        else
            throw std::domain_error("Error in the syntax of the file. Calendar.events: != "+line);
    }
    else
        throw std::domain_error("Error in the syntax of the file. Calendar != "+line);

    return c;
}

/**
 * Páciens beolvasása egy file alapú adatfolyamból.
 * @param fs az adatfolyam, amiből olvasunk.
 * @param line az aktuálisan kiolvasott sor.
 * @return egy dinamikusan lefoglalt páciensre mutató mutató.
 */
Patient* readPatient(std::fstream& fs, std::string& line) {
#ifdef DEBUG
    std::cout<<"Reading Patient"<<std::endl;
#endif
    Patient* p;
    if(line == "Patient")
    {
        std::getline(fs, line);
        std::string name = line;
        std::getline(fs, line);

        Password password = readPassword(fs, line);
        std::getline(fs, line);

        Calendar c = readCalendar(fs, line);
        std::getline(fs, line);

        p = new Patient(name, password, c);

        bool vaccinated = std::stoi(line);
        if(vaccinated)
            p->gotVaccinated();

        std::getline(fs, line);
        if(line == "refferals:")
        {

            std::getline(fs, line);
            while(line != "prescriptions:")
            {
#ifdef DEBUG
                std::cout<<"Reading refferals"<<std::endl;
#endif
                int ref = std::stoi(line);
                p->newRefferal(ref);
                std::getline(fs, line);
            }
            std::getline(fs, line);

            while(line != "informations:")
            {
#ifdef DEBUG
                std::cout<<"Reading prescriptions"<<std::endl;
#endif
                std::string pres;
                while(line != "end")
                {
                    pres += line;
                    std::getline(fs, line);
                }
                if(!pres.empty())
                {
                    p->newPrescription(pres);
                    std::getline(fs, line);
                }
            }
            std::getline(fs, line);

            while(line != "end")
            {
#ifdef DEBUG
                std::cout<<"Reading informations"<<std::endl;
#endif
                std::string info;
                while(line != "end")
                {
                    info += line;
                    std::getline(fs, line);
                }
                if(!info.empty())
                {
                    p->newInformation(info);
                    std::getline(fs, line);
                }
            }
        }
        else
            throw std::domain_error("Error in the syntax of the file: Patient.referrals: != "+line);
    }
    else
        throw std::domain_error("Error in the syntax of the file: Patient != "+line);

    return p;
}


/**
 * A paraméterként megadott string segítségével beolvassa a rendszer állapotát.
 * @param allUsers a felhasználókat tároló objektum.
 * @param allSpecialists a szakorvosokat tároló objektum.
 * @param file a beolvasandó file elérési útja.
 */
void import_state(AllUsers& allUsers, AllSpecialists& allSpecialists, const std::string& file)
{
    std::fstream fs;
    fs.open(file, std::ios_base::in);

    if(fs.is_open())
    {
        try {
            if(allUsers.getNum() != 0)
                throw std::invalid_argument("You have to stop and rerun the program in order to complete the import.\n"
                                            "(The actual state must be empty)");

            std::string line;
            std::getline(fs, line);
            while (line != "X")
            {

                if (line == "AllUsers")
                {
                    #ifdef DEBUG
                    std::cout<<"Reading AllUsers"<<std::endl;
                    #endif
                    std::getline(fs, line);
                    while (line != "end")
                    {
                        if (line == "Specialist")
                        {
                            #ifdef DEBUG
                            std::cout<<"Reading Specialist"<<std::endl;
                            #endif
                            std::getline(fs, line);
                            std::string name = line;
                            std::getline(fs, line);

                            //jelszo beolvasasa
                            Password password = readPassword(fs, line);
                            std::getline(fs, line);

                            int type = std::stoi(line);
                            std::getline(fs, line);

                            //naptar beolvasasa
                            Calendar c = readCalendar(fs, line);
                            std::getline(fs, line);

                            Specialist *spec = new Specialist(name, password, c, type);

                            //paciensek beolvasasa
                            if (line == "patients:")
                            {
                                #ifdef DEBUG
                                std::cout<<"Reading patients"<<std::endl;
                                #endif
                                std::getline(fs, line);
                                while (line != "end")
                                {
                                    Patient *p = readPatient(fs, line);
                                    if (allUsers.getUser(p->getName()) == nullptr)
                                    {
                                        allUsers.addUser(p);
                                        spec->addPatients(p);
                                    }
                                    else{
                                        spec->addPatients(dynamic_cast<Patient *>(allUsers.getUser(p->getName())));
                                        delete p;
                                    }


                                    std::getline(fs, line);
                                }
                            } else
                                throw std::domain_error("Error in the syntax of the file. Specialist.patients != " + line);

                            allUsers.addUser(spec);
                            allSpecialists.addSpecialist(spec);

                            std::getline(fs, line);
                        } else if (line == "Patient")
                        {
                            Patient *p = readPatient(fs, line);
                            if (allUsers.getUser(p->getName()) == nullptr)
                            {
                                allUsers.addUser(p);
                            }
                            else
                            {
                                delete p;
                            }

                            std::getline(fs, line);
                        } else if (line == "Physician")
                        {
                            #ifdef DEBUG
                            std::cout<<"Reading Physician"<<std::endl;
                            #endif
                            Physician *phy;
                            std::getline(fs, line);
                            std::string name = line;

                            std::getline(fs, line);
                            Password pass = readPassword(fs, line);

                            phy = new Physician(name, pass);
                            allUsers.addUser(phy);

                            std::getline(fs, line);
                            if (line == "patients:")
                            {
                                #ifdef DEBUG
                                std::cout<<"Reading patients"<<std::endl;
                                #endif
                                std::getline(fs, line);
                                while (line != "end")
                                {
                                    Patient *p = readPatient(fs, line);
                                    if (allUsers.getUser(p->getName()) == nullptr)
                                    {
                                        allUsers.addUser(p);
                                        phy->addExistingPatient(p);
                                    }
                                    else{
                                        phy->addExistingPatient(dynamic_cast<Patient *>(allUsers.getUser(p->getName())));
                                        delete p;
                                    }
                                    std::getline(fs, line);
                                }
                            } else
                                throw std::domain_error("Error in the syntax of the file. Physician.patients != " + line);
                            std::getline(fs, line);
                        }
                    }
                    std::getline(fs, line);
                }

            }
        }
        catch(std::domain_error& e)
        {
            std::cerr<<e.what()<<std::endl;
        }
        std::cout<<"State has been imported.\n";
        fs.close();
    }
    else
        throw std::runtime_error("Couldn't open file to read.");
}

/**
 * A fileba kiírás vezérléséért felelős függvény.
 * @param users a felhasználókat tároló objektum.
 * @param specialists a szakorvosokat tároló objektum.
 */
void export_state(AllUsers& users)
{
    std::fstream fs;
    fs.open("out.txt", std::ios_base::out);

    if(fs.is_open())
    {
        fs << users.exporter();
        fs << "X\n";
        fs.close();

        std::cout<<"The state (not whole Hungary) has been exported to \"out.txt\"\n";
    }
    else
        throw std::runtime_error("Couldn't open file to write.");

}