/***************************************************************
 * @file       AI.cpp
 * @brief      AI ʵ���㷨
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#include "TronAPI.h"
// ��������������ͷ�ļ�

using namespace TronAPI;

/*
   @brief: ��༭�ú���������Լ��� AI ����
*/
DirectType AIGetDirect()
{
	//#define TRONDEBUG
	/*
	[README]
		1. ע�⣺ǧ��Ҫʹ�� cin / cout / cerr / printf / scanf �ȵ�
				���׼����������׼���������׼��������صĺ������ܡ�
				�⽫Ӱ�쵽 ��Զ�̳��򽻻� �Ĺ����ȶ��ԡ�
				���������Ϣ������̨�������ֻ����ʹ�� `void TronAPI::printDbgMsg(string)` ����
		2. TronAPI.h �����൱һ���ֺ��������д AI�����ٲ鿴��
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