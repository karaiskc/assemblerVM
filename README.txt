Assembler and virtual machine for running simple assembly programs.
The list of supported instructions and their format are given in instruction_set.txt.

Usage:
   -Compile assembler.c 
       gcc -o assembler assembler.c
   -Write your assembly code in <your_filename>.asm
   -Run the assembler with your filename as first argument and a filename to write the binary output as second argument
       ./assembler <your_filename>.asm <your_filename>.bin
   -Compile the vm
       gcc -o vm vm.c main.c
   -Run the vm with the binary file as input
       ./vm <your_filename>.bin

Two example files (simple_test.asm, subroutine_test.asm) have been given for demonstration purposes.
