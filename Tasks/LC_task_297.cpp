#include <assert>
#include <queue>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

struct StringRep {
  int parent = -1;
  char tag = 'l';
  int val = 0;
};

std::string ToString(const StringRep& sr) {
  std::string res;
  res.reserve(13);
  res = std::to_string(sr.parent);
  res.push_back(',');
  res.push_back(sr.tag);
  res.push_back(',');
  res += std::to_string(sr.val);
  return res;
}

StringRep FromString(std::string_view data) {
  StringRep res;
  size_t pos = data.find(',');
  res.parent = std::stoi(std::string(data.substr(0, pos)));
  ++pos;
  res.tag = data[pos];
  pos += 2;
  res.val = std::stoi(std::string(data.substr(pos)));
  return res;
}

std::pair<StringRep, std::string_view> ParseNext(std::string_view data) {
  assert(!data.empty());
  assert(data.front() != ';');
  size_t pos = data.find(';');
  if (pos == std::string_view::npos) {
    return {FromString(data), {}};
  }
  return {FromString(data.substr(0, pos)), data.substr(pos + 1)};
}

std::vector<StringRep> ParseString(std::string_view data) {
  std::vector<StringRep> res;
  while (!data.empty()) {
    std::pair<StringRep, std::string_view> tmp = ParseNext(data);
    res.push_back(tmp.first);
    data = tmp.second;
  }
  return res;
}

TreeNode* BuildTree(const std::vector<StringRep>& data) {
  std::vector<TreeNode*> res;
  res.reserve(data.size());
  res.push_back(new TreeNode(data.front().val));
  for (int i = 1; i < data.size(); ++i) {
    TreeNode* parent = res[data[i].parent];
    if (data[i].tag == 'l') {
      parent->left = new TreeNode(data[i].val);
      res.push_back(parent->left);
    } else {
      parent->right = new TreeNode(data[i].val);
      res.push_back(parent->right);
    }
  }
  return res.front();
}

std::string ConvertToString(TreeNode* root) {
  std::string res;
  std::queue<std::pair<int, TreeNode*>> buff;
  buff.push({0, root});
  res += ToString({.parent = -1, .tag = 'l', root->val});
  int index = 1;
  while (!buff.empty()) {
    std::pair<int, TreeNode*> top = buff.front();
    buff.pop();
    if (top.second->left) {
      res.push_back(';');
      res += ToString(
          {.parent = top.first, .tag = 'l', .val = top.second->left->val});
      buff.push({index++, top.second->left});
    }

    if (top.second->right) {
      res.push_back(';');
      res += ToString(
          {.parent = top.first, .tag = 'r', .val = top.second->right->val});
      buff.push({index++, top.second->right});
    }
  }

  return res;
}

class Codec {
 public:
  // Encodes a tree to a single string.
  std::string serialize(TreeNode* root) {
    if (!root) return {};
    return ConvertToString(root);
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(std::string data) {
    if (data.empty()) return nullptr;
    return BuildTree(ParseString(data));
  }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
