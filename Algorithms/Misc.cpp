//闰年的判断：
#define RUN(x) (x%400==0||(x%4==0 && x%100)) 

//判断二进制表示中有多少个1
int pop(unsigned x) {
	x = x - ((x >> 1) & 0x55555555); 
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333); 
	x = (x + (x >> 4)) & 0x0F0F0F0F; 
	x = x + (x >> 8); 
	x = x + (x >> 16); 
	return x & 0x0000003F; 
}

//给定日期，返回星期几
int dayofweek(int y, int m, int d)	/* 0 = Sunday */
{
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

/*计算组合；调用allCombinations(0,0,result);*/
//【R.size(): (m)  |   n(n)】     C(n,m)
// R.resize(m); ---R中先要预留m个位置
Void allCombinations(int idx, int minVal, vector<int>& R){
	If(idx == R.size()){
		//do something with R here.
	}else{
		For(int i=minVal; i<n; i++){
			R[idx] = I;
			allCombinations(idx+1,i+1,R);
		}
	}
}
/*计算下一个组合；R中要先存一个组合*/
bool next_combination(vector<int>& R){
	int idx = SZ(R)-1;   //m==SZ(R)
	for(; idx>=0; idx--)  if(R[idx]<n-m+idx) break;
	if(idx<0) return false;
	R[idx]++;
	REPI(I, idx+1, SZ(R))
		R[i] = R[i-1]+1;
	Return true;
}