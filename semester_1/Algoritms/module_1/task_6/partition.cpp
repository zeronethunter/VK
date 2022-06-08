#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <cstring>

template<typename T>
class LessCmp {
public:
    bool operator()(T const &l, T const &r) {
        return l < r;
    }
};

template<typename T, class Compare>
size_t Partition(T *array, size_t l, size_t r, Compare cmp) {
    if (r == l) {
        return l;
    }
    size_t pivot = std::rand() % (r - l) + l;
    if (pivot != r - 1) {
        std::swap(array[pivot], array[r - 1]);
    }
    pivot = r - 1;
    size_t i = l;
    size_t j = l;
    while (j != r - 1) {
        if (cmp(array[pivot], array[j])) {
            ++j;
        } else {
            std::swap(array[i], array[j]);
            ++i;
            ++j;
        }
    }
    std::swap(array[i], array[j]);
    return i;
}

template<typename T, class Compare>
void FindStatistic(T *array, size_t l, size_t r, size_t k, Compare cmp) {
    size_t pivot_pos;
    do {
        pivot_pos = Partition(array, l, r, cmp);
        if (k < pivot_pos) {
            r = pivot_pos;
        } else if (k > pivot_pos) {
            l = pivot_pos + 1;
        }
    } while (pivot_pos != k);
    std::cout << array[k] << std::endl;
}

int *input(size_t n) {
    assert((n > 0));
    auto new_arr = new int[n];
    assert(new_arr);
    for (size_t i = 0; i < n; ++i) {
        int value;
        assert((value >= 0));
        std::cin >> value;
        new_arr[i] = value;
    }
    return new_arr;
}

void solve(int *array, size_t n) {
    int *array10 = array;
    int *array50 = new int[n];
    int *array90 = new int[n];
    memcpy(array50, array10, n * sizeof(int));
    memcpy(array90, array10, n * sizeof(int));

    FindStatistic(array10, 0, n, std::ceil(n / 10), LessCmp<int>());
    FindStatistic(array50, 0, n, std::ceil(n / 2), LessCmp<int>());
    FindStatistic(array90, 0, n, std::ceil(9 * n / 10), LessCmp<int>());


    delete[] array10;
    delete[] array50;
    delete[] array90;
}


int main() {
    size_t n;
    std::cin >> n;
    std::srand(std::time(nullptr));

    int *array = input(n);

    solve(array, n);

    return 0;
}
