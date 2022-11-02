//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/common/geometry/Geometry.msg.
//

#ifndef __INET_GEOMETRY_M_H
#define __INET_GEOMETRY_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0600
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {


}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/Units_m.h" // import inet.common.Units

// cplusplus {{
#include "inet/common/geometry/common/Coord.h"
#include "inet/common/geometry/common/EulerAngles.h"
#include "inet/common/geometry/common/Quaternion.h"
// }}


namespace inet {


}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::Coord *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::Coord *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::Coord>(); }
inline any_ptr toAnyPtr(const inet::EulerAngles *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::EulerAngles *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::EulerAngles>(); }
inline any_ptr toAnyPtr(const inet::Quaternion *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::Quaternion *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::Quaternion>(); }

}  // namespace omnetpp

#endif // ifndef __INET_GEOMETRY_M_H

