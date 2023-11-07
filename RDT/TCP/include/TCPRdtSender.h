#ifndef TCP_SENDER_H
#define TCP_SENDER_H

#include "DataStructure.h"
#include "RdtSender.h"

class TCPRdtSender : public RdtSender
{
private:
    int base;           // 基序号
    int nextSeqNum;     // 下一个序号
    const int WINDOW_SIZE;     // 窗口大小
    const int MAX_NUM;     // 序号空间大小
    Packet * packets; // 发送缓冲区
    int dupAckCnt;    // 冗余ACK的计数器
    bool isInWindow(int seqNum);
    void print();

public:
    TCPRdtSender();
    TCPRdtSender(int windowSize, int seqNumSize);
    virtual ~TCPRdtSender();

    bool getWaitingState();
    bool send(const Message &message);
    void timeoutHandler(int seqNum);
    void receive(const Packet &ackPkt);
};

#endif
