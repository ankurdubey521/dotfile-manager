#include "git_repo.h"

bool is_git_repo(const std::string &folder){
    std::string res = exec(std::string("git -C " + folder + " rev-parse --is-inside-work-tree").c_str()), tres;
    for(auto& ch: res){
        if(isalpha(ch)){
            tres += ch;
        }
    }
    return tres.compare("true") == 0;
}

git_repo::git_repo(config &configfile) {
    _repo_path = configfile.config_values["repo_path"];
    if(!IsPathExist(_repo_path)){
        system(std::string("mkdir " + _repo_path).c_str());
    }
    if(!is_git_repo(_repo_path)){
        git_init();
    }
}

void git_repo::git_init() {
    std::system(std::string("git -C " + _repo_path + " init").c_str());
}

void git_repo::git_add() {
    std::system(std::string("git -C " + _repo_path + " add " + _repo_path + "/*").c_str());
}

void git_repo::git_commit() {
    std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string curr_time = std::ctime(&end_time);
    std::system((std::string("git -C " + _repo_path + " commit -m \"" + curr_time + "\"")).c_str());
}

void git_repo::git_push() {
    std::system((std::string("git -C " + _repo_path + " push origin master")).c_str());
}

std::string git_repo::path() {
    return _repo_path;
}
