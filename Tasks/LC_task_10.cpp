#include <cassert>
#include <string>
#include <string_view>
#include <vector>

struct Token {
  char c = '\0';
  bool any_number = false;
};

std::vector<Token> LexPattern(std::string_view pattern) {
  std::vector<Token> result;
  result.reserve(pattern.size());
  int i = 0;
  while (i < pattern.size()) {
    Token t;
    t.c = pattern[i];
    i++;
    if (i != pattern.size() && pattern[i] == '*') {
      t.any_number = true;
      i++;
    }
    result.push_back(t);
  }
  return result;
}

bool CharMatchToken(char ch, Token token) {
  return token.c == '.' || ch == token.c || token.any_number;
}

bool CharCanBeConsumed(char ch, Token token) {
  return token.c == '.' || ch == token.c;
}

bool CanIgnoreRightTokens(const std::vector<Token>& tokens, int ti) {
  for (int i = ti; i < tokens.size(); ++i) {
    if (!tokens[i].any_number) return false;
  }
  return true;
}

bool MatchImpl(std::string_view s, const std::vector<Token>& tokens, int ti) {
  if (s.empty()) return CanIgnoreRightTokens(tokens, ti);
  if (ti >= tokens.size()) return false;
  if (CharMatchToken(s[0], tokens[ti])) {
    if (CharCanBeConsumed(s[0], tokens[ti])) {
      std::string_view s_cons = s;
      s_cons.remove_prefix(1);
      if (tokens[ti].any_number) {
        return MatchImpl(s_cons, tokens, ti) || MatchImpl(s, tokens, ti + 1);
      } else {
        return MatchImpl(s_cons, tokens, ti + 1);
      }
    } else {
      return MatchImpl(s, tokens, ti + 1);
    }
  } else {
    return false;
  }
}

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    std::vector<Token> tokens = LexPattern(p);
    return MatchImpl(s, tokens, 0);
  }
};

int main() {
  Solution s;
  assert(!s.isMatch("aa", "a"));
  assert(s.isMatch("aa", "a*"));
  assert(s.isMatch("ab", ".*"));
  assert(s.isMatch("aaa", "a*a"));
  assert(s.isMatch("aaa", "a*aa"));
  assert(s.isMatch("aaa", "a*aaa"));
  assert(s.isMatch("aaa", "aaaa*"));
  assert(s.isMatch("aaa", "aaa*"));
  assert(s.isMatch("aaa", "aa*"));
  assert(s.isMatch("aaa", "ab*a*c*a"));
  assert(!s.isMatch("ab", ".*c"));
  assert(s.isMatch("cab", "c.*"));
  assert(s.isMatch("cabc", "c.*c"));
}

