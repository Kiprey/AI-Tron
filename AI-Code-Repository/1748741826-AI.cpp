#include "TronAPI.h"
using namespace TronAPI;

DirectType AIGetDirect() {
  Point head = getSelfHeadPoint();
  vector<DirectType> directVector;

  // AI 1

  if (nodeIsEmpty(getTheUpPoint(head)) && nodeIsEmpty(getTheRightPoint(head)) &&
      nodeIsEmpty(getTheDownPoint(head))) {
    return DirectType::Up;
  }
  if (nodeIsEmpty(getTheDownPoint(head)) &&
      nodeIsEmpty(getTheRightPoint(head))) {
    return DirectType::Down;
  }
  if (nodeIsEmpty(getTheLeftPoint(head)) &&
      nodeIsEmpty(getTheRightPoint(head)) && getTheUpPoint(head).x == 2) {
    return DirectType::Right;
  }
  if (nodeIsEmpty(getTheUpPoint(head)) && nodeIsEmpty(getTheRightPoint(head))) {
    return DirectType::Up;
  }
  if (nodeIsEmpty(getTheRightPoint(head)) && getTheUpPoint(head).x <= 15) {
    return DirectType::Right;
  }

  // AI 2
  if (nodeIsEmpty(getTheUpPoint(head)) && nodeIsEmpty(getTheLeftPoint(head)) &&
      nodeIsEmpty(getTheDownPoint(head))) {
    return DirectType::Down;
  }
  if (nodeIsEmpty(getTheDownPoint(head)) &&
      nodeIsEmpty(getTheLeftPoint(head))) {
    return DirectType::Down;
  }
  if (nodeIsEmpty(getTheLeftPoint(head)) &&
      nodeIsEmpty(getTheRightPoint(head))) {
    return DirectType::Left;
  }
  if (nodeIsEmpty(getTheUpPoint(head)) && nodeIsEmpty(getTheLeftPoint(head))) {
    return DirectType::Up;
  }
  if (nodeIsEmpty(getTheLeftPoint(head))) {
    return DirectType::Left;
  }
  
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
  
    return directVector[rand() % directVector.size()];
}