#include <iostream>
#include <cassert>

template<typename T1, typename T2>
class Pair {
public:
    T1 l_;
    T2 r_;

    Pair() = default;

    Pair(T1 const &l, T2 const &r) : r_(r), l_(l) {
    }
};

class Date {
public:
    Date() = default;

    Date(size_t day, size_t month, size_t year) : day_(day), month_(month), year_(year) {
        assert((day >= 0) && (day <= 31));
        assert((month > 0) && (month <= 12));
        assert((year >= 0));
    }

    bool operator<(Date const &rhs) const {
        if (year_ < rhs.year_) {
            return true;
        } else if (year_ > rhs.year_) {
            return false;
        }
        if (month_ < rhs.month_) {
            return true;
        } else if (month_ > rhs.month_) {
            return false;
        }
        return day_ < rhs.day_;
    }

    bool operator>(Date const &rhs) const {
        if (year_ > rhs.year_) {
            return true;
        } else if (year_ < rhs.year_) {
            return false;
        }
        if (month_ > rhs.month_) {
            return true;
        } else if (month_ < rhs.month_) {
            return false;
        }
        return day_ > rhs.day_;
    }

    bool operator<=(Date const &rhs) const {
        if (year_ < rhs.year_) {
            return true;
        } else if (year_ > rhs.year_) {
            return false;
        }
        if (month_ < rhs.month_) {
            return true;
        } else if (month_ > rhs.month_) {
            return false;
        }
        return day_ <= rhs.day_;
    }

    bool operator>=(Date const &rhs) const {
        if (year_ > rhs.year_) {
            return true;
        } else if (year_ < rhs.year_) {
            return false;
        }
        if (month_ > rhs.month_) {
            return true;
        } else if (month_ < rhs.month_) {
            return false;
        }
        return day_ >= rhs.day_;
    }

    bool operator!=(Date const &rhs) const {
        return (day_ != rhs.day_) || (month_ != rhs.month_) || (year_ != rhs.year_);
    }

    bool operator==(Date const &rhs) const {
        return (day_ == rhs.day_) && (month_ == rhs.month_) && (year_ == rhs.year_);
    }

    Date &operator=(Date const *rhs) {
        this->day_ = rhs->day_;
        this->month_ = rhs->month_;
        this->year_ = rhs->year_;

        return *this;
    }

    void operator--() {
        if (day_ == 1) {
            if (month_ == 1) {
                --year_;
                month_ = 12;

            } else {
                --month_;
            }
            day_ = get_max_days(month_, year_);
        } else {
            --day_;
        }
    }

    [[nodiscard]] size_t get_day() const {
        return day_;
    }

    [[nodiscard]] size_t get_month() const {
        return month_;
    }

    [[nodiscard]] size_t get_year() const {
        return year_;
    }

    ~Date() = default;

private:
    [[nodiscard]] static size_t get_max_days(size_t month, size_t year) {
        switch (month) {
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                return 31;
                break;
            case 2:
                if (year % 4 == 0) {
                    return 29;
                } else {
                    return 28;
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            default:
                return 0;
        }
    }

    size_t day_;
    size_t month_;
    size_t year_;
};

class Author {
public:
    Author() = default;

    Author(Date const &birth, Date const &death) : birth_(birth), death_(death) {
        Date date_of_18 = Date(birth.get_day(), birth.get_month(), birth.get_year() + 18);
        Date date_of_80 = Date(birth.get_day(), birth.get_month(), birth.get_year() + 80);
        if (death_ > date_of_18) {
            if (death_ != date_of_80) {
                death_ = std::min(date_of_80, death);
            }
            --death_;
        }
        birth_ = date_of_18;
    }

    bool is_empty() {
        return  death_ <= birth_;
    }

    [[nodiscard]] Date get_birthday() const {
        return birth_;
    }

    [[nodiscard]] Date get_deathday() const {
        return death_;
    }

    ~Author() = default;

private:
    Date birth_;
    Date death_;
};

template<typename T, class Compare>
void Merge(T const &first, size_t f_size, T const &second, size_t s_size, T const &result, Compare cmp) {
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    while ((i != f_size) && (j != s_size)) {
        if (cmp(first[i], second[j])) {
            result[k] = first[i];
            ++i;
        } else {
            result[k] = second[j];
            ++j;
        }
        ++k;
    }
    while (i != f_size) {
        result[k] = first[i];
        ++i;
        ++k;
    }
    while (j != s_size) {
        result[k] = second[j];
        ++j;
        ++k;
    }
}

template<typename T, class Compare>
void MergeSort(T *array, size_t n, Compare cmp) {
    if (n <= 1) {
        return;
    }

    size_t first = n / 2;
    size_t second = n - first;

    MergeSort(array, first, cmp); // left side
    MergeSort(array + first, second, cmp); // right side

    T *result = new T[n];

    Merge(array, first, array + first, second, result, cmp);

    for (size_t i = 0; i < n; ++i) {
        array[i] = result[i];
    }

    delete[] result;
}

bool DateCmp(Pair<Date, int> const &lhs, Pair<Date, int> const &rhs) {
    return (lhs.l_ < rhs.l_ || (lhs.l_ == rhs.l_ && lhs.r_ > rhs.r_));
}

int max_contemporary(Author *authors, size_t n) {
    auto *sorted_dates = new Pair<Date, int>[2 * n];
    size_t i = 0;
    while (i != 2 * n) {
        if (!authors[i / 2].is_empty()) {
            if (i % 2 == 0) {
                sorted_dates[i].l_ = authors[i / 2].get_birthday();
                sorted_dates[i].r_ = 1;
            } else {
                sorted_dates[i].l_ = authors[i / 2].get_deathday();
                sorted_dates[i].r_ = -1;
            }
        } else {
            sorted_dates[i].l_ = authors[i / 2].get_birthday();
            sorted_dates[i].r_ = 0;
        }
        ++i;
    }

    MergeSort(sorted_dates, 2 * n, DateCmp);

    int counter = 0;
    int result = counter;

    for (size_t j = 0; j < 2 * n; ++j) {
        counter += sorted_dates[j].r_;
        result = std::max(counter, result);
    }

    delete[] sorted_dates;

    return result;
}

void solve(size_t n) {
    auto *authors = new Author[n];
    for (size_t i = 0; i < n; ++i) {
        int b_day;
        int b_month;
        int b_year;
        int d_day;
        int d_month;
        int d_year;
        std::cin >> b_day >> b_month >> b_year >> d_day >> d_month >> d_year;
        authors[i] = Author(Date(b_day, b_month, b_year), Date(d_day, d_month, d_year));
    }

    std::cout << max_contemporary(authors, n);

    delete[] authors;
}

int main() {
    size_t n;
    std::cin >> n;
    assert((n > 0));

    solve(n);

    return 0;
}
