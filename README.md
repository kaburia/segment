# Segment

## Creating a library in C and calling it in a different file
### Creating the library file
```
// library.c

#include "library.h"

int add(int a, int b) {
    return a + b;
}

```
### Create a header file library.h
```
// library.h

#ifndef LIBRARY_H
#define LIBRARY_H

int add(int a, int b);

#endif
```

### Compile the source file
```
gcc -c library.c
```
### Create a library file by archiving object file
```
ar rcs liblibrary.a library.o
```
### Create executable C file
```
gcc -o main main.c -L. -llibrary
avr-gcc -mmcu=atmega32 -Wall -Os -o main.elf main.c -std=c99 # compile to elf
avr-objcopy -j .text -j .data -O ihex main.elf main.hex # compile to hex
```
### Run the executable
```
./main
```

