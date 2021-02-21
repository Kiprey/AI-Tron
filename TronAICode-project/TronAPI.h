/***************************************************************
 * @file       TronAPI.h
 * @brief      实现 AI 使用的基础API
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   请勿随意更改当前文件！
 **************************************************************/

#pragma once

#include <iostream>
#include <vector>
using namespace std;

namespace TronAPI {
	/*********************** 一些基础声明 ***********************/
	// 坐标类
	struct Point {
		int x, y;
		Point(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	};
	// 地图的结点类
	enum MapNodeType { AI1_BODY, AI2_BODY, AI1_HEAD, AI2_HEAD, NONE };
	// DirectType 分别标识上下左右四个方向，以及上一次的方向
	// 由于执行程序时没有上一次方向的信息，因此 DirectType::None 可以看作听天由命 XD
	enum DirectType { Up, Down, Left, Right, None };
	enum AIType { AI1, AI2, UNINIT };
	using MapRowType = vector<MapNodeType>;
	using MapType = vector<MapRowType>;


	/****************** 以下是一些内部函数和内部变量，不建议调用 *****************/

	// 全局变量初始化
	static MapType _map = MapType(0);
	static int _mapLength = -1, _mapWidth = -1;
	static AIType _aiType = TronAPI::AIType::UNINIT;

	// 获取特定类型的结点
	static Point getTargetTypePoint(bool typeCheck(MapNodeType))
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

	/****************** 以下是一些公用 API 接口，请放心调用 *****************/

	inline static int getMapLength() { return _mapLength; }
	inline static int getMapWidth() { return _mapWidth; }
	inline static const MapType getMap() { return _map; }

	// 判断当前结点是否为当前 AI 的结点
	inline static bool nodeIsSelfHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_HEAD);
	}

	// 判断传入的 Point 是否越界 / 撞墙
	inline static bool nodeIsOutOfBound(Point point)
	{
		return point.x < 0 || point.x >= _mapLength || point.y < 0 || point.y >= _mapWidth;
	}

	inline static bool nodeIsSelfHead(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsSelfHead(_map[point.x][point.y]);
	}

	inline static bool nodeIsSelfBody(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_BODY)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_BODY);
	}
	inline static bool nodeIsSelfBody(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsSelfBody(_map[point.x][point.y]);
	}

	// 判断当前结点是否为对手 AI 的结点
	inline static bool nodeIsEnemeHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI2_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI1_HEAD);
	}
	inline static bool nodeIsEnemeHead(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEnemeHead(_map[point.x][point.y]);
	}

	inline static bool nodeIsEnemeBody(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI2_BODY)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI1_BODY);
	}
	inline static bool nodeIsEnemeBody(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEnemeBody(_map[point.x][point.y]);
	}

	// 判断当前结点是否没有被占据
	inline static bool nodeIsEmpty(MapNodeType node) { return node == MapNodeType::NONE; }
	inline static bool nodeIsEmpty(Point point) 
	{ 
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEmpty(_map[point.x][point.y]);
	}

	// 将错误信息输出至 standard error 流上，并强制退出当前程序
	// 注意执行该函数传入的信息，将会被显示在 远程的RichTextBox中
	static void reportErrorAndAbort(string msg)
	{
		cerr << "[FATAL] " << msg << endl;
		abort();
	}
	// 将信息返回至远程程序，但不abort
	static void reportInfo(string msg)
	{
		cerr << "[INFO] " << msg << endl;
	}
	// 用户调试用的输出，这类输出将被远程程序截获，但不会被处理
	static void printDbgMsg(string msg)
	{
		cerr << "[DEBUG] " << msg << endl;
	}
	// 从远程程序中获取地图信息以及当前身份
	static void getMapAndAIRoleFromRemote()
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
	static void setNextDirection(DirectType direct)
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
	static Point getTheUpPoint(Point point) { return Point(point.x, point.y - 1); }
	static Point getTheDownPoint(Point point) { return Point(point.x, point.y + 1); }
	static Point getTheLeftPoint(Point point) { return Point(point.x - 1, point.y); }
	static Point getTheRightPoint(Point point) { return Point(point.x + 1, point.y); }
	// 获取头节点地址
	static Point getSelfHeadPoint() { return getTargetTypePoint(nodeIsSelfHead); }
	static Point getEnemyHeadPoint() { return getTargetTypePoint(nodeIsEnemeHead); }
};
