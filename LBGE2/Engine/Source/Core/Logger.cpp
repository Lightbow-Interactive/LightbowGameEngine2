#include "Logger.h"
#include <iostream>

std::string Logger::m_log = "";

void Logger::Log(const std::string& line)
{
    std::cout << "[INFO] " << line << std::endl;
    m_log += "[INFO] " + line + "\n";
}

void Logger::Error(const std::string &line)
{
    Log(line);
}
