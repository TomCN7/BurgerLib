vector<int> &add(vector<int> &A, vector<int> &B)
{
	int _a = A.size(), _b = B.size();
	int i;
	for (i = 0; i < _a; ++i)
	{
		if (i < _b) A[i] += B[i];
		if (A[i] > BASE)
		{
			if (i == _a-1)
			{ 
				A.push_back(A[i] / BASE); 
				_a ++;
			}
			else
			{
				A[i+1] += A[i] / BASE;
			}
			A[i] = A[i] % BASE;
		}
	}
	while (i < _b)
	{
		A.push_back(B[i]);
		i++;
	}

	return A;
}

vector<int> &sub(vector<int> &A, vector<int> &B)
{  //A>B
	int _a = A.size(), _b = B.size();
	int i;
	for (i = 0; i<_a; i++)
	{
		if (i >= _b) break;
		if (A[i] < B[i])
		{
			A[i] += BASE;
			A[i + 1]--;
		}
		A[i] -= B[i];
	}
	return A;
}

vector<int> &mul(vector<int> &A, vector<int> &B){
	vector<int> C = A;   
	int _b = B.size(),  _c = C.size();
	A.resize(_b + _c);
	fill(A.begin(), A.end(), 0);
	for (int i = 0; i < _b; ++i)
	{
		for (int j = 0; j < _c; ++j)
		{
			A[i + j] += B[i] * C[j];
		}
	}
	for (int k = 0, _z(A.size()); k < _z; ++k)
	{
		if (A[k] > BASE)
		{
			if (k == _z - 1)
			{
				A.push_back(A[k] / BASE);
				_z++;
			}
			else A[k + 1] += A[k] / BASE;
			A[k] = A[k] % BASE;
		}
	}

	return A;
}
