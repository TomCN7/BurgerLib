//DFS找路，二分图匹配
#define MAXN  550
bool bGraph[MAXN][MAXN];
int nLeft, nRight;
int nMatchingLeftIdxForRight[MMAXN];  
bool bSearchedForRight[MAXN];
bool DfsFind(int nLeftIdx)
{
	for (int nRightIdx = 0; nRightIdx < nRight; ++nRightIdx)
		if (bGraph[nLeftIdx][nRightIdx] && !bSearchedForRight[nRightIdx])
		{
			bSearchedForRight[nRightIdx] = true;
			if (nMatchingLeftIdxForRight[nRightIdx] < 0 || DfsFind(nMatchingLeftIdxForRight[nRightIdx]))
			{
				nMatchingLeftIdxForRight[nRightIdx] = nLeftIdx; 
				return true;
			}
		}
		return false;
}
int Matching()
{
	memset(nMatchingLeftIdxForRight, -1, sizeof(nMatchingLeftIdxForRight));
	int nTotal =0 ;
	for (int nLeftIdx = 0; nLeftIdx < nLeft; ++nLeftIdx)
	{
		memset(bSearchedForRight, 0, sizeof(bSearchedForRight));

		if (DfsFind(nLeftIdx)) 
			++nTotal;
	}
	return nTotal;
}


int G[nx][ny];  //graph(left node nx, right node ny)
int nx, ny;
int cx[nx], cy[ny];  //cx[i]与xi顶点匹配的Y顶点
int pred[N], mk[N], open[N];
int BFS_Matching()
{		//最优匹配
	int nAns = 0;
	memset(mk, 0xff, sizeof(mk));
	memset(cx, 0xff, sizeof(cx));
	memset(cy, 0xff, sizeof(cy));
	for (int i = 0; i < nx; ++i)
	{
		pred[i] = -1 ;
		for (open[cur = tail = 0] = i; cur <= tail && cx[i] == -1; ++cur)
		{
			for (int u = open[cur], v = 0; v < ny && cx[i] == -1; ++v)
				if (G[u][v] && mk[v] != i)
				{
					mk[v] = i; 
					open[++tail] = cy[v];
					if (open[tail] >= 0)
					{
						pred[open[tail]] = u; 
						continue;
					}
					for (int d = u, e = v; d != -1;
						t = cx[d], cx[d] = e, cy[e] = d, e = t, d = pred[d]);
				}
	　	}
		if (cx[i] != -1) ++nAns;
	}
	return nAns ;
}

