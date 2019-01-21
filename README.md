# Dotfile Manager

Program for managing dotfiles and text configuration files on linux

```  
  usage: dmgr [-a <absolute path of file> <label>]
            [-e <absolute path of file> <label>]
            [-r <label>]  [-s <label>]  [-u]  [-d]
            [-g <command>]

        -a <path> <label>   add entry identified by "label" at "path"
        -e <path> <label>   add encrypted entry identified by "label" at "path"
        -r <label>          remove entry identified by "label"
        -s <label>          remove encrypted entry identified by "label"
        -u                  sync all entries with remote
        -d                  recreate symlinks for all entries
        -g <command>        passes "command" to git directly for set repo
Note: Only one command supported at a time as of now

```
