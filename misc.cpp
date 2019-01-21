#include "misc.h"

//https://stackoverflow.com/questions/478898/how-do-i-execute-a-command-and-get-output-of-command-within-c-using-posix
std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

/* The ifstream object is a assigned a "false" value if a file is not found.
 * Exploiting that behaviour to check if a file exist
*/
bool fexists(const std::string &filepath){
    std::ifstream ifile(filepath.c_str());
    return static_cast<bool>(ifile);
}

/*
 * Returns true if a path is valid. Mainly used here for directory checks
 */
bool IsPathExist(const std::string &s){
    struct stat buffer;
    return (stat (s.c_str(), &buffer) == 0);
}