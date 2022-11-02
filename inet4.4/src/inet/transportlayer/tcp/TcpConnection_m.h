//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp/TcpConnection.msg.
//

#ifndef __INET__TCP_TCPCONNECTION_M_H
#define __INET__TCP_TCPCONNECTION_M_H

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
namespace tcp {


}  // namespace tcp
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/ChunkBuffer_m.h" // import inet.common.packet.ChunkBuffer

#include "inet/common/packet/ChunkQueue_m.h" // import inet.common.packet.ChunkQueue

#include "inet/common/packet/Packet_m.h" // import inet.common.packet.Packet

#include "inet/networklayer/common/L3Address_m.h" // import inet.networklayer.common.L3Address

#include "inet/transportlayer/tcp/TcpConnectionState_m.h" // import inet.transportlayer.tcp.TcpConnectionState

// cplusplus {{
#include "inet/transportlayer/tcp/Tcp.h"
#include "inet/transportlayer/tcp/TcpAlgorithm.h"
#include "inet/transportlayer/tcp/TcpConnection.h"
#include "inet/transportlayer/tcp/TcpReceiveQueue.h"
#include "inet/transportlayer/tcp/TcpSackRexmitQueue.h"
#include "inet/transportlayer/tcp/TcpSendQueue.h"
#include "inet/transportlayer/tcp_common/TcpHeader.h"
// }}


namespace inet {
namespace tcp {


}  // namespace tcp
}  // namespace inet


namespace omnetpp {

inline any_ptr toAnyPtr(const inet::tcp::TcpSackRexmitQueue *p) {if (auto obj = as_cObject(p)) return any_ptr(obj); else return any_ptr(p);}
template<> inline inet::tcp::TcpSackRexmitQueue *fromAnyPtr(any_ptr ptr) { return ptr.get<inet::tcp::TcpSackRexmitQueue>(); }
template<> inline inet::tcp::TcpAlgorithm *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpAlgorithm*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpSendQueue *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpSendQueue*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpReceiveQueue *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpReceiveQueue*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpConnection *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpConnection*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__TCP_TCPCONNECTION_M_H

