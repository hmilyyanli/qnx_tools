#include <iostream>
#define TARGET_SELENA

#if defined(TARGET_SELENA) || defined(TARGET_UNITTEST)
template <typename Wrapped>
class SimOnlyVar
{
private:
   /// wrapped type
   Wrapped m_data;

public:
   /// \brief C'tor.
   /// Calls the default c'tor of the wrapped type if it exists.
   SimOnlyVar()
      : m_data()
   {
   }

   /// \brief C'tor.
   /// Just sets the wrapped member to the passed value if the wrapped member exists.
   ///
   /// \param wrapped the value to be wrapped
   explicit SimOnlyVar(const Wrapped& wrapped)
      : m_data(wrapped)
   {
   }

   /// \brief Assignment operator.
   /// Just sets the wrapped member to the passed value if the wrapped member exists.
   ///
   /// \param wrapped the wrapped value
   /// \return this instance
   SimOnlyVar& operator=(const Wrapped& wrapped)
   {
      m_data = wrapped;
      return *this;
   }

   /// \brief You can access the m_data member if it exists using this operator.
   /// Before using it, call ownsMemory().
   Wrapped* operator->()
   {
      return &m_data;
   }

   /// \brief Returns whether the wrapped type is backed with memory.
   /// \return true: backed with memory, false: no memory is used.
   bool ownsMemory()
   {
      return true;
   }
};
#else
template <typename Wrapped>
class SimOnlyVar
{
public:
   /// \brief C'tor.
   /// Calls the default c'tor of the wrapped type if it exists.
   SimOnlyVar()
   {
   }

   /// \brief C'tor.
   /// Just sets the wrapped member to the passed value if the wrapped member exists.
   ///
   /// \param wrapped the value to be wrapped
   explicit SimOnlyVar(const Wrapped&)
   {
   }

   /// \brief Assignment operator.
   /// Just sets the wrapped member to the passed value if the wrapped member exists.
   ///
    /// \param wrapped the wrapped value
   /// \return this instance
   SimOnlyVar& operator=(const Wrapped&)
   {
      return *this;
   }

   /// \brief You can access the m_data member if it exists using this operator.
   /// Before using it, call ownsMemory().
   Wrapped* operator->()
   {
      //VFC_ASSERT(false);
      return nullptr;
   }

   /// \brief Returns whether the wrapped type is backed with memory.
   /// \return true: backed with memory, false: no memory is used.
   bool ownsMemory()
   {
      return false;
   }
};
#endif
class ExampleClass
{
	public:
	uint8_t m_x;
};

int main()
{
	SimOnlyVar<uint32_t> m_mySimOnlyVar;
	m_mySimOnlyVar = 7;
    std::cout << "size " << sizeof(m_mySimOnlyVar) << std::endl;
	return 0;
}
