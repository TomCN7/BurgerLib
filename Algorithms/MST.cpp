int n;
#define MAXN 1005
int G[MAXN][MAXN];  //Graph
vector<pair<int,int> >edges;   // a lot of memory
vector<bool> mark;  //marks whether the edge is in MST
int f[MAXN];  //set; 
int find(int x){
	if(x!=f[x]) return f[x]=find(f[x]);
	return f[x];
}
void myunion(int x, int y){
	f[find(x)]=f[find(y)];
}
bool cmp(pair<int,int> x, pair<int,int> y){
	return G[x.first][x.second] < G[y.first][y.second];
}
void MST_KRUSKAL(){  //可以是最小生成树，也可以是最大生成树
	for(int i=0; i<n; i++){
		f[i] = i;
		for(int j=0; j<n; j++)
			edges.push_back(make_pair(i,j));
	}
	sort(edges.begin(), edges.end(), cmp);
	mark.resize(SZ(edges), false);
	for(int i=0, _I(SZ(edges)); i<_I; i++){
		if(find(edges[i].first) == find(edges[i].second))
			continue;
		myunion(edges[i].first, edges[i].second);
		mark[i] = true;
	}
}

//以邻接边为组织形式
int n;		//input 1
#define MAXN 1005
vector<pair<pair<int,int>,int> >edges;   //  input 2(needn't be sorted)
vector<bool> mark;  //marks whether the edge is in MST
int f[MAXN];  //set; 
int find(int x){
	if(x!=f[x]) return f[x]=find(f[x]);
	return f[x];
}
void myunion(int x, int y){
	f[find(x)]=f[find(y)];
}
bool cmp(pair<pair<int,int>,int> &x, pair<pair<int,int>,int> &y){
	return x.second < y.second;
}
void MST_KRUSKAL(){  //可以是最小生成树，也可以是最大生成树
	for(int i=0; i<n; i++){
		f[i] = i;
	}
	sort(edges.begin(), edges.end(), cmp);
	mark.resize(SZ(edges), false);
	for(int i=0, _I(SZ(edges)); i<_I; i++){
		if(find(edges[i].first.first) == find(edges[i].first.second))
			continue;
		myunion(edges[i].first.first, edges[i].first.second);
		mark[i] = true;
	}
}

//两种方式
//1. 对所有的相邻边做heap
int n;
#define MAXN 1005
int G[MAXN][MAXN];  //Graph
bool visited[MAXN];  //mark whether the node has been visited
vector<pair<int,int> > mst;  //edges in final MST
class cmp:public greater<pair<PII,int> >{
public:
	bool operator()(const pair<PII,int> &x, const pair<PII,int> &y){
		return x.second < y.second;
	}
};
priority_queue<pair<PII, int>, vector<pair<PII,int> >, cmp>   heap;   //pair<pair<node I, node j>, weight>
void MST_PRIM(int s){  //take node s as the start point
	visited[s] = true;  
	for(int i=0; i<n; i++) 
		if(G[s][i])
			heap.push(make_pair(make_pair(s,i),G[s][i]));
	int nodes_checked = 1; 
	while(nodes_checked < n && !heap.empty()){
		pair<PII,int> _t = heap.top();  heap.pop();
		if(visited[_t.first.second]) continue;
		mst.push_back(_t.first);
		visited[_t.first.second] = true;  
		for(int i=0; i<n; i++)
			if(G[_t.first.second][i] && visited[i]==false)
				heap.push(make_pair(make_pair(_t.first.second, i), 
				　　　　				G[_t.first.second][i]));
		nodes_checked ++;
	}
}
//2. 只对定点做heap
int n;
#define MAXN 1005
int G[MAXN][MAXN];  //graph
int parent[MAXN];  //parent of x in mst is parent[x]
int dist[MAXN];
void MST_PRIM(int s){
	for(int i=0; i<n; i++) 
		if(i!=s) 	dist[i] = PINF;
	for(int i=0; i<n; i++) 
		if(i!=s)	dist[i] = min(dist[i], G[s][i]);
	parent[s] = -1;  dist[s] = 0;
	int checked = 1;
	while(checked < n){
		int next = -1;
		for(int i=0; i<n; i++) 
			if(dist[i]!=0){ //unchecked
				if(next == -1 || dist[next]<dist[i])
					next = i;
			}
			dist[next] = 0;
			for(int i=0; i<n; i++) 
				if(dist[i]!=0 && G[next][i]>0 && G[next][i]<dist[i]){ 
					dist[i] = G[next][i];  parent[i] = next;
				}
				checked++;
	}
}