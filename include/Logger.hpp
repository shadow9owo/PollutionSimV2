#include "raylib.h"
#include <vector>
#include <string>

namespace Logger
{
    extern std::vector<std::string> logs;

    extern void clearlogger();
    extern bool renderlogger();
    extern bool sendmessage(std::string message);
}