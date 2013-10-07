//������жϣ�
#define RUN(x) (x%400==0||(x%4==0 && x%100)) 

//�ж϶����Ʊ�ʾ���ж��ٸ�1
int pop(unsigned x) {
	x = x - ((x >> 1) & 0x55555555); 
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333); 
	x = (x + (x >> 4)) & 0x0F0F0F0F; 
	x = x + (x >> 8); 
	x = x + (x >> 16); 
	return x & 0x0000003F; 
}

//�������ڣ��������ڼ�
int dayofweek(int y, int m, int d)	/* 0 = Sunday */
{
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

/*������ϣ�����allCombinations(0,0,result);*/
//��R.size(): (m)  |   n(n)��     C(n,m)
// R.resize(m); ---R����ҪԤ��m��λ��
void allCombinations(int idx, int minVal, vector<int>& R)
{
	if (idx == R.size())
    {
		//do something with R here.
	}
    else 
    {
		for (int i = minVal; i < n; ++i)
        {
			R[idx] = i;
			allCombinations(idx + 1, i + 1, R);
		}
	}
}
/*������һ����ϣ�R��Ҫ�ȴ�һ�����*/
bool next_combination(vector<int>& R)
{
	int idx = R->size() - 1;   //m==SZ(R)
	for (; idx >= 0; --idx)  if (R[idx] < n - m + idx) break;
	if (idx < 0) return false;
	R[idx]++;
    for (int i = idx + 1; i < R->size(); ++i)
        R[i] = R[i - 1] + 1;

    return true;
}