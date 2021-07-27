#include "DataIO.h"

#include <fstream>
#include <QDebug>

using json = nlohmann::json;

DataIO::DataIO()
{
}

DataIO::~DataIO()
{
}

void DataIO::SaveData(json data)
{
    Save(data, "./data/data.json");
}

json DataIO::LoadData()
{
    try {
        return Load("./data/data.json");
    } catch (json::exception& e) {
        return json() = {};
    }
}

void DataIO::SaveConfig(json config)
{
    Save(config, "./data/config.json");
}

json DataIO::LoadConfig()
{
    try {
        return Load("./data/config.json");
    } catch (json::exception& e) {
        return json() = {};
    }
}

void DataIO::Save(nlohmann::json configData, QString path)
{
    std::ofstream myfile;
    myfile.open(path.toStdString().c_str());
    myfile << configData;
    myfile.close();
}

json DataIO::Load(QString path)
{
    try {
        std::ifstream *ifs = new std::ifstream(path.toStdString().c_str());
        return json::parse(*ifs);
    } catch (json::exception& e) {
        return json() = {};
    }
}


