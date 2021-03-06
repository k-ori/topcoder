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
 
 9/3/2018
 
 13:53-14:19 AC (154.47 pt)
 
 Editorial:
  - https://www.topcoder.com/tc?module=Static&d1=match_editorials&d2=srm422
 
 */

int C[20][20]={};
int Pr[7]={2,3,5,7,11,13,17};
int Q[12]={0,1,4,6,8,9,10,12,14,15,16,18};

//int prs[100]={0,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,0,1};

/*
class PrimeSoccer {
public:
  double getProbability(int pa, int pb) {
    REP(i,20) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    double a=0.01*pa,b=0.01*pb;
    double P[2]={a,b};
    double X[2][2]={};
    REP(t,2) REP(i,19) {
      if (prs[i]==0) {
        // i-score
        X[t][0]+=C[18][i]*pow(P[t],i)*pow(1.0-P[t],18-i);
      } else {
        // i-score
        X[t][1]+=C[18][i]*pow(P[t],i)*pow(1.0-P[t],18-i);
      }
    }
    return 1.0-X[0][0]*X[1][0];
  }
};*/

class PrimeSoccer {
  public:
  double getProbability(int pa, int pb) {
    REP(i,20) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    double a=0.01*pa,b=0.01*pb;
    double P[2]={a,b};
    double X[2]={0,0};
    REP(t,2) REP(i,12) {
      int x=Q[i];
      X[t]+=C[18][x]*pow(P[t],x)*pow(1.0-P[t],18-x);
    }
    return 1.0-X[0]*X[1];
  }
};

class PrimeSoccer_org {
public:
  double getProbability(int pa, int pb) {
    REP(i,20) {
      C[i][0]=1;
      FORE(j,1,i) C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    double a=0.01*pa,b=0.01*pb;
    double P[2]={a,b};
    double X[2]={0,0};
    REP(t,2) REP(i,7) {
      int x=Pr[i];
      X[t]+=C[18][x]*pow(P[t],x)*pow(1.0-P[t],18-x);
    }
    return X[0]+X[1]-X[0]*X[1];
  }
};

// CUT begin
ifstream data("PrimeSoccer.sample");

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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(int skillOfTeamA, int skillOfTeamB, double __expected) {
    time_t startClock = clock();
    PrimeSoccer *instance = new PrimeSoccer();
    double __result = instance->getProbability(skillOfTeamA, skillOfTeamB);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        int skillOfTeamA;
        from_stream(skillOfTeamA);
        int skillOfTeamB;
        from_stream(skillOfTeamB);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(skillOfTeamA, skillOfTeamB, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1536007999;
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
        cout << "PrimeSoccer (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
