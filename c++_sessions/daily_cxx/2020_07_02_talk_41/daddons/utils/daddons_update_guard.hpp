//=============================================================================
//  C O P Y R I G H T
//-----------------------------------------------------------------------------
/// @copyright (c) 2018 by Robert Bosch GmbH. All rights reserved.
//
//  The reproduction, distribution and utilization of this file as
//  well as the communication of its contents to others without express
//  authorization is prohibited. Offenders will be held liable for the
//  payment of damages. All rights reserved in the event of the grant
//  of a patent, utility model or design.
//=============================================================================
//  P R O J E C T   I N F O R M A T I O N
//-----------------------------------------------------------------------------
//     Projectname: FVG3
//  Target systems: cross platform
//       Compilers: ISO C++11 compliant or higher
//=============================================================================
//  I N I T I A L   A U T H O R   I D E N T I T Y
//-----------------------------------------------------------------------------
//        Name: Christian Power
//  Department: CC-DA/ESV1
//=============================================================================
/// @file  daddons_update_guard.hpp
/// @brief Provide RAII like object to ensure cleanup() is called after a port update().
/// @generatedcode
/// @copyright (c) 2018 by Robert Bosch GmbH
/// @author Christian Power
/// @swcomponent daddons
//=============================================================================
#ifndef DADDONS_UPDATE_GUARD_HPP_INCLUDED
#define DADDONS_UPDATE_GUARD_HPP_INCLUDED

namespace daddons
{
    namespace utils
    {
        /// @defgroup daddyProxyUpdateGuard Port Update Guard
        /// @brief Scope guard for daddy port updates
        /// @ingroup daddons

        /// @brief Update guard provides a RAII-style mechanism to ensure that cleanup() is called after a
        ///        daddy receiver port update() call.
        ///
        /// It uses the scope to call update() and cleanup() of a port:
        ///   - in the constructor:     port.update() is called.
        ///   - in the destructor:      port.cleanup() is called.
        /// Using this mechanism makes it impossible to forget a cleanup.
        /// The updateing function can return from every location and the mechanism is even exception safe.
        /// @ingroup daddyProxyUpdateGuard
        template <class TDaddyPortType> class TUpdateGuard
        {
          public:
            /// @brief Constructor performs update action.
            ///
            /// @param[in] f_port Daddy receiver port
            ///
            TUpdateGuard(TDaddyPortType &f_port) : m_port_p(&f_port) { m_port_p->update(); }

            /// @brief Destructor performs cleanup action.
            ~TUpdateGuard()
            {
                /// To avoid to cleanup twice the m_port_p pointer will be set to nullptr on a copied guard object.
                /// So we have to check if the pointer is still valid here.
                /// If not the object was copied and the copied instance will perform the cleanup.
                if (nullptr != m_port_p)
                {
                    m_port_p->cleanup();
                }
            }

            /// @brief Copy constructor needed for the makeUpdateGuard() method.
            /// Copy member and do not perform update action.
            TUpdateGuard(TUpdateGuard<TDaddyPortType> &&f_rhs) : m_port_p(f_rhs.m_port_p)
            {
                // set m_port_p in the copied object to nullptr to avoid twice cleanup()
                f_rhs.m_port_p = nullptr;
            }

          private:
              TUpdateGuard(const TUpdateGuard<TDaddyPortType> &f_rhs); // = delete
              TUpdateGuard& operator=(const TUpdateGuard& f_rhs); // = delete
              TUpdateGuard& operator=(TUpdateGuard&& f_rhs); // = delete

            /// Daddy port, which needs update and cleanup.
            TDaddyPortType* m_port_p;
        };

        /// brief Create update guard object for the port passed as parameter.
        /// The object's constructor will call ->update() on the port. It's destructor will call ->cleanup() on it.
        /// Deduce concrete port type.
        ///
        /// @param[in] f_port Daddy receiver port
        ///
        template <class TDaddyPortType> TUpdateGuard<TDaddyPortType> makeUpdateGuard(TDaddyPortType &f_port)
        {
            return TUpdateGuard<TDaddyPortType>(f_port);
        }
    }
}

#endif // DADDONS_UPDATE_GUARD_HPP_INCLUDED
