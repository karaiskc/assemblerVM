#include <stdio.h>
#include "vm.h"
#include <stdlib.h>

//#define DEBUG
#ifdef DEBUG 
  #define PRINT if(1)
#else
  #define PRINT if(0)
#endif


/*  This is the struct for the virtual machine
    
    dataMem and programMem are the pointers to the start of the memory area
    instructionPointer keeps track of the current instruction
    registers are the registers of the virtual machine
    stateRegister is used to store the values of the instruction pointer and registers when jumping to the subroutine
*/
struct VirtualMachine {
  unsigned int* programMem;
  unsigned int* ram;

  unsigned int instructionPointer;
  unsigned int registers[5];
  unsigned int stateRegister[6];
};


/*  Initializes the virtual machine
    Pointers to the data and program memory are given as parameters
    all the registers and instructionPointer should be initialized to zero

    @param  programMem    pointer to the beginning of the program memory allocated to the virtual machine
    @param  ram           pointer to the beginning of ram usable by virtual machine
    @return               returns a pointer to the VirtualMachine struct or NULL if an error was encountered
*/
VirtualMachinePtr virtualMachineAllocInit(unsigned int* programMem, unsigned int* ram)
{
  int i;
  VirtualMachinePtr vm = malloc(sizeof(struct VirtualMachine));
  if (!vm) return NULL;

  for (i=0;i<5;i++)vm->registers[i] = 0;
  for (i=0;i<6;i++)vm->stateRegister[i] = 0;
  vm->instructionPointer = 0;
  vm->programMem = programMem;
  vm->ram = ram;
  return  vm;
}

/*  Destroys the virtual machine

    @param  vm            pointer to the virtual machine
*/
void virtualMachineDestruct(VirtualMachinePtr vm) {
  if (vm) free(vm);
}


/*  Executes the instruction pointed by instructionPointer and advances the instruction pointer to point to next execution

    @param  vm            pointer to the virtual machine
    @return               returns 0 by default or -1 if sto or invalid op-code was encountered
*/
int virtualMachineStep(VirtualMachinePtr vm)
{
  unsigned char temp;
  unsigned int arg1, arg2, arg3;
  char ch;

  switch (vm->programMem[vm->instructionPointer])
  {
    case 0: 	//sto
        return -1;
    case 1:		//rtm
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        PRINT printf("rtm %u %u\n",vm->programMem[arg1], vm->programMem[arg2]);
        vm->ram[vm->registers[vm->programMem[arg1]]] = vm->registers[vm->programMem[arg2]]; 
        vm->instructionPointer+=3;
        return 0;
    case 2:		//mtr
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        PRINT printf("mtr %u %u\n",vm->programMem[arg1], vm->programMem[arg2]);
        vm->registers[vm->programMem[arg1]] = vm->ram[vm->registers[vm->programMem[arg2]]]; 
        vm->instructionPointer+=3;
        return 0;
    case 3:		//rtr
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        PRINT printf("rtr %u %u\n",vm->programMem[arg1], vm->programMem[arg2]);
        vm->registers[vm->programMem[arg1]] = vm->registers[vm->programMem[arg2]];
        vm->instructionPointer+=3;
        return 0;
    case 4:		//inc
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("inc %u\n",vm->programMem[arg1]);
        vm->registers[vm->programMem[arg1]]++;
        vm->instructionPointer+=2;
        return 0;
    case 5:		//dec
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("dec %u\n",vm->programMem[arg1]);
        vm->registers[vm->programMem[arg1]]--;
        vm->instructionPointer+=2;
        return 0;
    case 6:		//loa
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        PRINT printf("loa %u %u\n",vm->programMem[arg1], vm->programMem[arg2]);
        vm->registers[vm->programMem[arg1]] = vm->programMem[arg2]; 
        vm->instructionPointer+=3;
        return 0;
    case 7:		//add
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("add %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        vm->registers[vm->programMem[arg1]] = vm->registers[vm->programMem[arg2]] + vm->registers[vm->programMem[arg3]];
        vm->instructionPointer+=4;
        return 0;
    case 8:		//sub
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("sub %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        if (vm->registers[vm->programMem[arg2]] < vm->registers[vm->programMem[arg3]])
        	vm->registers[vm->programMem[arg1]] = -(int)((vm->registers[vm->programMem[arg3]] - vm->registers[vm->programMem[arg2]]));
        else vm->registers[vm->programMem[arg1]] = (vm->registers[vm->programMem[arg2]] - vm->registers[vm->programMem[arg3]]);
        vm->instructionPointer+=4;
        return 0;
    case 9:		//mul
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("mul %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        vm->registers[vm->programMem[arg1]] = vm->registers[vm->programMem[arg2]] * vm->registers[vm->programMem[arg3]];
        vm->instructionPointer+=4;
        return 0;
    case 10:		//equ
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("equ %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        vm->registers[vm->programMem[arg1]] = (vm->registers[vm->programMem[arg2]] == vm->registers[vm->programMem[arg3]]);
        vm->instructionPointer+=4;
        return 0;
    case 11:		//neq
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("neq %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        vm->registers[vm->programMem[arg1]] = (vm->registers[vm->programMem[arg2]] != vm->registers[vm->programMem[arg3]]);
        vm->instructionPointer+=4;
        return 0;
    case 12:		//qrt
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        arg3 =  vm->instructionPointer + 3;
        PRINT printf("qrt %u %u %u\n",vm->programMem[arg1], vm->programMem[arg2],vm->programMem[arg3]);
        vm->registers[vm->programMem[arg1]] = (vm->registers[vm->programMem[arg2]] > vm->registers[vm->programMem[arg3]]);
        vm->instructionPointer+=4;
        return 0;
    case 13:		//jmp
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("jmp %u\n",vm->programMem[arg1]);
        vm->instructionPointer = vm->registers[vm->programMem[arg1]];
        return 0;
    case 14:		//cjp
        arg1 =  vm->instructionPointer + 1;
        arg2 =  vm->instructionPointer + 2;
        PRINT printf("cjp %u %u\n",vm->programMem[arg1], vm->programMem[arg2]);
        if (vm->registers[vm->programMem[arg1]] != 0)vm->instructionPointer = vm->registers[vm->programMem[arg2]];
        else vm->instructionPointer += 3;
        return 0;
    case 15:		//jsb
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("jsb %u\n",vm->programMem[arg1]);
        vm->stateRegister[0] = vm->registers[0];
        vm->stateRegister[1] = vm->registers[1];
        vm->stateRegister[2] = vm->registers[2];
        vm->stateRegister[3] = vm->registers[3];
        vm->stateRegister[4] = vm->registers[4];
        vm->stateRegister[5] = vm->instructionPointer+2;
        vm->instructionPointer = vm->registers[vm->programMem[vm->instructionPointer + 1]];
        return 0;
    case 16:		//ret
        PRINT printf("ret\n");
        vm->registers[0] = vm->stateRegister[0];
        vm->registers[1] = vm->stateRegister[1];
        vm->registers[2] = vm->stateRegister[2];
        vm->registers[3] = vm->stateRegister[3];
        vm->registers[4] = vm->stateRegister[4];
        vm->instructionPointer = vm->stateRegister[5];
        return 0;
    case 17:		//pri
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("pri %u\n",vm->programMem[arg1]);
        printf("%d",(int)vm->registers[vm->programMem[arg1]]);
        vm->instructionPointer+=2;
        return 0;
    case 18:		//prc
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("prc %u\n",vm->programMem[arg1]);
        printf("%c",(char)vm->registers[vm->programMem[arg1]]);
        vm->instructionPointer+=2;
        return 0;
    case 19:		//sci
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("sci %u\n",vm->programMem[arg1]);
        printf("\nPlease enter a non-negative integer: ");
        fscanf(stdin,"%u",&(vm->registers[vm->programMem[arg1]]));
        while ((ch = getchar()) != '\n' && ch != EOF);
        vm->instructionPointer+=2;
        return 0;
    case 20:		//scc
        arg1 =  vm->instructionPointer + 1;
        PRINT printf("scc %u\n",vm->programMem[arg1]);
        printf("\nPlease enter a character: ");
        fscanf(stdin,"%c",&temp);
        while ((ch = getchar()) != '\n' && ch != EOF);
        vm->registers[vm->programMem[arg1]] = (unsigned char)temp;
        vm->instructionPointer+=2;
        return 0;
    default: return -1;
    }	
}


/*  Prints the values of the registers, instructionPointer and in given ram address

    @param  vm            pointer to the virtual machine
    @param  address       queried ram memory address
    @return               returns the value in given ram memory address
*/
int virtualMachinePeek(VirtualMachinePtr vm, size_t address)
{
  printf("IP: %u R0: %u R1: %u R2: %u R3: %u R4: %u Address $%zu: %u\n------\n", 
    vm->instructionPointer,vm->registers[0],vm->registers[1],vm->registers[2],
    vm->registers[3],vm->registers[4],address,vm->ram[address]);
  return vm->ram[address];
}

