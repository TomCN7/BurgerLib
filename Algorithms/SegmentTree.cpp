class node{
public:
	node(int _s, int _e, 
		　　　　	int _l=-1, int _r=-1, int _c=-1):start(_s),end(_e),left(_l),right(_r),color(_c){}
	int start, end, left, right;
	int color;
};
//需要进一步验证
vector<node> tree;
int total = -1; 
void make_tree(int a, int b){
	total++;  int now=total;
	node _t(a, b, -1, -1, 0);
	tree.PB(_t);
	if(a+1<b){
		tree[now].left = total+1;   make_tree(a, (a+b)/2);
		tree[now].right = total+1;  make_tree((a+b)/2, b);
	}
}

void insert(int cur, int a, int b, int c){
	int m = (tree[cur].start + tree[cur].end)/2;
	if(a == tree[cur].start && b == tree[cur].end)
		tree[cur].color  = c;
	else{ 
		tree[cur].color = -1;
		if(b<=m) insert(tree[cur].left, a, b, c);
		else if(a>=m) insert(tree[cur].right, a, b, c);
		else{
			insert(tree[cur].left, a, m, c);
			insert(tree[cur].right, m, b, c);
		}
	}
}

int count(int cur){
	if(tree[cur].color) 
		return tree[cur].end - tree[cur].start;
	else if(tree[cur].end - tree[cur].start == 1) return 0;
	else return count(cur*2) + count(cur*2+1);
}

//树状数组
#define MAXN;
int in[MAXN];   //in是建立在原数组基础上的统计结构
int n;
int Lowbit(int t){
	return t & (t^(t-1));
}
int Sum(int end){	 //统计：统计从到end中in数值的和
	int sum = 0;
	while(end > 0){
		sum += in[end];
		end -= Lowbit(end);
	}
	return sum;
}
void plus(int pos, int num){	//更新：把pos位置上的数加上num，需要更新后续数值
	while(pos <= n){
		in[pos] += num;
		pos += Lowbit(pos);
	}
}