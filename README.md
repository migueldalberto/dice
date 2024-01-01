# dice

C tool for getting dice rolls.
This uses /dev/random for its random numbers, 
which is a special file of Unix-like operating systems.

## usage

examples:

```
./dice d20
./dice d20+3
./dice 1d6 4d4
./dice 2d4+1
./dice d9
```

## build

`gcc -o dice dice.c`
