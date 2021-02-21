/***************************************************************
 * @file       TronAPI.h
 * @brief      实现 AI 使用的基础API 的简要头文件
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   请勿随意更改当前文件！
 **************************************************************/

#ifndef TRONAPI_H
#define TRONAPI_H

#include <iostream>
#include <vector>
using namespace std;

// 如需启用 freopen，可以解除下行代码的注释符
//#ifdef TRONDEBUG

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

	// 获取特定类型的结点
	Point getTargetTypePoint(bool typeCheck(MapNodeType));

	inline int getMapLength();
	inline int getMapWidth();
	inline const MapType getMap();

	// 判断传入的 Point 是否越界 / 撞墙
	bool nodeIsOutOfBound(Point point);

	// 判断当前结点是否为当前 AI 的结点
	bool nodeIsSelfHead(MapNodeType node);
	bool nodeIsSelfHead(Point point);

	bool nodeIsSelfBody(MapNodeType node);
	bool nodeIsSelfBody(Point point);

	// 判断当前结点是否为对手 AI 的结点
	bool nodeIsEnemeHead(MapNodeType node);
	bool nodeIsEnemeHead(Point point);

	bool nodeIsEnemeBody(MapNodeType node);
	bool nodeIsEnemeBody(Point point);

	// 判断当前结点是否没有被占据
	bool nodeIsEmpty(MapNodeType node);
	bool nodeIsEmpty(Point point);

	// 将错误信息输出至 standard error 流上，并强制退出当前程序
	// 注意执行该函数传入的信息，将会被显示在 远程的RichTextBox中
	void reportErrorAndAbort(string msg);
	// 将信息返回至远程程序，但不abort
	void reportInfo(string msg);
	// 用户调试用的输出，这类输出将被远程程序截获，但不会被处理
	void printDbgMsg(string msg);
	// 从远程程序中获取地图信息以及当前身份
	void getMapAndAIRoleFromRemote();
	// 设置当前AI的下一个方向
	void setNextDirection(DirectType direct);
	// 获取某个坐标向特定方向移动后的坐标
	Point getTheUpPoint(Point point);
	Point getTheDownPoint(Point point);
	Point getTheLeftPoint(Point point);
	Point getTheRightPoint(Point point);
	// 获取头节点地址
	Point getSelfHeadPoint();
	Point getEnemyHeadPoint();
};

#endif;