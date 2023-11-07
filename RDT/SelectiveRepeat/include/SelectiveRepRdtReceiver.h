#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SelectiveRepRdtReceiver :public RdtReceiver
{
private:
	const int WINDOW_SIZE;          // 发送窗口的大小
	const int MAX_NUM; 				//序列号	
	int nextSeqNum;					// 下一个要发送的数据包的序列号
	Packet lastAckPkt;				//上次发送的确认报文
	Packet * const packets;
	bool * const received;
	bool isInWindow(int seqNum);

public:
	SelectiveRepRdtReceiver();
	SelectiveRepRdtReceiver(int windowSize, int maxNum);
	virtual ~SelectiveRepRdtReceiver();

public:
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif

