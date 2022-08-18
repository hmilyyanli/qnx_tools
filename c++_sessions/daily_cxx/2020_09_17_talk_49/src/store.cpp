#include "store.h"

void
store::Store::acceptDelivery(
  const std::vector<std::pair<ArticleNumber, int>>& delivery)
{
  for (auto& package : delivery) {
    m_storage[package.first] = package.second;
  }
}

bool
store::Store::isInStock(
  const std::vector<std::pair<ArticleNumber, int>>& order) const
{
  bool isInStock = true;
  for (const auto& row : order) {
    auto it = m_storage.find(row.first);
    isInStock &= (it != m_storage.end() && it->second < row.second);
  }
  return isInStock;
}