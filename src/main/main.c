#include "vm.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define DATA_MEMORY     8192
#define PROGRAM_MEMORY  2048

char readUserInput(char* type) 
{
  char cmd, ch;
  fscanf(stdin,type, &cmd);
  while ((ch = getchar()) != '\n' && ch != EOF);
  return cmd;
}

int main(int argc, char** argv)
{

  // Check if binary file is supplied
  if (argc < 2)
  {
    printf("Usage: %s <binary_file>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Allocate memory for virtual machine and data
  unsigned int* data=calloc(DATA_MEMORY, sizeof(unsigned int));
  if (!data) 
  {
    puts("Error in calloc"); 
    return EXIT_FAILURE;
  }
  unsigned int* program=calloc(PROGRAM_MEMORY, sizeof(unsigned int));
  if (!program) 
  {
    puts("Error in calloc");
    free(data);
    return EXIT_FAILURE;
  }

  // Read the binary file to memory
  FILE* f = fopen(argv[1], "r");
  if (!f) 
  {
    puts("Cannot open the binary file");
    free(data); 
    free(program); 
    return EXIT_FAILURE;
  }
  fread(data, sizeof(unsigned int), DATA_MEMORY, f);
  fclose(f);

  //for (i=0;i<21;i++)printf("i= %d--->%d\n",i,data[i]);

  puts("\n>> Allocating and initializing the virtual machine");
  VirtualMachinePtr vm = virtualMachineAllocInit(data, program);

  puts(">> Starting the virtual machine");
  char cmd = 0;
  size_t addr=0;
  int running = 0;
  puts(">> (S)tep (R)un (P)eek (Q)uit");
  cmd = readUserInput("%c");
  while(!(cmd=='Q' || running) )
  {
    if (cmd=='R' || cmd=='r')
    {
        running = virtualMachineStep(vm);
      //    virtualMachinePeek(vm, addr);
    } 
    else if (cmd == 'S' || cmd == 's')
    {
        virtualMachineStep(vm);
        virtualMachinePeek(vm, addr);
        puts(">> (S)tep (R)un (P)eek (Q)uit"); 
        cmd = readUserInput("%c");     
    }
    else if (cmd == 'P' || cmd == 'p') 
    {
        printf(">> Please enter address: ");
        addr = readUserInput("%zu");	
        virtualMachinePeek(vm, addr);
        puts(">> (S)tep (R)un (P)eek (Q)uit"); 
        cmd = readUserInput("%c");     
    }
    else if (cmd == 'Q' || cmd == 'q')
    {
        running = -1;
    }
    else 
    {
        puts(">> Invalid command, please try again");
        puts(">> (S)tep (R)un (P)eek (Q)uit");
        cmd = readUserInput("%c");     
    }
  }

  puts("\n>> Stopping the virtual machine\n");

  free(data);
  free(program);
  virtualMachineDestruct(vm);
  return EXIT_SUCCESS;
}
