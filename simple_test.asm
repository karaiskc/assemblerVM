//init the registers to 0
loa 0 10
loa 1 0
loa 2 0
loa 3 0
loa 4 0

//scan character and move to memory 10 times

scc 1
rtm 2 1
inc 2
equ 3 0 2
loa 4 37
cjp 3 4
loa 4 15
jmp 4

// print all saved characters

loa 2 0
mtr 1 2
prc 1
inc 2
equ 3 0 2
loa 4 62
cjp 3 4
loa 4 40
jmp 4
sto

