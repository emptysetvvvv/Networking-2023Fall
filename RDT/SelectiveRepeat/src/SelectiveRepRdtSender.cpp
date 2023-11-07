
#include "Global.h"
#include "SelectiveRepRdtSender.h"

bool SelectiveRepRdtSender::isInWindow(int seqNum) {
    int tail = (base + WINDOW_SIZE - 1) % MAX_NUM;
	if (base <= tail) return base <= seqNum && seqNum <= tail;
	else return base <= seqNum || seqNum <= tail;
}

void SelectiveRepRdtSender::print() {
	int tail = (base + WINDOW_SIZE) % MAX_NUM;
	char pktType = '#';
	cout << "[";
	for (int i = base; i != tail % MAX_NUM; i = (i+1) % MAX_NUM) {
		if (acked[i]) pktType = '#';
		else pktType = '*';
		cout << "< " << i << " " << pktType << " >";
	}
	cout << "]" << endl;
}

bool SelectiveRepRdtSender::getWaitingState() {
	return (base + WINDOW_SIZE) % MAX_NUM == nextSeqNum;
}

bool SelectiveRepRdtSender::send(const Message &message) {
	if (getWaitingState()) return false;
	packets[nextSeqNum].acknum = -1;
	packets[nextSeqNum].seqnum = nextSeqNum;
	memcpy(packets[nextSeqNum].payload, message.data, sizeof(message.data));
	packets[nextSeqNum].checksum = pUtils->calculateCheckSum(packets[nextSeqNum]);
	pUtils->printPacket("发送方发送报文", packets[nextSeqNum]);
	pns->sendToNetworkLayer(RECEIVER, packets[nextSeqNum]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, nextSeqNum);
	nextSeqNum = (nextSeqNum + 1) % MAX_NUM;
	return true;
}

void SelectiveRepRdtSender::receive(const Packet &ackPkt) {
	int checkSum = pUtils->calculateCheckSum(ackPkt);
	if (checkSum != ackPkt.checksum) {
		pUtils->printPacket("发送方没有正确收到确认", ackPkt);
		return;
	}
	pns->stopTimer(SENDER, ackPkt.acknum);
	if (isInWindow(ackPkt.acknum)) {
		acked[ackPkt.acknum] = true;
		print();
		while (acked[base]) {
			acked[base] = false;
			base = (base + 1) % MAX_NUM;
			print();
		}
	}
}

void SelectiveRepRdtSender::timeoutHandler(int seqNum) {
	pns->stopTimer(SENDER, seqNum);
	pns->sendToNetworkLayer(RECEIVER, packets[seqNum]);
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);
}

SelectiveRepRdtSender::SelectiveRepRdtSender() : WINDOW_SIZE(4), MAX_NUM(8),
    base(0), nextSeqNum(0), packets(new Packet[8]), acked(new bool[8]) {
    for (int i = 0; i < MAX_NUM; i++) acked[i] = false;
}

SelectiveRepRdtSender::SelectiveRepRdtSender(int windowSize, int maxNum) : WINDOW_SIZE(windowSize), MAX_NUM(maxNum),
	base(0), nextSeqNum(0), packets(new Packet[maxNum]), acked(new bool[maxNum]) {
	for (int i = 0; i < MAX_NUM; i++) acked[i] = false;
}

SelectiveRepRdtSender::~SelectiveRepRdtSender() {
	delete[] packets;
	delete[] acked;
}

