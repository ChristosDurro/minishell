# minishell

`minishell` is a basic shell implementation in C, created with bash as a reference. It provides core shell functionalities including command execution, redirection, piping, environment variable handling, and built-in commands.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [Signal Handling](#signal-handling)

## Introduction

The `minishell` project aims to create a shell that mimics the behavior of bash. It includes essential features such as command execution, history, redirections, pipes, and built-in commands.

## Features

- Display a prompt when waiting for a new command.
- Working command history.
- Search and launch executables based on the `PATH` variable or using a relative/absolute path.
- Handle single (`'`) and double (`"`) quotes to prevent interpretation of meta-characters.
- Implement redirections:
  - `<` for input redirection.
  - `>` for output redirection.
  - `<<` for heredoc redirection.
  - `>>` for output append redirection.
- Implement pipes (`|`) to connect the output of one command to the input of another.
- Handle environment variables (`$VAR`) and special variables like `$?`.
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\` signals with appropriate behavior.
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

## Installation

To compile the `minishell` program, clone this repository and run `make` using the provided Makefile:

```bash
git clone https://github.com/ChristosDurro/minishell.git
cd minishell
make
```

## Usage

To start the minishell program, run the executable:

```bash
./minishell
```

## Built-in Commands

minishell includes the following built-in commands:

- `echo [-n] [string ...]`: Display a line of text.
- `cd [directory]`: Change the current directory to directory.
- `pwd`: Print the current working directory.
- `export [name[=value] ...]`: Set environment variables.
- `unset [name ...]`: Unset environment variables.
- `env`: Display the current environment variables.
- `exit [n]`: Exit the shell with a status of n.
- Signal Handling
- In interactive mode, minishell handles signals as follows:

- `ctrl-C`: Displays a new prompt on a new line.
- `ctrl-D`: Exits the shell.
- `ctrl-\`: Does nothing.

