// This program tests the subroutine implementation

// Initialize the registers
$0
loa 0 0
loa 1 0
loa 2 0
loa 3 0
loa 4 0

// read char to registers 0-3
scc 0
scc 1
scc 2
scc 3

// print registers 0-3
prc 0
prc 1
prc 2
prc 3

// jump to the subroutine
loa 4 100
jsb 4

// print registers 0-3 again
prc 0
prc 1
prc 2
prc 3
sto

// this is the subroutine
// here we also read and print 4 characters
$100
scc 0
scc 1
scc 2
scc 3
prc 0
prc 1
prc 2
prc 3
ret
loa 2 200
jmp 200

// This should not be executed
$200
loa 0 100
loa 1 30
loa 2 0
prc 0
inc 2
equ 3 2 1
loa 4 250
cjp 3 4
loa 4 149
jmp 4
$250
sto
