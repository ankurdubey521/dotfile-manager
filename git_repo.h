/*
 * class git_repo:
 * Provides interface for interacting with git repository
 *
 * The path for repo is read from the passed configuration file. The repo is initialized if
 * it is not present. The class implements custom functions wrapped over the git command for
 * easy access. Other commands for managing the git repo are directly passed to git the manager class
 *
 * members:
 *      _repo_path: Stores the ABSOLUTE path of git repository
 *
 * methods:
 *      path(): Returns _repo_path
 *      git_init(): Initializes git repo at _repo_path if not already initialized
 *      git_add(): Executes git add * on _repo_path
 *      git_commit(): Commits all files in _repo_path with date/time set as commit message
 *      git_push(): Executes git push -u origin master on _repo_path
 *      git_rm(): Executes git rm on passed file path
 */

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

private:
    //Members
    std::string _repo_path;

public:
    //Methods
    explicit git_repo(config&);
    std::string path();
    void git_init();
    void git_add();
    void git_rm(const std::string&);
    void git_commit();
    void git_push();
};

#endif //DOTFILE_MANAGER_GIT_REPO_H
