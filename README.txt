Assembler and virtual machine for running simple assembly programs.
The list of supported instructions and their format are given in resources/instruction_set.txt.

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
To run the examples, type the following commands while inside the src/main folder:
  
   gcc -o assembler assembler.c
   ./assembler ../test/simple_test.asm ../test/simple_test.bin
   ./assembler ../test/subroutine_test.asm ../test/subroutine_test.bin

   gcc -o vm vm.c main.c
   ./vm ../test/simple_test.bin
   ./vm ../test/subroutine_test.bin

