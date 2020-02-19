#include "DataIO.h"
#include <fstream>

using json = nlohmann::json;

DataIO::DataIO()
{
}

void DataIO::SaveConfig(json configData, std::string pomodoroName)
{
    std::ofstream myfile;
    myfile.open("./data/" + pomodoroName + ".json");
    myfile << configData;
    myfile.close();
}

json DataIO::LoadConfig(std::string pomodoroName)
{
    try {
        std::ifstream *ifs = new std::ifstream("./data/" + pomodoroName + ".json");
        return json::parse(*ifs);
    } catch (json::exception& e) {
        return json() = {};
    }
}

DataIO::~DataIO()
{
}
