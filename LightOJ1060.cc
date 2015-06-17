// LightOJ 1060: nth Permutation
// http://www.lightoj.com/volume_showproblem.php?problem=1060
// 
// solution: nth_permutation
// 
// Permutation Index (possibly duplicates)
//
// Description:
//   nth_permutation(x,k) = next_permutation^k(x),
//   and rank_permutation is the inverse of nth_permutation.
//
// Algorithm:
//   The lexicographically smallest permutation whose first letter
//   is specified is computed by the multinomial coefficient.
//
// Complexity:
//   O(|length|^2)
//
// Verify: 
//   LightOJ 1060: nth Permutation (only for nth_permutation)

#include <cstring>
#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

#define fst first
#define snd second
#define all(c) ((c).begin()), ((c).end())

typedef long long ll;

#define FOR(i,x) for(__typeof(x.begin()) i=x.begin();i!=x.end();++i)

// n-th permutation of sort(x) in O(|x|^2)
template <class T>
vector<T> nth_permutation(vector<T> x, ll n) {
  map<T, ll> count;
  //for (T a: x) ++count[a];
  FOR(i,x) ++count[*i];
  for (int i = 0; i < x.size(); ++i) {
    ll coef = 1, tot = 0, last = 0;
    FOR(j,count) { pair<T,ll> p = *j;
    //for (auto p: count) 
      for (ll b = 1; b <= p.snd; ++b) 
        coef = (++tot * coef) / b;
    }
    if (n >= coef) return vector<T>(); //{};
    //for (auto &p: count) {
    FOR(j,count) {
      if (j->snd == 0) continue;
      ll step = (coef * j->snd) / tot;
      if (n < step) { x[i] = j->fst; j->snd -= 1; break; }
      /*
      ll step = (coef * p.snd) / tot;
      if (n < step) { x[i] = p.fst; p.snd -= 1; break; }
      */
      n -= step;
    }
  }
  return x;
}
// rank of the permutation of x in O(|x|^2)
// nth_permutation(x, rank_permutation(x)) == x
/*
template <class T>
ll rank_permutation(vector<T> x) {
  ll rank = 0;
  map<T, ll> count;
  for (T a: x) ++count[a];
  for (int i = 0; i < x.size(); ++i) {
    ll coef = 1, tot = 0, last = 0;
    for (auto p: count) 
      for (ll b = 1; b <= p.snd; ++b) 
        coef = (++tot * coef) / b;
    for (auto &p: count) {
      pair<T,ll> p = *j;
      ll step = (coef * p.snd) / tot;
      if (x[i] == p.fst) { p.snd -= 1; break; } 
      rank += step;
    }
  }
  return rank;
}
*/

int main() {
  int ncase; scanf("%d", &ncase);
  for (int icase = 0; icase < ncase; ++icase) {
    printf("Case %d: ", icase+1);
    int n;
    char s[1024]; scanf("%s %d", s, &n);
    vector<char> x;
    for (int i = 0; i < strlen(s); ++i)
      x.push_back(s[i]);
    x = nth_permutation(x, n-1);
    if (x.empty()) printf("Impossible\n");
    else {
      FOR(i,x) printf("%c", *i);
      //for (auto a: x) printf("%c", a);
      printf("\n");
    }
  }
}
