# _practice_dsa


in C++, __int128 cannot cout, have to write your own printer.
```c++
void print(__int128 x){
    if(x == 0){
        putchar('0');
        return;
    }
    if(x > 9) print(x / 10);
    putchar(x % 10 + '0');
}
```
