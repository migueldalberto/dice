# dice

C tool for getting dice rolls.

About its RNG, on Windows, it uses `srand` and `rand` functions from `stdlib.h`.
On Linux, it uses the `getrandom` syscall.

## usage

examples:

```
./dice d20
1d20 -> 4 = 4 

./dice d20+3
1d20+3 -> 7 (7+3) = 10

./dice 1d6 4d4
1d6 -> 1 = 1 
4d4 -> 2 1 1 2 = 6 

./dice 2d4+1
2d4+1 -> 4 4 (8+1) = 9 

./dice d9
1d9 -> 8 = 8 
```

## build

Build this program running `make`.

Install system wide running as root `make install`.

Uninstall it removing the binary from `/bin/dice` or using `make uninstall`.

That should work 😉 
