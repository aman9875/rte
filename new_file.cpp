#include <bits/stdc++.h>
#include <ctime>
#include<chrono>
using namespace std;

long long int c = 0;
long long int a,b;
float e;

struct Point
{
	int x, y;
};

int compareX(const void* a, const void* b)
{
    Point *p1 = (Point *)a,  *p2 = (Point *)b;
    if(p1->x != p2->x)
    {
        return p1->x - p2->x;
    }
    else
    {
        return p1->y - p2->y;
    }
}

int compareY(const void* a, const void* b)
{
    Point *p1 = (Point *)a,   *p2 = (Point *)b;
    if(p1->y != p2->y)
    {
        return p1->y - p2->y;
    }
    else
    {
        return p1->x - p2->x;
    }
}

float dist(Point *p1, Point *p2)
{
	c = c + 1;
	a = p1->x - p2->x;
	b = p1->y - p2->y;
	return sqrt(a*a + b*b);
}

float bruteForce(Point P[], int n)
{
	float min = FLT_MAX;
	for (int i = 0; i < n; ++i)
	{
		for (int j = i+1; j < n; ++j)
		{
			e = dist(&P[i], &P[j]);
			if (e < min)
				min = e;
		}
	}
	return min;
}

float stripClosest(Point strip[], int size, float d)
{
	float minimum = d;
	for (int i = 0; i < size; ++i)
	{
		for (int j = i+1; j < min(size , i+4) ; ++j) // check for only next three points
		{
			e = dist(&strip[i],&strip[j]);
			if (e < minimum)
				minimum = e;
			else if(abs(strip[i].y-strip[j].y) > d)
				break;
		}
	}
	return minimum;
}

float closestUtil(Point Px[], Point Py[], int n , int rec_level)
{
	if (n <= 3)
		return bruteForce(Px, n);

	int mid;

	if(n%2==0)
	{
		mid = n/2;
	}
	else
	{
		mid = (n/2) + 1;
	}
	Point midPoint = Px[mid-1];
	Point Pyl[mid];
	Point Pyr[n-mid];
	int li = 0, ri = 0;
	for (int i = 0; i < n; i++)
	{
		if (Py[i].x <= midPoint.x && li < mid)
			Pyl[li++] = Py[i];
		else
			Pyr[ri++] = Py[i];
	}
	float dl = closestUtil(Px, Pyl, mid , rec_level + 1);
	float dr = closestUtil(Px + mid, Pyr, n-mid , rec_level + 1);
	float d = min(dl, dr);
	Point strip[n];
	int j = 0;
	for (int i = 0; i < n; i++)
	{
		if (abs(Py[i].x - midPoint.x) < d)
		{
			strip[j] = Py[i]; 
			j++;
		}
	}

	return min(d , stripClosest(strip , j , d));
}

float closest(Point P[], int n)
{
	Point Px[n];
	Point Py[n];
	for (int i = 0; i < n; i++)
	{
		Px[i] = P[i];
		Py[i] = P[i];
	}

    qsort(Px, n, sizeof(Point), compareX);
    qsort(Py, n, sizeof(Point), compareY);

	return closestUtil(Px,Py,n,1);
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	freopen ("input2.txt","r",stdin);
    freopen ("output2.txt","w",stdout);
	int n;
	cin>>n;
	Point P[n+5];
	for(int i=1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		P[i-1].x = x;
		P[i-1].y = y;
	}
	float ans = closest(P,n);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
  	cout << "Elapsed time: " << elapsed.count() << " s\n";
	printf("%f\n%lld" , ans , c);

	return 0;
}
