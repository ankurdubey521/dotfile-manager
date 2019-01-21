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

/*
 * The ifstream object is a assigned a "false" value if a file is not found.
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
/*
 *  Encrypts file at plaintext_path using gpg key of gpg_receipient and
 *  creates encrypted file at ciphertext_path
 */
void encrypt(const std::string &gpg_receipient, const std::string &plaintext_path, const std::string &ciphertext_path) {
    system(std::string("gpg -o " + ciphertext_path + " -e -r \""+ gpg_receipient + "\" " + plaintext_path ).c_str());
}

/*
 *  Decrypts file at ciphertext_path and creates file at plaintext_path
 */
void decrypt(const std::string &plaintext_path, const std::string &ciphertext_path) {
    system(std::string("gpg -d -o " + plaintext_path + " " + ciphertext_path).c_str());
}
