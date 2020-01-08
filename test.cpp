
#include <iostream>
#include "minqueue.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

using namespace std;
TEST_CASE("Test 01", "[Project07]")
{
  vector<int>  keys = { 123, 456, 789, 1234, 5678, 91011 };

  minqueue<int, char> queue(6);
           
  REQUIRE(queue.empty());
  queue.pushinorder(keys[0], 'A');
  queue.pushinorder(keys[1], 'B');
  queue.pushinorder(keys[2], 'C');
  queue.pushinorder(keys[3], 'D');
  queue.pushinorder(keys[4], 'E');
  queue.pushinorder(keys[5], 'F');
  REQUIRE(queue.minfront() == 123);
  queue.minpop();
  REQUIRE(queue.minfront() == 456);
  queue.minpop();
  REQUIRE(queue.minfront() == 789);
  queue.minpop();
  REQUIRE(queue.minfront() == 1234);
  queue.minpop();
  REQUIRE(queue.minfront() == 5678);
  queue.minpop();
  REQUIRE(queue.minfront() == 91011);
  queue.minpop();

  REQUIRE(queue.empty());
}
TEST_CASE("Test 02", "[Project07]")
{
  vector<int>  keys = { 123, 456, 789, 1234, 5678, 91011 };
char  initialValue = '#';
  minqueue<int, char> queue(keys, initialValue);
           
  REQUIRE(!queue.empty());

  REQUIRE(queue.minfront() == 123);
  queue.minpop();
  REQUIRE(queue.minfront() == 456);
  queue.minpop();
  REQUIRE(queue.minfront() == 789);
  queue.minpop();
  REQUIRE(queue.minfront() == 1234);
  queue.minpop();
  REQUIRE(queue.minfront() == 5678);
  queue.minpop();
  REQUIRE(queue.minfront() == 91011);
  queue.minpop();

  REQUIRE(queue.empty());
}
TEST_CASE("Test 03", "[Project07]")
{
  vector<int>  keys = { 123, 456, 789, 1234, 5678, 91011 };

  minqueue<int, char> queue(6);
           
  REQUIRE(queue.empty());
  queue.pushinorder(keys[0], 'A');
  REQUIRE(queue.minfront() == 123);
  queue.pushinorder(keys[0], 'A');
  REQUIRE(queue.minfront() == 123);
  REQUIRE(queue.printsize() == 1);
  queue.minpop();
  REQUIRE(queue.printsize() == 0);
  queue.pushinorder(keys[1], 'B');
  REQUIRE(queue.minfront() == 456);
  REQUIRE(queue.printsize() == 1);
  queue.minpop();
  REQUIRE(queue.printsize() == 0);
  queue.pushinorder(keys[0], 'A');
  REQUIRE(queue.printsize() == 1);
  REQUIRE(queue.minfront() == 123);
  queue.minpop();
  REQUIRE(queue.empty());
  queue.pushinorder(keys[1], 'A');
  REQUIRE(queue.printsize() == 1);
  queue.pushinorder(keys[1], 'A');
  REQUIRE(queue.printsize() == 1);
  REQUIRE(queue.minfront() == 456);
  queue.minpop();
  REQUIRE(queue.empty());
  
  
}