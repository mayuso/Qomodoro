#ifndef DATAIO_H
#define DATAIO_H

#include "../vendor/json/single_include/nlohmann/json.hpp"

#include <QString>
class DataIO
{
public:
    explicit DataIO();
    ~DataIO();
    static void SaveConfig(nlohmann::json config);
    static nlohmann::json LoadConfig();
    static void SaveData(nlohmann::json data);
    static nlohmann::json LoadData();

private:
    static void Save(nlohmann::json configData, QString path);
    static nlohmann::json Load(QString path);
};

#endif // DATAIO_H
