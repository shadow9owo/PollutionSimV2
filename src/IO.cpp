#ifdef _WIN32
    #include <direct.h>
#elif __linux__
    #include <unistd.h>
#else 
    #error "Platform not supported"
#endif

#include "IO.hpp"
#include <string>

namespace IO
{
    std::string GetCurrentDir()
    {
        char buffer[FILENAME_MAX];
    #ifdef _WIN32
        _getcwd(buffer, FILENAME_MAX);
    #elif __linux__
        getcwd(buffer, FILENAME_MAX);
    #endif
        return std::string(buffer);
    }
}