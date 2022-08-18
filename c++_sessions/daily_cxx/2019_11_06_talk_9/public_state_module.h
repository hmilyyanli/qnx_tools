class TCPState;

class TCPConnection {
  const TCPState *m_state_p;

  friend class TCPState;

public:
  TCPConnection();

  auto open() -> void;
  auto synchronize() -> void;
  auto close() -> void;
  auto send() -> void;
};
