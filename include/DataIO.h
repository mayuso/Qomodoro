#ifndef DATAIO_H
#define DATAIO_H

#include "../vendor/json/single_include/nlohmann/json.hpp"

class DataIO
{
public:
    explicit DataIO();
    ~DataIO();
    static void SaveConfig(nlohmann::json configData, std::string pomodoroName);
    static nlohmann::json LoadConfig(std::string pomodoroName);
};

#endif // DATAIO_H
