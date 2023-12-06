```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

// 有序序列中查找第一个 >= target 的元素的位置
int lower_bound(const std::vector<int> &v, const int target) {
    int left = 0, right = v.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (v[mid] >= target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

// 有序序列中查找第一个 > target 的元素的位置
int upper_bound(const std::vector<int> &v, const int target) {
    int left = 0, right = v.size() - 1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (v[mid] > target) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

void print(const std::vector<int> &v, int i) {
    for (const auto &ele : v) {
        std::cout << ele << ' ';
    }
    std::cout << std::endl;
    if (-1 != i) {
        for (int j = 0; j < i; ++j) {
            std::cout << "  ";
        }
        std::cout << "^" << std::endl;
    }
}

int main() {
    std::vector<int> v { 3, 4, 4, 5, 5, 6, 7, 7, 8 };
    print(v, -1);
    int target = 5;
    printf("find value: %d\n", target);

    // lower_bound
    std::cout << "lower_bound" << std::endl;
    int index = lower_bound(v, target);
    print(v, index);
    printf("index: %d\n", index);
    printf("value: %d\n", v[index]);

    auto it = std::lower_bound(v.begin(), v.end(), target);
    print(v, index);
    printf("index2: %d\n", it - v.begin());
    printf("value2: %d\n", *it);

    // upper_bound
    std::cout << "upper_bound" << std::endl;
    index = upper_bound(v, target);
    print(v, index);
    printf("index: %d\n", index);
    printf("value: %d\n", v[index]);
    
    it = std::upper_bound(v.begin(), v.end(), target);
    print(v, it - v.begin());
    printf("index2: %d\n", it - v.begin());
    printf("value2: %d\n", *it);
    return 0;
}
```

