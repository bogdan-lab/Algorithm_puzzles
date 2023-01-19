#include <cassert>
#include <map>
#include <utility>

template <typename K, typename V>
class interval_map {
  friend void IntervalMapTest();
  V m_valBegin;
  std::map<K, V> m_map;

 public:
  // constructor associates whole range of K with val
  interval_map(V const& val) : m_valBegin(val) {}

  // Assign value val to interval [keyBegin, keyEnd).
  // Overwrite previous values in this interval.
  // Conforming to the C++ Standard Library conventions, the interval
  // includes keyBegin, but excludes keyEnd.
  // If !( keyBegin < keyEnd ), this designates an empty interval,
  // and assign must do nothing.
  void assign(K const& keyBegin, K const& keyEnd, V const& val) {
    auto eqv = [](const auto& l, const auto& r) {
      return !(l < r) && !(r < l);
    };

    auto replace_inside = [&](auto it, auto next, const V& vb, const V& v) {
      assert(it != m_map.end());
      assert(next != m_map.end());
      if (it->second == v) return;
      if (v == vb && v == next->second) {
        m_map.erase(it);
        m_map.erase(next);
      } else if (v == vb) {
        m_map.erase(it);
      } else if (v == next->second) {
        m_map.erase(next);
        it->second = v;
      } else {
        it->second = v;
      }
    };

    auto replace_end = [&](auto it, auto prev, const V& v) {
      assert(it != m_map.end());
      assert(prev != m_map.end());
      if (it->second == v) return;
      if (prev->second == v) {
        m_map.erase(it);
      } else {
        it->second = v;
      }
    };

    auto change_left_part = [&](auto it, const V& vb, const K& b, const K& e,
                                const V& v) {
      assert(it != m_map.end());
      if (it->second == v) return;
      auto next = std::next(it);
      auto node = m_map.extract(it);
      node.key() = e;
      next = m_map.insert(next, std::move(node));
      if (!vb == v) {
        m_map.emplace_hint(next, b, v);
      }
    };

    auto change_right_part = [&](const V& vc, auto next, const K& b,
                                 const V& v) {
      assert(next != m_map.end());
      if (eqv(vc, v)) return;
      if (eqv(v, next->second)) {
        auto next_after = std::next(next);
        auto node = m_map.extract(next);
        node.key() = b;
        m_map.insert(next_after, std::move(node));
      } else {
        m_map.emplace_hint(next, b, v);
      }
    };

    auto change_inside = [&](auto it, auto next, const K& b, const K& e,
                             const V& v) {
      assert(it != m_map.end());
      assert(next != m_map.end());
      if (eqv(v, it->second)) return;
      m_map.emplace_hint(next, b, v);
      m_map.emplace_hint(next, e, it->second);
    };

    auto change_in_left_edge = [&](const K& b, const K& e, const V& v) {
      assert(!m_map.empty());
      if (eqv(v, m_valBegin)) return;
      m_map.emplace_hint(m_map.begin(), e, m_valBegin);
      m_map.emplace_hint(m_map.begin(), b, v);
    };

    auto change_in_right_edge = [&](const V& vc, const K& b, const V& v) {
      if (eqv(vc, v)) return;
      m_map.emplace_hint(m_map.end(), b, v);
    };

    auto add_to_empty = [&](const K& b, const V& v) {
      if (v == m_valBegin) return;
      m_map.emplace_hint(m_map.end(), b, v);
    };

    auto set_small = [&](const V& vb, auto it, auto next, const K& b,
                         const K& e, const V& v) {
      if (next == m_map.end()) {
        // Setting stuff in the right edge
        if (eqv(it->first, b)) {
          change_left_part(it, vb, b, e, v);
        } else {
          change_in_right_edge(it->second, b, v);
        }
        return;
      }
      // All iterators are valid
      if (eqv(it->first, b) && eqv(next->first, e)) {
        replace_inside(it, next, vb, v);
      } else if (eqv(it->first, b)) {
        change_left_part(it, vb, b, e, v);
      } else if (eqv(next->first, e)) {
        change_right_part(it->second, next, b, v);
      } else {
        change_inside(it, next, b, e, v);
      }
    };

    auto is_in_range = [](const K& test, const K& b, const K& e) {
      return !(test < b) && !(e < test);
    };

    auto set_small_right_edge = [&](auto right_edge, const K& b, const K& e,
                                    const V& v) {
      if (right_edge == m_map.begin()) {
        if (eqv(right_edge->first, keyEnd)) {
          change_right_part(m_valBegin, right_edge, keyBegin, val);
        } else {
          change_in_left_edge(keyBegin, keyEnd, val);
        }
      } else {
        auto next = right_edge;
        --right_edge;
        if (right_edge == m_map.begin()) {
          set_small(m_valBegin, right_edge, next, keyBegin, keyEnd, val);
        } else {
          set_small(std::prev(right_edge)->second, right_edge, next, keyBegin,
                    keyEnd, val);
        }
      }
    };

    if (!(keyBegin < keyEnd)) return;

    auto it = m_map.upper_bound(keyBegin);
    // Remove all intervals which will be entirely replaced
    while (it != m_map.end() && is_in_range(it->first, keyBegin, keyEnd) &&
           (std::next(it) == m_map.end() ||
            is_in_range(std::next(it)->first, keyBegin, keyEnd))) {
      auto prev = it;
      it = std::next(it);
      m_map.erase(it);
    }

    if (m_map.empty()) {
      add_to_empty(keyBegin, val);
      return;
    }
    // Here we will have one of two situations.
    // The incoming interval lays entirely in some interval inside the tree
    // Or the incoming interval corsses two intervals from the tree
    if (it != m_map.end() && it->first < keyEnd) {
      // we cross two intervals
      Key split = it->first;
      auto next = std::next(it);
      set_small_right_edge(it, keyBegin, split, val);
      set_small_right_edge(next, split, keyEnd, val);
    } else {
      set_small_right_edge(it, keyBegin, keyEnd, val);
    }
  }

  // look-up of the value associated with key
  V const& operator[](K const& key) const {
    auto it = m_map.upper_bound(key);
    if (it == m_map.begin()) {
      return m_valBegin;
    } else {
      return (--it)->second;
    }
  }

  // Returns number of itnervals without the beginning one
  int size() const { return m_map.size(); }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

bool Equal(const interval_map<int, char>& res,
           const std::vector<std::pair<int, char>>& tests) {
  for (const auto& [key, val] : tests) {
    if (res[key] != val) return false;
  }
  return true;
}

int main() {
  // EMPTY ITNERVAL CASES
  {  // Add to empty interval
    char ic = 'A';
    interval_map<int, char> data(ic);
    assert(Equal(data, {{-1, ic}, {0, ic}, {100, ic}}));
    int start = 0;
    int end = 2;
    char c = 'B';
    data.assign(start, end, c);
    assert(Equal(
        data, {{-1, ic}, {start, c}, {start + 1, c}, {end, c}, {end + 1, c}}));
    assert(data.size() == 1);
  }
  {  // Add to empty interval with begin_val value
    char ic = 'A';
    interval_map<int, char> data(ic);
    int start = 0;
    int end = 30;
    data.assign(start, end, ic);
    assert(data.size() == 0);
    assert(Equal(data, {{-1, ic}, {0, ic}, {100, ic}}));
  }
  {  // Add empty to empty
    char ic = 'A';
    interval_map<int, char> data(ic);
    data.assign(0, 0, 'B');
    assert(data.size() == 0);
    data.assign(1, 0, 'B');
    assert(data.size() == 0);
  }
  {  // Assign with size 1
    char ic = 'A';
    interval_map<int, char> data(ic);
    assert(Equal(data, {{-1, ic}, {0, ic}, {100, ic}}));
    int start = 0;
    int end = 1;
    char c = 'B';
    data.assign(start, end, c);
    assert(Equal(data,
                 {{-1, ic}, {start, c}, {start, c}, {end, c}, {end + 1, c}}));
    assert(data.size() == 1);
  }

  // SINGLE INTERVAL CASES
  {  // Have one interval and reassign it entirely
    char ic = 'A';
    interval_map<int, char> data(ic);
    int start = 0;
    int end = 3;
    data.assign(start, end, 'B');
    data.assign(start, end, 'C');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, ic}, {start, 'C'}, {start + 1, 'C'}, {end, 'C'}}));
  }
  {  // Have one interval add empty
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(1, 1, 'C');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {3, 'B'}}));
    data.assign(1, 0, 'C');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {3, 'B'}}));
  }
  {  // Have one interval reassing right part of it
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(1, 3, 'C');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'C'}, {3, 'C'}}));
  }
  {  // Reassign right part to the same
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(1, 3, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {3, 'B'}}));
  }
  {  // reassign the right part as crossection
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(2, 5, 'C');
    assert(data.size() == 2);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {2, 'C'}, {3, 'C'}, {5, 'C'}}));
  }
  {  // Right part as crossection to the same
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(2, 5, 'B');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {2, 'B'}, {3, 'B'}, {5, 'B'}}));
  }
  {  // Have one interval reassgin left part of it
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(0, 2, 'C');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'C'}, {1, 'C'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // reassign left part to the initial value
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(0, 2, 'A');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'A'}, {1, 'A'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Assign interval before the first one with crossection
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 2, 'C');
    assert(data.size() == 2);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'C'}, {0, 'C'}, {1, 'C'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Before the first one with crossection to the initial
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 2, 'A');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'A'}, {0, 'A'}, {1, 'A'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Assign interval before the first one when borders touch each other
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 0, 'C');
    assert(data.size() == 2);
    assert(Equal(data, {{-3, 'A'}, {-2, 'C'}, {0, 'B'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Assign before the first one with the begin_val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 0, 'A');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'A'}, {-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Assign interval after when it touches the border
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 4, 'C');
    assert(data.size() == 2);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'C'}, {4, 'C'}}));
  }
  {  // Assign the same when it touches border on the right
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 4, 'B');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}}));
  }
  {  // Assign the second interval which surrounds the first one
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(-1, 3, 'C');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'}, {-1, 'C'}, {2, 'C'}, {3, 'C'}}));
  }
  {  // Assign surrounding with the same value
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(-1, 3, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'}, {-1, 'B'}, {2, 'B'}, {3, 'B'}}));
  }
  {  // Assign surrounding with the begin_val
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(-1, 3, 'A');
    assert(data.size() == 0);
    assert(Equal(data, {{-2, 'A'}, {-1, 'A'}, {2, 'A'}, {3, 'A'}}));
  }
  {  // Assign interval before the first with the gap
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(-3, -1, 'C');
    assert(data.size() == 3);
    assert(Equal(
        data,
        {{-4, 'A'}, {-3, 'C'}, {-2, 'C'}, {-1, 'A'}, {0, 'B'}, {2, 'B'}}));
  }
  {  // Before the first with the gap and begin_val
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(-3, -1, 'A');
    assert(data.size() == 1);
    assert(Equal(
        data,
        {{-4, 'A'}, {-3, 'A'}, {-2, 'A'}, {-1, 'A'}, {0, 'B'}, {2, 'B'}}));
  }
  {  // Assign interval after the first one
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(4, 5, 'C');
    assert(data.size() == 2);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'C'}, {5, 'C'}}));
  }
  {  // After the first one with the gap and the same value
    interval_map<int, char> data('A');
    data.assign(0, 2, 'B');
    data.assign(4, 5, 'B');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'B'}, {4, 'B'}, {5, 'B'}}));
  }

  // TOW INTERVAL CASES

  return 0;
}
