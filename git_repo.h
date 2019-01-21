
#ifndef DOTFILE_MANAGER_GIT_REPO_H
#define DOTFILE_MANAGER_GIT_REPO_H

#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "config.h"
#include "misc.h"
#include <iostream>
#include <cctype>

class git_repo {
    std::string _repo_path;
public:
    git_repo(config&);
    std::string path();
    void git_init();
    void git_add();
    void git_commit();
    void git_push();
};


#endif //DOTFILE_MANAGER_GIT_REPO_H
