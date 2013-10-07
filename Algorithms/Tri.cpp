/*1.使用二维数组来实现trie*/
vector<vector<pair<int,int> > > T;
pair<int,int> ---(terminate here strs, next transition idx)
vector<pair<int,int> > ex;  ex.resize(26, make_pair(0,-1));
T.push_back(ex);
void insert(string S)
{
	int idx = 0;
    for (int i = 0; i < S.size(); ++i)
	{
		if (i == S.size() - 1)
        {  //here it is.
			T[idx][S[i] - 'a'].first++;
            return;
		}
		if (T[idx][S[i] - 'a'].second < 0)
        { //not exist
			T.push_back(ex); 
			T[idx][S[i]- 'a'].second = T.size() - 1;  
			idx = T.size() - 1;
		}
        else   //exist
		{
			idx = T[idx][S[i] - 'a'].second;
		}
	}
}

int find(String S)
{
	int idx = 0;
    for (int i = 0; i < S.size(); ++i)
    {
		if (i == S.size() - 1) 
            return T[idx][S[i] - 'a'].first;
		if (T[idx][S[i] - 'a'].second < 0)
            return 0;

		idx = T[idx][S[i] - 'a'].second;
	}
}
/*2.使用vector<有序list>来实现trie*/
/*3.使用double array trie来实现trie*/
/*4.使用结构体来实现trie*/
#define MaxN 15
#define MaxM 26
#define MaxNum 500001
struct Node
{
	bool end;
	int id;
	Node *p[MaxM];
}*root;

void insert(char *s)
{
	Node *r = root;
	for (int i = 0; i < strlen(s); i++)
    {
		if (r->p[s[i] - 'a'] == NULL)
        {
			Node *tmp = new Node;
			tmp->end = false;
            tmp->id = -1;
			for (int j = 0; j < MaxM; j++)
                tmp->p[j] = NULL;
			r->p[s[i] - 'a'] = tmp;
		}
		r = r->p[s[i] - 'a'];
	}
	if (r->end) return;
	r->end = true; 
}
