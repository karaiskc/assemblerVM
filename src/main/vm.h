#ifndef C_VM_H
#define C_VM_H

#include <stddef.h>

/*  This is a pointer to the struct for the virtual machine  */
typedef struct VirtualMachine* VirtualMachinePtr;

/*  Initializes the virtual machine
    Pointers to the data and program memory are given as parameters
    all the registers and instructionPointer should be initialized to zero

    @param  programMem    pointer to the beginning of the program memory allocated to the virtual machine
    @param  ram           pointer to the beginning of ram usable by virtual machine
    @return               returns a pointer to the VirtualMachine struct or NULL if an error was encountered
*/
VirtualMachinePtr virtualMachineAllocInit(unsigned int* programMem, unsigned int* ram);

/*  Destroys the virtual machine

    @param  vm            pointer to the virtual machine
*/
void virtualMachineDestruct(VirtualMachinePtr vm);

/*  Executes the instruction pointed by instructionPointer and advances the instruction pointer to point to next execution

    @param  vm            pointer to the virtual machine
    @return               returns 0 by default or -1 if sto or invalid op-code was encountered
*/
int virtualMachineStep(VirtualMachinePtr vm);


/*  Prints the values of the registers, instructionPointer and given ram address

    @param  vm            pointer to the virtual machine
    @param  address       queried ram memory address
    @return               returns the value in given ram memory address
*/
int virtualMachinePeek(VirtualMachinePtr vm, size_t address);

#endif
