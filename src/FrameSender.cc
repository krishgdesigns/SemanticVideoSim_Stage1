#include "FrameSender.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include "FrameMsg_m.h"

Define_Module(FrameSender);

void FrameSender::initialize()
{
    gdfFile = par("gdfFile").stdstringValue();
    sendInterval = par("sendInterval");

    // Register signals
    rttSignal = registerSignal("ackRTT");
    retransmitSignal = registerSignal("retransmitCount");
    dropSignal = registerSignal("droppedFrame");

    loadGDFFile();

    sendTimer = new cMessage("sendTimer");
    scheduleAt(simTime() + sendInterval, sendTimer);
}

void FrameSender::handleMessage(cMessage *msg)
{
    if (msg == sendTimer) {
        sendNextFrame();
        if (currentIndex < frameList.size()) {
            scheduleAt(simTime() + sendInterval, sendTimer);
        }
    }
    else if (dynamic_cast<AckMsg *>(msg)) {
        AckMsg *ack = check_and_cast<AckMsg *>(msg);
        int frameId = ack->getFrameId();
        int receiverId = ack->getReceiverId();

        if (receiverId == -1) {
            EV << "ACK: Frame " << frameId << " was received by all UEs.\n";
            ackedFrames.insert(frameId);

            simtime_t sentTime = sentTimestamps[frameId];
            simtime_t rtt = simTime() - sentTime;
            emit(rttSignal, rtt);

        } else if (receiverId == -2) {
            EV << "Timeout for frame " << frameId << ". Attempting retransmission.\n";
            int retry = retryCount[frameId]++;
            if (retry < maxRetries) {
                emit(retransmitSignal, 1);
                auto it = std::find_if(frameList.begin(), frameList.end(),
                    [frameId](const FrameInfo& f) { return f.frameId == frameId; });

                if (it != frameList.end()) {
                    frameList.insert(frameList.begin() + currentIndex, *it);
                }
            } else {
                EV << "Frame " << frameId << " reached max retries. Dropping.\n";
                emit(dropSignal, 1);
            }
        }

        delete msg;
    }
    else {
        delete msg;
    }
}

void FrameSender::loadGDFFile()
{
    std::ifstream file(gdfFile);
    if (!file.is_open()) {
        EV << "Could not open GDF file: " << gdfFile << "\n";
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream ss(line);
        FrameInfo f;
        char comma;
        ss >> f.frameId >> comma >> f.timestamp >> comma >> f.mse >> comma >> f.sendFlag >> comma >> f.packetSize;
        frameList.push_back(f);
    }

    file.close();
    EV << "Loaded " << frameList.size() << " frames from GDF file.\n";
}

void FrameSender::sendNextFrame()
{
    if (currentIndex >= frameList.size())
        return;

    FrameInfo &f = frameList[currentIndex++];

    if (!f.sendFlag) {
        EV << "Frame " << f.frameId << " marked as drop. Skipping.\n";
        return;
    }

    FrameMsg *packet = new FrameMsg();
    packet->setFrameId(f.frameId);
    packet->setTimestamp(simTime().dbl());  // Store current time as "send time"
    packet->setMse(f.mse);
    packet->setSendFlag(f.sendFlag);
    packet->setSenderId(getId());
    packet->setPacketSize(f.packetSize);
    packet->setByteLength(f.packetSize);

    sentTimestamps[f.frameId] = simTime();  // Track for RTT

    EV << "Sending frame " << f.frameId << " to gNodeB.\n";
    send(packet, "out");
}
