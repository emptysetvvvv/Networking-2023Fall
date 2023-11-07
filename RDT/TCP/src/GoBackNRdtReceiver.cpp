
#include "Global.h"
#include "GoBackNRdtReceiver.h"

GoBackNRdtReceiver::GoBackNRdtReceiver() : MAX_NUM(8), nextSeqNum(0) {
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GoBackNRdtReceiver::GoBackNRdtReceiver(int n) : MAX_NUM(n), nextSeqNum(0) {
	lastAckPkt.acknum = -1;
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;
	memset(lastAckPkt.payload, '.', sizeof(lastAckPkt.payload));
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}

GoBackNRdtReceiver::~GoBackNRdtReceiver() {}

void GoBackNRdtReceiver::receive(const Packet &packet) {
	if (packet.checksum != pUtils->calculateCheckSum(packet)) {
		pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}
	if (packet.seqnum != nextSeqNum) {
		pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);
		return;
	}
	Message msg;
	memcpy(msg.data, packet.payload, sizeof(packet.payload));
	pns->delivertoAppLayer(RECEIVER, msg);
	pUtils->printPacket("接收方正确收到发送方的报文", packet);
	lastAckPkt.acknum = nextSeqNum;
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
	pUtils->printPacket("接收方发送确认报文", lastAckPkt);
	pns->sendToNetworkLayer(SENDER, lastAckPkt);
	nextSeqNum = (nextSeqNum + 1) % MAX_NUM;
}
