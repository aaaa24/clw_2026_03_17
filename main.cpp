#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

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
  bool res = v2.at(0) == 42;
  res = res && v2.getSize() == 1;
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
  bool res = v.at(0) == 42;
  res = res && v.at(1) == 52;
  return res;
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(42);
  bool res = v.at(0) == 42;
  v.pushBack(52);
  res = res && v.at(1) == 52;
  res = res && v.getSize() == 2;
  return res;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  bool res = v.at(1) == 52;
  v.popBack();
  res = res && v.at(0) == 42;
  res = res && v.getSize() == 1;
  return res;
}

bool testInsertOneToCorrectPos()
{
  topit::Vector< int > v;

  bool res = true;
  try {
    v.insert(0, 42);
    res = res && v.at(0) == 42;

    v.insert(0, 52);
    res = res && v.at(0) == 52 && v.at(1) == 42;

    v.insert(2, 62);
    res = res && v.at(0) == 52 && v.at(1) == 42 && v.at(2) == 62;

    v.insert(1, 72);
    res = res && v.at(0) == 52 && v.at(1) == 72 && v.at(2) == 42 && v.at(3) == 62;
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
    res = res && v.at(0) == 1 && v.getSize() == 1;

    v.insert(1, yav, 2, 4);
    res = res && v.at(0) == 1 && v.at(1) == 3 && v.at(2) == 4 && v.getSize() == 3;
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

  bool res = true;
  try {
    v.insert(0, v, 2, 1);
    res = res && false;
  } catch (const std::exception & e) {
    res = res && true;
  } catch (...) {
    res = res && false;
  }
  try {
    v.insert(0, v, 1, 5);
    res = res && false;
  } catch (const std::exception & e) {
    res = res && true;
  } catch (...) {
    res = res && false;
  }
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
    {"Get size", testGetSize},
    {"Get capacity", testGetCapacity},
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
    {"Insert many elements with incorrect bounds", testInsertManyWithIncorrectBounds}
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
