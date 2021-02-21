/***************************************************************
 * @file       main.cpp
 * @brief      ʵ�ֻ�����Ϸ���̿���
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "TronAPI.h"
#include "Windows.h"
// ��������������ͷ�ļ�
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace TronAPI;

/*
   @brief: ��༭�ú���������Լ��� AI ����
*/
TronAPI::DirectType AIGetDirect()
{
//#define TRONDEBUG
	/*
	[README]
		1. ע�⣺ǧ��Ҫʹ�� cin / cout / cerr / printf / scanf �ȵ�
			  ���׼����������׼���������׼��������صĺ������ܡ�
			  �⽫Ӱ�쵽 ��Զ�̳��򽻻� �Ĺ����ȶ��ԡ�
			  ���������Ϣ������̨�������ֻ����ʹ�� `void TronAPI::printDbgMsg(string)` ����
		2. TronAPI.h �����൱һ���ֺ��������д AI������ȥ����
		3. AI��д���壡
	*/

	// todo ��д����AI����

	/*
		������ʾ�� "AI" ���룬���Խ�֮�滻���Լ��� AI ����
	*/
	// ���Ȳ��ҵ�ǰ��headλ��
	Point head = getSelfHeadPoint();
	// �жϵ�ǰ���ߵķ��򣬲�������뼯����
	vector<DirectType> directVector;
	if (nodeIsEmpty(getTheUpPoint(head)))
		directVector.push_back(DirectType::Up);
	if (nodeIsEmpty(getTheDownPoint(head)))
		directVector.push_back(DirectType::Down);
	if (nodeIsEmpty(getTheLeftPoint(head)))
		directVector.push_back(DirectType::Left);
	if (nodeIsEmpty(getTheRightPoint(head)))
		directVector.push_back(DirectType::Right);
	// ���һ����û�У��ǿ϶������Ϸ��,�����һ��
	if (directVector.size() == 0)
	{
		reportInfo("no direct to go");
		return DirectType::None;
	}
	// ����ӿ����б��������һ��
	return directVector[rand() % directVector.size()];
}

// �ó���ÿ���������һ�Σ���� **�����ó���ѭ��** 
// WARNGING���벻Ҫ�޸ĸú���
int main()
{
#ifdef TRONDEBUG
	freopen("in.txt", "r", stdin);
#endif
	// ��ʼ�����������
	LARGE_INTEGER seed;
	QueryPerformanceCounter(&seed);
	srand((unsigned int)seed.QuadPart);//��ʼ��һ����΢��Ϊ��λ��ʱ������
	// ��ȡ����Զ�̵�����
	TronAPI::getMapAndAIRoleFromRemote();
	// ��ȡAI�ж������һ������
	TronAPI::DirectType direct = AIGetDirect();
	// ����һ�����򷵻ظ�Զ��
	TronAPI::setNextDirection(direct);
	return 0;
}