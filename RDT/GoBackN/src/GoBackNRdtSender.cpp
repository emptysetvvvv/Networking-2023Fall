
#include "Global.h"
#include "GoBackNRdtSender.h"

bool GoBackNRdtSender::isInWindow(int seqNum) {
    int tail = (base + WINDOW_SIZE - 1) % MAX_NUM;
	if (base <= tail) return base <= seqNum && seqNum <= tail;
	else return base <= seqNum || seqNum <= tail;
}

void GoBackNRdtSender::print() {
	int tail = (base + WINDOW_SIZE - 1) % MAX_NUM;
	char pktType = '#';
	cout << "[";
	for (int i = base; i != tail; i = (i+1) % MAX_NUM) {
		if (i == nextSeqNum) pktType = '*';
		cout << "< " << i << " " << pktType << "> ";
	}
	cout << "]" << endl;
}

bool GoBackNRdtSender::getWaitingState() {
    return (base + WINDOW_SIZE) % MAX_NUM == nextSeqNum;
}

bool GoBackNRdtSender::send(const Message &message) {
	if(getWaitingState()) return false;
	packets[nextSeqNum].acknum = -1;
	packets[nextSeqNum].checksum = nextSeqNum;
	memcpy(packets[nextSeqNum].payload, message.data, sizeof(message.data));
	packets[nextSeqNum].checksum = pUtils->calculateCheckSum(packets[nextSeqNum]);
	pUtils->printPacket("发送方发送报文", packets[nextSeqNum]);
	
}

GoBackNRdtSender::GoBackNRdtSender() : WINDOW_SIZE(3), MAX_NUM(4),
    base(0), nextSeqNum(0), packets(new Packet[4]) {}

GoBackNRdtSender::GoBackNRdtSender(int windowSize, int maxNum) : WINDOW_SIZE(windowSize), MAX_NUM(maxNum), 
	base(0), nextSeqNum(0), packets(new Packet[maxNum]) {}

GoBackNRdtSender::~GoBackNRdtSender() {
	delete[] packets;
}
