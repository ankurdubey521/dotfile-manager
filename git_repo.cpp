#include "git_repo.h"

/*
 * is_git_repo():
 * takes an ABSOLUTE path of folder and returns true if it is a valid git directory
 */
bool is_git_repo(const std::string &folder){
    std::string command_output = exec(std::string("git -C " + folder + " rev-parse --is-inside-work-tree").c_str());
    std::string command_output_filtered;

    //Remove any character other than alphabet from string
    for(auto &ch: command_output){
        if(isalpha(ch)){
            command_output_filtered += ch;
        }
    }

    return command_output_filtered.compare("true") == 0;
}

/*
 * git_repo::git_repo()
 */
git_repo::git_repo(config &configfile) {
    _repo_path = configfile.config_values["repo_path"];
    //If path does not exist create it
    if(!IsPathExist(_repo_path)){
        system(std::string("mkdir " + _repo_path).c_str());
    }
    //If repository is not initialized, initialize it
    if(!is_git_repo(_repo_path)){
        git_init();
    }
}

/*
 * git_repo::git_init()
 */
void git_repo::git_init() {
    std::system(std::string("git -C " + _repo_path + " init").c_str());
}

/*
 * git_repo::git_add()
 */
void git_repo::git_add() {
    std::system(std::string("git -C " + _repo_path + " add " + _repo_path + "/*").c_str());
}

/*
 * git_repo::git_commit()
 */
void git_repo::git_commit() {
    //Get current time
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string curr_time = std::ctime(&end_time);

    //Commit
    std::system((std::string("git -C " + _repo_path + " commit -m \"" + curr_time + "\"")).c_str());
}

/*
 * git_repo::git_push()
 */
void git_repo::git_push() {
    std::system((std::string("git -C " + _repo_path + " push origin master")).c_str());
}

/*
 * git_repo::git_path()
 */
std::string git_repo::path() {
    return _repo_path;
}

/*
 * git_repo::git_rm()
 */
void git_repo::git_rm(const std::string &path) {
    std::system(std::string("git -C " + _repo_path + "rm " + path).c_str());
}