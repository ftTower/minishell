# Minishell  
_As beautiful as a shell_  

![header](https://github.com/ftTower/ftTower/blob/main/assets/minishell/header.png)

## Summary  
This project involves creating a simple shell, your very own little Bash. Through this project, you will gain extensive knowledge about processes and file descriptors.  

![prompt](https://github.com/ftTower/ftTower/blob/main/assets/minishell/prompt.png)


## Table of Contents  
1. [Introduction](#introduction)  
2. [Common Instructions](#common-instructions)  
3. [Mandatory Part](#mandatory-part)  

---

## Chapter I: Introduction  
Shells have existed since the very beginning of IT. Initially, developers found communicating with computers via aligned 1/0 switches extremely frustrating. This led to the creation of software that allowed communication with computers using interactive command lines in a language closer to human language.  

With Minishell, you’ll experience the challenges developers faced before graphical interfaces like Windows existed.  

---

## Chapter II: Common Instructions  
- The project must be written in **C** and adhere to the **Norm**.  
- Functions must not quit unexpectedly (e.g., segmentation faults, bus errors).  
- All heap-allocated memory must be properly freed. Memory leaks are not tolerated.  
- A **Makefile** must be provided with the following rules: `$(NAME)`, `all`, `clean`, `fclean`, and `re`.  
- Bonus files must be placed in `_bonus.{c/h}` files and evaluated separately.  
- If allowed, include your **libft** in a `libft` folder and compile it using its Makefile.  
- Testing your project is encouraged but not graded.  
- Submit your work to the assigned Git repository. Only the repository content will be graded.  

---

## Chapter III: Mandatory Part  
### Program Name  
`minishell`  

### Turn-in Files  
`Makefile`, `*.h`, `*.c`  

### External Functions Allowed  
`readline`, `add_history`, `printf`, `malloc`, `free`, `write`, `fork`, `execve`, `pipe`, `signal`, `exit`, etc.  
![shlvl](https://github.com/ftTower/ftTower/blob/main/assets/minishell/shell_lvl.png)

### Description  
Your shell must:  
- Display a prompt and handle a working history.  
- Search and execute commands using the `PATH` variable or relative/absolute paths.  
- Handle single (`'`) and double (`"`) quotes.
![env_var](https://github.com/ftTower/ftTower/blob/main/assets/minishell/cat_var.png)
- Implement redirections (`<`, `>`, `<<`, `>>`) and pipes (`|`).  
![redirection](https://github.com/ftTower/ftTower/blob/main/assets/minishell/redirection.png)
- Handle environment variables (`$`), exit status (`$?`), and signals (`ctrl-C`, `ctrl-D`, `ctrl-\`).  
- Implement built-in commands:  
    - `echo` (with `-n` option)  
    - `cd`  
    - `pwd`  
    - `export`  
    - `unset`  
    - `env`  
    - `exit`  
![basic commands](https://github.com/ftTower/ftTower/blob/main/assets/minishell/basic_commands.png)

> **Note:** The `readline()` function may cause memory leaks, but your own code must not.  

---

Good luck with your Minishell project!  