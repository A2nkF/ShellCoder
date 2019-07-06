//
//  shellCoder.c
//  shellCoder
//
//  Created by A2nkF on 7/5/19.
//  Copyright © 2019 A2nkF. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <signal.h>
#include <string.h>
#include <stdint.h>


void *loadFile(char filename[], void *baseAddr) {
    FILE *fd = NULL;
    void *shellcode = NULL;
    unsigned long len = 0;
    
    fd = fopen(filename, "rb");
    if(fd == NULL) {
        printf("Failed to open %s\n", filename);
        exit(-1);
    }
    fseek(fd, 0, SEEK_END);
    len = ftell(fd);
    if(len == 0){
        puts("Failed to get file length");
        exit(-1);
    }
    fseek(fd, 0, SEEK_SET);
    
    shellcode = mmap((void *)baseAddr, len, 0x7, MAP_PRIVATE, fileno(fd), 0);
    if(shellcode != baseAddr) {
        printf("Failed to load file at %p\n", shellcode);
        exit(-1);
    }
    printf("Shellcode loaded at %p\n", shellcode);
    
    return shellcode;
}

int main(int argc, char *argv[]) {
    void *baseAddress = NULL;
    unsigned long entryPoint = 0;

    if(argc < 3) {
        printf("usage: %s filename baseAddress entryPointOffset [trap]\n", argv[0]);
        exit(1);
    }
    
    baseAddress = (void *)strtol(argv[2], &argv[2], 16);
    entryPoint = strtol(argv[3], &argv[3], 16);
    entryPoint += (unsigned long)baseAddress;
    
    printf("Loading %s to memory...\n", argv[1]);
    loadFile(argv[1], baseAddress);
    printf("Jumping into shellcode at %p...\n", (void *)entryPoint);
  

    // compile with -masm=intel
    if(argv[4] != NULL && atoi(argv[4])) {
        __asm__ __volatile__("int 3; call %0" ::"r"(entryPoint));
    } else {
         __asm__ __volatile__("call %0" ::"r"(entryPoint));
    }
        
    puts("\n\n----- Shellcode execution completed -----");
    
    return 0;
}
