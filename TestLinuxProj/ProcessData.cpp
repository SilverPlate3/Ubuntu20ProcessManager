#include "ProcessData.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const ProcessData& processData)
{
    os
        << std::left
        << std::setw(8) << std::setfill(' ') << std::to_string(processData.pid)
        << std::setw(8) << std::setfill(' ') << std::to_string(processData.ppid)
        << std::setw(50) << std::setfill(' ') << processData.processPath.substr(0, 47)
        << std::setw(50) << std::setfill(' ') << processData.Commandline.substr(0, 47)
        << std::setw(12) << std::setfill(' ') << std::to_string(processData.virtualMemory)
        << std::setw(12) << std::setfill(' ') << std::to_string(processData.RAM)
        << std::setw(8) << std::setfill(' ') << std::to_string(processData.threads);

    return os;
}

























