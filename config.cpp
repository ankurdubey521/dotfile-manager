#include "config.h"

/*
 *  config::config():
 *  Creates _config_folder_path and _config_file_path if not present and initializes file default_values.
 *  If file is already present the initialization part is skipped. _config_values is then populated
 */
config::config(const std::string &config_folder_path,const std::string &file_name,
        const std::map<std::string, std::string> &default_values){

    _config_folder_path = config_folder_path;
    //If folder does not exist create it
    if(!IsPathExist(_config_folder_path)){
        std::string command = "mkdir ";
        command += _config_folder_path;
        system(command.c_str());
    }

    _config_file_path = config_folder_path + "/" + file_name;
    //If file does not exist create and initialize it
    if(fexists(_config_file_path)){
        _populate_config_values();
    }
    else{
        _init_config_file(default_values);
        _populate_config_values();
    }
}

/*
 * config::_init_config_file()
 */
void config::_init_config_file(const std::map<std::string, std::string> &default_values) {
    config_values = default_values;
    write_config_file();
}

/*
 * config::_populate_config_values():
 * reads configuration file pointed by _config_file_path and populates config_values map
 */
void config::_populate_config_values() {
    std::ifstream configfile(_config_file_path.c_str());
    while(configfile){
        std::string line, field, val;
        int  i = 1;
        getline(configfile, line);

        //store field name in field
        while(i < line.size() && line[i] != '*'){
            field += line[i];
            ++i;
        }
        while(line[++i] != '*');
        ++i;

        //store value in value
        while(i < line.size() && line[i] != '*'){
            val += line[i];
            ++i;
        }
        config_values[field] = val;
    }
    configfile.close();
}

/*
 * config::write_config_file():
 * deleted the saved configuration file and replaces it with values in config_values
 */
void config::write_config_file() const{
    std::ofstream configfile(_config_file_path, std::ios::trunc);
    for(auto &val: config_values){
        configfile << "*" << val.first << "* = *" << val.second << "*" << std::endl;
    }
    configfile.close();
}

/*
 * config::get_folder_path():
 */
std::string config::get_folder_path() const{
    return _config_folder_path;
}
