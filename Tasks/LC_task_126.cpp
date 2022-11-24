#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <utility>
#include <vector>

constexpr int kMaxDist = 1000;

int GetDiffCount(const std::string& l, const std::string& r) {
  assert(l.size() == r.size());
  int diff_count = 0;
  for (int i = 0; i < l.size(); ++i) {
    diff_count += (l[i] != r[i]);
  }
  return diff_count;
}

std::vector<std::vector<uint8_t>> BuildMatchMap(
    const std::vector<std::string>& data) {
  std::vector<std::vector<uint8_t>> res(data.size(),
                                        std::vector<uint8_t>(data.size()));
  for (int i = 0; i < data.size(); ++i) {
    for (int j = i + 1; j < data.size(); ++j) {
      if (GetDiffCount(data[i], data[j]) == 1) {
        res[i][j] = 1;
        res[j][i] = 1;
      }
    }
  }
  return res;
}

void BuildGraph(const std::vector<std::vector<uint8_t>>& match_map, int ci,
                std::vector<std::vector<int>>& graph) {
  assert(graph.size() == match_map.size());
  if (!graph[ci].empty()) return;
  for (int i = 0; i < match_map.size(); ++i) {
    if (match_map[ci][i]) {
      graph[ci].push_back(i);
      BuildGraph(match_map, i, graph);
    }
  }
}

bool SaveLayer(const std::vector<int>& children, int p, int stop_id,
               std::queue<int>& buff, std::vector<int>& distances,
               std::vector<int8_t>& lookup) {
  for (const auto& el : children) {
    if (lookup[el]) continue;
    lookup[el] = 1;
    buff.push(el);
    distances[el] = distances[p] + 1;
    if (el == stop_id) return true;
  }
  return false;
}

std::vector<int> BFS(const std::vector<std::vector<int>>& graph, int start,
                     int end) {
  std::vector<int> distances(graph.size(), kMaxDist);
  std::vector<int8_t> lookup(graph.size());
  std::queue<int> buff;
  buff.push(start);
  lookup[start] = 1;
  distances[start] = 1;
  while (!buff.empty()) {
    int c = buff.front();
    buff.pop();
    if (SaveLayer(graph[c], c, end, buff, distances, lookup)) {
      break;
    }
  }
  return distances;
}

void DFS(const std::vector<std::vector<int>>& graph, int cid, int bid, int eid,
         std::vector<int>& path, const std::vector<int>& se,
         const std::vector<int>& es, std::vector<uint8_t>& lookup,
         std::vector<std::vector<int>>& all_pathes) {
  if (lookup[cid]) return;
  lookup[cid] = 1;
  if (path.size() + se[cid] > se[eid]) {
    lookup[cid] = 0;
    return;
  }
  path.push_back(cid);
  if (path.size() == se[eid] && cid == bid) {
    all_pathes.push_back(path);
    path.pop_back();
    lookup[cid] = 0;
    return;
  }
  for (const auto& id : graph[cid]) {
    if (es[id] <= es[cid]) continue;
    DFS(graph, id, bid, eid, path, se, es, lookup, all_pathes);
  }
  path.pop_back();
  lookup[cid] = 0;
}

std::vector<std::string> TranslatePath(const std::vector<std::string>& data,
                                       const std::vector<int>& p) {
  std::vector<std::string> res;
  res.reserve(p.size());
  std::transform(p.begin(), p.end(), std::back_inserter(res),
                 [&data](int id) { return data[id]; });
  return res;
}

std::vector<std::vector<std::string>> GetPathesWithLength(
    const std::vector<std::string>& data,
    const std::vector<std::vector<int>>& graph, int bid, int eid,
    const std::vector<int>& se, const std::vector<int>& es) {
  std::vector<uint8_t> lookup(data.size());
  std::vector<std::vector<int>> all_pathes;
  std::vector<int> path;
  path.reserve(se[eid]);
  DFS(graph, eid, bid, eid, path, se, es, lookup, all_pathes);

  for (auto& el : all_pathes) {
    std::reverse(el.begin(), el.end());
  }
  std::vector<std::vector<std::string>> res;
  res.reserve(all_pathes.size());
  std::transform(
      all_pathes.begin(), all_pathes.end(), std::back_inserter(res),
      [&data](const std::vector<int>& p) { return TranslatePath(data, p); });
  return res;
}

class Solution {
 public:
  std::vector<std::vector<std::string>> findLadders(
      std::string beginWord, std::string endWord,
      std::vector<std::string>& wordList) {
    int eid =
        std::find(wordList.begin(), wordList.end(), endWord) - wordList.begin();
    if (eid == wordList.size()) return {};
    int bid = std::find(wordList.begin(), wordList.end(), beginWord) -
              wordList.begin();
    if (bid == wordList.size()) {
      wordList.push_back(beginWord);
      bid = wordList.size() - 1;
    }
    // Build entire graph
    std::vector<std::vector<uint8_t>> match_map = BuildMatchMap(wordList);
    std::vector<std::vector<int>> graph(wordList.size());
    BuildGraph(match_map, bid, graph);
    // BFS results and tree prunning
    std::vector<int> se = BFS(graph, bid, eid);
    if (se[eid] == kMaxDist) return {};
    std::vector<int> es = BFS(graph, eid, bid);
    return GetPathesWithLength(wordList, graph, bid, eid, se, es);
  }
};

int main() {
  std::string beginWord = "aaaaa";
  std::string endWord = "ggggg";
  std::vector<std::string> wordList = {
      "aaaaa", "caaaa", "cbaaa", "daaaa", "dbaaa", "eaaaa", "ebaaa", "faaaa",
      "fbaaa", "gaaaa", "gbaaa", "haaaa", "hbaaa", "iaaaa", "ibaaa", "jaaaa",
      "jbaaa", "kaaaa", "kbaaa", "laaaa", "lbaaa", "maaaa", "mbaaa", "naaaa",
      "nbaaa", "oaaaa", "obaaa", "paaaa", "pbaaa", "bbaaa", "bbcaa", "bbcba",
      "bbdaa", "bbdba", "bbeaa", "bbeba", "bbfaa", "bbfba", "bbgaa", "bbgba",
      "bbhaa", "bbhba", "bbiaa", "bbiba", "bbjaa", "bbjba", "bbkaa", "bbkba",
      "bblaa", "bblba", "bbmaa", "bbmba", "bbnaa", "bbnba", "bboaa", "bboba",
      "bbpaa", "bbpba", "bbbba", "abbba", "acbba", "dbbba", "dcbba", "ebbba",
      "ecbba", "fbbba", "fcbba", "gbbba", "gcbba", "hbbba", "hcbba", "ibbba",
      "icbba", "jbbba", "jcbba", "kbbba", "kcbba", "lbbba", "lcbba", "mbbba",
      "mcbba", "nbbba", "ncbba", "obbba", "ocbba", "pbbba", "pcbba", "ccbba",
      "ccaba", "ccaca", "ccdba", "ccdca", "cceba", "cceca", "ccfba", "ccfca",
      "ccgba", "ccgca", "cchba", "cchca", "cciba", "ccica", "ccjba", "ccjca",
      "cckba", "cckca", "cclba", "cclca", "ccmba", "ccmca", "ccnba", "ccnca",
      "ccoba", "ccoca", "ccpba", "ccpca", "cccca", "accca", "adcca", "bccca",
      "bdcca", "eccca", "edcca", "fccca", "fdcca", "gccca", "gdcca", "hccca",
      "hdcca", "iccca", "idcca", "jccca", "jdcca", "kccca", "kdcca", "lccca",
      "ldcca", "mccca", "mdcca", "nccca", "ndcca", "occca", "odcca", "pccca",
      "pdcca", "ddcca", "ddaca", "ddada", "ddbca", "ddbda", "ddeca", "ddeda",
      "ddfca", "ddfda", "ddgca", "ddgda", "ddhca", "ddhda", "ddica", "ddida",
      "ddjca", "ddjda", "ddkca", "ddkda", "ddlca", "ddlda", "ddmca", "ddmda",
      "ddnca", "ddnda", "ddoca", "ddoda", "ddpca", "ddpda", "dddda", "addda",
      "aedda", "bddda", "bedda", "cddda", "cedda", "fddda", "fedda", "gddda",
      "gedda", "hddda", "hedda", "iddda", "iedda", "jddda", "jedda", "kddda",
      "kedda", "lddda", "ledda", "mddda", "medda", "nddda", "nedda", "oddda",
      "oedda", "pddda", "pedda", "eedda", "eeada", "eeaea", "eebda", "eebea",
      "eecda", "eecea", "eefda", "eefea", "eegda", "eegea", "eehda", "eehea",
      "eeida", "eeiea", "eejda", "eejea", "eekda", "eekea", "eelda", "eelea",
      "eemda", "eemea", "eenda", "eenea", "eeoda", "eeoea", "eepda", "eepea",
      "eeeea", "ggggg", "agggg", "ahggg", "bgggg", "bhggg", "cgggg", "chggg",
      "dgggg", "dhggg", "egggg", "ehggg", "fgggg", "fhggg", "igggg", "ihggg",
      "jgggg", "jhggg", "kgggg", "khggg", "lgggg", "lhggg", "mgggg", "mhggg",
      "ngggg", "nhggg", "ogggg", "ohggg", "pgggg", "phggg", "hhggg", "hhagg",
      "hhahg", "hhbgg", "hhbhg", "hhcgg", "hhchg", "hhdgg", "hhdhg", "hhegg",
      "hhehg", "hhfgg", "hhfhg", "hhigg", "hhihg", "hhjgg", "hhjhg", "hhkgg",
      "hhkhg", "hhlgg", "hhlhg", "hhmgg", "hhmhg", "hhngg", "hhnhg", "hhogg",
      "hhohg", "hhpgg", "hhphg", "hhhhg", "ahhhg", "aihhg", "bhhhg", "bihhg",
      "chhhg", "cihhg", "dhhhg", "dihhg", "ehhhg", "eihhg", "fhhhg", "fihhg",
      "ghhhg", "gihhg", "jhhhg", "jihhg", "khhhg", "kihhg", "lhhhg", "lihhg",
      "mhhhg", "mihhg", "nhhhg", "nihhg", "ohhhg", "oihhg", "phhhg", "pihhg",
      "iihhg", "iiahg", "iiaig", "iibhg", "iibig", "iichg", "iicig", "iidhg",
      "iidig", "iiehg", "iieig", "iifhg", "iifig", "iighg", "iigig", "iijhg",
      "iijig", "iikhg", "iikig", "iilhg", "iilig", "iimhg", "iimig", "iinhg",
      "iinig", "iiohg", "iioig", "iiphg", "iipig", "iiiig", "aiiig", "ajiig",
      "biiig", "bjiig", "ciiig", "cjiig", "diiig", "djiig", "eiiig", "ejiig",
      "fiiig", "fjiig", "giiig", "gjiig", "hiiig", "hjiig", "kiiig", "kjiig",
      "liiig", "ljiig", "miiig", "mjiig", "niiig", "njiig", "oiiig", "ojiig",
      "piiig", "pjiig", "jjiig", "jjaig", "jjajg", "jjbig", "jjbjg", "jjcig",
      "jjcjg", "jjdig", "jjdjg", "jjeig", "jjejg", "jjfig", "jjfjg", "jjgig",
      "jjgjg", "jjhig", "jjhjg", "jjkig", "jjkjg", "jjlig", "jjljg", "jjmig",
      "jjmjg", "jjnig", "jjnjg", "jjoig", "jjojg", "jjpig", "jjpjg", "jjjjg",
      "ajjjg", "akjjg", "bjjjg", "bkjjg", "cjjjg", "ckjjg", "djjjg", "dkjjg",
      "ejjjg", "ekjjg", "fjjjg", "fkjjg", "gjjjg", "gkjjg", "hjjjg", "hkjjg",
      "ijjjg", "ikjjg", "ljjjg", "lkjjg", "mjjjg", "mkjjg", "njjjg", "nkjjg",
      "ojjjg", "okjjg", "pjjjg", "pkjjg", "kkjjg", "kkajg", "kkakg", "kkbjg",
      "kkbkg", "kkcjg", "kkckg", "kkdjg", "kkdkg", "kkejg", "kkekg", "kkfjg",
      "kkfkg", "kkgjg", "kkgkg", "kkhjg", "kkhkg", "kkijg", "kkikg", "kkljg",
      "kklkg", "kkmjg", "kkmkg", "kknjg", "kknkg", "kkojg", "kkokg", "kkpjg",
      "kkpkg", "kkkkg", "ggggx", "gggxx", "ggxxx", "gxxxx", "xxxxx", "xxxxy",
      "xxxyy", "xxyyy", "xyyyy", "yyyyy", "yyyyw", "yyyww", "yywww", "ywwww",
      "wwwww", "wwvww", "wvvww", "vvvww", "vvvwz", "avvwz", "aavwz", "aaawz",
      "aaaaz"};

  Solution s;
  auto result = s.findLadders(beginWord, endWord, wordList);

  std::cout << "RESULT\n";
  for (const auto& path : result) {
    for (const auto& el : path) {
      std::cout << el << "->";
    }
    std::cout << '\n';
  }
  return 0;
}
