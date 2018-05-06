// CodeForces975D.cpp : Defines the entry point for the console application.
// http://codeforces.com/contest/975/problem/D 
// Accepted http://codeforces.com/contest/975/submission/37913354

//#include "stdafx.h"

#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<stack>
#include<set>
#include<queue>
#include<map>
#include<set>
#include<string>
#include<climits>
#include<cstring>
#include<iomanip>
using namespace std;

typedef struct _Point {
	long long x, vx, vy;
	_Point() :x(0), vx(0), vy(0) {}
} Point;

ostream& operator<<(ostream& os, Point& p) {
	os << p.vx << " " << p.vy;
	return os;
}

/*

Three main ideas
1. Geometrical
If you pass to velocities normal to the straight line and along the line, only pairs with the same normal speed and different
tanguent speed will allow the meeting in the same time
2. Programmatical
In math one must use sien and cosine but it will result in a floating point and indeterminate calculation
So, instead speed use speed/cosine, it will restrict usage to tan fanction which is integer, it is OK since we need only to compare speeds not use them
3. Combinatorical/programmatical
We must chose two points froM some set, it is C(N,2), but in the set there are identical values and we are forbiden to take identical
How to do it?
It is in function different_pairs below, sort, split into groups
The do recurrently: add by groups: mult and add


*/

bool myComp(Point p1, Point p2) {
	return p1.vy < p2.vy;
}
long long different_pairs(vector<long long>& v) {
	long long res = 0;
	set<long long> s(v.begin(), v.end());
	map<long long, long long>m;
	for (auto au = s.begin(); au != s.end(); au++) {
		m.insert(pair<long long, long long>(*au, 0));
	}
	for (auto au = v.begin(); au != v.end(); au++) {
		m[*au]++;
	}
	vector<long long> groups;
	for (auto au = m.begin(); au != m.end(); au++) {
		groups.push_back(au->second);
	}
	long long count = 0;
	for (auto au = groups.begin(); au != groups.end(); au++) {
		res += (*au)*count;
		count += *au;
	}
	return res;
}
int main()
{
	long long n;
	long long a, b;
	cin >> n >> a >> b;
	vector<Point> points(n);
	for (long long i = 0; i < n; i++) {
		cin >> points.at(i).x >> points.at(i).vx >> points.at(i).vy;
	}
	// decide to use only tan function which is a -integer

	for (long long i = 0; i < n; i++) {
				/*
		The new idea, we do not compute velocity, but velocity/cosine, it does not matter since we just compare them adn cosine is common
		This way every things remain integer!
		*/
		long long x = points.at(i).vx + points.at(i).vy*a;
		long long y = -points.at(i).vx*a + points.at(i).vy;
		points.at(i).vx = x;
		points.at(i).vy = y;
	}
	sort(points.begin(), points.end(), myComp);
	for (long long i = 0; i < n; i++) {
		//cout <<"\t"<< points.at(i).vx << " \t" << points.at(i).vy << endl;
	}
	set<long long>vYvalues;
	for (long long i = 0; i < n; i++) {
		vYvalues.insert(points.at(i).vy);
	}
	map<long long, vector<long long> > sortedVxmap;
	for (auto au = vYvalues.begin(); au != vYvalues.end(); au++) {
		sortedVxmap.insert(pair<long long, vector<long long> >(*au, vector<long long>()));
	}
	for (auto au = points.begin(); au != points.end(); au++) {
		sortedVxmap.at(au->vy).push_back(au->vx);
	}
	long long res = 0;
	for (auto au = sortedVxmap.begin(); au != sortedVxmap.end(); au++) {
		res += different_pairs(au->second);
	}
	cout << 2*res << endl;
    return 0;
}
