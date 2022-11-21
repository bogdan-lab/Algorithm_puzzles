#include <algorithm>
#include <limits>
#include <unordered_map>

struct Length {
  int straight = 0;
  int finished = 0;
};

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

Length Calculate(TreeNode *node, std::unordered_map<TreeNode *, Length> &data) {
  if (!node) return {};
  Length l = Calculate(node->left, data);
  Length r = Calculate(node->right, data);
  auto &curr = data[node];
  curr.straight =
      std::max({node->val, node->val + l.straight, node->val + r.straight});
  curr.finished = std::max({
      curr.straight,
      node->val + l.straight + r.straight,
  });
  return curr;
}

class Solution {
 public:
  int maxPathSum(TreeNode *root) {
    std::unordered_map<TreeNode *, Length> data;
    Calculate(root, data);
    int max_val = std::numeric_limits<int>::min();
    for (const auto &[n, l] : data) {
      max_val = std::max(max_val, l.finished);
    }
    return max_val;
  }
};
