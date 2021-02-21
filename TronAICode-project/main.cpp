/***************************************************************
 * @file       main.cpp
 * @brief      实现基础游戏流程控制
 * @author     Kiprey
 * @date       2021/2/21
 * @note	   请勿随意更改当前文件！
 **************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "TronAPI.h"
#include "Windows.h"
#include <cstdlib>

using namespace TronAPI;

extern DirectType AIGetDirect();

// 该程序每步都会调用一次，因此 **不设置成死循环** 
// WARNGING：请不要修改该函数
int main()
{
#ifdef TRONDEBUG
	freopen("in.txt", "r", stdin);
#endif
	// 初始化随机数种子
	LARGE_INTEGER seed;
	QueryPerformanceCounter(&seed);
	srand((unsigned int)seed.QuadPart);//初始化一个以微秒为单位的时间种子
	// 获取来自远程的数据
	TronAPI::getMapAndAIRoleFromRemote();
	// 获取AI判定后的下一步方向
	TronAPI::DirectType direct = AIGetDirect();
	// 将下一步方向返回给远程
	TronAPI::setNextDirection(direct);
	return 0;
}