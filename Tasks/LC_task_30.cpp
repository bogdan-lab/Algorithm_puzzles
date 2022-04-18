#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <string>
#include <string_view>
#include <vector>

constexpr size_t kEmptyId = std::numeric_limits<size_t>::max();

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

void AddPosForWord(std::vector<size_t>& word_map, size_t w_id,
                   std::string_view word, std::string_view input) {
  size_t curr_pos = 0;
  while (true) {
    curr_pos = input.find(word, curr_pos);
    if (curr_pos == std::string_view::npos) return;
    word_map[curr_pos] = w_id;
    curr_pos++;
  }
}

std::vector<size_t> CreateWordString(
    std::string_view input, const std::vector<std::string_view>& unique_words) {
  std::vector<size_t> result(input.size(), kEmptyId);
  for (size_t i = 0; i < unique_words.size(); ++i) {
    AddPosForWord(result, i, unique_words[i], input);
  }
  return result;
}

void AddToSolution(std::vector<int>& result, size_t start_index,
                   size_t word_size, size_t string_size,
                   const std::vector<size_t>& word_string,
                   const std::vector<int>& initial_count_pattern) {
  std::vector<int> curr_pattern = initial_count_pattern;
  // count first word if it exist
  std::optional<size_t> begin_index;
  size_t next_index = start_index;
  // if we find pattern match_count == count_pattern.size()
  size_t match_count = 0;
  while (next_index < word_string.size()) {
    if (word_string[next_index] == kEmptyId) {
      // found gap -> restart counting
      match_count = 0;
      curr_pattern = initial_count_pattern;
      begin_index.reset();
    } else {
      if (!begin_index) {
        begin_index = next_index;
      }
      // make count
      size_t id = word_string[next_index];
      curr_pattern[id]--;
      if (curr_pattern[id] == 0) {
        match_count++;
      } else if (curr_pattern[id] == -1) {
        match_count--;
      }
      // check for the answer
      if (match_count == curr_pattern.size()) {
        result.push_back(*begin_index);
      }
      if (next_index - *begin_index + word_size >= string_size) {
        size_t del_id = word_string[*begin_index];
        begin_index = *begin_index + word_size;
        curr_pattern[del_id]++;
        if (curr_pattern[del_id] == 0) {
          match_count++;
        } else if (curr_pattern[del_id] == 1) {
          match_count--;
        }
      }
    }
    next_index += word_size;
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
    std::vector<size_t> word_string =
        CreateWordString(s, pattern.GetUniqueWords());

    std::vector<int> result;
    size_t word_size = words.front().size();
    for (size_t i = 0; i < word_size; ++i) {
      AddToSolution(result, i, word_size, words.size() * word_size, word_string,
                    pattern.GetCount());
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
  {
    Solution test;
    std::string str = "abaababbaba";
    std::vector<std::string> words{"ab", "ba", "ab", "ba"};
    std::vector<int> expected{1, 3};
    auto result = test.findSubstring(str, words);
    assert(result == expected);
  }
  return 0;
}
