/*���Ҫ�õ�������ϣ�Ƶ������union��������ʵ�ֽϷ���
  ���ֻ�õ�һ�����ϣ�ֱ����STL set��ȽϷ��� */
/*1.������ʵ�ֲ��鼯*/
int f[MAX];   //f[i]=I;
int find(int x)
{
   if (x != f[x]) 
       return f[x] = find(f[x]);
   return f[x];
}

void union(int x, int y)
{
��  f[find(x)] = f[find(y)];
}
/*2.��STL setʵ�ֲ��鼯*/
vector<set<int> > V;
Set_union();
��