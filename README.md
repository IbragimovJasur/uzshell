# UZSHELL
This is a draft version of uzbek shell. It hasn't been finished yet and I'm still working on it ...

## Available Commands

```kir``` (in uzbek 'kirmoq') is a equivalent of ```cd``` command. Usage example: ```kir /usr/home/test/```


```aks``` (in uzbek 'aks-sado') is a equivalent of ```echo``` command. Usage example: ```aks 'Hello World'```


```chiq``` (in uzbek 'chiqmoq') is a equivalent of ```exit``` command. Usage example: ```chiq```

In *uzshell*, on top of the two above mentioned commands, you can run ```ls```, ```cp```, ```mv``` commands which are provided by Unix shell.

## Compile & Run
1. Download and Install [GCC](https://gcc.gnu.org/install/) or [Clang](https://clang.llvm.org/get_started.html) compiler

2. Compile the source code
Using GCC:
```
gcc main.c builtins.c -o main.o
```

Using Clang:
```
clang main.c builtins.c -o main.o
```

3. Execute the object file
```
./main.o
```
