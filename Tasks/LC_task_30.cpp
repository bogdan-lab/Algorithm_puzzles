#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <string_view>
#include <tuple>
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

class WordPattern {
 public:
  void AddWord(std::string_view word) {
    auto it = std::find(words_.begin(), words_.end(), word);
    if (it == words_.end()) {
      words_.push_back(word);
      count_.push_back(1);
    } else {
      count_[it - words_.begin()] += 1;
    }
  }

  const std::vector<std::string_view> GetUniqueWords() const { return words_; }

  const std::vector<int> GetCount() const { return count_; }

 private:
  std::vector<std::string_view> words_;
  std::vector<int> count_;
};

struct PriorityCompare {
  bool operator()(const WordPos& lhs, const WordPos& rhs) const {
    return std::tie(lhs.pos, lhs.id) > std::tie(rhs.pos, rhs.id);
  }
};

std::vector<WordPos> CreateWordString(
    std::string_view input, const std::vector<std::string_view>& unique_words) {
  std::vector<WordPos> result;
  std::vector<std::queue<size_t>> word_map =
      GetWordsStartPos(input, unique_words);
  std::priority_queue<WordPos, std::vector<WordPos>, PriorityCompare> map_queue;
  for (size_t i = 0; i < word_map.size(); ++i) {
    if (word_map[i].empty()) return result;
    map_queue.push({i, word_map[i].front()});
    word_map[i].pop();
  }
  while (!map_queue.empty()) {
    WordPos top = map_queue.top();
    result.push_back(top);
    map_queue.pop();
    if (!word_map[top.id].empty()) {
      map_queue.push({top.id, word_map[top.id].front()});
      word_map[top.id].pop();
    }
  }
  return result;
}

void ClearQueue(std::queue<int>& data) {
  while (!data.empty()) {
    data.pop();
  }
}

void AddToSolution(std::vector<int>& result, size_t start_index,
                   size_t word_size, size_t string_size,
                   const std::vector<WordPos>& word_string,
                   const std::vector<int>& initial_count_pattern) {
  std::vector<int> curr_pattern = initial_count_pattern;
  std::queue<int> picked_indexes;
  auto it = word_string.begin() + start_index;
  size_t next_pos = it->pos;
  // if we find pattern match_count == count_pattern.size()
  size_t match_count = 0;
  while (true) {
    it = std::find_if(it, word_string.end(), [&next_pos](const WordPos& el) {
      return next_pos <= el.pos;
    });
    if (it == word_string.end()) return;
    if (it->pos > next_pos) {
      // found gap -> restart counting
      match_count = 0;
      curr_pattern = initial_count_pattern;
      ClearQueue(picked_indexes);
      next_pos = it->pos;
    }
    // make_count
    picked_indexes.push(it - word_string.begin());
    int match_start_idx = picked_indexes.front();
    curr_pattern[it->id]--;
    if (curr_pattern[it->id] == 0) {
      match_count++;
    } else if (curr_pattern[it->id] == -1) {
      match_count--;
    }
    // check for the answer
    if (match_count == curr_pattern.size()) {
      result.push_back(word_string[match_start_idx].pos);
    }
    // update next_pos and delete tail if needed
    next_pos += word_size;
    if (next_pos - word_string[match_start_idx].pos >= string_size) {
      // unmake count at start_pos
      size_t id = word_string[match_start_idx].id;
      curr_pattern[id]++;
      if (curr_pattern[id] == 0) {
        match_count++;
      } else if (curr_pattern[id] == 1) {
        match_count--;
      }
      picked_indexes.pop();
    }
  }
}

class Solution {
 public:
  std::vector<int> findSubstring(std::string s,
                                 std::vector<std::string>& words) {
    WordPattern pattern;
    for (const auto& el : words) {
      pattern.AddWord(el);
    }

    std::vector<WordPos> word_string =
        CreateWordString(s, pattern.GetUniqueWords());
    std::vector<int> result;
    if (word_string.empty()) {
      return result;
    }

    size_t word_size = words.front().size();
    for (size_t i = 0; i < word_string.size(); ++i) {
      AddToSolution(result, i, word_size, words.size() * word_size, word_string,
                    pattern.GetCount());
    }
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
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
  {
    Solution test;
    std::string str = "ababababab";
    std::vector<std::string> words{"ababa", "babab"};
    std::vector<int> expected{0};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  {
    Solution test;
    std::string str = "a";
    std::vector<std::string> words{"a"};
    std::vector<int> expected{0};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  {
    Solution test;
    std::string str = "sheateateseatea";
    std::vector<std::string> words{"sea", "tea", "ate"};
    std::vector<int> expected{6};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  return 0;
}
