#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;
/*
 
 Union-find algorithm, O(α(N)) time per operation
 
  - Popular algorithm to manage disjoint set
 
 References:
  - https://en.wikipedia.org/wiki/Disjoint-set_data_structure
  - Ant book 2-4 data structures
  - CLRS 21 Data Structures for Disjoint Sets
 
 Usage:
 
  UF uf(10);
  uf.unite(0,1);
  uf.unite(1,2);
  cout << uf.sameset(0,1) << endl; // true
 
 */

struct UF {
public:
  int N,G/* # of disjoint sets */;
  UF(int N): N(N) { init(N); }
  void init(int N) {
    par=vector<int>(N),sz=vector<int>(N,1);
    for(int i=0; i<N; ++i) par[i]=i,sz[i]=1;
    G=N;
  }
  int find(int x) { return par[x]==x?x:par[x]=find(par[x]); }
  int size(int x) { return sz[find(x)]; }
  bool sameset(int x, int y) { return find(x)==find(y); }
  int unite(int x, int y) {
    x=find(x),y=find(y);
    if(x==y) return x;
    int p=x,c=y;
    if(sz[p]<sz[c]) swap(p,c);
    G--,sz[p]=sz[c]=sz[p]+sz[c];
    par[c]=p;
    return p;
  }
private:
  vector<int> par,sz;
};

int main(int argc, char const *argv[]) {
  UF uf(10);
  uf.unite(1,3);
  assert(uf.sameset(1,3));
  assert(uf.G==9);
  uf.unite(4,6);
  uf.unite(0,2);
  uf.unite(7,8);
  uf.unite(0,1);
  uf.unite(4,5);
  uf.unite(1,2);
  assert(uf.sameset(0,3));
  assert(uf.sameset(4,6));
  assert(uf.sameset(7,8));
  assert(uf.G==4);
}
// $ g++ -std=c++14 -Wall -O2 -D_GLIBCXX_DEBUG -fsanitize=address unionfind.cpp && ./a.out
