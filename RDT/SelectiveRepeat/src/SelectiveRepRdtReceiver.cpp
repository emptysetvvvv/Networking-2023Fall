
#include "Global.h"
#include "SelectiveRepRdtReceiver.h"

bool SelectiveRepRdtReceiver::isInWindow(int seqNum) {
    int tail = (nextSeqNum + WINDOW_SIZE - 1) % MAX_NUM;
	if (nextSeqNum <= tail) return nextSeqNum <= seqNum && seqNum <= tail;
	else return nextSeqNum <= seqNum || seqNum <= tail;
}

SelectiveRepRdtReceiver::SelectiveRepRdtReceiver() : WINDOW_SIZE(4), MAX_NUM(8),
    nextSeqNum(0), packets(new Packet[8]), received(new bool[8]) {
    for (int i = 0; i < MAX_NUM; i++) received[i] = false;
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum	= 0;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

SelectiveRepRdtReceiver::SelectiveRepRdtReceiver(int windowSize, int maxNum) : WINDOW_SIZE(windowSize), MAX_NUM(maxNum),
	nextSeqNum(0), packets(new Packet[maxNum]), received(new bool[maxNum]) {
	for (int i = 0; i < MAX_NUM; i++) received[i] = false;
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

SelectiveRepRdtReceiver::~SelectiveRepRdtReceiver() {
	delete[] packets;
	delete[] received;
}

void SelectiveRepRdtReceiver::receive(const Packet &packet) {
	int checkSum = pUtils->calculateCheckSum(packet);
	if (checkSum != packet.checksum) {
		pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		return;
	}
	if (!isInWindow(packet.seqnum)) {
		pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		lastAckPkt.acknum = packet.seqnum;
		lastAckPkt.seqnum = -1;
		memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}
	packets[packet.seqnum] = packet;
	received[packet.seqnum] = true;
	lastAckPkt.acknum = packet.seqnum;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
	pUtils->printPacket("接收方正确收到发送方的报文", packet);
	pns->sendToNetworkLayer(SENDER, lastAckPkt);

	while (received[nextSeqNum]) {
		pUtils->printPacket("接收方向上层交付报文", packets[nextSeqNum]);
		Message msg;
		memcpy(msg.data, packets[nextSeqNum].payload, sizeof(packets[nextSeqNum].payload));
		pns->delivertoAppLayer(RECEIVER, msg);
		received[nextSeqNum] = false;
		nextSeqNum = (nextSeqNum + 1) % MAX_NUM;
	}
}
