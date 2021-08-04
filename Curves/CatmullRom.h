#pragma once
#include<vector>
#include<iostream>

// Struct to hold a 2d point
struct Point2d
{
	float x;
	float y;
};

class CatmullRom
{
public:
	static Point2d getPointOnCurve(std::vector<Point2d> points, float t, bool isLooped=false)
	{
		int p0, p1, p2, p3;
		if (!isLooped)
		{
			p1 = (int)t + 1;
			p2 = p1 + 1;
			p3 = p2 + 1;
			p0 = p1 - 1;
		}
		else
		{
			p1 = (int)t;
			p2 = (p1 + 1) % points.size();
			p3 = (p2 + 1) % points.size();
			p0 = p1 >= 1 ? p1-1 : points.size()-1;
		}

		t = t - int(t);

		float tt = t * t;
		float ttt = tt * t;

		// Curve Equations
		float eq0 = -ttt + 2 * tt - t;
		float eq1 = 3 * ttt - 5 * tt + 2;
		float eq2 = -3 * ttt + 4 * tt + t;
		float eq3 = ttt - tt;

		// Calculate effect of each equation on the x and y coordinates of the point
		float xt = 0.5f * (points[p0].x * eq0 + points[p1].x * eq1 + points[p2].x * eq2 + points[p3].x * eq3);
		float yt = 0.5f * (points[p0].y * eq0 + points[p1].y * eq1 + points[p2].y * eq2 + points[p3].y * eq3);

		return Point2d{ xt, yt };
	}
};