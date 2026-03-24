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

bool testAt()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  bool res = v.at(0) == 42;
  res = res && v.at(1) == 52;
  return res;
}

bool testOperatorAt()
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
  v.pushBack(52);
  return v.getSize() == 2;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(42);
  v.pushBack(52);
  v.popBack();
  return v.getSize() == 1;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = {
    {"Empty vector", testEmptyVector},
    {"Get size", testGetSize},
    {"Get capacity", testGetCapacity},
    {"At", testAt},
    {"Operator []", testOperatorAt},
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
