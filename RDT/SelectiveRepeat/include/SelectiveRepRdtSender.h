#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
class SelectiveRepRdtSender :public RdtSender {
private:
	const int WINDOW_SIZE;          // 发送窗口的大小
	const int MAX_NUM; 				//序列号	
	int base; 						//最早未确认分组的序号
	int nextSeqNum;					// 下一个要发送的数据包的序列号
	Packet * const packets;
	bool * const acked;
	bool isInWindow(int seqNum);
	void print();

public:
	bool getWaitingState();
	bool send(const Message &message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet &ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用

public:
	SelectiveRepRdtSender();
	SelectiveRepRdtSender(int windowSize, int maxNum);
	virtual ~SelectiveRepRdtSender();
};

#endif

