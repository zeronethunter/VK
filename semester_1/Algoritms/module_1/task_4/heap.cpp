#include <cassert>
#include <cstring>
#include <iostream>

class Process {
 public:
  Process(size_t P, size_t t, size_t T) : P_(P), t_(t), T_(T) {
    assert((P > 0));
    assert((t >= 0));
    assert((T > 0));
  }
  Process() : P_(0), t_(0), T_(0) {
  }
  [[nodiscard]] size_t get_p() const {
    return P_;
  }
  [[nodiscard]] size_t get_t() const {
    return t_;
  }
  [[nodiscard]] size_t get_T() const {
    return T_;
  }
  void add() {
    t_ += P_;
  }
  bool operator!=(Process const& r) const {
    return (P_ != r.P_) && (t_ != r.t_) && (T_ != r.T_);
  }

 private:
  size_t P_;
  size_t t_;
  size_t T_;
};

class CmpProcess {
 public:
  bool operator()(Process const& l, Process const& r) {
    return (l.get_p() * (l.get_t() + 1)) < (r.get_p() * (r.get_t() + 1));
  }
};

template <typename T, class Compare>
class Heap {
 public:
  explicit Heap() : buffer_(new T[1]), length_(0), size_(1), cmp_(Compare()) {
  }

  Heap(size_t length)
      : length_(length), size_(length_ * 2), buffer_(size_), cmp_(Compare()) {
  }

  bool empty() {
    return length_ == 0;
  }
  bool full() {
    return length_ == size_;
  }

  void insert(T const& value) {
    if (full()) {
      expansion();
    }
    buffer_[++length_ - 1] = value;
    sift_up(length_ - 1);
  }
  [[nodiscard]] T peek_max() const {
    return buffer_[0];
  }
  T extract_max() {
    assert(!empty());
    T result = buffer_[0];
    buffer_[0] = buffer_[length_ - 1];
    buffer_[length_ - 1] = T();
    --length_;
    if (!empty()) {
      sift_down(0);
    }
    return result;
  }
  void expansion() {
    auto new_buffer = new T[size_ * 2];
    if (std::is_trivially_copyable_v<T>) {
      memcpy(new_buffer, buffer_, length_ * sizeof(T));
    } else {
      for (size_t i = 0; i < length_; ++i) {
        new_buffer[i] = buffer_[i];
      }
    }
    auto tmp = buffer_;
    buffer_ = new_buffer;
    delete[] tmp;

    size_ *= 2;
  }

 private:
  T* buffer_;
  size_t size_;
  size_t length_;
  Compare cmp_;

  size_t parent(size_t index) {
    return (index - 1) / 2;
  }

  size_t left(size_t index) {
    return (2 * index + 1);
  }

  size_t right(size_t index) {
    return (2 * index + 2);
  }

  void sift_down(size_t index) {
    size_t left_node = left(index);
    size_t right_node = right(index);

    size_t largest_node = index;

    if (left_node < length_ && cmp_(buffer_[left_node], buffer_[index]))
      largest_node = left_node;

    if (right_node < length_ &&
        cmp_(buffer_[right_node], buffer_[largest_node]))
      largest_node = right_node;

    if (largest_node != index) {
      std::swap(buffer_[index], buffer_[largest_node]);
      sift_down(largest_node);
    }
  }
  void sift_up(size_t index) {
    while (index > 0) {
      size_t parent_node = this->parent(index);
      if (cmp_(buffer_[parent_node], buffer_[index])) return;
      std::swap(buffer_[index], buffer_[parent_node]);
      index = parent_node;
    }
  }
};

void solve(size_t n);

int main() {
  size_t n;
  std::cin >> n;
  assert((n > 0));

  solve(n);

  return 0;
}

void solve(size_t n) {
  Heap<Process, CmpProcess> process_heap;
  size_t counter = 0;
  for (size_t i = 0; i < n; ++i) {
    size_t P, T;
    std::cin >> P >> T;
    process_heap.insert(Process(P, 0, T));
  }
  while (!process_heap.empty()) {
    Process min_process = process_heap.extract_max();
    if (min_process.get_t() < min_process.get_T()) {
      min_process.add();
      process_heap.insert(min_process);
      ++counter;
    }
  }
  std::cout << counter;
}
