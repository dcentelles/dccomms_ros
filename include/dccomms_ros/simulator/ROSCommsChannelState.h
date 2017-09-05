#ifndef COMMSCHANNELPROPERTIES_H
#define COMMSCHANNELPROPERTIES_H

#include <memory>
#include <random>
#include <dccomms_ros/simulator/ROSCommsDevice.h>
#include <condition_variable>

using namespace std;

namespace dccomms_ros
{

class CommsChannelState;
typedef std::shared_ptr<CommsChannelState> CommsChannelStatePtr;

class CommsChannelState
{
    typedef std::normal_distribution<double> NormalDist;
    typedef std::default_random_engine RandEngGen;

    typedef std::uniform_real_distribution<double> UniformRealDist;

public:

    static CommsChannelStatePtr BuildCommsChannelState();

    CommsChannelState();
    CommsChannelState(
            int maxBitRate,
            int delay
            );

    void SetMaxBitRate(int maxBitRate);
    int GetMaxBitRate();
    int SetDelay(int delay);
    int GetDelay();
    void SetLinkOk(bool ok);
    bool LinkOk();
    double GetNextTt();
    void SetErrRate(double);
    double GetErrRate();
    NormalDist GetTtDist();
    void SetTtDist(double mean, double sd);
    bool ErrOnNextPkt();

    void SetTxNode(ROSCommsDevicePtr dev);
    void SetRxNode(ROSCommsDevicePtr dev);

    ROSCommsDevicePtr GetTxNode();
    ROSCommsDevicePtr GetRxNode();

    //void ChannelFree(bool channelFree);
    //bool ChannelFree();

    //bool WaitForChannelFree();

    void Lock();
    void Unlock();

private:
    int _maxBitRate;
    int _delay; //ms
    bool _linkOk;
    bool _channelFree;
    NormalDist _ttDist;
    UniformRealDist _erDist;
    RandEngGen _ttGenerator,_erGenerator;

    ROSCommsDevicePtr _txDev, _rxDev;
    double _errRate;

    std::mutex _errRateMutex, _delayMutex, _channelMutex;
    //condition_variable _channelFreeCond;
};
}

#endif // COMMSCHANNELPROPERTIES_H