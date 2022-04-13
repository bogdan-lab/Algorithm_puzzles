#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Solution {
  struct Key {
    Key(int pos, std::vector<std::string_view> wds) {
      input_size = pos;
      std::sort(wds.begin(), wds.end());
      words_left = wds;
    }

    int input_size = 0;
    std::vector<std::string_view> words_left;
  };

  friend bool operator<(const Key& lhs, const Key& rhs) {
    if (lhs.input_size != rhs.input_size) {
      return lhs.input_size < rhs.input_size;
    }
    if (lhs.words_left.size() != rhs.words_left.size()) {
      return lhs.words_left.size() < rhs.words_left.size();
    }
    for (size_t i = 0; i < lhs.words_left.size(); ++i) {
      if (lhs.words_left[i] != rhs.words_left[i]) {
        return lhs.words_left[i] < rhs.words_left[i];
      }
    }
    return false;
  }

  bool StartsWith(std::string_view input, std::string_view word) {
    if (input.size() < word.size()) return false;
    for (size_t i = 0; i < word.size(); ++i) {
      if (input[i] != word[i]) {
        return false;
      }
    }
    return true;
  }

  void FindSubstringImpl(std::vector<int>& result, int index,
                         std::string_view input,
                         std::vector<std::string_view> words,
                         int initial_words_size) {
    if (input.empty()) return;
    if (words.empty()) {
      result.push_back(index);
      return;
    }
    for (size_t i = 0; i < words.size(); ++i) {
      if (StartsWith(input, words[i])) {
        std::vector<std::string_view> words_copy = words;
        std::swap(words_copy[i], words_copy.back());
        words_copy.pop_back();
        std::string_view input_copy = input;
        input_copy.remove_prefix(words[i].size());
        FindSubstringImpl(result, index, input_copy, words_copy,
                          initial_words_size);
      }
    }
    if (words.size() == initial_words_size) {
      index++;
      input.remove_prefix(1);
      FindSubstringImpl(result, index, input, words, initial_words_size);
    }
  }

 public:
  std::vector<int> findSubstring(std::string s,
                                 std::vector<std::string>& words) {
    std::vector<int> result;

    std::vector<std::string_view> words_view;
    words_view.reserve(words.size());
    for (const auto& word : words) {
      words_view.push_back(word);
    }
    FindSubstringImpl(result, 0, s, words_view, words.size());
    std::sort(result.begin(), result.end());
    result.erase(std::unique(result.begin(), result.end()), result.end());
    return result;
  }
};

void PrintRes(const std::vector<int>& res) {
  std::cout << "res = [";
  for (const auto& el : res) {
    std::cout << el << ", ";
  }
  std::cout << "]\n";
}

int main() {
  Solution test;
  {
    std::string input = "barfoothefoobarman";
    std::vector<std::string> words{"foo", "bar"};
    std::vector<int> res = test.findSubstring(input, words);
    PrintRes(res);
    std::cout << "expected = [0, 9]\n";
  }
  {
    std::string input = "barfoofoobarthefoobarman";
    std::vector<std::string> words{"bar", "foo", "the"};
    std::vector<int> res = test.findSubstring(input, words);
    PrintRes(res);
    std::cout << "expected = [6, 9, 12]\n";
  }
  {
    std::string input = "wordgoodgoodgoodbestword";
    std::vector<std::string> words{"word", "good", "best", "word"};
    std::vector<int> res = test.findSubstring(input, words);
    PrintRes(res);
    std::cout << "expected = []\n";
  }
  {
    std::string input = "wordgoodgoodgoodbestword";
    std::vector<std::string> words{"word", "good", "best", "good"};
    std::vector<int> res = test.findSubstring(input, words);
    PrintRes(res);
    std::cout << "expected = [8]\n";
  }

  return 0;
}
