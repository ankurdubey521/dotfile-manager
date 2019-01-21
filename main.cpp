#include <cstdlib>
#include <iostream>
#include <vector>

#include "config.h"
#include "git_repo.h"
#include "manager.h"

void display_help(){
    std::cout << "usage: dmgr [-a <absolute path of file> <label>]" << std::endl;
    std::cout << "            [-e <absolute path of file> <label>]" << std::endl;
    std::cout << "            [-r <label>]  [-s <label>]  [-u]  [-d]" << std::endl;
    std::cout << "            [-g <command>]" << std::endl;
    std::cout << std::endl;
    std::cout << "\t-a <path> <label>   add entry identified by \"label\" at \"path\"" << std::endl;
    std::cout << "\t-e <path> <label>   add encrypted entry identified by \"label\" at \"path\"" << std::endl;
    std::cout << "\t-r <label>          remove entry identified by \"label\"" << std::endl;
    std::cout << "\t-s <label>          remove encrypted entry identified by \"label\"" << std::endl;
    std::cout << "\t-u                  sync all entries with remote" << std::endl;
    std::cout << "\t-d                  recreate symlinks for all entries" << std::endl;
    std::cout << "\t-g <command>        passes \"command\" to git directly for set repo" << std::endl;
    std::cout << "Note: Only one command supported at a time as of now" << std::endl;
}

int main(int argc, char *argv[]) {
    const std::vector<std::string> argList(argv + 1, argv + argc);
    const std::string HOME = std::getenv("HOME");

    const std::string default_folder = HOME + "/test";

    const std::map<std::string, std::string> config_vals{
            {"repo_path", default_folder + "/repo/"},
            {"db_path", default_folder + "/symlinks"},
            {"gpg_recepient_name", "Ankur Dubey"},
            {"encrypt_db_path", default_folder + "/encrypt"}
    };
    config configfile(default_folder, "config", config_vals);
    manager mgr(configfile);

    if(argList.size() > 0) {
        if (argList[0] == "-a") {
            if (argList.size() != 3) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.add_entry(argList[1], argList[2]);
        }
        else if (argList[0] == "-e") {
            if (argList.size() != 3) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.add_encrypted_entry(argList[1], argList[2]);
        }
        else if (argList[0] == "-r") {
            if (argList.size() != 2) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.remove_entry(argList[1]);
        }
        else if (argList[0] == "-s") {
            if (argList.size() != 2) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.remove_encrypted_entry(argList[1]);
        }
        else if (argList[0] == "-u") {
            if (argList.size() != 1) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.update();
        }
        else if (argList[0] == "-d") {
            if (argList.size() != 1) {
                std::cout << "Invalid Number of arguments" << std::endl;
                return -1;
            }
            mgr.deploy_all();
        }
        else if (argList[0] == "-g") {
            std::string command;
            for (int i = 1; i < argList.size(); ++i) {
                command += argList[i];
                command += " ";
            }
            mgr.pass_to_git(command);
        }
        else{
            display_help();
        }
    }
    else{
        display_help();
    }
    return 0;
}