# Corewar

A fierce battle of survival between battle programs.

This project recreates the game “[Core war](https://en.wikipedia.org/wiki/Core_War)” by D. G. Jones & A. K. Dewdney

## Objective

- The assembler: this is the program that will compile your champions and translate them from the language you will write them in (assembly language) into “Bytecode”.Bytecode is a machine code, which will be directly interpreted by the virtual
machine.
- The virtual machine: It’s the “arena” in which your champions will be executed.
It offers various functions, all of which will be useful for the battle of the champions.
Obviously, the virtual machine should allow for numerous simultaneous processes;
we are asking you for a gladiator fight, not a one-man show simulator.

## Installation

`make` to compile the Assembler and Corewar (the Virtual Machine)

### Assembler

`./asm <your_champ.s>` to compile your champion

(Work in progress)

### Corewar

`./corewar [optional flags] <your_champ.cor>` to have your champ go beat other people up

### Test script

`./apustaja.sh` and follow the **VERY INTUITIVE** instructions

## Note

As most other projects in Hive, Corewar is restricted to only a handful of libc functions. For this project, the followings are used:
```
◦ open
◦ close
◦ read
◦ write
◦ malloc
◦ free
◦ exit
```
Everything else is written by yours truly (❁´◡`❁)
