#include <algorithm>
#include <iostream>
#include <queue>

template <typename T, typename Compare = std::less<T>>
class BinaryTree {
 public:
  explicit BinaryTree(const Compare& cmp = Compare()) noexcept
      : cmp_(cmp), root_(nullptr) {
  }

  explicit BinaryTree(const T& value, const Compare& cmp = Compare()) noexcept
      : cmp_(cmp), root_(new Node) {
    root_->_value = value;
  }

  ~BinaryTree() noexcept;

  void Add(const T& value) noexcept;

  friend std::ostream& operator<<(std::ostream& out_stream,
                                  const BinaryTree<T, Compare>& tree) noexcept {
    if (!tree.root_) {
      return out_stream;
    }

    std::queue<Node*> queue;
    queue.push(tree.root_);

    do {
      Node* tmp = queue.front();
      queue.pop();

      out_stream << tmp->_value << " ";

      if (tmp->_left) {
        queue.push(tmp->_left);
      }

      if (tmp->_right) {
        queue.push(tmp->_right);
      }
    } while (!queue.empty());
    return out_stream;
  }

  [[maybe_unused]] [[nodiscard]] bool HasSameElements() const noexcept;

  [[maybe_unused]] [[nodiscard]] size_t ShortestDist() noexcept {
    std::vector<size_t> result;
    shortestDist(root_, result, 1);
    return *std::min_element(result.begin(), result.end());
  }

 private:
  struct Node {
    explicit Node(Node* left = nullptr, Node* right = nullptr,
                  const T& value = T())
        : _left(std::move(left)), _right(std::move(right)), _value(value) {
    }
    Node* _left;
    Node* _right;
    T _value;
  };

  void shortestDist(Node* node, std::vector<size_t>& counter,
                    size_t count) noexcept;

  Node* root_;
  Compare cmp_;
};

template <typename T, typename Compare>
void BinaryTree<T, Compare>::Add(const T& value) noexcept {
  Node* new_node = new Node;
  new_node->_value = value;
  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }
  Node* cur = root_;
  while (cur) {
    if (cmp_(new_node->_value, cur->_value)) {
      if (!cur->_left) {
        cur->_left = new_node;
        return;
      }
      cur = cur->_left;
    } else {
      if (!cur->_right) {
        cur->_right = new_node;
        return;
      }
      cur = cur->_right;
    }
  }
}

template <typename T, typename Compare>
[[maybe_unused]] bool BinaryTree<T, Compare>::HasSameElements() const noexcept {
  Node* cur;
  Node* prev = root_;

  std::queue<Node*> queue;
  queue.push(root_);

  do {
    cur = queue.front();
    queue.pop();

    if (cur->_value != prev->_value) {
      return false;
    }

    if (cur->_left) {
      queue.push(cur->_left);
    }

    if (cur->_right) {
      queue.push(cur->_right);
    }

    prev = cur;
  } while (!queue.empty());
  return true;
}

template <typename T, typename Compare>
void BinaryTree<T, Compare>::shortestDist(Node* node,
                                          std::vector<size_t>& counter,
                                          size_t count) noexcept {
  if (node == nullptr) {
    return;
  }
  if (!node->_left && !node->_right) {
    counter.push_back(count);
  }

  shortest_dist(node->_left, counter, count + 1);
  shortest_dist(node->_right, counter, count + 1);
}

template <typename T, typename Compare>
BinaryTree<T, Compare>::~BinaryTree() noexcept {
  if (!root_) {
    return;
  }

  std::queue<Node*> queue;
  queue.push(root_);

  do {
    Node* tmp = queue.front();
    queue.pop();

    if (tmp->_left) {
      queue.push(tmp->_left);
    }

    if (tmp->_right) {
      queue.push(tmp->_right);
    }

    delete tmp;
  } while (!queue.empty());
}

void input_tree(BinaryTree<int>& tree, size_t n) {
  for (size_t i = 0; i < n; ++i) {
    int value;
    std::cin >> value;
    tree.Add(value);
  }
}

void solve(size_t n) {
  BinaryTree<int> b_tree;

  input_tree(b_tree, n);

  std::cout << b_tree;
}

int main() {
  size_t n;

  std::cin >> n;

  solve(n);

  return 0;
}
