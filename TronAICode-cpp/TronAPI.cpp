/***************************************************************
 * @file       TronAPI.cpp
 * @brief      ʵ�� AI ʹ�õĻ���API �ľ��庯��ʵ��
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   ����������ĵ�ǰ�ļ���
 **************************************************************/

#pragma once

#include "TronAPI.h"
using namespace std;

namespace TronAPI {
	// ȫ�ֱ�����ʼ��
	MapType _map = MapType(0);
	int _mapLength = -1, _mapWidth = -1;
	AIType _aiType = TronAPI::AIType::UNINIT;

	// ��ȡ�ض����͵Ľ��
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

	// �жϵ�ǰ����Ƿ�Ϊ��ǰ AI �Ľ��
	bool nodeIsSelfHead(MapNodeType node)
	{
		return (_aiType == AIType::AI1 && node == MapNodeType::AI1_HEAD)
			|| (_aiType == AIType::AI2 && node == MapNodeType::AI2_HEAD);
	}

	// �жϴ���� Point �Ƿ�Խ�� / ײǽ
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

	// �жϵ�ǰ����Ƿ�Ϊ���� AI �Ľ��
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

	// �жϵ�ǰ����Ƿ�û�б�ռ��
	bool nodeIsEmpty(MapNodeType node) { return node == MapNodeType::NONE; }
	bool nodeIsEmpty(Point point)
	{
		if (nodeIsOutOfBound(point))
			return false;
		return nodeIsEmpty(_map[point.x][point.y]);
	}

	// ��������Ϣ����� standard error ���ϣ���ǿ���˳���ǰ����
	// ע��ִ�иú����������Ϣ�����ᱻ��ʾ�� Զ�̵�RichTextBox��
	void reportErrorAndAbort(string msg)
	{
		cerr << "[FATAL] " << msg << endl;
		abort();
	}
	// ����Ϣ������Զ�̳��򣬵���abort
	void reportInfo(string msg)
	{
		cerr << "[INFO] " << msg << endl;
	}
	// �û������õ�����������������Զ�̳���ػ񣬵����ᱻ����
	void printDbgMsg(string msg)
	{
		cerr << "[DEBUG] " << msg << endl;
	}
	// ��Զ�̳����л�ȡ��ͼ��Ϣ�Լ���ǰ���
	void getMapAndAIRoleFromRemote()
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
	void setNextDirection(DirectType direct)
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
	/// NOTE: ��Ȼ����ԭ�ȵĺ������Ա��ڸ��õļ��ݾɰ�API
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
		default: reportErrorAndAbort("�޷�ʶ��ķ���"); return Point();
		}

	}
	// ��ȡͷ�ڵ��ַ
	Point getSelfHeadPoint() { return getTargetTypePoint(nodeIsSelfHead); }
	Point getEnemyHeadPoint() { return getTargetTypePoint(nodeIsEnemeHead); }
};
