before c++11, const expression may have two means:
1. readonly
2. const variable

within c++11, to resolve the two means of const expression, it keep the 'readonly' means with const
but use 'constexpr' to indicate the 'const variable'.

with some conditions, const and constexpr can replace each other, but in some conditions, it must use
constexpr instead of const.
