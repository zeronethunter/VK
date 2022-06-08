#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#define HORNER_CONST 13
#define DOUBLE_HASH_CONST 7
#define DEFAULT_TABLE_SIZE 8
#define LOAD_FACTOR 0.75
#define DEL_FACTOR 0.5

// Horner Rule hash mechanism
struct HornerRuleHash {
  size_t operator()(const std::string &bytes, size_t size,
                    bool is_double_hashing = false) const {
    size_t hash = 0;

    std::string::const_iterator it = bytes.cbegin();

    size_t constant = is_double_hashing ? DOUBLE_HASH_CONST : HORNER_CONST;

    // Exact algorithm
    for (; it < bytes.cend(); ++it) {
      hash = (hash * constant + *it) % size;
    }

    return is_double_hashing ? (2 * hash + 1) % size : hash % size;
  }
};

template <typename Key, typename HashMechanism = HornerRuleHash>
class HashTable {
 public:
  explicit HashTable(size_t init_size = DEFAULT_TABLE_SIZE,
                     float load_factor = LOAD_FACTOR,
                     float del_factor = DEL_FACTOR) noexcept
      : table_(std::vector<Element_>(init_size)),
        load_factor_(load_factor),
        del_factor_(del_factor),
        key_count_(0),
        del_count_(0) {
  }

  ~HashTable() noexcept = default;

  bool Has(const Key &key,
           const HashMechanism &hash = HashMechanism()) const noexcept;
  bool Add(const Key &key,
           const HashMechanism &hash = HashMechanism()) noexcept;
  bool Delete(const Key &key,
              const HashMechanism &hash = HashMechanism()) noexcept;

 private:
  class Element_ {
   public:
    typedef Key value;
    typedef size_t index;

    enum class Status { KEY, EMPTY, DELETED };

    Element_() noexcept = default;

    Element_(Status status, index hash, value data) noexcept
        : _hash(hash), _data(std::move(data)), _status(status) {
    }

    ~Element_() noexcept = default;

    void set_hash(const index new_hash) noexcept {
      _hash = new_hash;
    }

    void set_data(const value &new_data) noexcept {
      _data = new_data;
    }

    void set_status(const Status &new_status) noexcept {
      _status = new_status;
    }

    [[nodiscard]] index get_hash() const noexcept {
      return _hash;
    }

    [[nodiscard]] value get_data() const noexcept {
      return _data;
    }

    [[nodiscard]] Status get_status() const noexcept {
      return _status;
    }

   private:
    Status _status = Status::EMPTY;
    index _hash = 0;
    value _data;
  };

  void table_expansion(size_t size) noexcept;
  void table_expansion() noexcept;
  bool element_inserter(std::vector<Element_> &table, const Element_ &element,
                        const HashMechanism &hash = HashMechanism()) noexcept;

  std::vector<Element_> table_;

  size_t key_count_ = 0;
  size_t del_count_ = 0;
  float load_factor_ = LOAD_FACTOR;
  float del_factor_ = DEL_FACTOR;
};

template <typename Key, typename HashMechanism>
bool HashTable<Key, HashMechanism>::Has(
    const Key &key, const HashMechanism &hash) const noexcept {
  // Getting hash of key to find
  size_t key_hash = hash(key, table_.size());
  size_t i = key_hash;
  size_t step = hash(key, table_.size(), true);

  for (size_t j = 0; j < table_.size(); ++j) {
    auto status = table_[i].get_status();

    if (status == Element_::Status::EMPTY) {
      return false;
    } else if (status == Element_::Status::KEY) {
      if (key == table_[i].get_data()) {
        return true;
      }
    } else if (status != Element_::Status::DELETED) {
      assert(false);
    }

    // adding step of double hashing
    i = (i + step) % table_.size();
  }

  return false;
}

template <typename Key, typename HashMechanism>
bool HashTable<Key, HashMechanism>::Add(const Key &key,
                                        const HashMechanism &hash) noexcept {
  table_expansion();

  Element_ new_elem(Element_::Status::KEY, hash(key, table_.size()), key);

  if (element_inserter(table_, new_elem)) {
    ++key_count_;
    return true;
  }
  return false;
}

template <typename Key, typename HashMechanism>
bool HashTable<Key, HashMechanism>::Delete(const Key &key,
                                           const HashMechanism &hash) noexcept {
  // Getting hash of key to delete
  size_t i = hash(key, table_.size());
  size_t step = hash(key, table_.size(), true);

  for (size_t j = 0; j < table_.size(); ++j) {
    auto status = table_[i].get_status();

    if (status == Element_::Status::EMPTY) {
      return false;
    } else if (status == Element_::Status::KEY) {
      if (key == table_[i].get_data()) {
        table_[i].set_status(Element_::Status::DELETED);
        --key_count_;
        ++del_count_;
        return true;
      }
    } else if (status != Element_::Status::DELETED) {
      assert(false);
    }
    // adding step of double hashing
    i = (i + step) % table_.size();
  }

  return false;
}

template <typename Key, typename HashMechanism>
void HashTable<Key, HashMechanism>::table_expansion(size_t size) noexcept {
  std::vector<Element_> new_table(size, Element_());

  for (const Element_ &element : table_) {
    assert((element_inserter(new_table, element)));
  }

  table_ = std::move(new_table);
  del_count_ = 0;
}

template <typename Key, typename HashMechanism>
bool HashTable<Key, HashMechanism>::element_inserter(
    std::vector<Element_> &table, const HashTable::Element_ &element,
    const HashMechanism &hash) noexcept {
  size_t i = hash(element.get_data(), table.size());
  size_t step = hash(element.get_data(), table.size(), true);

  bool is_deleted_found = false;
  size_t deleted_index = 0;

  for (size_t j = 0; j < table.size(); ++j) {
    auto status = table[i].get_status();

    if (status == Element_::Status::EMPTY) {
      if (is_deleted_found) {
        table[deleted_index] = element;
      } else {
        table[i] = element;
      }
      return true;
    } else if (status == Element_::Status::KEY) {
      if (table[i].get_data() == element.get_data()) {
        return false;
      }
    } else if (status == Element_::Status::DELETED) {
      if (!is_deleted_found) {
        is_deleted_found = true;
        deleted_index = i;
      }
    } else {
      assert(false);
    }
    // adding step of double hashing
    i = (i + step) % table.size();
  }

  if (is_deleted_found) {
    table[deleted_index] = element;
    return true;
  }

  return false;
}

template <typename Key, typename HashMechanism>
void HashTable<Key, HashMechanism>::table_expansion() noexcept {
  if (static_cast<float>(key_count_) / table_.size() > load_factor_) {
    table_expansion(table_.size() * 2);
  } else if (static_cast<float>(del_count_) / table_.size() > del_factor_) {
    table_expansion(table_.size());
  }
}

void solve() {
  HornerRuleHash hash;
  HashTable<std::string> hash_table;

  char operation;
  std::string word;

  while (std::cin >> operation >> word) {
    if (operation == '+') {
      std::cout << (hash_table.Add(word) ? "OK" : "FAIL") << std::endl;
    } else if (operation == '?') {
      std::cout << (hash_table.Has(word) ? "OK" : "FAIL") << std::endl;
    } else if (operation == '-') {
      std::cout << (hash_table.Delete(word) ? "OK" : "FAIL") << std::endl;
    } else {
      assert(false);
    }
  }
}

int main() {
  solve();
  return 0;
}
