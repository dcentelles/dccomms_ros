#include <dccomms_ros/simulator/NetsimPacket.h>

namespace dccomms_ros {

NetsimHeader::NetsimHeader() {}
NetsimHeader::~NetsimHeader() {}

TypeId NetsimHeader::GetTypeId(void) {
  static TypeId tid = TypeId("ns3::NetsimHeader")
                          .SetParent<Header>()
                          .AddConstructor<NetsimHeader>();
  return tid;
}
TypeId NetsimHeader::GetInstanceTypeId(void) const { return GetTypeId(); }

void NetsimHeader::Print(std::ostream &os) const { os << "seq=" << _seq; }
uint32_t NetsimHeader::GetSerializedSize(void) const {
  return sizeof(_seq) + sizeof(_packetSize) + sizeof(_dst) + sizeof(_src) + 1;
}
void NetsimHeader::Serialize(Buffer::Iterator start) const {
  start.WriteHtonU32(_seq);
  start.WriteHtonU32(_packetSize);
  start.WriteHtonU32(_dst);
  start.WriteHtonU32(_src);
  start.WriteU8(_error ? 1 : 0);
}
uint32_t NetsimHeader::Deserialize(Buffer::Iterator start) {
  _seq = start.ReadNtohU32();
  _packetSize = start.ReadNtohU32();
  _dst = start.ReadNtohU32();
  _src = start.ReadNtohU32();
  _error = start.ReadU8() ? 1 : 0;
  return GetSerializedSize();
}
void NetsimHeader::SetSeqNum(uint32_t data) { _seq = data; }

void NetsimHeader::SetPacketSize(uint32_t size) { _packetSize = size; }

void NetsimHeader::SetDst(uint32_t addr) { _dst = addr; }

void NetsimHeader::SetSrc(uint32_t addr) { _src = addr; }

void NetsimHeader::SetPacketError(bool v) { _error = v; }

uint32_t NetsimHeader::GetSeqNum() const { return _seq; }

uint32_t NetsimHeader::GetPacketSize() const { return _packetSize; }

uint32_t NetsimHeader::GetDst() const { return _dst; }

uint32_t NetsimHeader::GetSrc() const { return _src; }

bool NetsimHeader::GetPacketError() const { return _error; }
}
