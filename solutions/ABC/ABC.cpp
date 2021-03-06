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
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n)  for(int i=0;i<(n);++i)
#define FORR(x,arr) for(auto& x:arr)
#define SZ(a) int((a).size())

// DP
#define MINUS(dp) memset(dp, -1, sizeof(dp))
#define ZERO(dp) memset(dp, 0, sizeof(dp))

// debug cout
#define dump(x)  cout << #x << " = " << (x) << endl;
#define dump2(x,y)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << endl;
#define dump3(x,y,z)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << endl;
#define dump4(x,y,z,a)  cout << #x << " = " << (x) << ", " << #y << " = " << (y) << ", " << #z << " = " << (z) << ", " << #a << " = " << (a) << endl;
#define dumpAR(ar) FORR(x,(ar)) { cout << x << ','; } cout << endl;

/*
 
 9/7/2017
 
 10:04-10:33 system test passed (578.67 pt)
 
 recurrence relation:
 
 f(i,a,b,k) = f(i-1,a+1,  b,k-b-c) + "A"
            ∪ f(i-1,  a,b+1,  k-b) + "B"
            ∪ f(i-1,  a,  b,    k) + "C"
            ∪ "#"
 
 f(0,_,_,k) = k==0 ? "" : "#"
 
 res = f(N,0,0,K)
 
 editorials:
  - http://kmjp.hatenablog.jp/entry/2015/02/06/1030
  - http://torus711.hatenablog.com/entry/20150209/1423488810
  - https://twitter.com/evima0/status/562246452441661441
    - writer's comment
  - http://roiti46.hatenablog.com/entry/2015/02/02/TopCoder_SRM_648_Div2
    - greedy
 
 div1 easy (easier version of div2 hard) editorial:
  - http://purple-jwl.hatenablog.com/entry/2015/02/02/230755
   - both dp AND greedy
  - http://sucrose.hatenablog.com/entry/2015/02/02/235957
   - greedy
  - http://torus711.hatenablog.com/entry/20150203/1422972945
   - dp
  - http://kmjp.hatenablog.jp/entry/2015/02/06/1000
   - greedy

 submit solutions:
  - greedy
    - https://community.topcoder.com/stat?c=problem_solution&rm=325029&rd=16312&pm=13645&cr=22867887
  - dp
    - https://community.topcoder.com/stat?c=problem_solution&rm=325004&rd=16312&pm=13645&cr=23320202
    - https://community.topcoder.com/stat?c=problem_solution&rm=325005&rd=16312&pm=13645&cr=23305191
    - https://community.topcoder.com/stat?c=problem_solution&rm=325003&rd=16312&pm=13645&cr=23197675
 
 key:
  - typical DP
  - easier version of div1 easy
  - greedy may be a bit complex
 
 summary:
  - figured out state transition of DP quickly
  - missed to memoize in the last case
  - somehow misunderstood if result should be reversed or not
  - string dp table may be a bit expensive
 
 22:30-22:55 add iterative DP backtrack solution
 
*/

int dp[31][31][31][436];
class ABC {
public:
  bool test(string s, int K) {
    int cnt=0,N=SZ(s);
    REP(j,N)REP(i,j) if(s[i]<s[j]) ++cnt;
    if(cnt!=K) dump3(s,cnt,K);
    return cnt==K;
  }
  
  string createString(int N, int K) {
    MINUS(dp);
    
    dp[0][0][0][0]=0;
    REP(i,N) REP(a,N+1)REP(b,N+1)REP(k,K+1) if(dp[i][a][b][k]>=0) {
      int c=i-a-b;
//      if(a+b+c>i) continue;
      if(a+1<=N)dp[i+1][a+1][b][k]=1;
      if(b+1<=N&&k+a<=K)dp[i+1][a][b+1][k+a]=2;
      if(c+1<=N&&k+a+b<=K)dp[i+1][a][b][k+a+b]=3;
    }
    
    string res;
    REP(A,N+1)REP(B,N+1) if(dp[N][A][B][K]>0) {
      res="";
      int a=A,b=B,i=N,k=K;
      while(i) {
        if(dp[i][a][b][k]==1) res.push_back('A'),--a;
        else if(dp[i][a][b][k]==2) res.push_back('B'),--b,k-=a;
        else if(dp[i][a][b][k]==3) res.push_back('C'),k-=a+b;
        else assert(false);
        --i;
      }
    }
    reverse(res.begin(),res.end());
    if(res!="") assert(test(res,K));
    
    return res;
  }
};

string memo[31][31][31][436];
class ABC_memo {
  public:
  int N;
  string f(int i, int a, int b, int k) {
    if(k<0) return "#";
    if(i==0) return k==0?"":"#";
    if(!memo[i][a][b][k].empty()) return memo[i][a][b][k];
    int c=N-i-a-b;
    assert(c>=0);
    
    string sa=f(i-1,a+1,b,k-b-c);
    if(sa!="#") return memo[i][a][b][k]=sa+"A";
    string sb=f(i-1,a,b+1,k-c);
    if(sb!="#") return memo[i][a][b][k]=sb+"B";
    string sc=f(i-1,a,b,k);
    if(sc!="#") return memo[i][a][b][k]=sc+"C";
    return memo[i][a][b][k]="#";
  }
  
  bool test(string s, int K) {
    int cnt=0,N=SZ(s);
    REP(j,N)REP(i,j) if(s[i]<s[j]) ++cnt;
    if(cnt!=K) dump3(s,cnt,K);
    return cnt==K;
  }
  
  string createString(int N, int K) {
    this->N=N;
    REP(i,31)REP(a,31)REP(b,31)REP(k,436) memo[i][a][b][k]="";
    string res = f(N,0,0,K);
    if(res=="#") return "";
    
    if(res!="") {
      assert(test(res,K));
    }
    
    return res;
  }
};

// CUT begin
ifstream data("ABC.sample");

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

bool do_test(int N, int K, string __expected) {
    time_t startClock = clock();
    ABC *instance = new ABC();
    string __result = instance->createString(N, K);
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
        int N;
        from_stream(N);
        int K;
        from_stream(K);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1504803874;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "ABC (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
