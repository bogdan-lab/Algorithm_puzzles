#include <cassert>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

bool IsLetter(char c) { return c >= 'a' && c <= 'z'; }

std::string_view RemovePrefixAndSuffix(std::string_view data) {
  size_t start = data.find_first_not_of(')');
  if (start == std::string_view::npos) return {};
  size_t end = data.find_last_not_of('(');
  return data.substr(start, end - start + 1);
}

int GetRemovalNumber(std::string_view str) {
  assert(!str.empty());
  std::stack<char> buff;
  int count = 0;
  for (const auto& el : str) {
    if (IsLetter(el)) continue;
    if (buff.empty()) {
      if (el == '(') {
        buff.push(el);
      } else {
        ++count;
      }
    } else {  // top == '(' because top == ')' is impossible
      if (el == '(') {
        buff.push('(');
      } else {
        buff.pop();
      }
    }
  }
  return count + buff.size();
}

bool CanInsert(char c, const std::stack<char>& stk) {
  if (IsLetter(c)) return true;
  if (stk.empty()) return c == '(';
  return true;
}

void PushToStack(std::stack<char>& stk, char c) {
  assert(CanInsert(c, stk));
  if (IsLetter(c)) return;
  if (c == '(') {
    stk.push(c);
    return;
  }
  stk.pop();
}

void RestoreStack(std::stack<char>& stk, char prev_pushed) {
  if (IsLetter(prev_pushed)) return;
  if (prev_pushed == '(') {
    stk.pop();
    return;
  }
  stk.push('(');
}

void BuildPathes(std::string_view str, int start, int deletion_left,
                 std::stack<char>& curr_stack, std::string& curr_path,
                 std::unordered_set<std::string>& res) {
  if (deletion_left < 0) return;
  if (start >= str.size()) {
    if (curr_stack.empty()) {
      res.insert(curr_path);
    }
    return;
  }

  if (IsLetter(str[start])) {
    curr_path.push_back(str[start]);
    BuildPathes(str, start + 1, deletion_left, curr_stack, curr_path, res);
    curr_path.pop_back();
    return;
  }

  if (CanInsert(str[start], curr_stack)) {
    PushToStack(curr_stack, str[start]);
    curr_path.push_back(str[start]);

    BuildPathes(str, start + 1, deletion_left, curr_stack, curr_path, res);

    curr_path.pop_back();
    RestoreStack(curr_stack, str[start]);
  }

  BuildPathes(str, start + 1, deletion_left - 1, curr_stack, curr_path, res);
}

class Solution {
 public:
  std::vector<std::string> removeInvalidParentheses(std::string s) {
    std::string_view corrected_str = RemovePrefixAndSuffix(s);
    if (corrected_str.empty()) return {{}};
    int rem_number = GetRemovalNumber(corrected_str);
    std::unordered_set<std::string> data;
    std::stack<char> stk;
    std::string path;
    BuildPathes(corrected_str, 0, rem_number, stk, path, data);
    return {data.begin(), data.end()};
  }
};

int main() {
  Solution s;
  auto tmp = s.removeInvalidParentheses("(()");
  return 0;
}
