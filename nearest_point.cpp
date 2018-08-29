// nearest_point.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdlib.h>
#include<math.h>

#define Pointnum 8

struct point
{
	double x, y;
};

double min(double x, double y)
{
	return x > y ? y : x;
}

double distance(struct point p1, struct point p2)
{
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}
void insert_sortx(struct point a[], int len)
{
	int i = 0, j = 0;
	struct point tmp;
	for (i = 0; i < len-1; i++)
	{
		j = i ;
		tmp = a[j+1];
		while (j >= 0 && tmp.x < a[j].x)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j+1] = tmp;
	}
}


void insert_sorty(struct point a[], int len)
{
	int i = 0, j = 0;
	struct point tmp;
	for (i = 0; i < len - 1; i++)
	{
		j = i;
		tmp = a[j + 1];
		while (j >= 0 && tmp.y < a[j].y)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}
}

double nearest(struct point p[], int start, int end,struct point nearest_point[])
{
	int mid;
	int i=0,j=0,cnt=0;
	double d1, d2,dmin;
	struct point tmp[Pointnum], tmp1[2],tmp2[2];
	if (end - start == 1)
	{
		nearest_point[0].x = p[start].x;
		nearest_point[0].y = p[start].y;
		nearest_point[1].x = p[end].x;
		nearest_point[1].y = p[end].y;
		return distance(p[start], p[end]);
	}
	else
	{
		mid = (start + end) / 2;
		d1=nearest(p, start, mid,nearest_point);
		tmp1[0].x = nearest_point[0].x;
		tmp1[0].y = nearest_point[0].y;
		tmp1[1].x = nearest_point[1].x;
		tmp1[1].y = nearest_point[1].y;
		d2=nearest(p, mid + 1, end, nearest_point);
	/*	tmp2[0].x = nearest_point[0].x;
		tmp2[0].y = nearest_point[0].y;
		tmp2[1].x = nearest_point[1].x;
		tmp2[1].y = nearest_point[1].y;
	*/
		dmin = min(d1, d2);
		if (d1 < d2)
		{
			nearest_point[0].x = tmp1[0].x;
			nearest_point[0].y = tmp1[0].y;
			nearest_point[1].x = tmp1[1].x;
			nearest_point[1].y = tmp1[1].y;
		}
		for (i = 0; i < end - start + 1; i++)
			if (p[mid].x - dmin < p[i].x && p[i].x<p[mid].x + dmin)
				tmp[cnt++] = p[i];
		insert_sorty(tmp, cnt);
		for(i=0;i<cnt;i++)
			for (j = i + 1; j < cnt; j++)
			{
				if (tmp[i].y - tmp[j].y >= dmin)break;
				else if (distance(tmp[i], tmp[j]) < dmin)
				{
					nearest_point[0].x = tmp[i].x;
					nearest_point[0].y = tmp[i].y;
					nearest_point[1].x = tmp[j].x;
					nearest_point[1].y = tmp[j].y;
					dmin = distance(tmp[i], tmp[j]);
				}

			}
		return dmin;
	}
}

void print(double a[], int len)
{
	int i = 0;
	for (i = 0; i < len; i++)
	{
		printf("%f ", a[i]);
	}
	printf("\n");
}

int main()
{
//	double a[] = { 2.1,3.2,3.5,6.8,9.3,1.9,3.1,4.3 };
	struct point p[Pointnum], nearest_point[2];
	int i = 0;
	double dmin = 0;
	for(i=0;i<Pointnum;i++)
	{
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	insert_sortx(p, Pointnum);
	dmin = nearest(p, 0, Pointnum - 1, nearest_point);
	printf("%f\n", dmin);
	printf("(%lf,%lf),(%lf,%lf)\n", nearest_point[0].x, nearest_point[0].y, nearest_point[1].x, nearest_point[1].y);
	//int len = sizeof(a) / sizeof(a[0]);

	//insert_sort(a, len);
	//print(a, len);

    return 0;
}

