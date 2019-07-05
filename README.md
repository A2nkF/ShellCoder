# ShellCoder

## Build
Clone the code and run `gcc shellCoder.c -o shellCoder -masm=intel`.

## Usage

```
./shellCoder filename baseAddress entryPointOffset
```

## Example

```
> # ./shellCoder shellcode.bin 0x123400000000 0x0                                  
Loading shellcode.bin to memory...
Shellcode loaded at 0x123400000000
Jumping into shellcode at 0x123400000000...
# ls
```
