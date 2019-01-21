#include "config.h"
#include "git_repo.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include "manager.h"


int main(int argc, char *argv[]) {
    const std::vector<std::string> argList(argv + 1, argv + argc);
    const std::string HOME = std::getenv("HOME");

    const std::string default_folder = HOME + "/test";

    const std::map<std::string, std::string> config_vals{
            {"repo_path", default_folder + "/repo/"},
            {"db_path", default_folder + "/symlinks"}

    };
    config cnf(default_folder, "config", config_vals);
    manager t(cnf);

    //t.add_entry(HOME + "/testrc", "test");
    ///t.add_entry(HOME + "/h/h", "h");
    //t.deploy_all();
    //t.pass_to_git("status");
    t.remove_entry("h");
    return 0;
}