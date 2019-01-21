#include "manager.h"

/*
 * manager::manager():
 * Initializes _symlinks, _encrypts, _repo
 */
manager::manager(config &configfile) :
    _symlinks(configfile.get_folder_path(), "symlinks", std::map<std::string, std::string>()),
    _encrypts(configfile.get_folder_path(), "encrypts", std::map<std::string, std::string>()),
    _repo(configfile){
    _gpg_recepient = configfile.config_values["gpg_recepient_name"];
}

/*
 * manager::add_entry():
 * adds an entry in _symlinks and sets up symlink to the file
 */
void manager::add_entry(const std::string &source, const std::string &label) {

    bool entry_present  = false;
    //Check if entry with same label is present
    if(!_symlinks.config_values[label].empty()){
        std::cout << "Label already exists for " << _symlinks.config_values[label] << std::endl;
        entry_present = true;
    }
    //Check if entry with same path is present
    else{
        for(auto p: _symlinks.config_values){
            if(p.second == source){
                std::cout << "Entry already exists for label " << p.first << std::endl;
                entry_present = true;
                break;
            }
        }
    }

    //If no conflicting entry is present
    if(!entry_present){

        //Update map and write configuration to file
        _symlinks.config_values[label] = source;
        _symlinks.write_config_file();

        //ABSOLUTE path to where file has to be moved
        std::string destination_path = _repo.path() + source.substr(1, source.length() - 1);
        size_t i =  destination_path.length() - 1, filename_size = 0;
        while(destination_path[i] != '/'){
            --i;
            ++filename_size;
        }
        ++filename_size;

        //Setup path if it does not exist
        system(std::string("mkdir -p " + destination_path.substr(0, destination_path.length() - filename_size)).c_str());

        //Move file to destination path
        system(std::string("mv " + source + " " + destination_path).c_str());

        //Create symlink
        system(std::string("ln -s " + destination_path + " " + source).c_str());
        std::cout << "Entry with label " << label << " at " << source << " added to tracking list" << std::endl;

        update();
    }
}

void manager::add_encrypted_entry(const std::string &source, const ::std::string &label) {
    bool entry_present  = false;
    //Check if entry with same label is present
    if(!_encrypts.config_values[label].empty()){
        std::cout << "Label already exists for " << _encrypts.config_values[label] << std::endl;
        entry_present = true;
    }
        //Check if entry with same path is present
    else{
        for(auto p: _encrypts.config_values){
            if(p.second == source){
                std::cout << "Entry already exists for label " << p.first << std::endl;
                entry_present = true;
                break;
            }
        }
    }

    //If no config entry is present
    if(!entry_present){
        //Update map and write configuration to file
        _encrypts.config_values[label] = source;
        _encrypts.write_config_file();

        //ABSOLUTE path to where file has to be moved
        std::string destination_path = _repo.path() + source.substr(1, source.length() - 1);
        size_t i =  destination_path.length() - 1, filename_size = 0;
        while(destination_path[i] != '/'){
            --i;
            ++filename_size;
        }
        ++filename_size;

        //Setup path if it does not exist
        system(std::string("mkdir -p " + destination_path.substr(0, destination_path.length() - filename_size)).c_str());

        destination_path += ".gpg";

        //Copy encrypted version of configfile to repo
        encrypt(_gpg_recepient, source, destination_path);
        std::cout << "Encrypted entry with label " << label << " at " << source << " added to tracking list" << std::endl;

        update();
    }
}

/*
 * manager::remove_entry():
 * removes entry in _symlinks and restores file to original state
 */
void manager::remove_entry(const std::string &label) {
    bool entry_found = false;
    for(auto &p: _symlinks.config_values){
        if(p.first == label) {
            //path: Original ABSOLUTE path of file
            auto path = p.second;
            entry_found = true;

            //remove symlink
            system(std::string("rm " + path).c_str());

            //destination: ABSOLUTE path where file is stored in repo
            std::string destination_path = _repo.path() + path.substr(1, path.length() - 1);

            //move file back to original path
            system(std::string("mv " + destination_path + " " + path).c_str());

            //untrack git file
            //_repo.git_rm(destination_path);

            //erase entry and update file
            _symlinks.config_values.erase(label);
            _symlinks.write_config_file();
            std::cout << "Entry with label " << label << " at " << path << " removed from tracking list" << std::endl;

            update();
            break;
        }
    }
    if(!entry_found){
        std::cout << "No entry with label " << label << " found" << std::endl;
    }
}


void manager::remove_encrypted_entry(const ::std::string &label) {
    bool entry_found = false;
    for(auto &p: _encrypts.config_values){
        if(p.first == label) {
            //path: Original ABSOLUTE path of file
            auto path = p.second;
            entry_found = true;

            //destination: ABSOLUTE path where file is stored in repo
            std::string destination_path = _repo.path() + path.substr(1, path.length() - 1) + ".gpg";

            //move file back to original path
            system(std::string("rm " + destination_path).c_str());

            //untrack git file
            //_repo.git_rm(destination_path);

            //erase entry and update file
            _encrypts.config_values.erase(label);
            _encrypts.write_config_file();
            std::cout << "Encrypted entry with label " << label << " at " << path << " removed from tracking list" << std::endl;

            update();
            break;
        }
    }
    if(!entry_found){
        std::cout << "No encrypted entry with label " << label << " found" << std::endl;
    }
}

/*
 * manager::update():
 * encrypts all files set to encryption and
 * adds, commits and pushes all changes to remote
 */
void manager::update() {
    //Encrypt and copy all files set in _encrypts
    for(auto &p: _encrypts.config_values){
        std::string source = p.second;
        if(source.length() > 1) {
            //ABSOLUTE path to where file has to be moved
            std::string destination_path = _repo.path() + source.substr(1, source.length() - 1) + ".gpg";

            //Remove old version of encrypted file
            system(std::string("rm " + destination_path).c_str());

            //Copy encrypted version of configfile to repo
            encrypt(_gpg_recepient, source, destination_path);
        }
    }

    _repo.git_add();
    _repo.git_commit();
    _repo.git_push();
}

/*
 *  manager::deploy_all():
 *  symlinks all entries in _symlink to their positions. Used for rapid deployment
 */
void manager::deploy_all() {
    //Create symlinks for all normal config files
    for(auto &p: _symlinks.config_values) {
        if (p.second.length() > 1) {
            //If any other file exists at that path delete it
            if(fexists(p.second)) {
                system(std::string("rm " + p.second).c_str());
            }

            //destination: ABSOLUTE path where file is stored in repo
            std::string destination_path = _repo.path() + p.second.substr(1, p.second.length() - 1);
            //Create symlink
            system(std::string("ln -s " + destination_path + " " + p.second).c_str());
            std::cout << "Entry with label " << p.first << " at " << p.second << " recreated" << std::endl;
        }
    }

    //Decrypt and copy back all encrypted files
    for(auto &p: _encrypts.config_values){
        if(p.second.length() > 1){
            //If any other file exists at that path delete it
            if(fexists(p.second)) {
                system(std::string("rm " + p.second).c_str());
            }

            //destination: ABSOLUTE path where encrypted file is stored in repo
            std::string destination_path = _repo.path() + p.second.substr(1, p.second.length() - 1) + ".gpg";

            //Create decrypted file at p.second
            decrypt(p.second, destination_path);
            std::cout << "Encrypted entry with label " << p.first << " at " << p.second << " recreated" << std::endl;
        }
    }
}

/*
 * manager::pass_to_git():
 * passes unhandled commands directly to git
 */
void manager::pass_to_git(const std::string &command) {
    std::cout << "git: " << std::flush;
    system(std::string("git -C " + _repo.path() + " " + command).c_str());
}