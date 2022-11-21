#include <algorithm>
#include <limits>
#include <unordered_map>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

int Calculate(TreeNode *node, int &max_val) {
  if (!node) return {};
  int l = Calculate(node->left, max_val);
  int r = Calculate(node->right, max_val);
  int straight = std::max({node->val, node->val + l, node->val + r});
  max_val = std::max({max_val, straight, node->val + l + r});
  return straight;
}

class Solution {
 public:
  int maxPathSum(TreeNode *root) {
    int max_val = std::numeric_limits<int>::min();
    Calculate(root, max_val);
    return max_val;
  }
};
