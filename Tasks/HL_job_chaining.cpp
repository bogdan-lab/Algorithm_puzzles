#include <algorithm>
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Job {
  int id = 0;
  int time = 0;
  int next = 0;
};

struct Chain {
  int start_id = 0;
  int last_id = 0;
  int total_time = 0;
  int job_num = 0;
};

std::string ToTime(int val) {
  int h = val / 3600;
  val -= h * 3600;
  int m = val / 60;
  std::ostringstream os;
  os << std::setfill('0') << std::setw(2) << h << ":" << std::setfill('0')
     << std::setw(2) << m << ":" << std::setfill('0') << std::setw(2)
     << val - m * 60;
  return os.str();
}

void PrintChain(const Chain& ch) {
  std::cout << "start_id: " << ch.start_id << '\n'
            << "last_id: " << ch.last_id << '\n'
            << "job_num: " << ch.job_num << '\n'
            << "total_time: " << ToTime(ch.total_time) << '\n'
            << "average_time: " << ToTime(ch.total_time / ch.job_num) << '\n';
}

bool ToInt(std::string_view str, int& val) {
  try {
    val = std::stoi(std::string(str));
    return true;
  } catch (...) {
    return false;
  }
}

bool ParseJob(std::string_view str, Job& job) {
  size_t prev_pos = 0;
  size_t pos = str.find(',', prev_pos);
  if (!ToInt(str.substr(0, pos), job.id)) {
    return false;
  }
  prev_pos = pos + 1;
  pos = str.find(',', prev_pos);
  if (!ToInt(str.substr(prev_pos, pos - prev_pos), job.time)) {
    return false;
  }
  if (!ToInt(str.substr(pos + 1), job.next)) {
    return false;
  }
  return true;
}

void PrintMalfromed() { std::cout << "Malformed Input\n"; }

void DFS(const std::unordered_map<int, int>& data, int id,
         std::unordered_set<int>& lookup, std::vector<int>& ordered_ids,
         bool& error_flag) {
  if (id == 0 || lookup.find(id) != lookup.end()) return;
  lookup.insert(id);
  auto it = data.find(id);
  if (it == data.end()) {
    error_flag = true;
    return;
  }
  DFS(data, it->second, lookup, ordered_ids, error_flag);
  ordered_ids.push_back(id);
}

bool TopologicalSort(const std::unordered_map<int, int>& data,
                     std::vector<std::vector<int>>& chain_rows) {
  std::unordered_set<int> lookup;
  std::vector<int> ordered_ids;
  ordered_ids.reserve(data.size());
  for (const auto& el : data) {
    if (lookup.find(el.first) != lookup.end()) continue;
    bool error_flag = false;
    DFS(data, el.first, lookup, ordered_ids, error_flag);
    if (error_flag) return false;
  }
  std::reverse(ordered_ids.begin(), ordered_ids.end());

  lookup.clear();
  for (int i = 0; i < ordered_ids.size(); ++i) {
    if (lookup.find(ordered_ids[i]) != lookup.end()) continue;
    lookup.insert(ordered_ids[i]);
    // here we are at the beginning of the new chain
    auto& back = chain_rows.emplace_back();
    back.push_back(ordered_ids[i]);
    int next_id = 0;
    auto it = data.find(ordered_ids[i]);
    if (it == data.end()) {
      return false;
    } else {
      next_id = it->second;
    }
    while (next_id != 0) {
      back.push_back(next_id);
      if (lookup.find(next_id) != lookup.end()) {
        return false;
      }
      lookup.insert(next_id);
      it = data.find(next_id);
      if (it == data.end()) {
        return false;
      } else {
        next_id = it->second;
      }
    }
  }
  return true;
}

void PrepareTestInput(const std::string& filename) {
  // Note that 0 signals that current job is last in the chain
  std::ofstream fout(filename);
  if (!fout.is_open()) {
    throw(std::runtime_error("Cannot create test file"));
  }
  fout << R"(#job_id,runtime_in_seconds,next_job_id
1,30,23
2,15,3
3,45,0
23,10,0)";
}

int main() {
  std::string filename = "test.txt";
  PrepareTestInput(filename);
  std::ifstream fin{filename};
  if (!fin.is_open()) {
    PrintMalfromed();
    return 0;
  }
  std::string buffer;
  if (!std::getline(fin, buffer)) {
    PrintMalfromed();
    return 0;
  }
  if (buffer != "#job_id,runtime_in_seconds,next_job_id") {
    PrintMalfromed();
    return 0;
  }
  Job buff_job;
  std::unordered_map<int, Job> all_jobs;
  std::unordered_map<int, int> connections;
  while (std::getline(fin, buffer)) {
    if (!ParseJob(buffer, buff_job)) {
      PrintMalfromed();
      return 0;
    }
    all_jobs.insert({buff_job.id, buff_job});
    auto it = connections.find(buff_job.id);
    if (it != connections.end()) {
      PrintMalfromed();
      return 0;
    }
    connections[buff_job.id] = buff_job.next;
  }

  std::vector<std::vector<int>> chain_ids;
  if (!TopologicalSort(connections, chain_ids)) {
    PrintMalfromed();
    return 0;
  }

  std::vector<Chain> all_chains;
  for (const auto& el : chain_ids) {
    auto& back = all_chains.emplace_back();
    assert(!el.empty());
    back.start_id = el.front();
    back.last_id = el.back();
    back.job_num = el.size();
    back.total_time = 0;
    for (const auto& id : el) {
      auto it = all_jobs.find(id);
      assert(it != all_jobs.end());
      back.total_time += it->second.time;
    }
  }

  std::sort(all_chains.begin(), all_chains.end(),
            [](const Chain& lhs, const Chain& rhs) {
              return lhs.total_time > rhs.total_time;
            });

  std::cout << "-\n";
  for (const auto& el : all_chains) {
    PrintChain(el);
    std::cout << "-\n";
  }

  return 0;
}
