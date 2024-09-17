### restrict

restrict 关键字用于声明指针的约束条件。它告诉编译器，一个指针是指向的内存区域在其生命周期内只能通过这个指针进行访问，而不会通过其他指针来访问。这样的约束允许编译器进行更多的优化，因为它可以更准确地推断指针的行为，从而提高代码的性能。

```cpp
#include <stdio.h>

void foo(int *restrict a, int *restrict b) {
    ++(*a);
    ++(*b);
}

int main(int argc, char *argv[]) {
    int a = 1, b = 1;

    foo(&a, &b);
    printf("a: %d, b: %d\n", a, b); // 2 2

    foo(&a, &a); // ub
    printf("a: %d, b: %d\n", a, b);
    return 0;
}
```

第二次 `foo` 调用中，两个 `restrict` 指针都指向了同一个内存，这是未定义行为。

```sh
警告：passing argument 1 to ‘restrict’-qualified parameter aliases with argument 2 [-Wrestrict]
   14 |     foo(&a, &a); // ub
      |         ^~  ~~
```

