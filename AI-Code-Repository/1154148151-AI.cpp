/***************************************************************
 * @file       AI.cpp
 * @brief      AI 实现算法
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#include "TronAPI.h"
#include <map>

#define max(x, y) ((x) > (y) ? (x) : (y))
using namespace TronAPI;

DirectType AIGetDirect() //AI算法
{
	//#define TRONDEBUG
	/*
			不要使用 cin / cout / cerr / printf / scanf 等等
			与标准输入流、标准输出流、标准错误流相关的函数或功能。。
			输出信息至控制台输出，使用 `void TronAPI::printDbgMsg(string)` 函数
	*/

	//AI具体实现：
	Point head = getSelfHeadPoint(); //头部节点指针
	multimap<int, DirectType> direct; //可选方向集合
	int up = 0, down = 0, left = 0, right = 0; //四个方向上的空路径数
	int _up = 0, _down = 0, _left = 0, _right = 0; //四个方向上的邻近空路径数
	//判断头部在四个方向及其邻近路径上可走格数的比例:
	for (Point p = head; nodeIsEmpty(getTheUpPoint(p)); p = getTheUpPoint(p))
	{
		up++;
		if (nodeIsEmpty(getTheLeftPoint(getTheUpPoint(p)))) _up++;
		if (nodeIsEmpty(getTheRightPoint(getTheUpPoint(p)))) _up++;
	}
	for (Point p = head; nodeIsEmpty(getTheDownPoint(p)); p = getTheDownPoint(p))
	{
		down++;
		if (nodeIsEmpty(getTheLeftPoint(getTheDownPoint(p)))) _down++;
		if (nodeIsEmpty(getTheRightPoint(getTheDownPoint(p)))) _down++;
	}
	for (Point p = head; nodeIsEmpty(getTheLeftPoint(p)); p = getTheLeftPoint(p))
	{
		left++;
		if (nodeIsEmpty(getTheUpPoint(getTheLeftPoint(p)))) _left++;
		if (nodeIsEmpty(getTheDownPoint(getTheLeftPoint(p)))) _left++;
	}
	for (Point p = head; nodeIsEmpty(getTheRightPoint(p)); p = getTheRightPoint(p))
	{
		right++;
		if (nodeIsEmpty(getTheUpPoint(getTheRightPoint(p)))) _right++;
		if (nodeIsEmpty(getTheDownPoint(getTheRightPoint(p))))  _right++;
	}
	int maxRoad = max(max(up, down), max(left, right)); //最大路径值
	if (maxRoad == 0) { reportInfo("No direct to go"); return DirectType::None; } //无路可走
	if (maxRoad == up) direct.insert(pair<int, DirectType>(_up, DirectType::Up));
	if (maxRoad == down) direct.insert(pair<int, DirectType>(_down, DirectType::Down));
	if (maxRoad == left) direct.insert(pair<int, DirectType>(_left, DirectType::Left));
	if (maxRoad == right) direct.insert(pair<int, DirectType>(_right, DirectType::Right));
	if (direct.size() == 0) { reportInfo("No proper way to go");  return DirectType::None; } //没有合适的路可以走(真的会这样吗...)
	map<int, DirectType>::iterator it = direct.end(); it--;
	return it->second;
}