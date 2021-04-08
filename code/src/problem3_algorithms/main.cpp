#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

enum class PClass{
    Upper = 1,
    Middle = 2,
    Lower = 3,
    NoInfo
};

enum class Sex{
    Male,
    Female,
    NoInfo
};

struct Passenger
{
    unsigned int id;
    bool survived;
    PClass pclass;
    std::string name;
    Sex sex;
    unsigned int age;
    unsigned int sibsp;
    unsigned int parch;
    std::string ticket;
    double fare;
    std::string cabin;
    std::string embarked;
};

typedef std::vector<Passenger> VecPassengers;


std::ostream& operator<<(std::ostream& out, Passenger p)
{
    out << std::setw(4) << p.id << ",";
    out << p.survived << ",";
    out << static_cast<int>(p.pclass) << ",";
    out << p.name << ",";
    out << static_cast<int>(p.sex) << ",";
    out << p.age << ",";
    out << p.sibsp << ",";
    out << p.parch << ",";
    out << p.ticket << ",";
    out << p.fare << ",";
    out << p.cabin << ",";
    out << p.embarked << "\n";
    return out;
}


PClass toPClass(const std::string& buffer)
{
    std::stringstream sspcl(buffer);
    int pclassInt = 0;
    sspcl >> pclassInt;
    PClass pclass = static_cast<PClass>(pclassInt);
    return pclass;
}


int toInt(const std::string& buffer)
{
    std::stringstream ssid(buffer);
    int id = 0;
    ssid >> id;
    return id;
}

double toDouble(const std::string& buffer)
{
    std::stringstream ssid(buffer);
    double id = 0;
    ssid >> id;
    return id;
}

Passenger extractData(std::istream& in)
{
    Passenger newPassenger;
    std::string buffer;
    
    std::getline(in, buffer, ','); // ID
    newPassenger.id = toInt(buffer);
    
    std::getline(in, buffer, ','); // survived
    newPassenger.survived = buffer == "1";
    
    std::getline(in, buffer, ','); // pclass
    newPassenger.pclass = toPClass(buffer);
    
    std::getline(in, buffer, ','); // full name
    newPassenger.name = buffer;
    
    std::getline(in, buffer, ','); // sex
    newPassenger.sex = buffer == "male"? Sex::Male : Sex::Female;
    
    std::getline(in, buffer, ','); // age
    newPassenger.age = toInt(buffer);
    
    std::getline(in, buffer, ','); // sibsp
    newPassenger.sibsp = toInt(buffer);
    
    std::getline(in, buffer, ','); // parch
    newPassenger.parch = toInt(buffer);
    
    std::getline(in, buffer, ','); // ticket
    newPassenger.ticket = buffer;
    
    std::getline(in, buffer, ','); // fare
    newPassenger.fare = toDouble(buffer);

    std::getline(in, buffer, ','); // Cabin
    newPassenger.cabin = buffer;

    std::getline(in, buffer, '\n'); // Embarked
    newPassenger.embarked = buffer;
    return newPassenger;
}

VecPassengers loadData(std::istream& in)
{
    VecPassengers passengers;
    std::string buffer;
    std::getline(in, buffer); // header
    while(std::getline(in, buffer))
    {
        std::stringstream lineStream(buffer);
        Passenger newPass = extractData(lineStream);
        passengers.push_back(newPass);
    }
    return passengers;
}


int main ()
{
    const std::string INPUT_FILE_NAME = "../../data/titanic.csv";
    std::ifstream inputFile;
    inputFile.open(INPUT_FILE_NAME);
    VecPassengers passengers = loadData(inputFile);
    std::cout << passengers[0];
}
