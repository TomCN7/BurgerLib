//DFS找路，二分图匹配
#define MAXN  550
bool G[MAXN][MAXN];
int nx,ny;
int match[MAXN];  bool searched[MAXN];
bool find(int a){
	for(int b=0;b<ny;b++)
		if(G[a][b]&&!searched[b]){
			searched[b]=true;
			if(match[b]<0 || find(match[b])){
				match[b]=a; return true;
			}
		}
		return false;
}
int Matching(){
	memset(match, -1, sizeof(match));
	int total =0 ;
	for(int a=0 ;a<nx ;a++){
		memset(searched, 0, sizeof(searched));
		if(find(a)) total++;
	}
	return total;
}


Int G[nx][ny];  //graph(left node nx, right node ny)
Int nx, ny;
Int cx[nx], cy[ny];  //cx[i]与xi顶点匹配的Y顶点
Int pred[N], mk[N], open[N];
int BFS_Matching(){		//最优匹配
	int ans = 0 ;
	memset(mk,0xff,sizeof(mk)) ;
	memset(cx,0xff,sizeof(cx)) ;
	memset(cy,0xff,sizeof(cy)) ;
	for(int i=0 ; i<nx ; i++){
		pred[i] = -1 ;
		for(open[cur=tail=0]=i; cur<=tail&&cx[i]==-1; cur++){
			for(int u=open[cur],v=0; v<ny&&cx[i]==-1; v++)
				if(G[u][v] && mk[v]!=i){
					mk[v]=i; open[++tail]=cy[v] ;
					if(open[tail]>=0){
						pred[open[tail]]=u; continue;
					　　　　　　　　　　　}
					　　　　　　　　　　　For(int d=u,e=v; d!=-1;
							   　　　　　　　　　　　   t=cx[d],cx[d]=e,cy[e]=d,e=t,d=pred[d]);
				　　　　　　　　}
		　　　　}
		　　　　if(cx[i]!=-1) ans++ ;
	　　　}
	　　　return ans ;
}