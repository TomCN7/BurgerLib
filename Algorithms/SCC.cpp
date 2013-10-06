int time ;	//search from here 	
vector<int> color, parent, start, finish ;
vector<vector<bool> > G ;		//this is the only input
vector<vector<bool> > GT ;		//this is the only input
list<pair<int,int> > topological_order ;
void DFS_VISIT(int u){ //depth first search
	color[u] = 1 ;  //gray
	time++ ;
	start[u]=time ;   //start time
	REPI(i,0,SZ(G[u]))
		if(G[u][i] && color[i]==0){
			parent[i]=u ;  DFS_VISIT(i) ;
		}
		color[u] = 2 ;  //black
		finish[u] = time = time+1 ;   //finish time
		topological_order.push_front(MP(u,finish[u])) ;  //topological order
}

void DFS(){ //depth first search
	color.clear();  
	color.resize(SZ(G),0);  parent = start = finish = color;
	time = 0;
	REPI(i, 0, SZ(G)){
		if(color[i] == 0){  //white
			DFS_VISIT(i);
		}
	}
}

int label;
void DFS_VISIT2(int u, vector<int> &T){ //depth first search
	color[u] = label ;    T.PB(u);
	for(list<pair<int,int> >::iterator it(topological_order.begin()); it!=topological_order.end(); it++)
		if(GT[u][it->first] && color[it->first] == 0){
			DFS_VISIT2(it->first, T) ;
		}
}

bool cmp(pair<int,int> x, pair<int,int> y){
	return x.second > y.second;
}
void SCC(){
	DFS();   GT = G;
	REPI(i,0,SZ(G))
		REPI(j,0,SZ(G[i]))
		GT[i][j] = G[j][i];
	topological_order.sort(cmp);
	fill(color.begin(), color.end(), 0);    label = 0;

	for(list<pair<int,int> >::iterator it(topological_order.begin()); it!=topological_order.end(); it++)
		if(color[it->first]==0){
			vector<int> T;  label ++;
			DFS_VISIT2(it->first, T);
		}
		return;
}