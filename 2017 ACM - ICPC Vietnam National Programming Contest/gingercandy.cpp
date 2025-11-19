#include<bits/stdc++.h>
#define FOR(i,a,b) for (int i=(a),_b=(b);i<=_b;i=i+1)
#define FORD(i,b,a) for (int i=(b),_a=(a);i>=_a;i=i-1)
#define REP(i,n) for (int i=0,_n=(n);i<_n;i=i+1)
#define FORE(i,v) for (__typeof((v).begin()) i=(v).begin();i!=(v).end();i++)
#define ALL(v) (v).begin(),(v).end()
#define fi   first
#define se   second
#define MASK(i) (1LL<<(i))
#define BIT(x,i) (((x)>>(i))&1)
#define div   ___div
#define next   ___next
#define prev   ___prev
#define left   ___left
#define right   ___right
#define __builtin_popcount __builtin_popcountll
using namespace std;
template<class X,class Y>
    void minimize(X &x,const Y &y) {
        if (x>y) x=y;
    }
template<class X,class Y>
    void maximize(X &x,const Y &y) {
        if (x<y) x=y;
    }
template<class T>
    T Abs(const T &x) {
        return (x<0?-x:x);
    }

/** END OF TEMPLATE - ACTUAL SOLUTION COMES HERE **/

class DisjointSet {
	private:
	vector<int> label; 
	public:
	DisjointSet(){}
	DisjointSet(int n) {
		label.assign(n+7,-1); 
	}
	int find(int x) { 
		if (label[x]<0) return (x); 
		label[x]=find(label[x]);
		return (label[x]); 
	}
	bool join(int a,int b) { 
		int x=find(a);
		int y=find(b);
		if (x==y) return (false); 
		if (label[x]>label[y]) swap(x,y); 
		label[x]+=label[y];
		label[y]=x; 
		return (true);
	}
	int getSize(int x) { 
		return (-label[find(x)]);
	}
};


struct Edge {
    int u, v, c;

    Edge() {
        u = v = c = 0;
    }

    void input(void) {
        scanf("%d%d%d", &u, &v, &c);
    }

    int other(int x) const {
        assert(u == x || v == x);
        return u ^ v ^ x;
    }

    bool operator < (const Edge &e) const {
        return c < e.c;
    }
};

#define MAX   200200
const string NO_ANSWER = "Poor girl";

Edge edges[MAX];
vector<int> adj[MAX];
int dist[MAX];
int n, m, alpha;

void loadGraph(void) {
    scanf("%d%d%d", &n, &m, &alpha);
    FOR(i, 1, m) edges[i].input();
    sort(edges + 1, edges + m + 1);
    FOR(i, 1, m) {
        adj[edges[i].u].push_back(i);
        adj[edges[i].v].push_back(i);
    }
}

int findEdge(void) {
    DisjointSet dsu(n);
    FOR(i, 1, m) if (!dsu.join(edges[i].u, edges[i].v)) return i;
    return -1;
}

int bfs(int block) {
    int s = edges[block].u;
    int t = edges[block].v;

    memset(dist, -1, sizeof dist);
    queue<int> q;
    dist[s] = 0; q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        FORE(it, adj[u]) if (*it != block && edges[*it].c < edges[block].c) {
            int v = edges[*it].other(u);
            if (dist[v] < 0) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    assert(dist[t] >= 0);
    return dist[t];
}

void process(void) {
    int id = findEdge();
    if (id < 0) {
        cout << NO_ANSWER << endl;
        return;
    }

    int tmp = bfs(id);
    cout << 1LL * edges[id].c * edges[id].c + alpha * (tmp + 1) << endl;
}

int main(void) {
    loadGraph();
    process();
    return 0;
}