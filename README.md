# assembler_compiler
### courework project - assembler compiler of defined assembly language

This coursework project is a compailer of an imagination computer machine according to a define assembly language and it's addressing methods.


**The operations table:**  

| Operarion name | Operation code (decimal) | Example |
| --------------|:-------------------------|--------|
| mov |0| mov A, r1 |
| cmp |1| cmp A, r1 |
| add |2| add A, r0 |
| sub |3| sub #3, r1 |
| lea |4| lea HELLO, r1 |
| clr |5| clr r2 |
| not |6| not r2 |
| inc |7| inc r2 |
| dec |8| dec C |
| jmp |7| jmp LINE |
| bne |10| bne LINE |
| red |11| red r1 |
| prn |12| prn r1 |
| jsr |13| jsr FUNC |
| rts |14| rts |
| stop |15| stop |



**The addresing method table:**

	
| Addresing number | Addresing method | Example |
|:--------------|---------------|---------------|
| 0 |immediate addresing| mov #-1,r2 |
| 1 |direct addresing| x: .data 23 OR dec x |
| 2 |indirect register addresing| inc *r1 OR mov *r1,**r2 |
| 3 |direct register addresing| clr r1 OR  mov r1,*r2 |




 **The program take care of the translating process and not for the linking and loading.**



### The program get as an input files of assembly language with the suffix 'as' and return as an output 3 files for each assembly file: ###

1. *object file* that contain the machine code translating to octal base with the appropriate memmory addres in decimal base.
this file is with the suffix 'ob'.

2. *enteranl file* that contain the labels that defined in the assemly text as an entry label with it's appropriate vlue in the labels table.
this file is with the suffix 'ent'.

3. *external file* that contain the labels that defined as externals and the appropriate address that they have been used in the asseembly program. this file is with the suffix 'ext'.

The program get the assembly files by their names (without the suffix) as arguments to the command line.

**The package contain:**
- makefile to compile the poject by gcc compiler.
- run file named assembler.
- The package divided to modules by topicts (main, analize, function1, etc.)
- The package also contain header files that contain static tables, prototypes, libraries etc.
