/***************************************************************
 * @file       main.cpp
 * @brief      ʵ�ֻ�����Ϸ���̿���
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   ����������ĵ�ǰ�ļ���
 **************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "TronAPI.h"
#include "Windows.h"
#include <cstdlib>

using namespace TronAPI;

extern DirectType AIGetDirect();

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