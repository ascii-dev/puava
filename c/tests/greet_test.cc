#include "gtest/gtest.h"

extern "C" {
#include "includes/greet.h"
}

TEST(GreetTest, ReturnsOne) {
  int result = puava_greet();

  ASSERT_EQ(result, 1);
}
