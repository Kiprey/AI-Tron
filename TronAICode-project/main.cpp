/***************************************************************
 * @file       main.cpp
 * @brief      实现基础游戏流程控制
 * @author     Kiprey
 * @date       2021/2/21
 **************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include "TronAPI.h"
#include "Windows.h"
// 请自行添加所需的头文件
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace TronAPI;

/*
   @brief: 请编辑该函数以设计自己的 AI 代码
*/
TronAPI::DirectType AIGetDirect()
{
//#define TRONDEBUG
	/*
	[README]
		1. 注意：千万不要使用 cin / cout / cerr / printf / scanf 等等
			  与标准输入流、标准输出流、标准错误流相关的函数或功能。
			  这将影响到 与远程程序交互 的功能稳定性。
			  如需输出信息至控制台输出，则只允许使用 `void TronAPI::printDbgMsg(string)` 函数
		2. TronAPI.h 中有相当一部分函数方便编写 AI。速速去看！
		3. AI编写冲冲冲！
	*/

	// todo 编写个人AI代码

	/*
		以下是示例 "AI" 代码，可以将之替换成自己的 AI 代码
	*/
	// 首先查找当前的head位置
	Point head = getSelfHeadPoint();
	// 判断当前可走的方向，并将其加入集合中
	vector<DirectType> directVector;
	if (nodeIsEmpty(getTheUpPoint(head)))
		directVector.push_back(DirectType::Up);
	if (nodeIsEmpty(getTheDownPoint(head)))
		directVector.push_back(DirectType::Down);
	if (nodeIsEmpty(getTheLeftPoint(head)))
		directVector.push_back(DirectType::Left);
	if (nodeIsEmpty(getTheRightPoint(head)))
		directVector.push_back(DirectType::Right);
	// 如果一个都没有，那肯定输掉游戏了,随便走一个
	if (directVector.size() == 0)
	{
		reportInfo("no direct to go");
		return DirectType::None;
	}
	// 否则从可走列表中随便走一个
	return directVector[rand() % directVector.size()];
}

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