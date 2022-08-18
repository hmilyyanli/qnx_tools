#ifndef STORE_H
#define STORE_H

#include <cassert>
#include <map>
#include <utility> // pair
#include <vector>

namespace store {

struct ArticleNumber
{
  ArticleNumber() = default;
  explicit ArticleNumber(int number)
    : value{ number }
  {}
  // Required for use in map
  bool operator<(const ArticleNumber& other) const
  {
    return value < other.value;
  }

  int value = -1;
};

class PriceList
{
public:
  // Returns the price of an existing article. The article number must have been
  // added beforehand
  float getPrice(ArticleNumber itemId) const
  {
    assert(m_priceList.find(itemId) != m_priceList.end());
    return m_priceList.at(itemId);
  }

  // Add or update a price
  void setPrice(ArticleNumber id, float price)
  {
    m_priceList.insert(std::make_pair(id, price));
  }

private:
  std::map<ArticleNumber, float> m_priceList;
};

class Store
{
public:
  Store(const PriceList& priceList)
    : m_priceList{ priceList }
    , m_storage{}
  {}

  // Stores the items in the delivery. A delivery can be thought of as multiple
  // packages, each containing a certain amount of one article
  void acceptDelivery(
    const std::vector<std::pair<ArticleNumber, int>>& delivery);

  // Checks if the articles in the order are available in the store
  bool isInStock(const std::vector<std::pair<ArticleNumber, int>>& order) const;

  // Returns the number of items in stock
  int getInventory(ArticleNumber articlenumber) const;

  // Precondition:  Enough items are in the storage to fullfil this order.
  //                The pricelist contains all articlenumbers in this order.
  //                Articlenumbers can occurr multiple times.
  // Postcondition: The items in the order are removed from the storage,
  //                all other amounts are kept the same
  // @return The price of this order
  float order(const std::vector<std::pair<ArticleNumber, int>>& order);

private:
  const PriceList& m_priceList;
  std::map<ArticleNumber, int> m_storage;
};

} // namespace store

#endif STORE_H
