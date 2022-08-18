#include "public_state_module.h"

int main() {
  auto tcp = TCPConnection{};
  tcp.send();
  tcp.open();
  tcp.send();
  tcp.synchronize();
  tcp.send();
  tcp.close();
}
