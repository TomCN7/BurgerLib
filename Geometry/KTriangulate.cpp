inline int PREV(int i, int n) { return i - 1 >= 0 ? i - 1 : n - 1; }
inline int NEXT(int i, int n) { return i + 1 < n ? i + 1 : 0; }

inline int Area2(const int* a, const int* b, const int* c)
{
    return (b[0] - a[0]) * (c[2] - a[2]) - (c[0] - a[0]) * (b[2] - a[2]);
}

//	Exclusive or: true iff exactly one argument is true.
//	The arguments are negated to ensure that they are 0/1
//	values.  Then the bitwise Xor operator may apply.
//	(This idea is due to Michael Baldwin.)
inline BOOL xorb(BOOL x, BOOL y)
{
    return !x ^ !y;
}

// Returns true iff c is strictly to the left of the directed
// line through a to b.
inline BOOL ACIsLeftOfAB(const int* A, const int* B, const int* C)
{
    return Area2(A, B, C) < 0;
}

inline BOOL ACIsLeftOnOfAB(const int* A, const int* B, const int* C)
{
    return Area2(A, B, C) <= 0;
}

inline BOOL Collinear(const int* A, const int* B, const int* C)
{
    return Area2(A, B, C) == 0;
}

//	Returns true iff ab properly intersects cd: they share
//	a point interior to both segments.  The properness of the
//	intersection is ensured by using strict leftness.
static BOOL IsABintersectPropCD(const int* A, const int* B, const int* C, const int* D)
{
    // Eliminate improper cases.
    if (Collinear(A,B,C) || Collinear(A,B,D) ||
        Collinear(C,D,A) || Collinear(C,D,B))
        return false;

    return xorb(ACIsLeftOfAB(A,B,C), ACIsLeftOfAB(A,B,D)) && xorb(ACIsLeftOfAB(C,D,A), ACIsLeftOfAB(C,D,B));
}

// Returns T iff (a,b,c) are collinear and point c lies 
// on the closed segement ab.
static BOOL IsCbetweenAB(const int* A, const int* B, const int* C)
{
    if (!Collinear(A, B, C))
        return false;
    // If ab not vertical, check betweenness on x; else on y.
    if (A[0] != B[0])
        return	((A[0] <= C[0]) && (C[0] <= B[0])) || ((A[0] >= C[0]) && (C[0] >= B[0]));
    else
        return	((A[2] <= C[2]) && (C[2] <= B[2])) || ((A[2] >= C[2]) && (C[2] >= B[2]));
}

// Returns true iff segments ab and cd intersect, properly or improperly.
static BOOL IsABintersectCD(const int* A, const int* B, const int* C, const int* D)
{
    if (IsABintersectPropCD(A, B, C, D))
        return true;
    else if (IsCbetweenAB(A, B, C) || IsCbetweenAB(A, B, D) ||
        IsCbetweenAB(C, D, A) || IsCbetweenAB(C, D, B))
        return true;
    else
        return false;
}

static BOOL VEqual(const int* a, const int* b)
{
    return a[0] == b[0] && a[2] == b[2];
}

// Returns T iff (v_i, v_j) is a proper internal *or* external
// diagonal of P, *ignoring edges incident to v_i and v_j*.
static BOOL IsDiagonalIgnoreIncident(int i, int j, int n, const int* pVerts, int* pIndices)
{
    const int* d0 = &pVerts[(pIndices[i] & 0x0fffffff) * 4];
    const int* d1 = &pVerts[(pIndices[j] & 0x0fffffff) * 4];

    // For each edge (k,k+1) of P
    for (int k = 0; k < n; k++)
    {
        int k1 = NEXT(k, n);
        // Skip edges incident to i or j
        if (!((k == i) || (k1 == i) || (k == j) || (k1 == j)))
        {
            const int* p0 = &pVerts[(pIndices[k] & 0x0fffffff) * 4];
            const int* p1 = &pVerts[(pIndices[k1] & 0x0fffffff) * 4];

            if (VEqual(d0, p0) || VEqual(d1, p0) || VEqual(d0, p1) || VEqual(d1, p1))
                continue;

            if (IsABintersectCD(d0, d1, p0, p1))
                return false;
        }
    }
    return true;
}

// Returns true iff the diagonal (i,j) is strictly internal to the 
// polygon P in the neighborhood of the i endpoint.
static BOOL	IsInCone(int i, int j, int n, const int* pVerts, int* pIndices)
{
    const int* pi = &pVerts[(pIndices[i] & 0x0fffffff) * 4];
    const int* pj = &pVerts[(pIndices[j] & 0x0fffffff) * 4];
    const int* pni = &pVerts[(pIndices[NEXT(i, n)] & 0x0fffffff) * 4];
    const int* ppi = &pVerts[(pIndices[PREV(i, n)] & 0x0fffffff) * 4];

    // If P[i] is a convex vertex [ i+1 left or on (i-1,i) ].
    if (ACIsLeftOnOfAB(ppi, pi, pni))
        return ACIsLeftOfAB(pi, pj, ppi) && ACIsLeftOfAB(pj, pi, pni);
    // Assume (i-1,i,i+1) not collinear.
    // else P[i] is reflex. [both i, (i+1) concave]
    return !(ACIsLeftOnOfAB(pi, pj, pni) && ACIsLeftOnOfAB(pj, pi, ppi));
}

// Returns T iff (v_i, v_j) is a proper internal diagonal of P.
static BOOL IsDiagonal(int i, int j, int n, const int* pVerts, int* pIndices)
{
    return IsInCone(i, j, n, pVerts, pIndices) && IsDiagonalIgnoreIncident(i, j, n, pVerts, pIndices);
}

int Triangulate(int nVerts, const int* pVerts, int* pIndices, int* pTris)
{
    int nTris = 0;
    int* pDstTris = pTris;

    // The last bit of the index is used to indicate if the vertex can be removed.
    for (int i = 0; i < nVerts; i++)
    {
        int i1 = NEXT(i, nVerts);
        int i2 = NEXT(i1, nVerts);
        if (IsDiagonal(i, i2, nVerts, pVerts, pIndices))
            pIndices[i1] |= 0x80000000;
    }

    while (nVerts > 3)
    {
        int minLen = -1;
        int mini = -1;
        for (int i = 0; i < nVerts; i++)
        {
            int i1 = NEXT(i, nVerts);
            if (pIndices[i1] & 0x80000000)
            {
                const int* p0 = &pVerts[(pIndices[i] & 0x0fffffff) * 4];
                const int* p2 = &pVerts[(pIndices[NEXT(i1, nVerts)] & 0x0fffffff) * 4];

                int len = (p2[0] - p0[0]) * (p2[0] - p0[0]) + (p2[2] - p0[2]) * (p2[2] - p0[2]);
                if (minLen < 0 || len < minLen)
                {
                    minLen = len;
                    mini = i;
                }
            }
        }

        if (mini == -1)
            return -nTris;   // Should not happen.

        int i = mini;
        int i1 = NEXT(i, nVerts);
        int i2 = NEXT(i1, nVerts);

        *pDstTris++ = pIndices[i] & 0x0fffffff;
        *pDstTris++ = pIndices[i1] & 0x0fffffff;
        *pDstTris++ = pIndices[i2] & 0x0fffffff;
        nTris++;

        // Removes P[i1] by copying P[i+1]...P[n-1] left one index.
        nVerts--;
        for (int k = i1; k < nVerts; k++)
            pIndices[k] = pIndices[k+1];

        if (i1 >= nVerts) i1 = 0;
        i = PREV(i1, nVerts);
        // Update diagonal flags.
        if (IsDiagonal(PREV(i, nVerts), i1, nVerts, pVerts, pIndices))
            pIndices[i] |= 0x80000000;
        else
            pIndices[i] &= 0x0fffffff;

        if (IsDiagonal(i, NEXT(i1, nVerts), nVerts, pVerts, pIndices))
            pIndices[i1] |= 0x80000000;
        else
            pIndices[i1] &= 0x0fffffff;
    }

    // Append the remaining triangle.
    *pDstTris++ = pIndices[0] & 0x0fffffff;
    *pDstTris++ = pIndices[1] & 0x0fffffff;
    *pDstTris++ = pIndices[2] & 0x0fffffff;
    nTris++;

    return nTris;
}