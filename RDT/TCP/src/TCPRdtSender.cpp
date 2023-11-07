#include "Global.h"
#include "TCPRdtSender.h"

bool TCPRdtSender::isInWindow(int seqNum) {
    int tail = (base + WINDOW_SIZE - 1) % MAX_NUM;
	if (base <= tail) return base <= seqNum && seqNum <= tail;
	else return base <= seqNum || seqNum <= tail;
}

void TCPRdtSender::print() {
    int tail = (base + WINDOW_SIZE) % MAX_NUM;
	char pktType = '#';
	cout << "[";
	for (int i = base; i != tail % MAX_NUM; i = (i+1) % MAX_NUM) {
		if (i == nextSeqNum) pktType = '*';
		cout << "< " << i << " " << pktType << " >";
	}
	cout << "]" << endl;
}

TCPRdtSender::TCPRdtSender() : 
    WINDOW_SIZE(4), MAX_NUM(8),
    base(0), nextSeqNum(0), packets(new Packet[8]), dupAckCnt(0) {}

TCPRdtSender::TCPRdtSender(int windowSize, int seqNumSize) : 
    WINDOW_SIZE(windowSize), MAX_NUM(seqNumSize), 
    base(0), nextSeqNum(0), packets(new Packet[seqNumSize]), dupAckCnt(0) {}

TCPRdtSender::~TCPRdtSender() {
    delete[] packets;
}

bool TCPRdtSender::getWaitingState() {
    return (base + WINDOW_SIZE) % MAX_NUM == nextSeqNum;
}

bool TCPRdtSender::send(const Message &message) {
    if (getWaitingState()) return false;
    packets[nextSeqNum].acknum = -1;
    packets[nextSeqNum].seqnum = nextSeqNum;
    memcpy(packets[nextSeqNum].payload, message.data, sizeof(message.data));
    packets[nextSeqNum].checksum = pUtils->calculateCheckSum(packets[nextSeqNum]);
    pUtils->printPacket("发送方发送报文", packets[nextSeqNum]);
    if (base == nextSeqNum) pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
    pns->sendToNetworkLayer(RECEIVER, packets[nextSeqNum]);
    nextSeqNum = (nextSeqNum + 1) % MAX_NUM;
    return true;
}

void TCPRdtSender::timeoutHandler(int seqNum) {
    pns->stopTimer(SENDER, 0);
    pns->sendToNetworkLayer(RECEIVER, packets[base]);
    pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
}

void TCPRdtSender::receive(const Packet &ackPkt) {
    int checkSum = pUtils->calculateCheckSum(ackPkt);
    if (checkSum != ackPkt.checksum) {
        pUtils->printPacket("发送方没有正确收到确认", ackPkt);
        return;
    }
    if (isInWindow(ackPkt.acknum)) {
        pUtils->printPacket("发送方正确收到确认", ackPkt);
        base = (ackPkt.acknum + 1) % MAX_NUM;
        print();
        pns->stopTimer(SENDER, 0);
        if (base != nextSeqNum) pns->startTimer(SENDER, Configuration::TIME_OUT, 0);
        dupAckCnt = 0;
    }
    else {
        pUtils->printPacket("发送方已正确收到过该报文确认", ackPkt);
        dupAckCnt++;
        cout << "dup ack count " << dupAckCnt << endl;
        if (dupAckCnt == 3) {
            pUtils->printPacket("发送方收到冗余确认，快速重传", packets[ackPkt.acknum]);
            pns->sendToNetworkLayer(RECEIVER, packets[ackPkt.acknum]);
            dupAckCnt = 0;
            cout << "resend " << ackPkt.acknum << endl;
        }
    }
}
