#ifndef LBGE2_LOGGER_H
#define LBGE2_LOGGER_H

#include <string>

class Logger
{
public:
    static void Log(const std::string& line);
    static void Error(const std::string& line);

    static std::string& GetLog() { return m_log; }

private:
    static std::string m_log;

};


#endif //LBGE2_LOGGER_H
