/***************************************************************
 * @file       TronAPI.cpp
 * @brief      实现 AI 使用的基础API 的具体函数实现
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   请勿随意更改当前文件！
 **************************************************************/

#pragma once

#include "TronAPI.h"
using namespace std;

namespace TronAPI {
	// 全局变量初始化
	MapType _map = MapType(0);
	int _mapLength = -1, _mapWidth = -1;
	AIType _aiType = TronAPI::AIType::UNINIT;

	// 获取特定类型的结点
	Point getTargetTypePoint(bool typeCheck(MapNodeType))
	{
		Point headLoc;
		for (headLoc.x = 0; headLoc.x < _mapLength; headLoc.x++)
		{
			bool headFound = false;
			for (headLoc.y = 0; headLoc.y < _mapWidth; headLoc.y++)
			{
				if (typeCheck(_map[headLoc.x][headLoc.y]))
				{
					headFound = true;
					break;
				}
			}
			if (headFound)
				break;
		}
		return headLoc;
	}

	int getMapLength() { return _mapLength; }
	int getMapWidth() { return _mapWidth; }
	const MapType getMap() { return _map; }

	// 判断当前结点是否为当前 AI 的结点
	bool nodeIsSelfHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_HEAD);
	}

	// 判断传入的 Point 是否越界 / 撞墙
	bool nodeIsOutOfBound(Point point)
	{
		return point.x < 0 || point.x >= _mapLength || point.y < 0 || point.y >= _mapWidth;
	}

	bool nodeIsSelfHead(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsSelfHead(_map[point.x][point.y]);
	}

	bool nodeIsSelfBody(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_BODY)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_BODY);
	}
	bool nodeIsSelfBody(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsSelfBody(_map[point.x][point.y]);
	}

	// 判断当前结点是否为对手 AI 的结点
	bool nodeIsEnemeHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI2_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI1_HEAD);
	}
	bool nodeIsEnemeHead(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEnemeHead(_map[point.x][point.y]);
	}

	bool nodeIsEnemeBody(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI2_BODY)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI1_BODY);
	}
	bool nodeIsEnemeBody(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEnemeBody(_map[point.x][point.y]);
	}

	// 判断当前结点是否没有被占据
	bool nodeIsEmpty(MapNodeType node) { return node == MapNodeType::NONE; }
	bool nodeIsEmpty(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEmpty(_map[point.x][point.y]);
	}

	// 将错误信息输出至 standard error 流上，并强制退出当前程序
	// 注意执行该函数传入的信息，将会被显示在 远程的RichTextBox中
	void reportErrorAndAbort(string msg)
	{
		cerr << "[FATAL] " << msg << endl;
		abort();
	}
	// 将信息返回至远程程序，但不abort
	void reportInfo(string msg)
	{
		cerr << "[INFO] " << msg << endl;
	}
	// 用户调试用的输出，这类输出将被远程程序截获，但不会被处理
	void printDbgMsg(string msg)
	{
		cerr << "[DEBUG] " << msg << endl;
	}
	// 从远程程序中获取地图信息以及当前身份
	void getMapAndAIRoleFromRemote()
	{
		string AIRole;
		cin >> AIRole >> _mapLength >> _mapWidth;
		// 设置当前 AI 角色
		if (AIRole == "AI1")
			_aiType = AIType::AI1;
		else if (AIRole == "AI2")
			_aiType = AIType::AI2;
		else
			reportErrorAndAbort("设置 AI 角色时出错！");

		// 开始设置地图
		_map = MapType(_mapWidth, MapRowType(_mapLength));
		for (int i = 0; i < _mapLength; i++)
		{
			for (int j = 0; j < _mapWidth; j++)
			{
				std::string singleton;
				cin >> singleton;
				if (singleton == "N")
					_map[j][i] = MapNodeType::NONE;
				else if (singleton == "1B")
					_map[j][i] = MapNodeType::AI1_BODY;
				else if (singleton == "2B")
					_map[j][i] = MapNodeType::AI2_BODY;
				else if (singleton == "1H")
					_map[j][i] = MapNodeType::AI1_HEAD;
				else if (singleton == "2H")
					_map[j][i] = MapNodeType::AI2_HEAD;
				else
					reportErrorAndAbort("remote 端返回了错误的 map 结点格式");
			}
		}
	}
	// 设置当前AI的下一个方向
	void setNextDirection(DirectType direct)
	{
		// 向远程发送信息
		switch (direct)
		{
		case DirectType::Down:	cout << "down";		break;
		case DirectType::Up:	cout << "up";		break;
		case DirectType::Left:	cout << "left";		break;
		case DirectType::Right: cout << "right";	break;
		case DirectType::None:  cout << "none";	break;
		default: reportErrorAndAbort("无法识别的方向");
		}
	}
	// 获取某个坐标向特定方向移动后的坐标
	/// NOTE: 仍然保留原先的函数，以便于更好的兼容旧版API
	Point getTheUpPoint(Point point) { return Point(point.x, point.y - 1); }
	Point getTheDownPoint(Point point) { return Point(point.x, point.y + 1); }
	Point getTheLeftPoint(Point point) { return Point(point.x - 1, point.y); }
	Point getTheRightPoint(Point point) { return Point(point.x + 1, point.y); }

	Point getBesidePoint(Point point,DirectType direct)
	{
		switch (direct)
		{
		case DirectType::Down:	return Point(point.x, point.y + 1);
		case DirectType::Up:	return Point(point.x, point.y - 1);
		case DirectType::Left:	return Point(point.x - 1, point.y);
		case DirectType::Right: return Point(point.x + 1, point.y);
		default: reportErrorAndAbort("无法识别的方向"); return Point();
		}

	}
	// 获取头节点地址
	Point getSelfHeadPoint() { return getTargetTypePoint(nodeIsSelfHead); }
	Point getEnemyHeadPoint() { return getTargetTypePoint(nodeIsEnemeHead); }
};
