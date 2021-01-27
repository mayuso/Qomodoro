#ifndef DATAIO_H
#define DATAIO_H

#include "../vendor/json/single_include/nlohmann/json.hpp"

class DataIO
{
public:
    explicit DataIO();
    ~DataIO();
    static void SaveConfig(nlohmann::json configData);
    static nlohmann::json LoadConfig();
};

#endif // DATAIO_H
