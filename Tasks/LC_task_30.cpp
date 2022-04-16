#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <vector>

std::queue<size_t> FindWord(std::string_view input, std::string_view word) {
  std::queue<size_t> result;
  size_t pos = 0;
  while (true) {
    size_t new_pos = input.find(word, pos);
    if (new_pos == std::string_view::npos) {
      break;
    }
    result.push(new_pos);
    pos = new_pos + 1;
  }
  return result;
}

std::vector<std::queue<size_t>> GetWordsStartPos(
    std::string_view input, const std::vector<std::string_view>& words) {
  std::vector<std::queue<size_t>> res;
  res.reserve(words.size());
  for (const auto& el : words) {
    res.push_back(FindWord(input, el));
  }
  return res;
}

struct WordPos {
  size_t id;
  size_t pos;
};

struct PriorityCompare {
  bool operator()(const WordPos& lhs, const WordPos& rhs) const {
    return lhs.pos > rhs.pos;
  }
};

class Solution {
 public:
  std::vector<int> findSubstring(std::string s,
                                 std::vector<std::string>& words) {
    std::vector<std::string_view> word_views;
    word_views.reserve(words.size());
    for (const auto& el : words) {
      word_views.push_back(el);
    }
    std::string_view s_view = s;
    std::vector<std::queue<size_t>> word_map =
        GetWordsStartPos(s_view, word_views);

    std::vector<int> result;
    for (const auto& el : word_map) {
      if (el.empty()) return result;
    }
    std::priority_queue<WordPos, std::vector<WordPos>, PriorityCompare>
        map_queue;

    for (size_t i = 0; i < word_map.size(); ++i) {
      map_queue.push({i, word_map[i].front()});
      word_map[i].pop();
    }

    std::vector<int> word_is_present(word_views.size());
    std::queue<WordPos> picked_queue;
    size_t next_index = 0;
    while (!map_queue.empty()) {
      const WordPos& top = map_queue.top();
      if (top.pos == next_index) {
        // add to the current picked_queue
        if (word_is_present[top.id]) {
          // delete all chosen words before it and itself
          size_t curr_id = picked_queue.front().id;
          while (curr_id != top.id) {
            word_is_present[curr_id] = 0;
            picked_queue.pop();
            curr_id = picked_queue.front().id;
          }
          word_is_present[top.id] = 0;
          picked_queue.pop();  // deleted old top.id
        }
      } else {
        // found substring that does not match any word -> free picked_queue
        while (!picked_queue.empty()) {
          word_is_present[picked_queue.front().id] = 0;
          picked_queue.pop();
        }
      }
      word_is_present[top.id] = 1;
      picked_queue.push(top);
      // Finalize step - guarantee map_queu reduction, update next index and
      // check for success
      if (picked_queue.size() == word_views.size()) {
        result.push_back(picked_queue.front().pos);
      }
      next_index = picked_queue.back().pos + word_views.front().size();
      if (!word_map[top.id].empty()) {
        WordPos new_el{top.id, word_map[top.id].front()};
        word_map[top.id].pop();
        map_queue.push(new_el);
      }
      map_queue.pop();
    }
    return result;
  }
};

int main() {
  {
    Solution test;
    std::string str = "barfoothefoobarman";
    std::vector<std::string> words{"foo", "bar"};
    std::vector<int> expected{0, 9};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  {
    Solution test;
    std::string str = "wordgoodgoodgoodbestword";
    std::vector<std::string> words{"woord", "good", "best", "word"};
    std::vector<int> expected{};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  {
    Solution test;
    std::string str = "barfoofoobarthefoobarman";
    std::vector<std::string> words{"bar", "foo", "the"};
    std::vector<int> expected{6, 9, 12};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  {
    Solution test;
    std::string str = "wordgoodgoodgoodbestword";
    std::vector<std::string> words{"word", "good", "best", "good"};
    std::vector<int> expected{8};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  return 0;
}
