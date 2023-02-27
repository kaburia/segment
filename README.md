# Segment

## Creating a library in C and calling it in a different file
### Creating the library file
```
touch library.c
touch library.h
```
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
```
### Run the executable
```
./main
```

