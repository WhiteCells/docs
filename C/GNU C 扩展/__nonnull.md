### __nonnull(())

```c
#include <stdio.h>

void __THROWNL __nonnull((1, 3)) foo(int *a, int *b, int *c, int *d) {
    printf("%d ", *a);
    if (b) {
        printf("%d ", *b);
    }
    printf("%d ", *c);
    if (d) {
        printf("%d ", *d);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int a = 1, b = 2, c = 3, d = 4;
    foo(&a, NULL, &c, NULL); // no warning

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}
```

`nonnull((1, 3))` 在向编译器作保证，保证参数 1 和参数 2 非空，如果在对 a 和 c 进行判空：

```c
#include <stdio.h>

void  __nonnull((1, 3)) foo(int *a, int *b, int *c, int *d) {
    if (a) {
        printf("%d ", *a);
    }
    if (b) {
        printf("%d ", *b);
    }
    if (c) {
        printf("%d ", *c);
    }
    if (d) {
        printf("%d ", *d);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int a = 1, b = 2, c = 3, d = 4;
    foo(&a, NULL, &c, NULL); // no warning

    printf("%d %d %d %d\n", a, b, c, d);
    return 0;
}
```

会给出警告：

```cpp
警告：‘nonnull’ argument ‘a’ compared to NULL [-Wnonnull-compare]
    4 |     if (a) {
      |        ^
警告：‘nonnull’ argument ‘c’ compared to NULL [-Wnonnull-compare]
   10 |     if (c) {
```

