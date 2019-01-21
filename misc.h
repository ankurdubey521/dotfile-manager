/*
 * Provides miscellaneous functions for support
 */

#ifndef DOTFILE_MANAGER_MISC_H
#define DOTFILE_MANAGER_MISC_H

#include <array>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

//Returns the "text" output of a shell command
std::string exec(const char*);

//Returns true if a directory exists
bool IsPathExist(const std::string&);

//Returns true if a file exists
bool fexists(const std::string&);

//Encrypts a file using gpg
void encrypt(const std::string&, const std::string&, const std::string&);

//Decrypts a gpg encrypted file
void decrypt(const std::string&, const std::string&);

#endif //DOTFILE_MANAGER_EXEC_H
