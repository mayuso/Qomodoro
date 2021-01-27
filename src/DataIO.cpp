#include "DataIO.h"
#include <fstream>

using json = nlohmann::json;

DataIO::DataIO()
{
}

void DataIO::SaveConfig(json configData)
{
    std::ofstream myfile;
    myfile.open("./data/data.json");
    myfile << configData;
    myfile.close();
}

json DataIO::LoadConfig()
{
    try {
        std::ifstream *ifs = new std::ifstream("./data/data.json");
        return json::parse(*ifs);
    } catch (json::exception& e) {
        return json() = {};
    }
}

DataIO::~DataIO()
{
}
