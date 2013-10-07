/*ford-fulkerson方法*/
int G[n][n];  //input graph
int F[n][n];  //flow graph?: all initialized to 0
void Ford_Fulkerson(int s, int t){
    vector<int> path;
    while (findPath(s, t, path))
    {
        int minC;
        for(int _i = 0, _n = path.size(); _i < _n - 1; ++_i)
        {
            minC = min(minC, G[path[_i]][path[_i + 1]] – F[path[_i]][path[_i + 1]]);
        }
        for(int _i = 0, _n = path.size(); _i < _n - 1; ++_i)
        {
            F[path[_i]][path[_i + 1]] += minC;
            F[path[_i + 1]][path[_i]] -= minC;
        }
    }
}

int R[n][n];  //residual graph; R[x][y]=G[x][y]-F[x][y];
/*使用DFS寻找增广路径*/
bool findPath(int s, int t, vector<int> &path){
    for(int i = 0; i < n; ++i)
        if(R[s][i])
        {
            if(i==t)
            {
                path.push_back(s and t); 
                return true;
            }
            Path.push_back(s);
            if (findPath(I, t)) return true;
            Path.pop_back(s);
        }
    return false;
}

//使用BFS寻找增广路径  Edmonds-Karp  O(V*E^2)
bool findPath(int s, int t, vector<int> &path)
{
    vector<bool> mark;  mark[s] = mark[t] = true;
    vector<pair<int,int> > Q;
    //使用vector而不是queue，是为了保存路径
    Q.push_back(make_pair(-1, s));
    int idx = 0;
    bool found = false;
    while (found == false && idx < SZ(Q))
    {
        int _s = Q[idx].second;
        for (int _i = 0; _i < n; ++_i)
            if (R[_s][_i])
            {
                if(_i == t) 
                {
                    Q.push_back(MP(_s,t)); 
                    found = true; 
                    break;
                }
                Q.push_back(MP(_s, _i));
            }
    }
    if (found == false) 
        return false;
    idx = SZ(Q) - 1;
    while (Q[idx].first > 0)
    {
        Path.push_back(Q[idx].second);
        idx = Q[idx].first;
    }
    Path.push_back(s);  
    reverse(path.begin(), path.end());

    return true;
}


//*relabel_to_front算法     O(V^3)
#define MAXN  1005
int n;	//number of nodes in graph
int G[MAXN][MAXN];  //input graph
int F[MAXN][MAXN];  //flow graph : all initialized to 0
int e[MAXN], h[MAXN];   //excess amount ; height function
vector<list<int>::iterator> current ;  //neighbour iterator
vector<list<int> > neighbour ;

void initialize_preflow(int s)
{
	for (int i = 0; i < n; ++i)
    {
		h[i] = e[i] = 0 ;
	}
	h[s] = n ;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			F[i][j] = 0;
	for (int i = 0; i < n; ++i)
		if (G[s][i])
        {
			F[s][i] = G[s][i];    
            F[i][s] = -G[s][i];
			e[i] = G[s][i];   
            e[s] = e[s] - G[s][i];
		}
}

void push(int u, int v){
	int amount = min(e[u], G[u][v] - F[u][v]);
	F[u][v] += amount ;
	F[v][u] = -F[u][v] ;
	e[u] -= amount ;
	e[v] += amount ;
}

void relabel(int u)
{
	int height = PINF;
	for (int i = 0; i < n; ++i)
		if (i != u && G[u][i] - F[u][i] > 0 && h[i] < height) 
			height = h[i];

    h[u] = 1 + height;
}

void discharge(int u)
{
	while (e[u] > 0)
    {
		list<int>::iterator it = current[u];
		if (it == neighbour[u].end())
        {
			relabel(u);   
            current[u] = neighbour[u].begin();
		}
		else if (G[u][*it] - F[u][*it] > 0 && h[u] == h[*it] + 1)
        {
			push(u, *it);
		}
		else current[u]++;
	}
}

int Relabel_to_Front (int s, int t)
{
	initialize_preflow(s);
	list<int> LN;
	current.resize(n);   
    neighbour.resize(n);
	for (int i = 0; i < n; i++)
		for (int j=0; j<n; j++)
			if(G[i][j] || G[j][i]) neighbour[i].push_back(j);
	for (int i = 0; i < n; i++)
		if (i != s && i != t) 
        {
			LN.push_back(i);
			current[i] = neighbour[i].begin();
		}
		list<int>::iterator it(LN.begin());
		while (it != LN.end())
        {
			int u = *it, old_height = h[u];
			discharge(u);
			if (h[u] > old_height)
            {
				LN.erase(it); 
				LN.push_front(u);
				it = LN.begin();
			}
			it++;
		}
    return e[t];
}



/*dinic算法*/  

#include <iostream>
#include <vector>
using namespace std;

#define MAXN 20010
#define inf 0x7fffffff
struct node {
	int next, c, f, other;
	node(int _n, int _c, int _f, int _o):next(_n), c(_c), f(_f), other(_o){}
};

vector<node> G[MAXN]; // 原图; stored using adjacency list; 也是残图
vector<int> lever_map[MAXN]; // 层次图

int que[MAXN*1], lever[MAXN], pre[MAXN], hash[MAXN], d[MAXN];
int s, t;
void init() {
	for(int i = s;i <= t; i++)	 G[i].clear();
}

void add(int u, int v, int c) {   //edge(u,v); capacity c
	G[u].push_back(node(v, c, 0, G[v].size()));
	G[v].push_back(node(u, 0, 0, G[u].size()-1));
}

bool bulid() {
	int head = 0, tail = 0, cur, next, i, j;
	for(i = s; i <= t; i++) lever_map[i].clear();
	memset(lever, -1, sizeof(lever));

    que[tail++] = s;
	lever[s] = 0;
	while (head < tail) 
    {
	    cur = que[head++];
		for (i = 0; i < G[cur].size(); ++i) 
        {
		    node N = G[cur][i];
			if (N.c > N.f) 
            {
			    if (lever[N.next] == -1)
                {
				    que[tail++] = N.next;
					lever[N.next] = lever[cur] + 1;
				}
				if (lever[N.next] == lever[cur] + 1) 
                {
				    lever_map[cur].push_back(i);
                }
			}
		}
	}

    return lever[t] != -1;
}

int Dinic() {
	int i, j, ans = 0, len, tmp;

	while (bulid()) 
    {
		memset(hash, 0, sizeof(hash));
		while (!hash[s]) 
        {
			d[s] = inf;
			pre[s] = -1;
			for (i = s; i != t && i != -1; i = j) 
            {
				len = lever_map[i].size();
				while (len && hash[map[i][lever_map[i][len - 1]].next])
				{ 
                    lever_map[i].pop_back();
                    len--;
                }
				if (!len) 
                {
					hash[i] = 1;
					j = pre[i];
					continue;
				}
				j = G[i][lever_map[i][len-1]].next;
				pre[j] = i;
				d[j] = min(d[i], G[i][lever_map[i][len - 1]].c - G[i][lever_map[i][len-1]].f);
			}
			if (i == t) 
            {
				ans += d[t];
				tmp = d[t];
				while (i != s) 
                {
					j = pre[i];
					len = lever_map[j][lever_map[j].size() - 1];
					G[j][len].f += tmp;
					if (G[j][len].f == G[j][len].c)
						lever_map[j].pop_back();
					G[i][map[j][len].other].f -= tmp;
					i = j;
				}
			}
		}
	}
	return ans;
}

//Another DINIC     checked already!
#define PINF (1<<30)
vector<vector<int> > G;	//graph;  原图
int n, s, t;		//node number, source, destination

bool construct(vector<vector<int> > &F, vector<vector<int> > &L)
{
	vector<int> label(G.size(), -1);
	for (int i = 0; i < n; ++i) 
        L[i].clear();
	queue<int> Q;
    Q.push(s);
    label[s] = 0;
	while (!Q.empty())
    {
		int cur = Q.front();  Q.pop();
		for (int i = 0, _I(G[cur].size()); i < _I; ++i)
        {
			if (F[cur][i] < G[cur][i])
            {
				if (label[i] < 0)
                {
					Q.push(i);
                    label[i] = label[cur] + 1;
				}

				if (label[i] == label[cur] + 1)
                    L[cur].push_back(i);
			}
		}
	}

	return label[t] >= 0;
}

long long dinic()
{
	vector<vector<int> > F(G.size(), vector<int>(G.size(), 0));  //flow graph
	vector<vector<int> > L(G.size());  //level graph;  store edges
	long long flow = 0;
	while (construct(F, L))
    {
		vector<bool> mark(G.size(), false);  //visit back
		while (mark[s] == false)
        {
			vector<int> d(G.size(), PINF);  //delta
			vector<int> pre(G.size(), -1);
			int i, j;
			for (i = s; i != t && i != -1; i = j)
            {
				int len = L[i].size();
				while (len && mark[L[i][len - 1]])
                { 
                    len--;
                    L[i].pop_back(); 
                }
				if (!len)
                { 
                    mark[i] = true;
                    j = pre[i];
                    continue;
                }
				j = L[i][len - 1];
                pre[j] = i;
				d[j] = min(d[i], G[i][j] - F[i][j]);
			}
			if (i == t)
            {
				flow += d[t];   
				while (i != s)
                {
					j = pre[i];
                    F[j][i] += d[t];
                    F[i][j] -= d[t];
					if (F[j][i] == G[j][i])
                        L[j].pop_back();
					i = j;
				}
			}
		}
	}

    return flow;
}
