//
// Created by ankurdubey on 20/1/19.
//

#include "manager.h"

manager::manager(config &configfile) : _symlinks(configfile.get_folder_path(), "symlinks", std::map<std::string, std::string>()),
                                        _repo(configfile){
}

void manager::add_entry(const std::string &source, const std::string &label) {
    bool entry_present  = false;
    if(!_symlinks.config_values[label].empty()){
        std::cout << "Label already exists for " << _symlinks.config_values[label] << std::endl;
        entry_present = true;
    }
    else{
        for(auto p: _symlinks.config_values){
            if(p.second == source){
                std::cout << "Entry already exists for label " << p.first << std::endl;
                entry_present = true;
                break;
            }
        }
    }
    if(!entry_present){
        _symlinks.config_values[label] = source;
        _symlinks.write_config_file();

        std::string destination_path = _repo.path() + source.substr(1, source.length() - 1);
        int i =  destination_path.length() - 1, filename_size = 0;
        while(destination_path[i] != '/'){
            --i;
            ++filename_size;
        }
        ++filename_size;
        system(std::string("mkdir -p " + destination_path.substr(0, destination_path.length() - filename_size)).c_str());
        system(std::string("mv " + source + " " + destination_path).c_str());
        system(std::string("ln -s " + destination_path + " " + source).c_str());
        std::cout << "Entry with label " << label << " at " << source<< " added to tracking list" << std::endl;
        update();
    }
}

void manager::remove_entry(const std::string &label) {
    bool entry_found = false;
    for(auto &p: _symlinks.config_values){
        if(p.first == label) {
            auto path = p.second;
            _symlinks.config_values.erase(label);
            entry_found = true;
            std::cout << "Entry with label " << label << " at " << path << " removed from tracking list" << std::endl;
            system(std::string("rm " + path).c_str());
            std::string destination_path = _repo.path() + path.substr(1, path.length() - 1);
            system(std::string("mv " + destination_path + " " + path).c_str());
            _symlinks.write_config_file();
            update();
            break;
        }
    }
    if(!entry_found){
        std::cout << "No entry with label " << label << " found" << std::endl;
    }
}

void manager::update() {
    _repo.git_add();
    _repo.git_commit();
    _repo.git_push();
}

void manager::deploy_all() {
    for(auto &p: _symlinks.config_values) {
        if (p.second.length() > 1) {
            system(std::string("rm " + p.second).c_str());
            std::string destination_path = _repo.path() + p.second.substr(1, p.second.length() - 1);
            system(std::string("ln -s " + destination_path + " " + p.second).c_str());
            std::cout << "Entry with label " << p.first << " at " << p.second << " recreated" << std::endl;
        }
    }
}

void manager::pass_to_git(const std::string &command) {
    std::cout << "git: " << std::flush;
    system(std::string("git -C " + _repo.path() + " " + command).c_str());
}


