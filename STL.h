#ifndef UNTITLED22_STL_H
#define UNTITLED22_STL_H

// H. Большая политика

/*
#include <queue>
#include <vector>
#include <iostream>

int main() {
  std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
  int n = 0;
  std::cin >> n;
  for (int i = 0; i < n; i++) {
    int num = 0;
    std::cin >> num;
    pq.push(num);
  }
  int64_t ans = 0;
  while (!pq.empty()) {
    int f = pq.top();
    pq.pop();
    int s = pq.top();
    pq.pop();
    if (pq.empty()) {
      ans += f + s;
      break;
    }
    ans += f + s;
    pq.push(f + s);
  }
  std::cout << ans;
  return 0;
}
*/


// I. Номер появления слова


/*
#include <iostream>
#include <unordered_map>
#include <string>

int main() {
  std::unordered_map<std::string, int> mp;
  std::string s;
  while (std::cin >> s) {
    std::cout << mp[s] << ' ';
    mp[s]++;
  }
  return 0;
}
*/

// J. Частотный анализ
/*
 #include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

static bool Comp(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
 if (a.second != b.second) {
   return a.second > b.second;
 }
 return a.first < b.first;
}
int main() {
 std::unordered_map<std::string, int> mp;
 std::string s;
 while (std::cin >> s) {
   mp[s]++;
 }
 std::vector<std::pair<std::string, int>> ans(mp.begin(), mp.end());
 sort(ans.begin(), ans.end(), Comp);
 for (auto& pair : ans) {
   std::cout << pair.first << '\n';
 }
 return 0;
}
*/

// K. Пароли

/*
 #include <iostream>
#include <vector>
#include <string>

int main() {
 int n = 0;
 std::cin >> n;
 std::vector<std::string> arr(n);
 int i = 0;
 while (i < n) {
   std::string s;
   std::cin >> s;
   arr[i] = s;
   i++;
 }
 int count = 0;
 for (int i = 0; i < n; ++i) {
   for (int j = 0; j < n; ++j) {
     if (i != j && arr[j].find(arr[i]) != std::string::npos) {
       count++;
     }
   }
 }
 std::cout << count << '\n';
 return 0;
}
*/
#endif  // UNTITLED22_STL_H
