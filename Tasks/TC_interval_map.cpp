#include <cassert>
#include <map>
#include <utility>
#include <vector>

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
      if (next == m_map.end()) {
        m_map.erase(it);
      } else {
        auto node = m_map.extract(it);
        node.key() = e;
        next = m_map.insert(next, std::move(node));
      }
      if (vb != v) {
        m_map.emplace_hint(next, b, v);
      }
    };

    auto change_right_part = [&](const V& vc, auto next, const K& b,
                                 const V& v) {
      assert(next != m_map.end());
      if (vc == v) return;
      if (v == next->second) {
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
      if (v == it->second) return;
      m_map.emplace_hint(next, b, v);
      m_map.emplace_hint(next, e, it->second);
    };

    auto change_in_left_edge = [&](const K& b, const K& e, const V& v) {
      assert(!m_map.empty());
      if (v == m_valBegin) return;
      m_map.emplace_hint(m_map.begin(), b, v);
    };

    auto change_in_right_edge = [&](const V& vc, const K& b, const V& v) {
      if (vc == v) return;
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
      return !(test < b) && test < e;
    };

    auto set_small_right_edge = [&](auto right_edge, const K& b, const K& e,
                                    const V& v) {
      if (right_edge == m_map.begin()) {
        if (eqv(right_edge->first, e)) {
          change_right_part(m_valBegin, right_edge, b, v);
        } else {
          change_in_left_edge(b, e, v);
        }
      } else {
        auto next = right_edge;
        --right_edge;
        if (right_edge == m_map.begin()) {
          set_small(m_valBegin, right_edge, next, b, e, v);
        } else {
          set_small(std::prev(right_edge)->second, right_edge, next, b, e, v);
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
      m_map.erase(prev);
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
      K split = it->first;
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
  {  // Have one interval reassign right part of it
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
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'C'}, {1, 'C'}, {2, 'C'}, {3, 'C'}}));
  }
  {  // reassign left part to the initial value
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(0, 2, 'A');
    assert(data.size() == 0);
    assert(Equal(data, {{-1, 'A'}, {0, 'A'}, {1, 'A'}, {2, 'A'}, {3, 'A'}}));
  }
  {  // Assign interval before the first one with crossection
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 2, 'C');
    assert(data.size() == 1);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'C'}, {0, 'C'}, {1, 'C'}, {2, 'C'}, {3, 'C'}}));
  }
  {  // Before the first one with crossection to the initial
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(-2, 2, 'A');
    assert(data.size() == 0);
    assert(Equal(
        data, {{-3, 'A'}, {-2, 'A'}, {0, 'A'}, {1, 'A'}, {2, 'A'}, {3, 'A'}}));
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
    assert(data.size() == 2);
    assert(Equal(
        data,
        {{-4, 'A'}, {-3, 'C'}, {-2, 'C'}, {-1, 'C'}, {0, 'B'}, {2, 'B'}}));
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
  {  // Reassign the first itnerval
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(0, 3, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'D'}, {2, 'D'}, {3, 'C'}, {5, 'C'}}));
  }
  {  // Reassign the first itnerval same value
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(0, 3, 'B');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'C'}, {5, 'C'}}));
  }
  {  // Reassign the first itnerval to begin_val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(0, 3, 'A');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'A'}, {2, 'A'}, {3, 'C'}, {5, 'C'}}));
  }
  {  // Reassign the second interval
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(3, 5, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'D'}, {5, 'D'}}));
  }
  {  // Reassign the second interval same value
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(3, 5, 'C');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'C'}, {5, 'C'}}));
  }
  {  // Reassign the second interval prev val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(3, 5, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'B'}, {5, 'B'}}));
  }
  {  // Reassign left part of the first one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(0, 2, 'D');
    assert(data.size() == 3);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'D'}, {1, 'D'}, {2, 'B'}, {3, 'C'}, {5, 'C'}}));
  }

  {  // Reassign the right part of the first one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(1, 3, 'D');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'D'}, {3, 'C'}, {5, 'C'}}));
  }

  {  // Reassign the middle of the first one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(1, 2, 'D');
    assert(data.size() == 4);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {1, 'D'}, {2, 'B'}, {3, 'C'}, {5, 'C'}}));
  }

  {  // Reassign the left part of the second one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(3, 4, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'D'}, {5, 'D'}}));
  }

  {  // Reassign the right part of the second one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 5, 'C');
    data.assign(4, 5, 'D');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'C'}, {5, 'D'}}));
  }

  {  // Reassign the middle of the second one
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(4, 5, 'D');
    assert(data.size() == 3);
    assert(Equal(
        data, {{-1, 'A'}, {0, 'B'}, {2, 'B'}, {3, 'C'}, {5, 'D'}, {6, 'D'}}));
  }

  {  // Reassign crossing both
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(2, 4, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'D'},
                        {3, 'D'},
                        {4, 'D'},
                        {6, 'D'}}));
  }

  {  // Reassign surrounding both
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(0, 4, 'D');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'D'},
                        {1, 'D'},
                        {2, 'D'},
                        {3, 'D'},
                        {4, 'D'},
                        {6, 'D'}}));
  }
  {  // Reassign surrounding both begin val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(0, 4, 'A');
    assert(data.size() == 0);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'A'},
                        {1, 'A'},
                        {2, 'A'},
                        {3, 'A'},
                        {4, 'A'},
                        {6, 'A'}}));
  }
  {  // Reassign surrounding both 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(-1, 4, 'D');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'},
                        {-1, 'D'},
                        {1, 'D'},
                        {2, 'D'},
                        {3, 'D'},
                        {4, 'D'},
                        {6, 'D'}}));
  }

  {  // Reassign Surrounding second overlaping with first
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(1, 7, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'D'}, {7, 'D'}}));
  }

  {  // Reassign surrounding first one overlapping with the second
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(0, 4, 'D');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'D'}, {3, 'D'}, {4, 'D'}, {7, 'D'}}));
  }

  {  // Reassign surrounding first one overlapping with the second 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(-1, 4, 'D');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'}, {-1, 'D'}, {3, 'D'}, {4, 'D'}, {7, 'D'}}));
  }

  // THREE INTERVALS CHANGE THE MIDDLE ONE modify middle
  {  // Reassign middle
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 6, 'E');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'E'},
                        {5, 'E'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Reassign middle GATES
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'B');
    data.assign(3, 6, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'B'},
                        {5, 'B'},
                        {6, 'B'},
                        {9, 'B'}}));
  }
  {  // Reassign middle PREV
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 6, 'B');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'B'},
                        {5, 'B'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Reassign middle NEXT
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 6, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'D'},
                        {5, 'D'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Middle overlapping
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(2, 7, 'E');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'E'},
                        {3, 'E'},
                        {5, 'E'},
                        {6, 'E'},
                        {7, 'E'},
                        {9, 'E'}}));
  }
  {  // Middle overlapping bridge
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'B');
    data.assign(2, 7, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'B'},
                        {5, 'B'},
                        {6, 'B'},
                        {7, 'B'},
                        {9, 'B'}}));
  }
  {  // Left part of middle
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 5, 'E');
    assert(data.size() == 4);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'E'},
                        {4, 'E'},
                        {5, 'C'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Left part of middle PREV
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 5, 'B');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {2, 'B'},
                        {3, 'B'},
                        {4, 'B'},
                        {5, 'C'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Left part of middle with overlapping
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(2, 5, 'E');
    assert(data.size() == 4);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'E'},
                        {3, 'E'},
                        {4, 'E'},
                        {5, 'C'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Right part
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(4, 6, 'E');
    assert(data.size() == 4);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'C'},
                        {4, 'E'},
                        {5, 'E'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Right part NEXT val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(4, 6, 'D');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'C'},
                        {4, 'D'},
                        {5, 'D'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Right part NEXT val 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(3, 6, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'D'},
                        {4, 'D'},
                        {5, 'D'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Right part overlap
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(4, 7, 'E');
    assert(data.size() == 3);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'C'},
                        {4, 'E'},
                        {5, 'E'},
                        {6, 'E'},
                        {9, 'E'}}));
  }
  {  // Middle in the middle
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(4, 5, 'E');
    assert(data.size() == 5);
    assert(Equal(data, {{-1, 'A'},
                        {0, 'B'},
                        {1, 'B'},
                        {2, 'B'},
                        {3, 'C'},
                        {4, 'E'},
                        {5, 'C'},
                        {6, 'D'},
                        {9, 'D'}}));
  }
  {  // Overlap all
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(0, 10, 'E');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'E'}, {10, 'E'}}));
  }
  {  // Overlap all 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(-1, 7, 'E');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'}, {-1, 'E'}, {10, 'E'}}));
  }
  {  // Overlap all begin val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(0, 10, 'A');
    assert(data.size() == 0);
    assert(Equal(data, {{-1, 'A'}, {0, 'A'}, {10, 'A'}}));
  }
  {  // Overlap all prev val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(0, 10, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {10, 'B'}}));
  }
  {  // Overlap all Next val
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(-1, 7, 'D');
    assert(data.size() == 1);
    assert(Equal(data, {{-2, 'A'}, {1, 'D'}, {10, 'D'}}));
  }
  {  // Cover last two
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(2, 7, 'E');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {2, 'E'}, {7, 'E'}}));
  }
  {  // Cover last two NEXT
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(2, 7, 'D');
    assert(data.size() == 2);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {2, 'D'}, {7, 'D'}}));
  }
  {  // Cover last two Prev
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(2, 7, 'B');
    assert(data.size() == 1);
    assert(Equal(data, {{-1, 'A'}, {0, 'B'}, {1, 'B'}, {2, 'B'}, {7, 'B'}}));
  }
  {  // Cover first two
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(0, 6, 'E');
    assert(data.size() == 2);
    assert(Equal(data, {{{-1, 'A'}, {0, 'E'}, {6, 'D'}, {7, 'D'}}}));
  }
  {  // Cover first two 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(-1, 6, 'E');
    assert(data.size() == 2);
    assert(Equal(data, {{{-2, 'A'}, {-1, 'E'}, {6, 'D'}, {7, 'D'}}}));
  }
  {  // Cover first two PREV
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'D');
    data.assign(-1, 6, 'A');
    assert(data.size() == 1);
    assert(Equal(data, {{{-2, 'A'}, {-1, 'A'}, {6, 'D'}, {7, 'D'}}}));
  }
  {  // Cover first two PREV 2
    interval_map<int, char> data('A');
    data.assign(0, 3, 'B');
    data.assign(3, 6, 'C');
    data.assign(6, 9, 'A');
    data.assign(-1, 6, 'A');
    assert(data.size() == 0);
    assert(Equal(data, {{{-2, 'A'}, {-1, 'A'}, {6, 'A'}, {7, 'A'}}}));
  }
  return 0;
}
