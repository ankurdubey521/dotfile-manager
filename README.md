# Dotfile Manager

Manages backing up and easy deployment of dotfiles and text configuration files on linux based systems. This program helps you to track various configurtion files by backing them up periodically to a user defined remote git repository. Sensitive files can be encrypted with the help of a user defined gpg key before uploading. The backed up configuration files can be restored at once using a single command. 


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
        -d                  recreate all deleted config files
        -g <command>        passes "command" to git directly for set repo
Note: Only one command supported at a time as of now

```
