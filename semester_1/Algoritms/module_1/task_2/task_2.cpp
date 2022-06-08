#include <iostream>
#include <cassert>

void input_data(size_t &n, size_t &m);

void input_array(int *arr, size_t size);

void solve(int *arr_a, int *arr_b, size_t size_a, size_t size_b);

size_t binary_search(const int *arr, size_t begin, size_t end, size_t size, int val);

size_t exponential_search(const int *arr, size_t size, int val);


int main() {
    size_t n, m;
    input_data(n, m);

    auto a = new int[n];
    auto b = new int[m];

    input_array(a, n);
    input_array(b, m);

    solve(a, b, n, m);


    delete [] a;
    delete [] b;

    return 0;
}

void input_data(size_t &n, size_t &m) {  // input n, k variables
    std::cin >> n;
    std::cin >> m;
    assert((n >= 0 && m >= 0));
}

void input_array(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        int tmp;
        std::cin >> tmp;
        arr[i] = tmp;
    }
}

void solve(int *arr_a, int *arr_b, size_t size_a, size_t size_b) {
    for (size_t i = 0; i < size_b - 1; ++i) {
        std::cout << exponential_search(arr_a, size_a, arr_b[i]) << ' ';
    }
    std::cout << exponential_search(arr_a, size_a, arr_b[size_b - 1]);
}

size_t binary_search(const int *arr, size_t begin, size_t end, size_t size, int val) {
    size_t first = begin;
    size_t last = end;
    while (first < last) {
        size_t mid = (first + last) / 2;
        if (arr[mid] < val) {
            first = mid + 1;
        } else {
            last = mid;
        }
    }
    return (arr[first] < val) ? size : first;
}

size_t exponential_search(const int *arr, size_t size, int val) {
    if (arr[0] >= val) {
        return 0;
    }
    size_t i = 1;
    while (i < size && arr[i] <= val)
        i = i * 2;

    return binary_search(arr, i / 2, std::min(size - 1, i), size, val);
}
