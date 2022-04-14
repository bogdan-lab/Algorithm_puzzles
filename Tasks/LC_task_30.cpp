#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Key {
  Key(size_t g_size, std::vector<std::string_view> wds)
      : input_size(g_size), words_left(std::move(wds)) {
    std::sort(words_left.begin(), words_left.end());
  }

  size_t input_size = 0;
  std::vector<std::string_view> words_left;
};

bool operator==(const Key& lhs, const Key& rhs) {
  if (lhs.input_size != rhs.input_size) {
    return false;
  }
  if (lhs.words_left.size() != rhs.words_left.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs.words_left.size(); ++i) {
    if (lhs.words_left[i] != rhs.words_left[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Key& lhs, const Key& rhs) { return !(lhs == rhs); }

struct HashKey {
  size_t operator()(const Key& k) const {
    std::hash<size_t> int_hash;
    std::hash<std::string_view> sv_hash;

    size_t result = int_hash(k.input_size);
    for (const auto& el : k.words_left) {
      result ^= sv_hash(el);
    }
    return result;
  }
};

class Solution {
  bool StartsWith(std::string_view input, std::string_view word) {
    if (input.size() < word.size()) return false;
    for (size_t i = 0; i < word.size(); ++i) {
      if (input[i] != word[i]) {
        return false;
      }
    }
    return true;
  }

  std::vector<int> FindSubstringImpl(
      std::unordered_map<Key, std::vector<int>, HashKey>& memo, int index,
      std::string_view input, const std::vector<std::string_view>& words,
      int initial_words_size) {
    std::vector<int> result;
    if (words.empty()) {
      result.push_back(index);
      return result;
    }
    if (input.empty()) return result;
    for (size_t i = 0; i < words.size(); ++i) {
      if (StartsWith(input, words[i])) {
        std::vector<std::string_view> words_copy = words;
        std::swap(words_copy[i], words_copy.back());
        words_copy.pop_back();
        std::string_view input_copy = input;
        input_copy.remove_prefix(words[i].size());
        Key k{input.size(), words_copy};
        auto it = memo.find(k);
        if (it == memo.end()) {
          it = memo
                   .insert(std::make_pair(
                       k, FindSubstringImpl(memo, index, input_copy, words_copy,
                                            initial_words_size)))
                   .first;
        }
        for (const auto& el : it->second) {
          result.push_back(el);
        }
      }
    }
    if (words.size() == initial_words_size) {
      index++;
      input.remove_prefix(1);
      Key k(input.size(), words);
      auto it = memo.find(k);
      if (it == memo.end()) {
        it = memo.insert(std::make_pair(
                             k, FindSubstringImpl(memo, index, input, words,
                                                  initial_words_size)))
                 .first;
      }
      for (const auto& el : it->second) {
        result.push_back(el);
      }
    }
    return result;
  }

 public:
  std::vector<int> findSubstring(std::string s,
                                 std::vector<std::string>& words) {
    std::vector<std::string_view> words_view;
    words_view.reserve(words.size());
    for (const auto& word : words) {
      words_view.push_back(word);
    }
    std::unordered_map<Key, std::vector<int>, HashKey> memo;
    std::vector<int> result =
        FindSubstringImpl(memo, 0, s, words_view, words.size());
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
