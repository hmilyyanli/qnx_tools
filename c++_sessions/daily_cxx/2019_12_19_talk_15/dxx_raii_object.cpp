#include <dxx_raii_object.hpp>

#include <iostream>

namespace dxx::raii {

//                         ------------
//                         class Object
//                         ------------

Object::Object(const Object *f_nestedObj, int f_idValue)
    : m_nestedObj{f_nestedObj}, m_idValue{f_idValue} {
  ::std::cout << " Object(): " << this << ", nestedObj: " << f_nestedObj
              << ", idValue: " << f_idValue << "\n";
}

Object::~Object() {
  ::std::cout << "~Object(): " << this << ", nestedObj: " << this->m_nestedObj
              << ", idValue: " << this->m_idValue << "\n";
}

} // namespace dxx::raii
