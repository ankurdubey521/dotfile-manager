#ifndef DOTFILE_MANAGER_MANAGER_H
#define DOTFILE_MANAGER_MANAGER_H

#include "config.h"
#include "git_repo.h"
#include <cstdlib>

class manager {
    config _symlinks;
    git_repo _repo;
public:
    manager(config&);
    void add_entry(const std::string&, const::std::string&);
    void remove_entry(const std::string&);
    void update();
    void deploy_all();
    void pass_to_git(const std::string&);
};


#endif //DOTFILE_MANAGER_MANAGER_H
