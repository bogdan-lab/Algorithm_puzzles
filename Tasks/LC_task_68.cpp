#include <cassert>
#include <string>
#include <vector>

struct LineInfo {
  size_t word_count = 0;
  size_t not_space_count = 0;
};

LineInfo AccumulatesSingleLine(const std::vector<std::string>& words,
                               size_t begin, size_t max_width);

std::string ConstructLine(const std::vector<std::string>& words,
                          size_t max_width, size_t begin, LineInfo info);

std::string ConstructLastLine(const std::vector<std::string>& words,
                              size_t max_width, size_t begin);
class Solution {
 public:
  std::vector<std::string> fullJustify(std::vector<std::string>& words,
                                       int max_width) {
    std::vector<std::string> result;
    size_t index = 0;
    while (index < words.size()) {
      LineInfo curr_line = AccumulatesSingleLine(words, index, max_width);
      if (index + curr_line.word_count < words.size()) {
        result.push_back(ConstructLine(words, max_width, index, curr_line));
      } else {
        result.push_back(ConstructLastLine(words, max_width, index));
      }
      index += curr_line.word_count;
    }
    return result;
  }
};

LineInfo AccumulatesSingleLine(const std::vector<std::string>& words,
                               size_t begin, size_t max_width) {
  size_t total_char_count = 0;
  LineInfo res;
  for (size_t i = begin; i < words.size(); ++i) {
    assert(words[i].size() <= max_width);
    total_char_count += words[i].size();
    if (total_char_count > max_width) break;
    ++res.word_count;
    res.not_space_count += words[i].size();
    ++total_char_count;  // Add space after new word
  }
  return res;
}

std::string ConstructLine(const std::vector<std::string>& words,
                          size_t max_width, size_t begin, LineInfo info) {
  assert(begin < words.size());
  assert(info.word_count > 0);
  std::string result;
  result.reserve(max_width);
  result.append(words[begin]);
  if (info.word_count == 1) {
    size_t space_left = max_width - info.not_space_count;
    if (space_left > 0) {
      result.append(std::string(space_left, ' '));
    }
    return result;
  }
  // Evenly distribute spaces
  size_t space_count = info.word_count - 1;
  size_t vacant_places = max_width - info.not_space_count;
  std::vector<int> space_distr(space_count, vacant_places / space_count);
  size_t spaces_left = vacant_places % space_count;
  for (size_t i = 0; i < spaces_left; ++i) {
    ++space_distr[i];
  }
  // Filling the line
  for (size_t i = 0; i < space_distr.size(); ++i) {
    result.append(std::string(space_distr[i], ' '))
        .append(words[begin + i + 1]);
  }
  return result;
}

std::string ConstructLastLine(const std::vector<std::string>& words,
                              size_t max_width, size_t begin) {
  assert(begin < words.size());
  std::string result;
  result.reserve(max_width);
  size_t space_left = max_width;
  for (size_t i = begin; i < words.size(); ++i) {
    result.append(words[i]);
    space_left -= words[i].size();
    if (space_left > 0) {
      result.append(" ");
      --space_left;
    }
  }
  if (space_left > 0) {
    result.append(std::string(space_left, ' '));
  }
  return result;
}