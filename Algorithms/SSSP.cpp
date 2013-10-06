Int G[n][n];  //graph
Int d[n];  //distance
Int parent[n];   //parent
Void initialize-single-source(s){
	For(int i=0; i<n; i++){
		D[i] = PINF;  parent[i] = -1;
	����}
	����D[s] = 0;
}
Void relax(int u, int v){
	If(d[v] > d[u]+G[u][v]){
		D[v] = d[u]+G[u][v];
		Parent[v] = u;
	������}
}
bool BELLMAN-FORD(s){
	Initialize-single-source(s);
	For(int i=0; i<n-1; i++){
		For(int j=0; j<n; j++)
			For(int k=0; k<n; k++)
			Relax(j,k);
	������}
	������For(int i=0; i<n; i++)
		   ������   For(int j=0; j<n; j++)
				 ������      If(d[j] > d[i]+G[i][j]) return false;
	   ������Return true;
}


Int G[n][n];  //graph
Int d[n];  //distance
Int parent[n];   //parent
Void DAG-SHORTEST-PATHS(s){
	Topological-sort();
	Initialize-single-source(s);
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			if(G[topological_order[i]][j]){
				relax(topological_order[i], j);
			��������������}
}



/*ʹ��set��ʵ��(http://www.topcoder.com/tc?module=Static&d1=tutorials&d2=standardTemplateLibrary2) */
//����priority_queue��֧��decrease_key����������set���Դﵽdecrease_key��Ч����

typedef pair<int,int> ii ;
typedef vector<int> vi;
typedef vector<ii> vii ;
typedef vector<vii> vvii ;
#define tr(container, it) \
	for(vii::iterator it = container.begin(); it != container.end(); it++) 

int N;
vvii G;

vi Dijkstra(int start) {
	vi D(N, 987654321) ;
	//start vertex supposed to be 0
	set<ii> Q ;
	D[start] = 0 ;
	Q.insert(ii(0,start));   //pair<distance, node>
	while(!Q.empty()){
		ii top = *Q.begin();
		Q.erase(Q.begin());
		int v = top.second, d = top.first;
		tr(G[v],it){   //adjacent nodes of v
			int v2 = it->first, cost = it->second;
			if(D[v2] > D[v]+cost){
				if(D[v2] != 987654321){        
					Q.erase(Q.find(ii(D[v2],v2)));
				}
				D[v2] = D[v] + cost;
				Q.insert(ii(D[v2],v2));
			}
		}
	}
	return D;
}


//floyd Algorithm
for(int k=0; k<cur; k++)
for(int i=0; i<cur; i++)
for(int j=0; j<cur; j++)
P[i][j] = P[i][j] || P[i][k]&&P[k][j];
P[i][j] = min(P[i][j], P[i][k]+P[k][j]);