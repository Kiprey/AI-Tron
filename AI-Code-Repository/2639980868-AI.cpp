/***************************************************************
 * @file       AI.cpp
 * @brief      AI 实现算法
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#include "TronAPI.h"
#include <queue>
#include <tuple>
// 请自行添加所需的头文件

using namespace TronAPI;

/*
   @brief: 请编辑该函数以设计自己的 AI 代码
*/

int getMaxDist(Point pnt)
{
	bool visited[40][40] = { {false} };
	int maxDist = 0;
	queue<tuple<Point, int>> q;
	q.emplace(pnt, 0);
	while (!q.empty())
	{
		Point tmp;
		int dist;
		tie(tmp, dist) = q.front();
		q.pop();
		int dx[4] = { 1,-1,0,0 },
			dy[4] = { 0,0,1,-1 };
		for (int i = 0; i < 4; i++)
		{
			Point newPoint(tmp.x + dx[i], tmp.y + dy[i]);
			if (!visited[newPoint.x][newPoint.y] && nodeIsEmpty(newPoint) && !nodeIsOutOfBound(newPoint))
			{
				q.emplace(newPoint, dist + 1);
				visited[newPoint.x][newPoint.y] = true;
				if (dist + 1 > maxDist)
					maxDist = dist;
			}
		}
	}
	return maxDist;
}

DirectType AIGetDirect()
{
	Point head = getSelfHeadPoint();
	vector<DirectType> directVector;
	int maxDistOfAll = -1;
	int dx[4] = { 0,0,-1,1 };
	int dy[4] = { -1,1,0,0 };

	for (int i = 0; i < 4; i++)
	{
		Point newPoint(head.x + dx[i], head.y + dy[i]);
		if (nodeIsEmpty(newPoint) && !nodeIsOutOfBound(newPoint))
		{
			int maxDist = getMaxDist(newPoint);
			if (maxDist > maxDistOfAll)
			{
				directVector.push_back((DirectType)i);
				maxDistOfAll = maxDist;
			}
		}
	}
	if (directVector.size() == 0)
	{
		reportInfo("no direct to go");
		return DirectType::None;
	}
	return directVector.back();
}