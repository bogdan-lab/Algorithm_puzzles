#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

enum class Symbol {
  kUndefined,
  kNumber,
  kPlus,
  kMinus,
  kMult,
  kOpenBracket,
  kCloseBracket,
  kFunction,
  kDedMoroz,
  kMoroz,
  kSnegurochka
};

struct Lexem {
  Symbol symbol = Symbol::kUndefined;
  std::string_view raw;
};

class Lexer {
 public:
  Lexer() = default;
  void Init(std::string str) {
    data_ = std::move(str);
    lexems_ = Parse(data_);
  }

  const std::string& GetData() const { return data_; }

  void InitScanner() { index_ = 0; }

  bool ScanNext() { return ++index_ < lexems_.size(); }

  bool HasTocken() const { return index_ < lexems_.size(); }

  const Lexem& CurrentTocken() const { return lexems_[index_]; }

 private:
  static std::vector<Lexem> Parse(std::string_view data) {
    std::vector<Lexem> res;

    int index = 0;
    while (true) {
      switch (data[index]) {
        case '.': {
          return res;
        }
        case '+': {
          res.push_back({Symbol::kPlus, data.substr(index, 1)});
          break;
        }
        case '-': {
          res.push_back({Symbol::kMinus, data.substr(index, 1)});
          break;
        }
        case '*': {
          res.push_back({Symbol::kMult, data.substr(index, 1)});
          break;
        }
        case '(': {
          res.push_back({Symbol::kOpenBracket, data.substr(index, 1)});
          break;
        }
        case ')': {
          res.push_back({Symbol::kCloseBracket, data.substr(index, 1)});
          break;
        }
        default: {
          // function, number, constant
          if (std::isdigit(data[index])) {
            int start = index;
            int count = 0;
            while (std::isdigit(data[index])) {
              ++count;
              ++index;
            }
            res.push_back({Symbol::kNumber, data.substr(start, count)});
            --index;  // because in the end we increase it
          } else if (data.substr(index, 7) == "Podarok") {
            res.push_back({Symbol::kFunction, data.substr(index, 7)});
            index += 6;  // later we will add 1 more
          } else if (data.substr(index, 9) == "Ded Moroz") {
            res.push_back({Symbol::kDedMoroz, data.substr(index, 9)});
            index += 8;  // later we will add 1 more
          } else if (data.substr(index, 5) == "Moroz") {
            res.push_back({Symbol::kMoroz, data.substr(index, 5)});
            index += 4;  // later we will add 1 more
          } else if (data.substr(index, 11) == "Snegurochka") {
            res.push_back({Symbol::kSnegurochka, data.substr(index, 11)});
            index += 10;  // later we will add 1 more
          } else {
            throw std::runtime_error("bad input");
          }
          break;
        }
      }
      ++index;
    }

    return res;
  }

  std::string data_;
  std::vector<Lexem> lexems_;
  int index_ = -1;
};

struct Node {
  Lexem lex;
  Node* left = nullptr;
  Node* right = nullptr;
};

long ToLong(char c) {
  long res = static_cast<long>(c) - static_cast<long>('0');
  if (res > 9 || res < 0) throw std::runtime_error("bad number");
  return res;
}

long ConvertToLong(std::string_view data) {
  long res = 0;
  if (!ToLong(data[0]) && data.size() > 1)
    throw std::runtime_error("bad number");
  long mult = 10;
  for (const auto& el : data) {
    res = res * mult + ToLong(el);
  }
  return res;
}

long Podarok(long val) { return val > 0 ? val + 5 : -val; }

class Parser {
 public:
  explicit Parser(std::string str) {
    try {
      lexer_.Init(std::move(str));
    } catch (...) {
      root_ = nullptr;
      return;
    }
    lexer_.InitScanner();
    root_ = ParseExpression();
    if (lexer_.HasTocken()) {
      root_ = nullptr;
    }
  }

  void Print() {
    std::cout << "INPUT = " << lexer_.GetData() << '\n';
    std::cout << "OUTPUT = ";
    PrintNode(root_);
    std::cout << '\n';
  }

  void Calc() {
    if (!root_) {
      std::cout << "WRONG\n";
      return;
    }
    try {
      std::cout << CalcNode(root_) << '\n';
    } catch (...) {
      std::cout << "WRONG\n";
    }
  }

  ~Parser() { DeleteNode(root_); }

 private:
  void DeleteNode(Node* node) {
    if (!node) return;
    DeleteNode(node->left);
    DeleteNode(node->right);
    delete node;
  }

  void PrintNode(Node* node) {
    if (!node) {
      return;
    } else if (!node->right && !node->left) {
      std::cout << node->lex.raw;
      return;
    }
    std::cout << '(';
    PrintNode(node->left);
    std::cout << node->lex.raw;
    PrintNode(node->right);
    std::cout << ')';
  }

  long CalcNode(Node* node) {
    switch (node->lex.symbol) {
      case Symbol::kNumber: {
        return ConvertToLong(node->lex.raw);
      }
      case Symbol::kDedMoroz: {
        return 2020l;
      }
      case Symbol::kMoroz: {
        return -30l;
      }
      case Symbol::kSnegurochka: {
        return 10l;
      }
      case Symbol::kFunction: {
        if (!node->left) {
          throw std::runtime_error("bad tocken");
        }
        return Podarok(CalcNode(node->left));
      }
      case Symbol::kPlus: {
        if (!node->left || !node->right) {
          throw std::runtime_error("bad tocken");
        }
        return CalcNode(node->left) + CalcNode(node->right);
      }
      case Symbol::kMinus: {
        if (!node->left || !node->right) {
          throw std::runtime_error("bad tocken");
        }
        return CalcNode(node->left) - CalcNode(node->right);
      }
      case Symbol::kMult: {
        if (!node->left || !node->right) {
          throw std::runtime_error("bad tocken");
        }
        return CalcNode(node->left) * CalcNode(node->right);
      }
      default:
        throw std::runtime_error("bad tocken");
    }
  }

  Node* ParseExpression() {
    Node* a = ParseTerm();
    if (!a) return nullptr;
    while (true) {
      if (!lexer_.HasTocken()) break;
      Lexem curr = lexer_.CurrentTocken();
      switch (curr.symbol) {
        case Symbol::kPlus:
        case Symbol::kMinus: {
          lexer_.ScanNext();  // consume plus or minus
          Node* b = ParseTerm();
          if (!b) return nullptr;
          Node* tmp = new Node();
          tmp->left = a;
          tmp->right = b;
          tmp->lex = curr;
          a = tmp;
          break;
        }
        case Symbol::kCloseBracket:
          return a;
        default:
          return nullptr;
      }
    }
    return a;
  }

  Node* ParseTerm() {
    Node* a = ParseFactor();
    if (!a) return nullptr;
    while (true) {
      if (!lexer_.HasTocken()) break;
      Lexem curr = lexer_.CurrentTocken();
      switch (curr.symbol) {
        case Symbol::kMult: {
          lexer_.ScanNext();  // consume multiplication
          Node* b = ParseFactor();
          if (!b) return nullptr;
          Node* tmp = new Node();
          tmp->left = a;
          tmp->right = b;
          tmp->lex = curr;
          a = tmp;
          break;
        }
        case Symbol::kPlus:
        case Symbol::kMinus:
        case Symbol::kCloseBracket:
          return a;
        default:
          return nullptr;
      }
    }
    return a;
  }

  Node* ParseFactor() {
    if (!lexer_.HasTocken()) return nullptr;
    Lexem curr = lexer_.CurrentTocken();
    switch (curr.symbol) {
      case Symbol::kNumber:
      case Symbol::kDedMoroz:
      case Symbol::kMoroz:
      case Symbol::kSnegurochka: {
        Node* res = new Node();
        res->lex = curr;
        lexer_.ScanNext();  // consume number or constant
        return res;
      }
      case Symbol::kOpenBracket: {
        lexer_.ScanNext();  // consume open bracket
        Node* res = ParseExpression();
        if (lexer_.CurrentTocken().symbol != Symbol::kCloseBracket) {
          return nullptr;
        }
        lexer_.ScanNext();  // consume close bracket
        return res;
      }
      case Symbol::kFunction: {
        Node* f = new Node();
        f->lex = curr;
        lexer_.ScanNext();  // consume function name
        if (!lexer_.HasTocken()) return nullptr;
        if (lexer_.CurrentTocken().symbol != Symbol::kOpenBracket) {
          return nullptr;
        }
        lexer_.ScanNext();  // consume open brackets for function

        f->left = ParseExpression();
        if (lexer_.CurrentTocken().symbol != Symbol::kCloseBracket) {
          return nullptr;
        }
        lexer_.ScanNext();  // consume close brackets for function
        return f;
      }
      default:
        return nullptr;
    }
  }

  Lexer lexer_;
  Node* root_ = nullptr;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string data;
  std::getline(input, data);

  Parser parser(std::move(data));
  parser.Calc();
  // parser.Print();
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1+(2*2-3).
  )";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(105+202+301+101+523.
  )";
    Solution(ss);
    std::cout << "expected = 1232\n";
  }
  {
    std::stringstream ss;
    ss << R"((10+26)*15-7*35+(12-4)*(15+6).
  )";
    Solution(ss);
    std::cout << "expected = 463\n";
  }
  {
    std::stringstream ss;
    ss << R"((1-2)*0*(2-1).
  )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(1234.
  )";
    Solution(ss);
    std::cout << "expected = 1234\n";
  }
  {
    std::stringstream ss;
    ss << R"((1234).
  )";
    Solution(ss);
    std::cout << "expected = 1234\n";
  }
  {
    std::stringstream ss;
    ss << R"((1234)+(5)-(5).
  )";
    Solution(ss);
    std::cout << "expected = 1234\n";
  }
  {
    std::stringstream ss;
    ss << R"(((5+(42-7)*15)*(4-8)-12)*5.
  )";
    Solution(ss);
    std::cout << "expected = -10660\n";
  }
  {
    std::stringstream ss;
    ss << R"(8+5.
  )";
    Solution(ss);
    std::cout << "expected = 13\n";
  }
  {
    std::stringstream ss;
    ss << R"(8-5.
  )";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
  {
    std::stringstream ss;
    ss << R"(8*5.
  )";
    Solution(ss);
    std::cout << "expected = 40\n";
  }
  {
    std::stringstream ss;
    ss << R"(2+2*2.
  )";
    Solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(2*2+2.
  )";
    Solution(ss);
    std::cout << "expected = 6\n";
  }
  {
    std::stringstream ss;
    ss << R"(1+2-3.
  )";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(1-2+3.
  )";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"((((((1-2+3))))).
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"((((((1-2+3)))+)).
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"((((((1-2+3)))-)).
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"((((((1-2+3)))*)).
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(1+a+1.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(b.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(1-.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(1+.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(1*.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(-1.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(+1.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(*1.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(*.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(-.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(+.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(().
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"().
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"((.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(1+A.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(-5+6.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(02+3.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(4*(35+8.
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(4*35+8).
)";
    Solution(ss);
    std::cout << "expected = WRONG\n";
  }
  {
    std::stringstream ss;
    ss << R"(Podarok(Moroz-Ded Moroz)*2.
)";
    Solution(ss);
    std::cout << "expected = 4100\n";
  }
  {
    std::stringstream ss;
    ss << R"(Snegurochka-30.
)";
    Solution(ss);
    std::cout << "expected = -20\n";
  }
}
