#include <string>
#include <unordered_map>
#include <vector>

void ConvertDouble(int num, const std::unordered_map<int, std::string>& names,
                   std::vector<std::string>& out) {
  auto it = names.find(num);
  if (it == names.end()) {
    int rem = num % 10;
    int top = num - rem;
    out.push_back(names.at(rem));
    out.push_back(names.at(top));
    return;
  }
  out.push_back(it->second);
}

void ConvertTriplet(int num, const std::unordered_map<int, std::string>& names,
                    std::vector<std::string>& out) {
  int top = num / 100;
  if (top) {
    int rem = num - 100 * top;
    if (rem) {
      ConvertDouble(num - 100 * top, names, out);
    }
    out.push_back("Hundred");
    out.push_back(names.at(top));
    return;
  }
  ConvertDouble(num, names, out);
}

std::string BuildWords(const std::vector<std::string>& words) {
  std::string res;
  res.reserve(10 * words.size());
  for (int i = words.size() - 1; i > 0; --i) {
    res += words[i];
    res += " ";
  }
  res += words.front();
  return res;
}

class Solution {
 public:
  inline static const std::unordered_map<int, std::string> names{
      {0, "Zero"},      {1, "One"},       {2, "Two"},
      {3, "Three"},     {4, "Four"},      {5, "Five"},
      {6, "Six"},       {7, "Seven"},     {8, "Eight"},
      {9, "Nine"},      {10, "Ten"},      {11, "Eleven"},
      {12, "Twelve"},   {13, "Thirteen"}, {14, "Fourteen"},
      {15, "Fifteen"},  {16, "Sixteen"},  {17, "Seventeen"},
      {18, "Eighteen"}, {19, "Nineteen"}, {20, "Twenty"},
      {30, "Thirty"},   {40, "Forty"},    {50, "Fifty"},
      {60, "Sixty"},    {70, "Seventy"},  {80, "Eighty"},
      {90, "Ninety"}

  };
  std::string numberToWords(int num) {
    if (!num) return names.at(num);
    std::vector<std::string> words;
    words.reserve(20);
    std::vector<std::string> levels{"Thousand", "Million", "Billion"};
    int i = -1;
    while (num) {
      int rem = num % 1000;
      num /= 1000;
      if (rem) {
        if (i >= 0) {
          words.push_back(levels[i]);
        }
        ConvertTriplet(rem, names, words);
      }
      ++i;
    }
    return BuildWords(words);
  }
};
