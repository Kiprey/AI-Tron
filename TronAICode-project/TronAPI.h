/***************************************************************
 * @file       TronAPI.h
 * @brief      ʵ�� AI ʹ�õĻ���API
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   ����������ĵ�ǰ�ļ���
 **************************************************************/

#pragma once

#include <iostream>
#include <vector>
using namespace std;

namespace TronAPI {
	/*********************** һЩ�������� ***********************/
	// ������
	struct Point {
		int x, y;
		Point(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	};
	// ��ͼ�Ľ����
	enum MapNodeType { AI1_BODY, AI2_BODY, AI1_HEAD, AI2_HEAD, NONE };
	// DirectType �ֱ��ʶ���������ĸ������Լ���һ�εķ���
	// ����ִ�г���ʱû����һ�η������Ϣ����� DirectType::None ���Կ����������� XD
	enum DirectType { Up, Down, Left, Right, None };
	enum AIType { AI1, AI2, UNINIT };
	using MapRowType = vector<MapNodeType>;
	using MapType = vector<MapRowType>;


	/****************** ������һЩ�ڲ��������ڲ���������������� *****************/

	// ȫ�ֱ�����ʼ��
	static MapType _map = MapType(0);
	static int _mapLength = -1, _mapWidth = -1;
	static AIType _aiType = TronAPI::AIType::UNINIT;

	// ��ȡ�ض����͵Ľ��
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

	/****************** ������һЩ���� API �ӿڣ�����ĵ��� *****************/

	inline static int getMapLength() { return _mapLength; }
	inline static int getMapWidth() { return _mapWidth; }
	inline static const MapType getMap() { return _map; }

	// �жϵ�ǰ����Ƿ�Ϊ��ǰ AI �Ľ��
	inline static bool nodeIsSelfHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_HEAD);
	}

	// �жϴ���� Point �Ƿ�Խ�� / ײǽ
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

	// �жϵ�ǰ����Ƿ�Ϊ���� AI �Ľ��
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

	// �жϵ�ǰ����Ƿ�û�б�ռ��
	inline static bool nodeIsEmpty(MapNodeType node) { return node == MapNodeType::NONE; }
	inline static bool nodeIsEmpty(Point point) 
	{ 
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEmpty(_map[point.x][point.y]);
	}

	// ��������Ϣ����� standard error ���ϣ���ǿ���˳���ǰ����
	// ע��ִ�иú����������Ϣ�����ᱻ��ʾ�� Զ�̵�RichTextBox��
	static void reportErrorAndAbort(string msg)
	{
		cerr << "[FATAL] " << msg << endl;
		abort();
	}
	// ����Ϣ������Զ�̳��򣬵���abort
	static void reportInfo(string msg)
	{
		cerr << "[INFO] " << msg << endl;
	}
	// �û������õ�����������������Զ�̳���ػ񣬵����ᱻ����
	static void printDbgMsg(string msg)
	{
		cerr << "[DEBUG] " << msg << endl;
	}
	// ��Զ�̳����л�ȡ��ͼ��Ϣ�Լ���ǰ���
	static void getMapAndAIRoleFromRemote()
	{
		string AIRole;
		cin >> AIRole >> _mapLength >> _mapWidth;
		// ���õ�ǰ AI ��ɫ
		if (AIRole == "AI1")
			_aiType = AIType::AI1;
		else if (AIRole == "AI2")
			_aiType = AIType::AI2;
		else
			reportErrorAndAbort("���� AI ��ɫʱ����");

		// ��ʼ���õ�ͼ
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
					reportErrorAndAbort("remote �˷����˴���� map ����ʽ");
			}
		}
	}
	// ���õ�ǰAI����һ������
	static void setNextDirection(DirectType direct)
	{
		// ��Զ�̷�����Ϣ
		switch (direct)
		{
		case DirectType::Down:	cout << "down";		break;
		case DirectType::Up:	cout << "up";		break;
		case DirectType::Left:	cout << "left";		break;
		case DirectType::Right: cout << "right";	break;
		case DirectType::None:  cout << "none";	break;
		default: reportErrorAndAbort("�޷�ʶ��ķ���");
		}
	}
	// ��ȡĳ���������ض������ƶ��������
	static Point getTheUpPoint(Point point) { return Point(point.x, point.y - 1); }
	static Point getTheDownPoint(Point point) { return Point(point.x, point.y + 1); }
	static Point getTheLeftPoint(Point point) { return Point(point.x - 1, point.y); }
	static Point getTheRightPoint(Point point) { return Point(point.x + 1, point.y); }
	// ��ȡͷ�ڵ��ַ
	static Point getSelfHeadPoint() { return getTargetTypePoint(nodeIsSelfHead); }
	static Point getEnemyHeadPoint() { return getTargetTypePoint(nodeIsEnemeHead); }
};
