/*BFS具体实现代码*/
vector<int> Color, Parent, Dist;
vector<vector<int> > G;
queue<int> Q;
int src;	//search from here

enum
{
	WHITE = 0,
	GRAY,
	BLACK
};

void bfs()
{
	for (int i = 0; i < G.size(); ++i)
	{
		if (i == src)
			continue;
		Color[i] = WHITE;   //white
		Dist[i] = INT_MAX;	//positive infinity
		Parent[i] = -1;   //unknown parent
	}

	Color[src] = GRAY;   //gray
	Dist[src] = 0;  //distance
	Parent[src] = -1;  //no parent
	Q.push(src);
	while (!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for (int i = 0; i < G[u].size(); ++i)
		{
			if (G[u][i] && color[i] == WHITE)
			{  //white
				color[i] = GRAY;  //gray
				dist[i] = dist[u] + 1;
				parent[i] = u;
				Q.push(i);
			}
		}
		color[u] = BLACK; //black
	}
}

//-------------------------------------

int nTimeCounter; 	
vector<int> color, parent, start, finish;
vector<vector<int> > G;		//this is the only input
list<int> topological_order;

void DFS_VISIT(int u)
{ //depth first search
	color[u] = GRAY;  //gray
	start[u] = ++nTimeCounter;
	for (int i = 0; i < G[u].size(); ++i)
	{
		if (G[u][i] && color[i] == WHITE)
		{
			parent[i] = u;  
			DFS_VISIT(i);
		}
	}
	color[u] = BLACK;  //black
	finish[u] = ++nTimeCounter;   //finish time
//	topological_order.push_front(u);  //topological order
}

void DFS()
{ //depth first search
	color.clear();  
	color.resize(G.size(), 0);
	parent = start = finish = color;
	nTimeCounter = 0;
	for (int i = 0; i < G.size(); ++i)
	{
		if (color[i] == WHITE)
		{  //white
			DFS_VISIT(i);
		}
	}
}
