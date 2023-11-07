
#include "Global.h"
#include "GoBackNRdtSender.h"

GoBackNRdtSender::GoBackNRdtSender() : WINDOW_SIZE(4), MAX_NUM(8),
    base(0), nextSeqNum(0), packets(new Packet[8]) {}

GoBackNRdtSender::GoBackNRdtSender(int windowSize, int maxNum) : WINDOW_SIZE(windowSize), MAX_NUM(maxNum), 
	base(0), nextSeqNum(0), packets(new Packet[maxNum]) {}

GoBackNRdtSender::~GoBackNRdtSender() {
	delete[] packets;
}

bool GoBackNRdtSender::isInWindow(int seqNum) {
    int tail = (base + WINDOW_SIZE - 1) % MAX_NUM;
	if (base <= tail) return base <= seqNum && seqNum <= tail;
	else return base <= seqNum || seqNum <= tail;
}

void GoBackNRdtSender::print() {
	int tail = (base + WINDOW_SIZE) % MAX_NUM;
	char pktType = '#';
	cout << "[";
	for (int i = base; i != tail % MAX_NUM; i = (i+1) % MAX_NUM) {
		if (i == nextSeqNum) pktType = '*';
		cout << "< " << i << " " << pktType << " >";
	}
	cout << "]" << endl;
}

bool GoBackNRdtSender::getWaitingState() {
    return (base + WINDOW_SIZE) % MAX_NUM == nextSeqNum;
}

bool GoBackNRdtSender::send(const Message &message) {
	if (getWaitingState()) return false;
	packets[nextSeqNum].acknum = -1;
	packets[nextSeqNum].seqnum = nextSeqNum;
	memcpy(packets[nextSeqNum].payload, message.data, sizeof(message.data));
	packets[nextSeqNum].checksum = pUtils->calculateCheckSum(packets[nextSeqNum]);

	// cout << "before send: " << endl;
	// print();

	pUtils->printPacket("发送方发送报文", packets[nextSeqNum]);
	if (base == nextSeqNum) pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	pns->sendToNetworkLayer(RECEIVER, packets[nextSeqNum]);
	nextSeqNum = (nextSeqNum + 1) % MAX_NUM;

	// cout << "after send: " << endl;
	// print();
	return true;
}

void GoBackNRdtSender::receive(const Packet &ackPkt) {
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum != ackPkt.checksum) {
		pUtils->printPacket("发送方没有正确收到确认", ackPkt);
		return;
	}
	base = (ackPkt.acknum + 1) % MAX_NUM;
	cout << "------------------------------" << endl;
	print();
	pns->stopTimer(SENDER, 0);
	if (base != nextSeqNum) 
		pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	cout << "发送方正确收到确认" << endl;
	// print();
}

void GoBackNRdtSender::timeoutHandler(int seqNum) {
	if (nextSeqNum == base) return;
	pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
	for (int i = base; i != nextSeqNum; i = (i+1) % MAX_NUM) {
		pUtils->printPacket("发送方重新发送报文", packets[i]);
		pns->sendToNetworkLayer(RECEIVER, packets[i]);
	}
	cout << "发送方重新发送报文" << endl;
}

