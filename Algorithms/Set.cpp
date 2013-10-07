/*如果要用到多个集合，频繁操作union，用数组实现较方便
  如果只用到一个集合，直接用STL set会比较方便 */
/*1.用数组实现并查集*/
int f[MAX];   //f[i]=I;
int find(int x)
{
   if (x != f[x]) 
       return f[x] = find(f[x]);
   return f[x];
}

void union(int x, int y)
{
　  f[find(x)] = f[find(y)];
}
/*2.用STL set实现并查集*/
vector<set<int> > V;
Set_union();
…