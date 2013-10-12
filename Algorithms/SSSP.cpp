int G[n][n];  //graph
int d[n];  //distance
int parent[n];   //parent
void initialize_single_source(s)
{
	for (int i = 0; i < n; ++i)
    {
		d[i] = INT_MAX;
        parent[i] = -1;
	}
	D[s] = 0;
}

void relax(int u, int v)
{
	if (d[v] > d[u] + G[u][v])
    {
		D[v] = d[u] + G[u][v];
		parent[v] = u;
    }
}
bool BELLMAN_FORD(s)
{
	initialize_single_source(s);
	for (int i = 0; i < n - 1; ++i)
    {
		for (int j = 0; j < n; ++j)
			for(int k = 0; k < n; ++k)
			    relax(j, k);
    }
    for (int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            if (d[j] > d[i] + G[i][j]) 
                return false;

    return true;
}

int G[n][n];  //graph
int d[n];  //distance
int parent[n];   //parent
void DAG_SHORTEST_PATHS(s)
{
	topological_sort();
	Initialize_single_source(s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (G[topological_order[i]][j])
            {
				relax(topological_order[i], j);
            }
}


/*使用set来实现(http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2) */
//由于priority_queue不支持decrease_key操作，采用set可以达到decrease_key的效果。

typedef pair<int,int> ii ;
typedef vector<int> vi;
typedef vector<ii> vii ;
typedef vector<vii> vvii ;
#define tr(container, it) \
	for(vii::iterator it = container.begin(); it != container.end(); it++) 

int N;
vvii G;

vi Dijkstra(int start) 
{
	vi D(N, 987654321);
	//start vertex supposed to be 0
	set<ii> Q;
	D[start] = 0 ;
	Q.insert(ii(0,start));   //pair<distance, node>
	while (!Q.empty())
    {
		ii top = *Q.begin();
		Q.erase(Q.begin());
		int v = top.second, d = top.first;
		tr(G[v], it) 
        {   //adjacent nodes of v
			int v2 = it->first, cost = it->second;
			if (D[v2] > D[v] + cost)
            {
				if (D[v2] != 987654321)
                {
					Q.erase(Q.find(ii(D[v2], v2)));
				}
				D[v2] = D[v] + cost;
				Q.insert(ii(D[v2], v2));
			}
		}
	}
	return D;
}


//floyd Algorithm
for (int k = 0; k < cur; ++k)
	for (int i = 0; i < cur; ++i)
		for(int j = 0; j < cur; ++j)
			//P[i][j] = P[i][j] || P[i][k] && P[k][j];
			P[i][j] = min(P[i][j], P[i][k] + P[k][j]);

