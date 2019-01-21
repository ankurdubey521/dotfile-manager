# Dotfile Manager

Program for managing dotfiles and text configuration files on linux

```  
  usage: dmgr [-a <absolute path of file> <label>]
            [-r <label>]  [-u]  [-d]  [-g <command>] 
            
        -a <path> <label>   add entry identified by "label" at "path"
        -r <label>          remove entry identified by "label"
        -u                  sync all entries with remote
        -d                  recreate symlinks for all entries
        -g <command>        passes "command" to git directly for set repo
```
