#include "gtest/gtest.h"

#include "store.h"

using store::ArticleNumber;
using store::PriceList;

namespace store_tests {

TEST(PriceList, getPrice_shallReturnCorrectValueWhenItemWasAdded)
{
  // Arrange
  PriceList priceList{};
  priceList.setPrice(ArticleNumber{ 7 }, 2.f);
  priceList.setPrice(ArticleNumber{ 4 }, 3.5f);

  // Act
  float returnedValueFirst = priceList.getPrice(ArticleNumber{ 7 });
  float returnedValueSecond = priceList.getPrice(ArticleNumber{ 4 });

  // Assert
  EXPECT_FLOAT_EQ(returnedValueFirst, 2.f);
  EXPECT_FLOAT_EQ(returnedValueSecond, 3.5f);
}
}