#include <fstream> // for greed plugin
#include <iostream>
#include <algorithm> // max,min
#include <vector>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <iostream>
#include <utility>
#include <cctype>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <limits.h>
#include <cstring>
#include <tuple>
#include <cassert>
#include <numeric>
using namespace std;
// type alias
typedef long long LL;
typedef vector < int > VI;
typedef unordered_map < int, int > MAPII;
typedef unordered_set < int > SETI;
typedef pair< int , int > II;
typedef tuple< int, int, int > III;
// repetition
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)
#define REPE(i,n)  for(int i=0;i<=(n);++i)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())
// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))
// minmax
#define SMAX(a,b) a = max(a,b)
#define SMIN(a,b) a = min(a,b)
// debug cout
#define TRACE true
#define dump(x) if(TRACE) { cout << #x << " = " << (x) << endl; }
#define dump2(x,y) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl; }
#define dump3(x,y,z) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl; }
#define dump4(x,y,z,a) if(TRACE) { cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl; }
#define dumpAR(ar) if(TRACE) { FORR(x,(ar)) { cout << x << ','; } cout << endl; }

/*
 
 2/21/2018
 
 9:37-9:47 ACC (218.40 pt)
 18:23-18:28 add greedy solution
 
 Editorials:
  - https://apps.topcoder.com/wiki/display/tc/SRM+528
  - http://purple-jwl.hatenablog.com/entry/20121020/1350714247
  - http://kujira16.hateblo.jp/entry/20111229/1325132490
  - http://topcodermania.blog.fc2.com/blog-entry-19.html
  - https://ddrer.exblog.jp/17393732/
 
 */

// greedy, O(N) time
class MinCostPalindrome {
public:
  int getMinimum(string S, int O, int X) {
    int N=SZ(S);
    int res=0;
    int l=0,r=N-1;
    while(l<r) {
      if(S[l]=='o'&&S[r]=='x') return -1;
      if(S[l]=='x'&&S[r]=='o') return -1;
      if(S[l]=='?'&&S[r]=='?') res+=2*min(O,X);
      if(S[l]=='?'&&S[r]=='o') res+=O;
      if(S[l]=='?'&&S[r]=='x') res+=X;
      if(S[l]=='o'&&S[r]=='?') res+=O;
      if(S[l]=='x'&&S[r]=='?') res+=X;
      ++l,--r;
    }
    return res;
  }
};

// brute-force, O(N*2^N) time
class MinCostPalindrome_org {
  public:
  int getMinimum(string S, int O, int X) {
    const int Inf=1e4;
    int N=SZ(S);
    int res=Inf;
    REP(mask,1<<N) {
      int x=0;
      
      int l=0,r=N-1;
      bool ok=true;
      while(l<r) {
        int a=(mask>>l)&1,b=(mask>>r)&1;
        if(a!=b) ok=false;
        ++l,--r;
      }
      if(!ok) continue;
      
      REP(i,N) {
        if((mask>>i)&1) {
          if(S[i]=='x') x=Inf;
          if(S[i]=='?') x+=O;
        } else {
          if(S[i]=='o') x=Inf;
          if(S[i]=='?') x+=X;
        }
      }
//      if(x<Inf) dump2(mask,x);
      res=min(res,x);
    }
    return res>=Inf?-1:res;
  }
};

// CUT begin
ifstream data("MinCostPalindrome.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(string s, int oCost, int xCost, int __expected) {
    time_t startClock = clock();
    MinCostPalindrome *instance = new MinCostPalindrome();
    int __result = instance->getMinimum(s, oCost, xCost);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        string s;
        from_stream(s);
        int oCost;
        from_stream(oCost);
        int xCost;
        from_stream(xCost);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(s, oCost, xCost, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1519234641;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "MinCostPalindrome (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
