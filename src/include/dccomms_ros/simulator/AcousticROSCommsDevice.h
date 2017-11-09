#ifndef DCCOMMS_ROS_ACOUSTIC_ROSCOMMSDEVICE_H_
#define DCCOMMS_ROS_ACOUSTIC_ROSCOMMSDEVICE_H_

#include <dccomms_ros/simulator/AcousticCommsChannel.h>
#include <dccomms_ros/simulator/ROSCommsDevice.h>
#include <ns3/aqua-sim-net-device.h>
#include <ns3/aqua-sim-helper.h>

using namespace dccomms;
using namespace cpplogging;

namespace dccomms_ros {

class AcousticROSCommsDevice : public ROSCommsDevice {
public:
  AcousticROSCommsDevice(ROSCommsSimulatorPtr, PacketBuilderPtr);

  DEV_TYPE GetDevType();

protected:
  void DoSetMac(uint32_t mac);
  void DoSend(PacketPtr dlf);
  void DoLinkToChannel(CommsChannelPtr channel);
  void DoStart();

private:
  ns3::Ptr<ns3::AquaSimChannel> _channel;
  ns3::Ptr<ns3::AquaSimNetDevice> _device;
  ns3::Ptr<ns3::AquaSimMac> _macLayer;
  ns3::Ptr<ns3::AquaSimRouting> _routingLayer;
  ns3::Ptr<ns3::Node> _node;
  ns3::Ptr<ns3::MobilityModel> _mobility;
  ns3::AquaSimHelper _asHelper;
  ns3::AquaSimAddress _aquaSimAddr;

  bool _started;
  uint32_t _nodeListIndex;

  void _Recv(std::string context, ns3::Ptr<const ns3::Packet>);
};
}
#endif // COMMSNODE_H
