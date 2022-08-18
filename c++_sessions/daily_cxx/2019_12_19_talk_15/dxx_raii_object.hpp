#ifndef DXX_RAII_OBJECT_INCLUDED
#define DXX_RAII_OBJECT_INCLUDED

namespace dxx::raii {

//                         ============
//                         class Object
//                         ============

class Object {
  const Object *m_nestedObj; // can be 'nullptr'
  int m_idValue;

public:
  explicit Object(const Object *f_nestedObj, int f_idValue);
  ~Object();

  [[nodiscard]] auto idValue() const -> int { return this->m_idValue; }
};

} // namespace dxx::raii

#endif // DXX_RAII_OBJECT_INCLUDED
