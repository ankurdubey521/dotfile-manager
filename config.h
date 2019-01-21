/*
 *  class config:
 *  provides interface for interacting with configuration files
 *
 *  The configuration file is written at _config_file_path, which resides in the folder
 *  given by _config_folder_path.The configuration files are stored in the following format:
 *      *field_name* = *field_value*
 *  The object reads the configuration file and exposes a map<string, string> for accessing
 *  and modifying fields
 *
 *  members:
 *      _config_file_path: ABSOLUTE path of configuration file
 *      _config_folder_path: ABSOLUTE path of configuration folder
 *      config_values: map for accessing configuration fields
 *
 *  methods:
 *      _init_config_file(): initializes config file with default values passed to it
 *      _populate_config_values(): reads configuration file and populates config_values
 *      write_config_file(): overwrites config file with contents of config_values
 *      get_folder_path(): returns _config_folder_path
 */

#ifndef DOTFILE_MANAGER_CONFIG_H
#define DOTFILE_MANAGER_CONFIG_H

#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include "misc.h"

class config{

private:
    //Members
    std::string _config_file_path,_config_folder_path;
    //Methods
    void _init_config_file(const std::map<std::string, std::string>&);
    void _populate_config_values();

public:
    //Members
    std::map<std::string, std::string> config_values;
    //Methods
    config(const std::string&, const std::string&,const std::map<std::string, std::string>&);
    void write_config_file() const;
    std::string get_folder_path() const;
};

#endif //DOTFILE_MANAGER_CONFIG_H
