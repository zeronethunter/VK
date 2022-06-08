#include <cassert>
#include <iostream>

template <typename T>
class Node_ {
 public:
  explicit Node_<T>(const T &data = T(), size_t height = 1,
                    size_t count_children = 1, Node_<T> *left = nullptr,
                    Node_<T> *right = nullptr)
      : _data(data),
        _height(height),
        _count_children(count_children),
        _left(left),
        _right(right) {
  }

  T GetData() {
    return _data;
  }

  size_t &GetHeight() {
    return _height;
  }

  Node_ *&GetLeft() {
    return _left;
  }

  Node_ *&GetRight() {
    return _right;
  }

  size_t &GetCountChildren() {
    return _count_children;
  }

  void SetCountChildren(size_t count_children) {
    _count_children = count_children;
  }

 private:
  T _data;
  size_t _count_children;
  size_t _height;
  Node_<T> *_left;
  Node_<T> *_right;
};

template <typename T, typename Cmp = std::less<T>>
class AVLTree {
 public:
  AVLTree() : root_(nullptr), cmp_(Cmp()) {
  }

  [[maybe_unused]] explicit AVLTree(const T &data, Cmp cmp = Cmp())
      : root_(new Node_<T>(data)), cmp_(cmp) {
  }

  ~AVLTree();

  size_t Insert(const T &data) {
    size_t statistic = 0;
    root_ = insert(root_, data, statistic);
    return statistic;
  }

  void Remove(size_t index) {
    root_ = remove(root_, index);
  }

 private:
  Node_<T> *root_;
  Cmp cmp_;

  size_t height(Node_<T> *node);
  size_t countOfChildren(Node_<T> *node);
  int bFactor(Node_<T> *node);
  void fixHeight(Node_<T> *node);
  void fixCountOfChildren(Node_<T> *node);
  Node_<T> *rotateRight(Node_<T> *p);
  Node_<T> *rotateLeft(Node_<T> *q);
  Node_<T> *balance(Node_<T> *node);
  Node_<T> *findAndRemoveMax(Node_<T> *node, Node_<T> *&max);
  Node_<T> *insert(Node_<T> *node, T data, size_t &statistic);
  Node_<T> *remove(Node_<T> *node, size_t index);
  void DeleteTree(Node_<T> *node);
};

template <typename T, typename Cmp>
size_t AVLTree<T, Cmp>::height(Node_<T> *node) {
  return node ? node->GetHeight() : 0;
}

template <typename T, typename Cmp>
size_t AVLTree<T, Cmp>::countOfChildren(Node_<T> *node) {
  return node ? node->GetCountChildren() : 0;
}

template <typename T, typename Cmp>
int AVLTree<T, Cmp>::bFactor(Node_<T> *node) {
  return height(node->GetRight()) - height(node->GetLeft());
}

template <typename T, typename Cmp>
void AVLTree<T, Cmp>::fixHeight(Node_<T> *node) {
  size_t left_height = height(node->GetLeft());
  size_t right_height = height(node->GetRight());

  node->GetHeight() = std::max(left_height, right_height) + 1;
}

template <typename T, typename Cmp>
void AVLTree<T, Cmp>::fixCountOfChildren(Node_<T> *node) {
  size_t left_count_of_children = countOfChildren(node->GetLeft());
  size_t right_count_of_children = countOfChildren(node->GetRight());

  node->SetCountChildren(left_count_of_children + right_count_of_children + 1);
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::rotateRight(Node_<T> *p) {
  Node_<T> *q = p->GetLeft();
  p->GetLeft() = q->GetRight();
  q->GetRight() = p;

  // make correct count of children
  fixCountOfChildren(p);
  fixCountOfChildren(q);

  fixHeight(p);
  fixHeight(q);

  return q;
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::rotateLeft(Node_<T> *q) {
  Node_<T> *p = q->GetRight();
  q->GetRight() = p->GetLeft();
  p->GetLeft() = q;

  // make correct count of children
  fixCountOfChildren(q);
  fixCountOfChildren(p);

  fixHeight(q);
  fixHeight(p);

  return p;
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::balance(Node_<T> *node) {
  fixHeight(node);
  fixCountOfChildren(node);

  if (bFactor(node) == 2) {
    if (bFactor(node->GetRight()) < 0)
      node->GetRight() = rotateRight(node->GetRight());
    return rotateLeft(node);
  }
  if (bFactor(node) == -2) {
    if (bFactor(node->GetLeft()) > 0)
      node->GetLeft() = rotateLeft(node->GetLeft());
    return rotateRight(node);
  }

  return node;
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::insert(Node_<T> *node, T data, size_t &statistic) {
  if (!node) return new Node_<T>(data);

  ++node->GetCountChildren();

  if (data == node->GetData()) {
    assert(false);
  } else if (cmp_(data, node->GetData())) {
    statistic += countOfChildren(node->GetRight()) + 1;
    node->GetLeft() = insert(node->GetLeft(), data, statistic);
  } else {
    node->GetRight() = insert(node->GetRight(), data, statistic);
  }

  return balance(node);
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::findAndRemoveMax(Node_<T> *node, Node_<T> *&max) {
  if (!node->GetRight()) {
    max = node;
    return node->GetLeft();
  }

  node->GetRight() = findAndRemoveMax(node->GetRight(), max);
  --node->GetCountChildren();

  return balance(node);
}

template <typename T, typename Cmp>
Node_<T> *AVLTree<T, Cmp>::remove(Node_<T> *node, size_t index) {
  if (!node) {
    return nullptr;
  }

  if (index > node->GetCountChildren()) {
    return node;
  }

  size_t statistic = countOfChildren(node->GetRight());
  if (index == statistic) {
    Node_<T> *left = node->GetLeft();
    Node_<T> *right = node->GetRight();

    delete node;

    if (!left) {
      return right;
    }

    Node_<T> *max;
    Node_<T> *erased_left = findAndRemoveMax(left, max);

    max->GetLeft() = erased_left;
    max->GetRight() = right;

    fixCountOfChildren(max);

    return balance(max);
  } else if (cmp_(index, statistic)) {
    node->GetRight() = remove(node->GetRight(), index);
  } else {
    node->GetLeft() = remove(node->GetLeft(), index - statistic - 1);
  }

  return balance(node);
}

template <typename T, typename Cmp>
AVLTree<T, Cmp>::~AVLTree() {
  DeleteTree(root_);
}

template <typename T, typename Cmp>
void AVLTree<T, Cmp>::DeleteTree(Node_<T> *node) {
  if (node) {
    DeleteTree(node->GetLeft());
    DeleteTree(node->GetRight());
    delete node;
  }
}

int main() {
  size_t n;
  std::cin >> n;

  AVLTree<int> tree;
  for (size_t i = 0; i < n; ++i) {
    size_t op;
    int height;
    std::cin >> op >> height;
    if (op == 1) {
      std::cout << tree.Insert(height) << std::endl;
    } else if (op == 2) {
      tree.Remove(height);
    } else {
      assert(false);
    }
  }
  return 0;
}
