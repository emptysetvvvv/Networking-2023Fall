#ifndef GO_BACK_N_RDT_RECEIVER_H
#define GO_BACK_N_RDT_RECEIVER_H
#include "RdtReceiver.h"
class GoBackNRdtReceiver :public RdtReceiver
{
private:
	const int MAX_NUM;	//最大序列号
	int nextSeqNum;	// 期待收到的下一个报文序号
	Packet lastAckPkt;				//上次发送的确认报文

public:
	GoBackNRdtReceiver();
	GoBackNRdtReceiver(int n);
	virtual ~GoBackNRdtReceiver();

public:
	void receive(const Packet &packet);	//接收报文，将被NetworkService调用
};

#endif

