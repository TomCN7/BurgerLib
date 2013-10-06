/*BFS具体实现代码*/
Vector<int> color, parent, dist ;
Vector<vector<int> > G ;
Queue<int> Q ;
Int s ;	//search from here
Void bfs(){
	　　　REPI(I, 0, SZ(G)) 
		   　　　　　　if(i!=s){ 
					 　　　　　　　　color[i]=0;   //white
							 　　　　　　　　dist[i]=PINF;	//positive infinity
									 　　　　　　　　parent[i]=-1;   //unknown parent
				 　　　　　　}
				 　　　Color[s]=1;   //gray
					　　　Dist[s]=0;  //distance
					   　　　Parent[s]=-1;  //no parent
						  　　　Q.push(s);
							 　　　While(!Q.empty()){
									　　　    Int u = Q.back();   Q.pop();
										   　　　    REPI(I, 0, SZ(G[u])){
													  　　　        If(G[u][i] && color[i]==0){  //white
																	 　　　            Color[i]=1;  //gray
																					　　　            Dist[i]=dist[u]+1;
																								   　　　            Parent[i]=u;
																												  　　　            Q.push(i);
																 　　　        }
												  　　　　　　}
												  　　　　　　Color[u] = 2; //black
								　　　}
}

int time ;	//search from here 	
vector<int> color, parent, start, finish ;
vector<vector<int> > G ;		//this is the only input
list<int> topological_order ;
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
		Topological_order.push_front(u) ;  //topological order
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