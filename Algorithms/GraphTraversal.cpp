/*BFS具体实现代码*/
vector<int> color, parent, dist;
vector<vector<int> > G;
queue<int> Q;
int s;	//search from here

void bfs()
{
	for (int i = 0; i < G.size(); ++i)
	{
		if (i == s)
			continue;
		color[i] = 0;   //white
		dist[i] = PINF;	//positive infinity
		parent[i] = -1;   //unknown parent
	}

	color[s] = 1;   //gray
	dist[s] = 0;  //distance
	parent[s] = -1;  //no parent
	Q.push(s);
	while (!Q.empty())
	{
		int u = Q.back();
		Q.pop();
		for (int i = 0; i < G[u].size(); ++i)
		{
			if(G[u][i] && color[i] == 0)
			{  //white
				color[i] = 1;  //gray
				dist[i] = dist[u] + 1;
				parent[i] = u;
				Q.push(i);
			}
		}
		color[u] = 2; //black
	}
}

int time;	//search from here 	
vector<int> color, parent, start, finish;
vector<vector<int> > G;		//this is the only input
list<int> topological_order;

void DFS_VISIT(int u)
{ //depth first search
	color[u] = 1;  //gray
	time++;
	start[u] = time;   //start time
	for (int i = 0; i < G[u].size(); ++i)
	{
		if (G[u][i] && color[i] == 0)
		{
			parent[i] = u;  
			DFS_VISIT(i);
		}
	}
	color[u] = 2;  //black
	finish[u] = time = time + 1;   //finish time
	topological_order.push_front(u);  //topological order
}

void DFS()
{ //depth first search
	color.clear();  
	color.resize(G.size(), 0);
	parent = start = finish = color;
	time = 0;
	for (int i = 0; i < G.size(); ++i)
	{
		if (color[i] == 0)
		{  //white
			DFS_VISIT(i);
		}
	}
}
