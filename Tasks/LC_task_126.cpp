#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>

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

std::vector<int> BFS(const std::vector<std::string>& data, int root,
                     const std::vector<std::vector<int>>& graph,
                     std::vector<int>& levels) {
  std::vector<int> parents(data.size(), -1);
  std::vector<int8_t> lookup(data.size());
  std::queue<int> buff;
  buff.push(root);
  lookup[root] = 1;
  levels[root] = 0;
  while (!buff.empty()) {
    int c = buff.front();
    for (const auto& el : graph[c]) {
      if (!lookup[el]) {
        lookup[el] = 1;
        buff.push(el);
        parents[el] = c;
        levels[el] = levels[c] + 1;
      }
    }
    buff.pop();
  }
  return parents;
}

int GetMinPathLength(const std::vector<int>& parents, int i) {
  int count = 0;
  while (i >= 0) {
    ++count;
    i = parents[i];
  }
  return count;
}

void PruneGraph(std::vector<std::vector<int>>& graph,
                const std::vector<int>& levels, int min_len) {
  for (int i = 0; i < graph.size(); ++i) {
    auto p_end = std::partition(graph[i].begin(), graph[i].end(), [&](int id) {
      return levels[i] < levels[id] && levels[id] <= min_len + 1;
    });
    graph[i].erase(p_end, graph[i].end());
  }
}

void DFS(const std::vector<std::vector<int>>& graph, int cid, int eid,
         std::vector<int>& path, int min_len, std::vector<uint8_t>& lookup,
         std::vector<std::vector<int>>& all_pathes) {
  if (lookup[cid]) return;
  lookup[cid] = 1;
  path.push_back(cid);
  if (path.size() < min_len) {
    for (const auto& id : graph[cid]) {
      DFS(graph, id, eid, path, min_len, lookup, all_pathes);
    }
  } else if (path.size() == min_len && cid == eid) {
    all_pathes.push_back(path);
  }
  // restore before going back up
  lookup[cid] = 0;
  path.pop_back();
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
    const std::vector<std::vector<int>>& graph, int bid, int eid, int min_len) {
  std::vector<uint8_t> lookup(data.size());
  std::vector<std::vector<int>> all_pathes;
  std::vector<int> path;
  path.reserve(min_len + 1);
  DFS(graph, bid, eid, path, min_len, lookup, all_pathes);

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
    std::vector<std::vector<uint8_t>> match_map = BuildMatchMap(wordList);
    std::vector<std::vector<int>> graph(wordList.size());
    BuildGraph(match_map, bid, graph);
    std::vector<int> levels(wordList.size(), std::numeric_limits<int>::max());
    std::vector<int> parents = BFS(wordList, bid, graph, levels);
    if (parents[eid] == -1) return {};
    int min_path_len = GetMinPathLength(parents, eid);
    PruneGraph(graph, levels, min_path_len);
    return GetPathesWithLength(wordList, graph, bid, eid, min_path_len);
  }
};

int main() {
  std::string beginWord = "cet";
  std::string endWord = "ism";
  std::vector<std::string> wordList = {
      "kid", "tag", "pup", "ail", "tun", "woo", "erg", "luz", "brr", "gay",
      "sip", "kay", "per", "val", "mes", "ohs", "now", "boa", "cet", "pal",
      "bar", "die", "war", "hay", "eco", "pub", "lob", "rue", "fry", "lit",
      "rex", "jan", "cot", "bid", "ali", "pay", "col", "gum", "ger", "row",
      "won", "dan", "rum", "fad", "tut", "sag", "yip", "sui", "ark", "has",
      "zip", "fez", "own", "ump", "dis", "ads", "max", "jaw", "out", "btu",
      "ana", "gap", "cry", "led", "abe", "box", "ore", "pig", "fie", "toy",
      "fat", "cal", "lie", "noh", "sew", "ono", "tam", "flu", "mgm", "ply",
      "awe", "pry", "tit", "tie", "yet", "too", "tax", "jim", "san", "pan",
      "map", "ski", "ova", "wed", "non", "wac", "nut", "why", "bye", "lye",
      "oct", "old", "fin", "feb", "chi", "sap", "owl", "log", "tod", "dot",
      "bow", "fob", "for", "joe", "ivy", "fan", "age", "fax", "hip", "jib",
      "mel", "hus", "sob", "ifs", "tab", "ara", "dab", "jag", "jar", "arm",
      "lot", "tom", "sax", "tex", "yum", "pei", "wen", "wry", "ire", "irk",
      "far", "mew", "wit", "doe", "gas", "rte", "ian", "pot", "ask", "wag",
      "hag", "amy", "nag", "ron", "soy", "gin", "don", "tug", "fay", "vic",
      "boo", "nam", "ave", "buy", "sop", "but", "orb", "fen", "paw", "his",
      "sub", "bob", "yea", "oft", "inn", "rod", "yam", "pew", "web", "hod",
      "hun", "gyp", "wei", "wis", "rob", "gad", "pie", "mon", "dog", "bib",
      "rub", "ere", "dig", "era", "cat", "fox", "bee", "mod", "day", "apr",
      "vie", "nev", "jam", "pam", "new", "aye", "ani", "and", "ibm", "yap",
      "can", "pyx", "tar", "kin", "fog", "hum", "pip", "cup", "dye", "lyx",
      "jog", "nun", "par", "wan", "fey", "bus", "oak", "bad", "ats", "set",
      "qom", "vat", "eat", "pus", "rev", "axe", "ion", "six", "ila", "lao",
      "mom", "mas", "pro", "few", "opt", "poe", "art", "ash", "oar", "cap",
      "lop", "may", "shy", "rid", "bat", "sum", "rim", "fee", "bmw", "sky",
      "maj", "hue", "thy", "ava", "rap", "den", "fla", "auk", "cox", "ibo",
      "hey", "saw", "vim", "sec", "ltd", "you", "its", "tat", "dew", "eva",
      "tog", "ram", "let", "see", "zit", "maw", "nix", "ate", "gig", "rep",
      "owe", "ind", "hog", "eve", "sam", "zoo", "any", "dow", "cod", "bed",
      "vet", "ham", "sis", "hex", "via", "fir", "nod", "mao", "aug", "mum",
      "hoe", "bah", "hal", "keg", "hew", "zed", "tow", "gog", "ass", "dem",
      "who", "bet", "gos", "son", "ear", "spy", "kit", "boy", "due", "sen",
      "oaf", "mix", "hep", "fur", "ada", "bin", "nil", "mia", "ewe", "hit",
      "fix", "sad", "rib", "eye", "hop", "haw", "wax", "mid", "tad", "ken",
      "wad", "rye", "pap", "bog", "gut", "ito", "woe", "our", "ado", "sin",
      "mad", "ray", "hon", "roy", "dip", "hen", "iva", "lug", "asp", "hui",
      "yak", "bay", "poi", "yep", "bun", "try", "lad", "elm", "nat", "wyo",
      "gym", "dug", "toe", "dee", "wig", "sly", "rip", "geo", "cog", "pas",
      "zen", "odd", "nan", "lay", "pod", "fit", "hem", "joy", "bum", "rio",
      "yon", "dec", "leg", "put", "sue", "dim", "pet", "yaw", "nub", "bit",
      "bur", "sid", "sun", "oil", "red", "doc", "moe", "caw", "eel", "dix",
      "cub", "end", "gem", "off", "yew", "hug", "pop", "tub", "sgt", "lid",
      "pun", "ton", "sol", "din", "yup", "jab", "pea", "bug", "gag", "mil",
      "jig", "hub", "low", "did", "tin", "get", "gte", "sox", "lei", "mig",
      "fig", "lon", "use", "ban", "flo", "nov", "jut", "bag", "mir", "sty",
      "lap", "two", "ins", "con", "ant", "net", "tux", "ode", "stu", "mug",
      "cad", "nap", "gun", "fop", "tot", "sow", "sal", "sic", "ted", "wot",
      "del", "imp", "cob", "way", "ann", "tan", "mci", "job", "wet", "ism",
      "err", "him", "all", "pad", "hah", "hie", "aim"};

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
