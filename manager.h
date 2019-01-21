/*
 * class manager:
 * main class of the program that uses class git_repo for functioning
 *
 * A _symlink object of class config is initialized in the same directory as config file passed to it,
 * also, a git_repo is initialized to the path stored in the passed config_file. Entries are added to the _symlink
 * file in the following format:
 *         *label name* = *original ABSOLUTE path of dotfile*
 * the dotfile is moved to repo_path + original_path. For eg: if a file was located at $HOME/.bashrc,
 * it will be moved to repo_path/$HOME/.bashrc. A symlink to the original position is then created
 *
 * Members:
 *      _symlinks: config file for storing list of symlinked files
 *      _repo: git repo initialized at path pointed by passed configfile
 * Methods:
 *      add_entry(): adds an entry in _symlinks and sets up symlink to the file
 *      remove_entry(): removes entry in _symlinks and restores file to original state
 *      update(): adds, commits and pushes all changes to remote
 *      deploy_all(): symlinks all entries in _symlink to their positions. Used for rapid deployment
 *      pass_to_git(): passes unhandled commands directly to git
 */

#ifndef DOTFILE_MANAGER_MANAGER_H
#define DOTFILE_MANAGER_MANAGER_H

#include "config.h"
#include "git_repo.h"
#include <cstdlib>

class manager {
private:
    //Members
    config _symlinks;
    git_repo _repo;

public:
    //Methods
    explicit manager(config&);
    void add_entry(const std::string&, const::std::string&);
    void remove_entry(const std::string&);
    void update();
    void deploy_all();
    void pass_to_git(const std::string&);
};


#endif //DOTFILE_MANAGER_MANAGER_H
