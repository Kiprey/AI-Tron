/***************************************************************
 * @file       AI.cpp
 * @brief      AI ʵ���㷨
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#include "TronAPI.h"
#include <map>

#define max(x, y) ((x) > (y) ? (x) : (y))
using namespace TronAPI;

DirectType AIGetDirect() //AI�㷨
{
	//#define TRONDEBUG
	/*
			��Ҫʹ�� cin / cout / cerr / printf / scanf �ȵ�
			���׼����������׼���������׼��������صĺ������ܡ���
			�����Ϣ������̨�����ʹ�� `void TronAPI::printDbgMsg(string)` ����
	*/

	//AI����ʵ�֣�
	Point head = getSelfHeadPoint(); //ͷ���ڵ�ָ��
	multimap<int, DirectType> direct; //��ѡ���򼯺�
	int up = 0, down = 0, left = 0, right = 0; //�ĸ������ϵĿ�·����
	int _up = 0, _down = 0, _left = 0, _right = 0; //�ĸ������ϵ��ڽ���·����
	//�ж�ͷ�����ĸ��������ڽ�·���Ͽ��߸����ı���:
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
	int maxRoad = max(max(up, down), max(left, right)); //���·��ֵ
	if (maxRoad == 0) { reportInfo("No direct to go"); return DirectType::None; } //��·����
	if (maxRoad == up) direct.insert(pair<int, DirectType>(_up, DirectType::Up));
	if (maxRoad == down) direct.insert(pair<int, DirectType>(_down, DirectType::Down));
	if (maxRoad == left) direct.insert(pair<int, DirectType>(_left, DirectType::Left));
	if (maxRoad == right) direct.insert(pair<int, DirectType>(_right, DirectType::Right));
	if (direct.size() == 0) { reportInfo("No proper way to go");  return DirectType::None; } //û�к��ʵ�·������(��Ļ�������...)
	map<int, DirectType>::iterator it = direct.end(); it--;
	return it->second;
}