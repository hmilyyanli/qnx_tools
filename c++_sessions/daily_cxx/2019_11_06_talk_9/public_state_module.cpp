#include "public_state_module.h"
#include "private_state_module.h"

TCPConnection::TCPConnection() : m_state_p{::TCPStateFlyweight::closeState()} {}

auto TCPConnection::open() -> void {
  if (auto new_state = this->m_state_p->open(*this)) {
    this->m_state_p = new_state;
  }
}
auto TCPConnection::synchronize() -> void {
  if (auto new_state = this->m_state_p->synchronize(*this)) {
    this->m_state_p = new_state;
  }
}
auto TCPConnection::close() -> void {
  if (auto new_state = this->m_state_p->close(*this)) {
    this->m_state_p = new_state;
  }
}
auto TCPConnection::send() -> void {
  if (auto new_state = this->m_state_p->send(*this)) {
    this->m_state_p = new_state;
  }
}
