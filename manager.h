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
 * For encrypted entries, the encrypted version is simply copied to the repo maintianing a similar directory
 * structure. Because it is not a symlink, update() has to manualy copy new encrypted versions to repo before
 * pushing
 *
 * Members:
 *      _symlinks: config file for storing list of symlinked files
 *      _encrypts: config file for storing list of encrypted files
 *      _repo: git repo initialized at path pointed by passed configfile
 * Methods:
 *      add_entry(): adds an entry in _symlinks and sets up symlink to the file
 *      add_encrypted_entry: adds an entry in _encrypts and copies encrypted file to repo
 *      remove_entry(): removes entry in _symlinks and restores file to original state
 *      remove_encrypted_entry(): removes entry in _encrypts and encrypted file from repo
 *      update(): adds, commits and pushes all changes to remote
 *      deploy_all(): symlinks all entries in _symlink to their positions. Used for rapid deployment
 *      pass_to_git(): passes unhandled commands directly to git
 */

#ifndef DOTFILE_MANAGER_MANAGER_H
#define DOTFILE_MANAGER_MANAGER_H

#include <cstdlib>

#include "config.h"
#include "git_repo.h"
#include "misc.h"


class manager {
private:
    //Members
    config _symlinks, _encrypts;
    git_repo _repo;
    std::string _gpg_recepient;

public:
    //Methods
    explicit manager(config&);
    void add_entry(const std::string&, const::std::string&);
    void add_encrypted_entry(const std::string&, const::std::string&);
    void remove_entry(const std::string&);
    void remove_encrypted_entry(const::std::string&);
    void update();
    void deploy_all();
    void pass_to_git(const std::string&);
};


#endif //DOTFILE_MANAGER_MANAGER_H
