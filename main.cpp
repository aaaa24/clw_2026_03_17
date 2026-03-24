#include <iostream>
#include <iomanip>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
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

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Get size", testGetSize},
    {"Get capacity", testGetCapacity},
    {"Inbound access", testElementInboundAccess},
    {"OutOfBound access", testElementOutOfBoundAccess},
    {"Operator []", testOperatorElementAccess},
    {"Push back", testPushBack},
    {"Pop back", testPopBack}
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
