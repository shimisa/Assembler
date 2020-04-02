# assembler_computing
courework project - assembler compiler of defined assembly language

This coursework project is a compailer of an imagination computer machine according to a define assembly language and it's addressing nmthods. The program take care of the translating process and not for the linking and loading. 

The program get as an input files of assembly language with the suffix 'as' and return as an output 3 files for each assembly file: 
1. object file that contain the machine code translating to octal base with the appropriate memmory addres in decimal base.
this file is with the suffix 'ob'.
2. enteranl file that contain the labels that defined in the assemly text as an entry label with it's appropriate vlue in the labels table.
this file is with the suffix 'ent'.
3. external file taht contain the labels that defined as externals and the appropriate address that they have been used in the asseembly program. this file is with the suffix 'ext'.

The program get the assembly files by their names (without the suffix) as arguments to the command line.

