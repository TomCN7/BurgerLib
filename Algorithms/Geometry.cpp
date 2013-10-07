struct Point
{
	Point(int a = 0, int b = 0) : x(a), y(b){}
	int x;
	int y;
};

Point p0;
//点相减
Point operator-(Point a, Point b)
{
	return Point((a.x - b.x), (a.y - b.y));
}
//向量a,b的叉乘
int operator *(Point a, Point b)
{
	return a.x * b.y - b.x * a.y;
}
//a->b 在a->c 的方位(正为顺时针,负为逆时针)
int Direction(Point a, Point b, Point c)
{ 
	return (b - a) * (c - a);
}
//判断点c是否在ab点的矩形内
bool OnSegment(Point a, Point b, Point c)
{
	return c.x >= min(a.x, b.x) && c.x <= max(a.x, b.x) && c.y >= min(a.y, b.y) && c.y <= max(a.y, b.y);
}
//判断线段p1-p2和线段p3-p4是否相交
bool SegmentsIntersect(Point p1, Point p2, Point p3, Point p4)
{
	int d1 = Direction(p3, p4, p1);
	int d2 = Direction(p3, p4, p2);
	int d3 = Direction(p1, p2, p3);
	int d4 = Direction(p1, p2, p4);
	if(d1 * d2 < 0 && d3 * d4 < 0)
		return true;
	if(d1 == 0 && OnSegment(p3, p4, p1))
		return true;
	if(d2 == 0 && OnSegment(p3, p4, p2))
		return true;
	if(d3 == 0 && OnSegment(p1, p2, p3))
		return true;
	if(d4 == 0 && OnSegment(p1, p2, p4))
		return true;
	return false;
}
//判断极角大小,相对于p0
bool operator <(const Point & a, const Point & b)
{
	if (Direction(p0, a, b) > 0)
		return true;
	else
		return false;
}
//扫描,找点集a中的凸包,结果存放在数组b中,返回凸包上点的个数
int GrahamScan(Point a[], int size_a, Point b[], int size_b)
{
	if (size_a <= 3)
    {
		memcpy(b, a, size_a * sizeof(a[0]));
		return size_a;
	}
	int i, cnt;
	p0 = a[0];
	for (i = 1; i < size_a; ++i)
    {
		if (a[i].y < p0.y || a[i].y == p0.y && a[i].x < p0.x)
        {
			p0 = a[i];
			Point tmp = a[i];
			a[i] = a[0];
			a[0] = tmp;
		}
	}
	sort(a+1, a+size_a); //按极角排序
	b[0] = a[0];
	b[1] = a[1];
	b[2] = a[2];
	cnt = 3;
	for (i = 3; i < size_a; ++i)
    {
		while (Direction(b[cnt-2], b[cnt-1], a[i]) < 0)  //<=  如果有=则会漏掉一些点
			--cnt;
		b[cnt++] = a[i];
	}

	return cnt;
}