#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class WordCollection {
 public:
  WordCollection(const std::vector<std::string>& data) {
    str_.reserve(data.size());
    uint16_t count = 0;
    for (const auto& el : data) {
      str_.push_back(el);
    }
    std::sort(str_.begin(), str_.end());
    ids_.resize(data.size());
    std::iota(ids_.begin(), ids_.end(), static_cast<uint16_t>(0));
  }

  const std::vector<std::string_view>& GetStr() const { return str_; }

  const std::vector<uint16_t>& GetIds() const { return ids_; }

  bool Empty() const { return str_.empty(); }

  size_t Size() const { return ids_.size(); }

  void Pop(size_t index) {
    std::swap(str_[index], str_.back());
    std::swap(ids_[index], ids_.back());
    str_.pop_back();
    ids_.pop_back();
    std::sort(str_.begin(), str_.end());
    std::sort(ids_.begin(), ids_.end());
  }

 private:
  std::vector<std::string_view> str_;
  std::vector<uint16_t> ids_;
};

struct Key {
  Key(size_t g_size, WordCollection wds)
      : input_size(g_size), words_left(std::move(wds)) {}

  size_t input_size = 0;
  WordCollection words_left;
};

bool operator==(const Key& lhs, const Key& rhs) {
  if (lhs.input_size != rhs.input_size) {
    return false;
  }
  const auto& lhs_ids = lhs.words_left.GetIds();
  const auto& rhs_ids = rhs.words_left.GetIds();
  if (lhs_ids.size() != rhs_ids.size()) {
    return false;
  }
  for (size_t i = 0; i < lhs_ids.size(); ++i) {
    if (lhs_ids[i] != rhs_ids[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const Key& lhs, const Key& rhs) { return !(lhs == rhs); }

struct HashKey {
  size_t operator()(const Key& k) const {
    std::hash<size_t> int_hash;
    size_t result = int_hash(k.input_size);
    for (const auto& el : k.words_left.GetIds()) {
      result ^= int_hash(el);
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
      std::string_view input, const WordCollection& words,
      int initial_words_size) {
    std::vector<int> result;
    if (words.Empty()) {
      result.push_back(index);
      return result;
    }
    if (input.empty()) return result;
    const auto& words_str = words.GetStr();
    for (size_t i = 0; i < words_str.size(); ++i) {
      if (StartsWith(input, words_str[i])) {
        WordCollection words_copy = words;
        words_copy.Pop(i);
        std::string_view input_copy = input;
        input_copy.remove_prefix(words_str[i].size());
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
    if (words.Size() == initial_words_size) {
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
    WordCollection words_col(words);
    std::unordered_map<Key, std::vector<int>, HashKey> memo;
    std::vector<int> result =
        FindSubstringImpl(memo, 0, s, words_col, words.size());
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
