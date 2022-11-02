//
// Generated file, do not edit! Created by opp_msgtool 6.0 from inet/transportlayer/tcp_common/TcpHeader.msg.
//

#ifndef __INET__TCP_TCPHEADER_M_H
#define __INET__TCP_TCPHEADER_M_H

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

class SackItem;
class Sack;
class TcpOption;
class TcpOptionEnd;
class TcpOptionNop;
class TcpOptionMaxSegmentSize;
class TcpOptionWindowScale;
class TcpOptionSackPermitted;
class TcpOptionSack;
class TcpOptionTimestamp;
class TcpOptionUnknown;
class TcpHeader;

}  // namespace tcp
}  // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs

#include "inet/common/packet/chunk/Chunk_m.h" // import inet.common.packet.chunk.Chunk

#include "inet/transportlayer/common/CrcMode_m.h" // import inet.transportlayer.common.CrcMode

#include "inet/transportlayer/contract/TransportHeaderBase_m.h" // import inet.transportlayer.contract.TransportHeaderBase


namespace inet {
namespace tcp {

// cplusplus {{
const B TCP_MIN_HEADER_LENGTH = B(20);  // default TCP header length: 20 bytes without options
const B TCP_MAX_HEADER_LENGTH = B(60);  // maximum TCP header length (base + options): 60 = 15 * 4 bytes

const B TCP_OPTIONS_MAX_SIZE     = B(40);  // 40 bytes, 15 * 4 bytes (15 is the largest number in 4 bits length data offset field), TCP_MAX_HEADER_OCTETS - TCP_HEADER_OCTETS = 40
const B TCP_OPTION_HEAD_SIZE = B(2);       // 2 bytes, type and length
const B TCP_OPTION_SACK_MIN_SIZE = B(10);  // 10 bytes, option length = 8 * n + 2 bytes (NOP)
const B TCP_OPTION_SACK_ENTRY_SIZE = B(8); // sack entry size
const B TCP_OPTION_TS_SIZE       = B(12);  // 12 bytes, option length = 10 bytes + 2 bytes (NOP)
// }}

/**
 * Enum generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:27</tt> by opp_msgtool.
 * <pre>
 * enum TcpConstants
 * {
 *     // maximum allowed sack entry number, if no other options are used
 *     TCP_MAX_SACK_ENTRIES = 4;
 * }
 * </pre>
 */
enum TcpConstants {
    TCP_MAX_SACK_ENTRIES = 4
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpConstants& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpConstants& e) { int n; b->unpack(n); e = static_cast<TcpConstants>(n); }

/**
 * Enum generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:40</tt> by opp_msgtool.
 * <pre>
 * //
 * // TCP Option Numbers
 * // Reference: http://www.iana.org/assignments/tcp-parameters/
 * // Date: 2011-07-02
 * //
 * // Note: Options not yet implemented should stay commented out
 * //
 * enum TcpOptionNumbers
 * {
 *     TCPOPTION_END_OF_OPTION_LIST = 0;                   // RFC 793, LENGTH: 1 Byte
 *     TCPOPTION_NO_OPERATION = 1;                         // RFC 793, LENGTH: 1 Byte
 *     TCPOPTION_MAXIMUM_SEGMENT_SIZE = 2;                 // RFC 793, LENGTH: 4 Bytes
 *     TCPOPTION_WINDOW_SCALE = 3;                         // RFC 1323, LENGTH: 3 Bytes
 *     TCPOPTION_SACK_PERMITTED = 4;                       // RFC 2018, LENGTH: 2 Bytes
 *     TCPOPTION_SACK = 5;                                 // RFC 2018, LENGTH: N (max. N = 4) 8 * n + 2 Bytes  => 32 + 2 + 2 * NOP = 36 Bytes; If TIMESTAMP option is used with SACK: max. n = 3 => 12 Bytes (for Timestamp) + 28 Bytes (for SACK) = 40 Bytes
 *     //    TCPOPTION_ECHO = 6;                               // (obsoleted by option 8) RFC 1072 & RFC 6247, LENGTH: 6 Bytes
 *     //    TCPOPTION_ECHO_REPLY = 7;                         // (obsoleted by option 8) RFC 1072 & RFC 6247, LENGTH: 6 Bytes
 *     TCPOPTION_TIMESTAMP = 8;                            // RFC 1323, LENGTH: 10 Bytes
 * }
 * </pre>
 */
enum TcpOptionNumbers {
    TCPOPTION_END_OF_OPTION_LIST = 0,
    TCPOPTION_NO_OPERATION = 1,
    TCPOPTION_MAXIMUM_SEGMENT_SIZE = 2,
    TCPOPTION_WINDOW_SCALE = 3,
    TCPOPTION_SACK_PERMITTED = 4,
    TCPOPTION_SACK = 5,
    TCPOPTION_TIMESTAMP = 8
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionNumbers& e) { b->pack(static_cast<int>(e)); }
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionNumbers& e) { int n; b->unpack(n); e = static_cast<TcpOptionNumbers>(n); }

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:80</tt> by opp_msgtool.
 * <pre>
 * //
 * // This structure represents a single SACK (selective acknowledgment):
 * //
 * class SackItem extends cObject
 * {
 *     \@packetData;
 *     unsigned int start;     // start seq no. of sack block
 *     unsigned int end;       // end seq no. of sack block
 * }
 * </pre>
 */
class INET_API SackItem : public ::omnetpp::cObject
{
  protected:
    unsigned int start = 0;
    unsigned int end = 0;

  private:
    void copy(const SackItem& other);

  protected:
    bool operator==(const SackItem&) = delete;

  public:
    SackItem();
    SackItem(const SackItem& other);
    virtual ~SackItem();
    SackItem& operator=(const SackItem& other);
    virtual SackItem *dup() const override {return new SackItem(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned int getStart() const;
    virtual void setStart(unsigned int start);

    virtual unsigned int getEnd() const;
    virtual void setEnd(unsigned int end);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const SackItem& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, SackItem& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:87</tt> by opp_msgtool.
 * <pre>
 * class Sack extends SackItem
 * {
 * }
 * </pre>
 */
class INET_API Sack : public ::inet::tcp::SackItem
{
  protected:

  private:
    void copy(const Sack& other);

  protected:
    bool operator==(const Sack&) = delete;

  public:
    Sack();
    Sack(const Sack& other);
    virtual ~Sack();
    Sack& operator=(const Sack& other);
    virtual Sack *dup() const override {return new Sack(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;


  public:
    Sack(unsigned int start_par, unsigned int end_par) { setSegment(start_par, end_par); }
    virtual bool empty() const;
    virtual bool contains(const Sack& other) const;
    virtual void clear();
    virtual void setSegment(unsigned int start_par, unsigned int end_par);
    virtual std::string str() const override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const Sack& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, Sack& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:102</tt> by opp_msgtool.
 * <pre>
 * // Header Options (optional):
 * class TcpOption extends cObject
 * {
 *     \@packetData;
 *     TcpOptionNumbers kind;            // option kind
 *     unsigned short length = 1;                    // option length
 * }
 * </pre>
 */
class INET_API TcpOption : public ::omnetpp::cObject
{
  protected:
    TcpOptionNumbers kind = static_cast<inet::tcp::TcpOptionNumbers>(-1);
    unsigned short length = 1;

  private:
    void copy(const TcpOption& other);

  protected:
    bool operator==(const TcpOption&) = delete;

  public:
    TcpOption();
    TcpOption(const TcpOption& other);
    virtual ~TcpOption();
    TcpOption& operator=(const TcpOption& other);
    virtual TcpOption *dup() const override {return new TcpOption(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual TcpOptionNumbers getKind() const;
    virtual void setKind(TcpOptionNumbers kind);

    virtual unsigned short getLength() const;
    virtual void setLength(unsigned short length);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOption& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOption& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:109</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionEnd extends TcpOption
 * {
 *     kind = TCPOPTION_END_OF_OPTION_LIST;
 *     length = 1;
 * }
 * </pre>
 */
class INET_API TcpOptionEnd : public ::inet::tcp::TcpOption
{
  protected:

  private:
    void copy(const TcpOptionEnd& other);

  protected:
    bool operator==(const TcpOptionEnd&) = delete;

  public:
    TcpOptionEnd();
    TcpOptionEnd(const TcpOptionEnd& other);
    virtual ~TcpOptionEnd();
    TcpOptionEnd& operator=(const TcpOptionEnd& other);
    virtual TcpOptionEnd *dup() const override {return new TcpOptionEnd(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionEnd& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionEnd& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:115</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionNop extends TcpOption
 * {
 *     kind = TCPOPTION_NO_OPERATION;
 *     length = 1;
 * }
 * </pre>
 */
class INET_API TcpOptionNop : public ::inet::tcp::TcpOption
{
  protected:

  private:
    void copy(const TcpOptionNop& other);

  protected:
    bool operator==(const TcpOptionNop&) = delete;

  public:
    TcpOptionNop();
    TcpOptionNop(const TcpOptionNop& other);
    virtual ~TcpOptionNop();
    TcpOptionNop& operator=(const TcpOptionNop& other);
    virtual TcpOptionNop *dup() const override {return new TcpOptionNop(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionNop& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionNop& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:121</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionMaxSegmentSize extends TcpOption
 * {
 *     kind = TCPOPTION_MAXIMUM_SEGMENT_SIZE;
 *     length = 4;
 *     uint16_t maxSegmentSize;   // uint16_t
 * }
 * </pre>
 */
class INET_API TcpOptionMaxSegmentSize : public ::inet::tcp::TcpOption
{
  protected:
    uint16_t maxSegmentSize = 0;

  private:
    void copy(const TcpOptionMaxSegmentSize& other);

  protected:
    bool operator==(const TcpOptionMaxSegmentSize&) = delete;

  public:
    TcpOptionMaxSegmentSize();
    TcpOptionMaxSegmentSize(const TcpOptionMaxSegmentSize& other);
    virtual ~TcpOptionMaxSegmentSize();
    TcpOptionMaxSegmentSize& operator=(const TcpOptionMaxSegmentSize& other);
    virtual TcpOptionMaxSegmentSize *dup() const override {return new TcpOptionMaxSegmentSize(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint16_t getMaxSegmentSize() const;
    virtual void setMaxSegmentSize(uint16_t maxSegmentSize);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionMaxSegmentSize& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionMaxSegmentSize& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:128</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionWindowScale extends TcpOption
 * {
 *     kind = TCPOPTION_WINDOW_SCALE;
 *     length = 3;
 *     unsigned short windowScale;   // uint8_t
 * }
 * </pre>
 */
class INET_API TcpOptionWindowScale : public ::inet::tcp::TcpOption
{
  protected:
    unsigned short windowScale = 0;

  private:
    void copy(const TcpOptionWindowScale& other);

  protected:
    bool operator==(const TcpOptionWindowScale&) = delete;

  public:
    TcpOptionWindowScale();
    TcpOptionWindowScale(const TcpOptionWindowScale& other);
    virtual ~TcpOptionWindowScale();
    TcpOptionWindowScale& operator=(const TcpOptionWindowScale& other);
    virtual TcpOptionWindowScale *dup() const override {return new TcpOptionWindowScale(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned short getWindowScale() const;
    virtual void setWindowScale(unsigned short windowScale);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionWindowScale& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionWindowScale& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:135</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionSackPermitted extends TcpOption
 * {
 *     kind = TCPOPTION_SACK_PERMITTED;
 *     length = 2;
 * }
 * </pre>
 */
class INET_API TcpOptionSackPermitted : public ::inet::tcp::TcpOption
{
  protected:

  private:
    void copy(const TcpOptionSackPermitted& other);

  protected:
    bool operator==(const TcpOptionSackPermitted&) = delete;

  public:
    TcpOptionSackPermitted();
    TcpOptionSackPermitted(const TcpOptionSackPermitted& other);
    virtual ~TcpOptionSackPermitted();
    TcpOptionSackPermitted& operator=(const TcpOptionSackPermitted& other);
    virtual TcpOptionSackPermitted *dup() const override {return new TcpOptionSackPermitted(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionSackPermitted& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionSackPermitted& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:141</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionSack extends TcpOption
 * {
 *     kind = TCPOPTION_SACK;
 *     length = 2;     // 2 + getSackArraySize() * 8
 *     SackItem sackItem[];
 * }
 * </pre>
 */
class INET_API TcpOptionSack : public ::inet::tcp::TcpOption
{
  protected:
    SackItem *sackItem = nullptr;
    size_t sackItem_arraysize = 0;

  private:
    void copy(const TcpOptionSack& other);

  protected:
    bool operator==(const TcpOptionSack&) = delete;

  public:
    TcpOptionSack();
    TcpOptionSack(const TcpOptionSack& other);
    virtual ~TcpOptionSack();
    TcpOptionSack& operator=(const TcpOptionSack& other);
    virtual TcpOptionSack *dup() const override {return new TcpOptionSack(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setSackItemArraySize(size_t size);
    virtual size_t getSackItemArraySize() const;
    virtual const SackItem& getSackItem(size_t k) const;
    virtual SackItem& getSackItemForUpdate(size_t k) { return const_cast<SackItem&>(const_cast<TcpOptionSack*>(this)->getSackItem(k));}
    virtual void setSackItem(size_t k, const SackItem& sackItem);
    virtual void insertSackItem(size_t k, const SackItem& sackItem);
    [[deprecated]] void insertSackItem(const SackItem& sackItem) {appendSackItem(sackItem);}
    virtual void appendSackItem(const SackItem& sackItem);
    virtual void eraseSackItem(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionSack& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionSack& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:148</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionTimestamp extends TcpOption
 * {
 *     kind = TCPOPTION_TIMESTAMP;
 *     length = 10;
 *     uint32_t senderTimestamp;
 *     uint32_t echoedTimestamp;
 * }
 * </pre>
 */
class INET_API TcpOptionTimestamp : public ::inet::tcp::TcpOption
{
  protected:
    uint32_t senderTimestamp = 0;
    uint32_t echoedTimestamp = 0;

  private:
    void copy(const TcpOptionTimestamp& other);

  protected:
    bool operator==(const TcpOptionTimestamp&) = delete;

  public:
    TcpOptionTimestamp();
    TcpOptionTimestamp(const TcpOptionTimestamp& other);
    virtual ~TcpOptionTimestamp();
    TcpOptionTimestamp& operator=(const TcpOptionTimestamp& other);
    virtual TcpOptionTimestamp *dup() const override {return new TcpOptionTimestamp(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual uint32_t getSenderTimestamp() const;
    virtual void setSenderTimestamp(uint32_t senderTimestamp);

    virtual uint32_t getEchoedTimestamp() const;
    virtual void setEchoedTimestamp(uint32_t echoedTimestamp);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionTimestamp& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionTimestamp& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:156</tt> by opp_msgtool.
 * <pre>
 * class TcpOptionUnknown extends TcpOption
 * {
 *     kind = static_cast<TcpOptionNumbers>(-1);
 *     uint8_t bytes[];
 * }
 * </pre>
 */
class INET_API TcpOptionUnknown : public ::inet::tcp::TcpOption
{
  protected:
    uint8_t *bytes = nullptr;
    size_t bytes_arraysize = 0;

  private:
    void copy(const TcpOptionUnknown& other);

  protected:
    bool operator==(const TcpOptionUnknown&) = delete;

  public:
    TcpOptionUnknown();
    TcpOptionUnknown(const TcpOptionUnknown& other);
    virtual ~TcpOptionUnknown();
    TcpOptionUnknown& operator=(const TcpOptionUnknown& other);
    virtual TcpOptionUnknown *dup() const override {return new TcpOptionUnknown(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual void setBytesArraySize(size_t size);
    virtual size_t getBytesArraySize() const;
    virtual uint8_t getBytes(size_t k) const;
    virtual void setBytes(size_t k, uint8_t bytes);
    virtual void insertBytes(size_t k, uint8_t bytes);
    [[deprecated]] void insertBytes(uint8_t bytes) {appendBytes(bytes);}
    virtual void appendBytes(uint8_t bytes);
    virtual void eraseBytes(size_t k);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpOptionUnknown& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpOptionUnknown& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>inet/transportlayer/tcp_common/TcpHeader.msg:176</tt> by opp_msgtool.
 * <pre>
 * //
 * // Represents a TCP segment, to be used with the ~TCP module.
 * //
 * // TCP header fields not explicitly modelled: work on going
 * // - Data Offset (number of 32 bit words in the header): represented
 * //   by cMessage::length().
 * // - Reserved (reserved for future use)
 * // - Checksum (header checksum): modelled by cMessage::hasBitError()
 * // - Header Options: Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented
 * // - Padding
 * //
 * // cMessage::getKind() may be set to an arbitrary value: TCP entities will
 * // ignore it and use only the header fields (synBit, ackBit, rstBit).
 * //
 * class TcpHeader extends TransportHeaderBase
 * {
 *     chunkLength = TCP_MIN_HEADER_LENGTH;
 * 
 *     // Source Port
 *     unsigned short srcPort;
 * 
 *     // Destination Port
 *     unsigned short destPort;
 * 
 *     // Sequence Number: first sequence number of the first data octet
 *     // in the respective segment (except if SYN is set; then the the
 *     // seq. number is the initial seq. number (ISS) and the first data
 *     // octet is ISS + 1)
 *     uint32_t sequenceNo;
 * 
 *     // Acknowledgement Number: if ACK flag is set, this field contains
 *     // the next sequence number the sender of this segment is expecting
 *     // to receive
 *     uint32_t ackNo;
 * 
 *     // TCP Header Length including options
 *     B headerLength = TCP_MIN_HEADER_LENGTH;
 * 
 *     bool cwrBit; // CWR: congestion window reduced bit (RFC 3168)
 *     bool eceBit; // ECE: ECN-echo bit (RFC 3168)
 *     bool urgBit; // URG: urgent pointer field significant if set
 *     bool ackBit; // ACK: ackNo significant if set
 *     bool pshBit; // PSH: push function
 *     bool rstBit; // RST: reset the connection
 *     bool synBit; // SYN: synchronize seq. numbers
 *     bool finBit; // FIN: finish - no more data from sender
 * 
 *     // Window Size: the number of data octets beginning with the one indicated
 *     // in the acknowledgement field which the sender of this segment is
 *     // willing to accept
 *     uint16_t window;
 * 
 *     // Urgent Pointer: communicates the current value of the urgent pointer
 *     // as a positive offset from the sequence number in this segment. The
 *     // urgent pointer points to the sequence number of the octet following
 *     // the urgent data. This field is only be interpreted in segments with
 *     // the URG control bit set.
 *     uint16_t urgentPointer;
 * 
 *     uint16_t crc = 0;
 *     CrcMode crcMode = CRC_MODE_UNDEFINED;
 * 
 *     // Header options (optional)
 *     // Currently only EOL, NOP, MSS, WS, SACK_PERMITTED, SACK and TS are implemented
 *     TcpOption *headerOption[] \@owned;
 * }
 * </pre>
 */
class INET_API TcpHeader : public ::inet::TransportHeaderBase
{
  protected:
    unsigned short srcPort = 0;
    unsigned short destPort = 0;
    uint32_t sequenceNo = 0;
    uint32_t ackNo = 0;
    ::inet::B headerLength = TCP_MIN_HEADER_LENGTH;
    bool cwrBit = false;
    bool eceBit = false;
    bool urgBit = false;
    bool ackBit = false;
    bool pshBit = false;
    bool rstBit = false;
    bool synBit = false;
    bool finBit = false;
    uint16_t window = 0;
    uint16_t urgentPointer = 0;
    uint16_t crc = 0;
    ::inet::CrcMode crcMode = CRC_MODE_UNDEFINED;
    TcpOption * *headerOption = nullptr;
    size_t headerOption_arraysize = 0;

  private:
    void copy(const TcpHeader& other);

  protected:
    bool operator==(const TcpHeader&) = delete;

  public:
    TcpHeader();
    TcpHeader(const TcpHeader& other);
    virtual ~TcpHeader();
    TcpHeader& operator=(const TcpHeader& other);
    virtual TcpHeader *dup() const override {return new TcpHeader(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual unsigned short getSrcPort() const;
    virtual void setSrcPort(unsigned short srcPort);

    virtual unsigned short getDestPort() const;
    virtual void setDestPort(unsigned short destPort);

    virtual uint32_t getSequenceNo() const;
    virtual void setSequenceNo(uint32_t sequenceNo);

    virtual uint32_t getAckNo() const;
    virtual void setAckNo(uint32_t ackNo);

    virtual ::inet::B getHeaderLength() const;
    virtual void setHeaderLength(::inet::B headerLength);

    virtual bool getCwrBit() const;
    virtual void setCwrBit(bool cwrBit);

    virtual bool getEceBit() const;
    virtual void setEceBit(bool eceBit);

    virtual bool getUrgBit() const;
    virtual void setUrgBit(bool urgBit);

    virtual bool getAckBit() const;
    virtual void setAckBit(bool ackBit);

    virtual bool getPshBit() const;
    virtual void setPshBit(bool pshBit);

    virtual bool getRstBit() const;
    virtual void setRstBit(bool rstBit);

    virtual bool getSynBit() const;
    virtual void setSynBit(bool synBit);

    virtual bool getFinBit() const;
    virtual void setFinBit(bool finBit);

    virtual uint16_t getWindow() const;
    virtual void setWindow(uint16_t window);

    virtual uint16_t getUrgentPointer() const;
    virtual void setUrgentPointer(uint16_t urgentPointer);

    virtual uint16_t getCrc() const;
    virtual void setCrc(uint16_t crc);

    virtual ::inet::CrcMode getCrcMode() const;
    virtual void setCrcMode(::inet::CrcMode crcMode);

    virtual void setHeaderOptionArraySize(size_t size);
    virtual size_t getHeaderOptionArraySize() const;
    virtual const TcpOption * getHeaderOption(size_t k) const;
    virtual TcpOption * getHeaderOptionForUpdate(size_t k) { handleChange();return const_cast<TcpOption *>(const_cast<TcpHeader*>(this)->getHeaderOption(k));}
    virtual void setHeaderOption(size_t k, TcpOption * headerOption);
    virtual TcpOption * removeHeaderOption(size_t k);
    [[deprecated]] TcpOption * dropHeaderOption(size_t k) {return removeHeaderOption(k);}
    virtual void insertHeaderOption(size_t k, TcpOption * headerOption);
    [[deprecated]] void insertHeaderOption(TcpOption * headerOption) {appendHeaderOption(headerOption);}
    virtual void appendHeaderOption(TcpOption * headerOption);
    virtual void eraseHeaderOption(size_t k);


  public:
    /**
     * Returns RFC 793 specified SEG.LEN:
     *     SEG.LEN = the number of octets occupied by the data in the segment
     *               (counting SYN and FIN)
     *
     */
    uint32_t getSynFinLen() const { return (finBit ? 1 : 0) + (synBit ? 1 : 0); }

    /** Calculate Length of TCP Options Array in bytes */
    virtual B getHeaderOptionArrayLength();

    /** Drops all TCP options of the TCP segment */
    virtual void dropHeaderOptions();

    // implements TransportHeaderBase functions:
    virtual unsigned int getSourcePort() const override { return getSrcPort(); }
    virtual void setSourcePort(unsigned int port) override { setSrcPort(port); }
    virtual unsigned int getDestinationPort() const override { return getDestPort(); }
    virtual void setDestinationPort(unsigned int port) override { setDestPort(port); }
    virtual std::string str() const override;
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const TcpHeader& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, TcpHeader& obj) {obj.parsimUnpack(b);}


}  // namespace tcp
}  // namespace inet


namespace omnetpp {

template<> inline inet::tcp::SackItem *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::SackItem*>(ptr.get<cObject>()); }
template<> inline inet::tcp::Sack *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::Sack*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOption *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOption*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionEnd *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionEnd*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionNop *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionNop*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionMaxSegmentSize *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionMaxSegmentSize*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionWindowScale *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionWindowScale*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionSackPermitted *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionSackPermitted*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionSack *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionSack*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionTimestamp *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionTimestamp*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpOptionUnknown *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpOptionUnknown*>(ptr.get<cObject>()); }
template<> inline inet::tcp::TcpHeader *fromAnyPtr(any_ptr ptr) { return check_and_cast<inet::tcp::TcpHeader*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __INET__TCP_TCPHEADER_M_H
