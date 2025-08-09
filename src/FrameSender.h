#ifndef __FRAMESENDER_H_
#define __FRAMESENDER_H_

#include <omnetpp.h>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace omnetpp;

struct FrameInfo {
    int frameId;
    double timestamp;
    double mse;
    bool sendFlag;
    int packetSize;
};

class FrameSender : public cSimpleModule
{
  private:
    std::vector<FrameInfo> frameList;
    int currentIndex = 0;
    simtime_t sendInterval;
    cMessage *sendTimer = nullptr;
    std::string gdfFile;

    std::set<int> ackedFrames;
    std::map<int, int> retryCount;              // frameId → retry count
    std::map<int, simtime_t> sentTimestamps;    // frameId → time sent
    int maxRetries = 3;

    // Signals
    simsignal_t rttSignal;
    simsignal_t retransmitSignal;
    simsignal_t dropSignal;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    void loadGDFFile();
    void sendNextFrame();
};

#endif
