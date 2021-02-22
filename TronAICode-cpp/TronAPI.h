/***************************************************************
 * @file       TronAPI.h
 * @brief      ʵ�� AI ʹ�õĻ���API �ļ�Ҫͷ�ļ�
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   ����������ĵ�ǰ�ļ���
 **************************************************************/

#ifndef TRONAPI_H
#define TRONAPI_H

#include <iostream>
#include <vector>
using namespace std;

// �������� freopen�����Խ�����д����ע�ͷ�
//#ifdef TRONDEBUG

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

	// ��ȡ�ض����͵Ľ��
	Point getTargetTypePoint(bool typeCheck(MapNodeType));

	inline int getMapLength();
	inline int getMapWidth();
	inline const MapType getMap();

	// �жϴ���� Point �Ƿ�Խ�� / ײǽ
	bool nodeIsOutOfBound(Point point);

	// �жϵ�ǰ����Ƿ�Ϊ��ǰ AI �Ľ��
	bool nodeIsSelfHead(MapNodeType node);
	bool nodeIsSelfHead(Point point);

	bool nodeIsSelfBody(MapNodeType node);
	bool nodeIsSelfBody(Point point);

	// �жϵ�ǰ����Ƿ�Ϊ���� AI �Ľ��
	bool nodeIsEnemeHead(MapNodeType node);
	bool nodeIsEnemeHead(Point point);

	bool nodeIsEnemeBody(MapNodeType node);
	bool nodeIsEnemeBody(Point point);

	// �жϵ�ǰ����Ƿ�û�б�ռ��
	bool nodeIsEmpty(MapNodeType node);
	bool nodeIsEmpty(Point point);

	// ��������Ϣ����� standard error ���ϣ���ǿ���˳���ǰ����
	// ע��ִ�иú����������Ϣ�����ᱻ��ʾ�� Զ�̵�RichTextBox��
	void reportErrorAndAbort(string msg);
	// ����Ϣ������Զ�̳��򣬵���abort
	void reportInfo(string msg);
	// �û������õ�����������������Զ�̳���ػ񣬵����ᱻ����
	void printDbgMsg(string msg);
	// ��Զ�̳����л�ȡ��ͼ��Ϣ�Լ���ǰ���
	void getMapAndAIRoleFromRemote();
	// ���õ�ǰAI����һ������
	void setNextDirection(DirectType direct);
	// ��ȡĳ���������ض������ƶ��������
	Point getTheUpPoint(Point point);
	Point getTheDownPoint(Point point);
	Point getTheLeftPoint(Point point);
	Point getTheRightPoint(Point point);
	// ��ȡͷ�ڵ��ַ
	Point getSelfHeadPoint();
	Point getEnemyHeadPoint();
};

#endif;