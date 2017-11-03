#ifndef DCCOMMS_ROS_ROSCOMMSDEVICE_H_
#define DCCOMMS_ROS_ROSCOMMSDEVICE_H_

#include <cpplogging/Loggable.h>
#include <dccomms/CommsDeviceService.h>
#include <dccomms/Utils.h>
#include <dccomms_ros/simulator/CommsChannel.h>
#include <ns3/aqua-sim-net-device.h>

using namespace dccomms;
using namespace cpplogging;

namespace dccomms_ros {

class ROSCommsDevice;
typedef std::shared_ptr<ROSCommsDevice> ROSCommsDevicePtr;

class ROSCommsSimulator;
typedef std::shared_ptr<ROSCommsSimulator> ROSCommsSimulatorPtr;

class ROSCommsDevice : public virtual Loggable {
public:
  ROSCommsDevice(ROSCommsSimulatorPtr, PacketBuilderPtr,
                 DEV_TYPE devType = ACOUSTIC_UNDERWATER_DEV);

  CommsDeviceServicePtr GetService();
  void ReceiveFrame(PacketPtr);
  void StartDeviceService();
  void StartNodeWorker();
  std::string GetDccommsId();
  void SetDccommsId(const std::string name);
  void SetMaxBitRate(uint32_t);
  void SetChannel(CommsChannelPtr channel);
  uint32_t GetMaxBitRate();

  virtual void SetLogName(std::string name);
  virtual void SetLogLevel(cpplogging::LogLevel);
  virtual void FlushLog();
  virtual void FlushLogOn(cpplogging::LogLevel);
  virtual void LogToConsole(bool);
  virtual void LogToFile(const std::string &filename);

  void SetMac(int mac);
  void SetDevType(DEV_TYPE type);
  void SetTfFrameId(const std::string &);

  int GetMac();
  DEV_TYPE GetDevType();
  std::string GetTfFrameId();

  std::string ToString();
  void Start();

private:
  void _Transmit(PacketPtr dlf);
  std::mutex _receiveFrameMutex;
  CommsDeviceServicePtr _device;
  CommsChannelPtr _channel;
  ROSCommsSimulatorPtr _sim;
  ServiceThread<ROSCommsDevice> _txserv;
  PacketPtr _txdlf;
  std::string _name, _tfFrameId;
  int _mac;
  DEV_TYPE _devType;
  int _maxBitRate;
  PacketBuilderPtr _pb;
  ns3::Ptr<ns3::AquaSimMac> _asMac;
  ns3::Ptr<ns3::AquaSimPhy> _asPhy;

  void _TxWork();
};
}
#endif // COMMSNODE_H
