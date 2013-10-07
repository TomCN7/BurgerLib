#include<cstring>

#define MAXX  550
#define MAXY  550
bool bGraph[MAXX][MAXY];
int  nX, nY;
int  nMatching[MAXY];  
bool bSearched[MAXX];

bool DfsFind(int i)
{
	for (int j = 0; j < nY; ++j)
	{
		if (bGraph[i][j] && !bSearched[j])
		{
			bSearched[j] = true;
			if (nMatching[j] < 0 || DfsFind(nMatching[j]))
			{
				nMatching[j] = i; 
				return true;
			}
		}
	}
	return false;
}

int Matching()
{
	memset(nMatching, -1, sizeof(nMatching));
	int nTotal =0 ;
	for (int i = 0; i < nX; ++i)
	{
		memset(bSearched, 0, sizeof(bSearched));

		if (DfsFind(i)) 
			++nTotal;
	}

	return nTotal;
}


int G[nX][nY];  //graph(left node nx, right node ny)
int nX, nY;
int cx[nX], cy[nX];  //cx[i]与xi顶点匹配的Y顶点
int pred[N], mk[N], open[N];
int BFS_Matching()
{		//最优匹配
	int nAns = 0, nCur = 0, nTail = 0, t = 0;

	memset(mk, 0xff, sizeof(mk));
	memset(cx, 0xff, sizeof(cx));
	memset(cy, 0xff, sizeof(cy));

	for (int i = 0; i < nX; ++i)
	{
		pred[i] = -1;
		for (open[nCur = nTail = 0] = i; nCur <= nTail && cx[i] == -1; ++nCur)
		{
			for (int u = open[nCur], v = 0; v < nY && cx[i] == -1; ++v)
			{
				if (G[u][v] && mk[v] != i)
				{
					mk[v] = i; 
					open[++nTail] = cy[v];
					if (open[nTail] >= 0)
					{
						pred[open[nTail]] = u; 
						continue;
					}

					for (int d = u, e = v; d != -1;
						t = cx[d], cx[d] = e, cy[e] = d, e = t, d = pred[d]);
				}
			}
		}
		if (cx[i] != -1) ++nAns;
	}

	return nAns;
}

