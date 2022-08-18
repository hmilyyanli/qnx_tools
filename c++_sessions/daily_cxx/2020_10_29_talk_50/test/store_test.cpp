#include "gtest/gtest.h"

#include "store.h"

using store::ArticleNumber;
using store::PriceList;
using store::Store;

namespace store_tests {

TEST(PriceListTest, getPriceShallReturnCorrectValueWhenItemWasAdded)
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

class StoreFixture : public ::testing::Test
{
protected:
  StoreFixture()
  {
    priceList.setPrice(validArticleNumbers.at(0), 1.5f);
    priceList.setPrice(validArticleNumbers.at(1), 3.5f);
    priceList.setPrice(validArticleNumbers.at(2), 2.5f);
  }

  // Hint: You could omit all functions that are not used, i.e. in this example
  // the only function you need to implement is the constructor
  ~StoreFixture() = default;

  void SetUp() override {}
  void TearDown() override {}

  static void SetUpTestCase(){};
  static void TearDownTestCase(){};

  std::vector<ArticleNumber> validArticleNumbers{ ArticleNumber{ 43 },
                                                  ArticleNumber{ 5 },
                                                  ArticleNumber{ 2 } };

  PriceList priceList{};
  Store store{ priceList };
};

TEST_F(StoreFixture, orderShallRemoveItemsFromStore)
{
  // Arrange
  store.acceptDelivery({ { validArticleNumbers.at(0), 3 },
                         { validArticleNumbers.at(1), 1 },
                         { validArticleNumbers.at(2), 1 } });
  std::vector<std::pair<ArticleNumber, int>> order = {
    { validArticleNumbers.at(0), 2 }
  };
  ASSERT_TRUE(store.isInStock(order));

  // Act
  store.order(order);

  // Assert
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(0)), 1); // reduced
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(1)), 1); // same
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(2)), 1); // same
}

TEST_F(StoreFixture, orderShallXWhenY)
{
  // Arrange
  store.acceptDelivery({ { validArticleNumbers.at(0), 3 },
                         { validArticleNumbers.at(1), 1 },
                         { validArticleNumbers.at(2), 1 } });
  std::vector<std::pair<ArticleNumber, int>> order = {
    { validArticleNumbers.at(0), 3 }
  };
  ASSERT_TRUE(store.isInStock(order));

  // Act
  store.order(order);

  // Assert
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(0)), 0); // reduced
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(1)), 1); // same
  ASSERT_EQ(store.getInventory(validArticleNumbers.at(2)), 1); // same
}
}