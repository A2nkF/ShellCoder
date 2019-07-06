# ShellCoder

## Build
Clone the code and run `gcc shellCoder.c -o shellCoder -masm=intel`.

## Usage

```
./shellCoder filename baseAddress entryPointOffset [trap]
```

`filename`: path to the shellcode file. (e.g `/payloads/shellcode.bin`)

`baseAddress`: address to load the shellcode to in hex (e.g. `0x1337133700`)

`entryPointOffset`: code offset in the shellcode (probably `0x0` if you're working with raw shellcode).

`trap`: boolean `[1|0]` to specify whether you want a breakpoint placed right before execution is being transfered to the shellcode. 

**NOTE**: you need to be in a debugger to catch the SIGTRAP if this option is set to `1`

The `binsh.bin` file contains sample shellcode that spawns a shell :D

## Examples

```
~$ ./shellCoder shellcode.bin 0x123400000000 0 0x0                                  
Loading shellcode.bin to memory...
Shellcode loaded at 0x123400000000
Jumping into shellcode at 0x123400000000...
# id
root
```

```
~$ gdb shellCoder     
pwndbg> r shellcode.bin 0x123400000000 0x0 1
Starting program: /shellCoder shellcode.bin 0x123400000000 0x0 1
Loading shellcode.bin to memory...
Shellcode loaded at 0x123400000000
Jumping into shellcode at 0x123400000000...

Program received signal SIGTRAP, Trace/breakpoint trap.
0x00000000004009f3 in main ()
pwndbg> x/i $rip
=> 0x4009f3 <main+279>:	call   rax
pwndbg> # You can debug you shellcode safely now 
