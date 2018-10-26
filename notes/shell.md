# How a shell works

A shell does 3 main things while it lives.

1. *Initialize*: Read and execute its configuration files, which some of them
   may change it's behaviour. For example, `zsh` reads its configuration files
   from `/etc/zshrc` or `~/.zshrc`.
2. *Interpret*: The shell reads commands (most user commands) from the `stdin`
   then it executes them.
3. *Terminate*: After step 2, the shell executes any shutdown commands, frees up
   memory and terminates.

