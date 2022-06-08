#define EXIT_CODE -1

#include <cassert>
#include <cstring>
#include <iostream>

void mod(int &lhs, int const &rhs) {
  int q;
  if (lhs < 0) {
    q = (lhs / rhs) * (-1) - 1;
  } else {
    q = lhs / rhs;
  }
  lhs -= rhs * q;
}

template <typename T>
class deque {
  int tail_index;
  int head_index;
  size_t size;
  size_t capacity;
  T *buffer;

  void expansion();

 public:
  deque()
      : buffer(new T[4]()),
        tail_index(-1),
        head_index(0),
        size(0),
        capacity(4) {
    assert(buffer);
  }

  ~deque() {
    delete[] buffer;
  }

  [[nodiscard]] bool is_full() const;

  [[nodiscard]] bool is_empty() const;

  void push_back(T new_value);

  T pop_back();

  void push_front(T value);

  T pop_front();

  //  void print();
};

template <typename T>
void deque<T>::expansion() {
  auto new_buffer = new T[capacity * 2]();
  assert(new_buffer);
  if (tail_index >= head_index) {
    if (std::is_trivially_copyable_v<T>) {
      memcpy(new_buffer, buffer, capacity * sizeof(T));
    } else {
      for (size_t i = 0; i < capacity; ++i) {
        new_buffer[i] = buffer[i];
      }
    }
  } else {
    if (std::is_trivially_copyable_v<T>) {
      memcpy(new_buffer + (capacity + head_index), buffer + head_index,
             (capacity - head_index) * sizeof(T));
      memcpy(new_buffer, buffer, (tail_index + 1) * sizeof(T));
    } else {
      for (size_t i = 0; i < capacity - head_index; ++i) {
        new_buffer[2 * capacity - i - 1] = buffer[capacity - i - 1];
      }
      for (size_t i = 0; i < tail_index; ++i) {
        new_buffer[i] = buffer[i];
      }
    }
    head_index += capacity;
  }
  auto tmp = buffer;
  buffer = new_buffer;
  delete[] tmp;

  capacity *= 2;
}

template <typename T>
bool deque<T>::is_full() const {
  return size == capacity;
}

template <typename T>
bool deque<T>::is_empty() const {
  return size == 0;
}

template <typename T>
void deque<T>::push_back(const T new_value) {
  if (is_full()) {
    expansion();
  }
  mod(++tail_index, capacity);
  buffer[tail_index] = new_value;
  if (!size) {
    head_index = tail_index;
  }
  ++size;
}

template <typename T>
T deque<T>::pop_back() {
  if (is_empty()) {
    return EXIT_CODE;
  }
  T tmp = buffer[tail_index];
  buffer[tail_index] = T();
  mod(--tail_index, capacity);
  --size;
  return tmp;
}

template <typename T>
void deque<T>::push_front(const T new_value) {
  if (is_full()) {
    expansion();
  }
  mod(--head_index, capacity);
  buffer[head_index] = new_value;

  if (!size) {
    tail_index = head_index;
  }

  ++size;
}

template <typename T>
T deque<T>::pop_front() {
  if (is_empty()) {
    return EXIT_CODE;
  }
  T tmp = buffer[head_index];
  buffer[head_index] = T();
  mod(++head_index, capacity);
  --size;
  return tmp;
}

template <typename T>
void deque<T>::print() {
for (size_t i = 0; i < capacity; ++i) {
 if ((tail_index == head_index) && (tail_index == i)) {
   std::cout << "th" << buffer[i] << ' ';
 } else if (i == tail_index) {
   std::cout << 't' << buffer[i] << ' ';
 } else if (i == head_index) {
   std::cout << 'h' << buffer[i] << ' ';
 } else {
   std::cout << buffer[i] << ' ';
 }
}
std::cout << std::endl;
}

void solve(size_t n);

int main() {
  size_t n;
  std::cin >> n;
  assert((n >= 0));

  solve(n);
  return 0;
}

void solve(size_t n) {
  deque<int> int_deque;
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    switch (a) {
      case 1:
        int_deque.push_front(b);
        break;
      case 2:
        if (int_deque.pop_front() != b) {
          std::cout << "NO";
          return;
        }
        break;
      case 3:
        int_deque.push_back(b);
        break;
      case 4:
        if (int_deque.pop_back() != b) {
          std::cout << "NO";
          return;
        }
        break;
      default:
        assert(false);
    }
  }
  std::cout << "YES";
}
