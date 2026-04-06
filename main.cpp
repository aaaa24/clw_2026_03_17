#include <iostream>
#include <iomanip>
#include "Vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2 = v1;
  return v1 == v2;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v1;
  v1.pushBack(42);
  topit::Vector< int > v2 = v1;
  return v1 == v2;
}

bool testMoveConstructorForEmpty()
{
  topit::Vector< int > v1;
  topit::Vector< int > v2 = std::move(v1);
  return v2.isEmpty();
}

bool testMoveConstructorForNonEmpty()
{
  topit::Vector< int > v1;
  v1.pushBack(42);
  topit::Vector< int > v2 = std::move(v1);
  bool res = v2[0] == 42;
  res = res && v2.getSize() == 1;
  return res;
}

bool testCopyOperatorForEmpty()
{
    topit::Vector< int > v1;
    topit::Vector< int > v2;
    v2.pushBack(42);
    v2 = v1;
    return v2.isEmpty() && v2.getSize() == v1.getSize();
}

bool testCopyOperatorForNonEmpty()
{
    topit::Vector< int > v1;
    v1.pushBack(1);
    v1.pushBack(2);
    topit::Vector< int > v2;
    v2.pushBack(42);
    v2 = v1;
    return v2 == v1 && v2.getSize() == 2 && v2[0] == 1 && v2[1] == 2;
}

bool testCopyOperatorSelf()
{
    topit::Vector< int > v;
    v.pushBack(1);
    v.pushBack(2);
    v = v;
    return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testInitializerList()
{
  topit::Vector< int > v({1, 2, 3});
  return v.getSize() == 3 && v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testMoveOperatorForEmpty()
{
    topit::Vector< int > v1;
    topit::Vector< int > v2;
    v2.pushBack(42);
    v2 = std::move(v1);
    return v2.isEmpty();
}

bool testMoveOperatorForNonEmpty()
{
    topit::Vector< int > v1;
    v1.pushBack(1);
    v1.pushBack(2);
    topit::Vector< int > v2;
    v2.pushBack(42);
    v2 = std::move(v1);
    return v2.getSize() == 2 && v2[0] == 1 && v2[1] == 2;
}

bool testBegin()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  topit::VIter< int > iter = v.begin();
  return *iter == 42;
}

bool testEnd()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  topit::VIter< int > iter = v.begin() + 2;
  return iter == v.end();
}

bool testBeginConst()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  const topit::Vector< int > & vc = v;
  topit::VCIter< int > iter = vc.begin();
  return *iter == 42;
}

bool testEndConst()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  const topit::Vector< int > & vc = v;
  topit::VCIter< int > iter = vc.begin() + 2;
  return iter == vc.end();
}

bool testCBeginConst()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  topit::VCIter< int > iter = v.cbegin();
  return *iter == 42;
}

bool testCEndConst()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  topit::VCIter< int > iter = v.cbegin() + 2;
  return iter == v.cend();
}

bool testSwap()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);

  topit::Vector< int > yav;
  yav.pushBack(62);

  v.swap(yav);

  bool res = v.getSize() == 1 && yav.getSize() == 2;
  res = res && v[0] == 62;
  res = res && yav[0] == 42 && yav[1] == 52;
  return res;
}

bool testGetSize()
{
  topit::Vector< int > v;
  v.pushBack(42);
  return v.getSize() == 1;
}

bool testGetCapacity()
{
  topit::Vector< int > v;
  v.pushBack(42);
  return v.getCapacity() == 1;
}

bool testReserve()
{
  topit::Vector< int > v({1, 2, 3});
  v.reserve(100);
  bool res = v.getCapacity() == 100;
  res = res && v[0] == 1 && v[1] == 2 && v[2] == 3;
  return res;
}

bool testShrinkToFit()
{
  topit::Vector< int > v({1, 2, 3});
  v.reserve(100);
  v.shrinkToFit();
  bool res = v.getCapacity() == 3;
  res = res && v[0] == 1 && v[1] == 2 && v[2] == 3;
  return res;
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  bool res = true;
  try {
    res = res && v.at(0) == 42;
    res = res && v.at(1) == 52;
  } catch (...) {
    res = false;
  }
  return res;
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  const topit::Vector< int > & cv = v;
  bool res = true;
  try {
    res = res && cv.at(0) == 42;
    res = res && cv.at(1) == 52;
  } catch (...) {
    res = false;
  }
  return res;
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range & e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  topit::Vector< int > v;
  const topit::Vector< int > & cv = v;
  try {
    cv.at(0);
    return false;
  } catch (const std::out_of_range & e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testOperatorElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  bool res = v[0] == 42;
  res = res && v[1] == 52;
  return res;
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(42);
  bool res = v[0] == 42;
  v.pushBack(52);
  res = res && v[1] == 52;
  res = res && v.getSize() == 2;
  return res;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  bool res = v[1] == 52;
  v.popBack();
  res = res && v[0] == 42;
  res = res && v.getSize() == 1;
  return res;
}

bool testInsertOneToCorrectPos()
{
  topit::Vector< int > v;

  bool res = true;
  try {
    int num = 42;
    v.insert(0, num);
    res = res && v[0] == 42;

    v.insert(0, 52);
    res = res && v[0] == 52 && v[1] == 42;

    v.insert(2, 62);
    res = res && v[0] == 52 && v[1] == 42 && v[2] == 62;

    v.insert(1, 72);
    res = res && v[0] == 52 && v[1] == 72 && v[2] == 42 && v[3] == 62;
  } catch (...) {
    res = false;
  }
  return res;
}

bool testInsertOneToIncorrectPos()
{
  topit::Vector< int > v;

  try {
    v.insert(1, 42);
    return false;
  } catch (const std::out_of_range & e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertManyToCorrectPos()
{
  topit::Vector< int > v;

  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);
  yav.pushBack(3);
  yav.pushBack(4);

  bool res = true;
  try {
    v.insert(0, yav, 0, 1);
    res = res && v[0] == 1 && v.getSize() == 1;

    v.insert(1, yav, 2, 4);
    res = res && v[0] == 1 && v[1] == 3 && v[2] == 4 && v.getSize() == 3;
  } catch (...) {
    res = false;
  }
  return res;
}

bool testInsertManyToIncorrectPos()
{
  topit::Vector< int > v;

  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);

  try {
    v.insert(1, yav, 0, 2);
    return false;
  } catch (const std::exception & e) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testInsertManyWithIncorrectBounds()
{
  topit::Vector< int > v;
  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);

  try {
    v.insert(0, v, 2, 1);
    return false;
  } catch (const std::exception & e) {
  } catch (...) {
    return false;
  }

  try {
    v.insert(0, v, 1, 5);
    return false;
  } catch (const std::exception & e) {
  } catch (...) {
    return false;
  }
  return true;
}

bool testIterInsertOne()
{
  topit::Vector< int > v;
  topit::VIter< int > iter = v.begin();
  bool res = true;

  int num = 42;
  iter = v.insert(iter, num);
  res = res && v[0] == 42;

  iter = v.insert(iter, 52);
  res = res && v[0] == 52 && v[1] == 42;

  iter = v.insert(iter + 2, 62);
  res = res && v[0] == 52 && v[1] == 42 && v[2] == 62;

  iter = v.insert(iter - 1, 72);
  res = res && v[0] == 52 && v[1] == 72 && v[2] == 42 && v[3] == 62;

  return res;
}

bool testIterInsertMany()
{
  topit::Vector< int > v;
  topit::VIter< int > iter = v.begin();

  topit::Vector< int > yav;
  yav.pushBack(1);
  yav.pushBack(2);
  yav.pushBack(3);
  yav.pushBack(4);
  topit::VIter< int > yav_iter = yav.begin();

  bool res = true;

  iter = v.insert(iter, yav_iter, yav_iter + 1);
  res = res && v[0] == 1 && v.getSize() == 1;

  iter = v.insert(iter + 1, yav_iter + 2, yav_iter + 4);
  res = res && v[0] == 1 && v[1] == 3 && v[2] == 4 && v.getSize() == 3;

  res = res && iter == v.insert(iter, yav_iter, yav_iter);

  return res;
}

bool testEraseOne()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; ++i) {
    v.pushBack(i);
  }

  bool res = true;
  try {
    v.erase(2);
    res = res && v.getSize() == 4;
    res = res && v[0] == 0 && v[1] == 1 && v[2] == 3 && v[3] == 4;

    v.erase(0);
    res = res && v.getSize() == 3;
    res = res && v[0] == 1 && v[1] == 3 && v[2] == 4;

    v.erase(2);
    res = res && v.getSize() == 2;
    res = res && v[0] == 1 && v[1] == 3;
  } catch (...) {
    res = false;
  }
  return res;
}

bool testEraseOneOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(42);
  try {
    v.erase(1);
    return false;
  } catch (const std::out_of_range &) {
    return true;
  } catch (...) {
    return false;
  }
}

bool testEraseMany()
{
  topit::Vector< int > v;
  for (int i = 0; i < 10; ++i) {
    v.pushBack(i);
  }
  bool res = true;
  try {
    v.erase(2, 5);
    res = res && v.getSize() == 7;
    res = res && v[0] == 0 && v[1] == 1 && v[2] == 5 && v[3] == 6 && v[4] == 7 && v[5] == 8 && v[6] == 9;

    v.erase(0, 2);
    res = res && v.getSize() == 5;
    res = res && v[0] == 5 && v[1] == 6 && v[2] == 7 && v[3] == 8 && v[4] == 9;

    v.erase(3, 5);
    res = res && v.getSize() == 3;
    res = res && v[0] == 5 && v[1] == 6 && v[2] == 7;

    v.erase(1, 1);
    res = res && v.getSize() == 3;
    res = res && v[0] == 5 && v[1] == 6 && v[2] == 7;

    v.erase(0, v.getSize());
    res = res && v.isEmpty();
  } catch (...) {
    res = false;
  }
  return res;
}

bool testEraseOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);

  try {
    v.erase(3, 4);
    return false;
  } catch (const std::out_of_range &) {
  } catch (...) {
    return false;
  }

  try {
    v.erase(1, 3);
    return false;
  } catch (const std::out_of_range &) {
  } catch (...) {
    return false;
  }

  return true;
}

bool testIterEraseOne()
{
  topit::Vector< int > v;
  for (int i = 0; i < 5; ++i) {
    v.pushBack(i);
  }
  topit::VIter< int > iter = v.begin();

  bool res = true;

  iter = v.erase(iter + 2);
  res = res && v.getSize() == 4;
  res = res && v[0] == 0 && v[1] == 1 && v[2] == 3 && v[3] == 4;

  iter = v.erase(iter - 2);
  res = res && v.getSize() == 3;
  res = res && v[0] == 1 && v[1] == 3 && v[2] == 4;

  iter = v.erase(iter + 2);
  res = res && v.getSize() == 2;
  res = res && v[0] == 1 && v[1] == 3;

  return res;
}

bool testIterEraseMany()
{
  topit::Vector< int > v;
  for (int i = 0; i < 10; ++i) {
    v.pushBack(i);
  }
  topit::VIter< int > iter = v.begin();

  bool res = true;

  iter = v.erase(iter + 2, iter + 5);
  res = res && v.getSize() == 7;
  res = res && v[0] == 0 && v[1] == 1 && v[2] == 5 && v[3] == 6 && v[4] == 7 && v[5] == 8 && v[6] == 9;

  iter = v.erase(iter - 2, iter);
  res = res && v.getSize() == 5;
  res = res && v[0] == 5 && v[1] == 6 && v[2] == 7 && v[3] == 8 && v[4] == 9;

  iter = v.erase(iter + 3, iter + 5);
  res = res && v.getSize() == 3;
  res = res && v[0] == 5 && v[1] == 6 && v[2] == 7;

  iter = v.erase(iter, iter);
  res = res && v.getSize() == 3;
  res = res && v[0] == 5 && v[1] == 6 && v[2] == 7;

  v.erase(v.begin(), v.end());
  res = res && v.isEmpty();

  return res;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Copy empty vector", testCopyConstructorForEmpty},
    {"Copy non-empty vector", testCopyConstructorForNonEmpty},
    {"Move empty vector", testMoveConstructorForEmpty},
    {"Move non-empty vector", testMoveConstructorForNonEmpty},
    {"Non-empty vector for non-empty initializer list", testInitializerList},
    {"Copy operator for empty vector", testCopyOperatorForEmpty},
    {"Copy operator for non-empty vector", testCopyOperatorForNonEmpty},
    {"Copy operator self", testCopyOperatorSelf},
    {"Move operator for empty vector", testMoveOperatorForEmpty},
    {"Move operator for non-empty vector", testMoveOperatorForNonEmpty},
    {"Get begin iterator", testBegin},
    {"Get begin iterator", testEnd},
    {"Get begin const iterator", testBeginConst},
    {"Get begin const iterator", testEndConst},
    {"Get cbegin const iterator", testCBeginConst},
    {"Get cend const iterator", testCEndConst},
    {"Swap", testSwap},
    {"Get size", testGetSize},
    {"Get capacity", testGetCapacity},
    {"Reserve", testReserve},
    {"Shrink to fit", testShrinkToFit},
    {"Inbound access", testElementInboundAccess},
    {"Inbound const access", testElementInboundConstAccess},
    {"OutOfBound access", testElementOutOfBoundAccess},
    {"OutOfBound const access", testElementOutOfBoundConstAccess},
    {"Operator []", testOperatorElementAccess},
    {"Push back", testPushBack},
    {"Pop back", testPopBack},
    {"Insert one element to correct position", testInsertOneToCorrectPos},
    {"Insert one element to incorrect position", testInsertOneToIncorrectPos},
    {"Insert many elements to correct position", testInsertManyToCorrectPos},
    {"Insert many elements to incorrect position", testInsertManyToIncorrectPos},
    {"Insert many elements with incorrect bounds", testInsertManyWithIncorrectBounds},
    {"Insert one element to correct position by iter", testIterInsertOne},
    {"Insert many elements to correct position by iter", testIterInsertMany},
    {"Erase one element", testEraseOne},
    {"Erase one element out of range", testEraseOneOutOfRange},
    {"Erase range", testEraseMany},
    {"Erase range out of range", testEraseOutOfRange},
    {"Erase one element by iter", testIterEraseOne},
    {"Erase many elements by iter", testIterEraseMany}
  };
  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i) {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";\
    pass = pass && res;
  }
  std::cout << "RESULT: " << pass << "\n";
}
