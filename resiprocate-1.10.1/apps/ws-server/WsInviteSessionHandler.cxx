#include "WsInviteSessionHandler.hxx"

#include "/usr/local/include/rutil/Logger.hxx"

#include "/usr/local/include/resip/dum/ServerInviteSession.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace server;


WsInviteSessionHandler::WsInviteSessionHandler()
{
}

WsInviteSessionHandler::~WsInviteSessionHandler()
{
}
     
void
WsInviteSessionHandler::onNewSession(ClientInviteSessionHandle, InviteSession::OfferAnswerType oat, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onNewSession");
}

void
WsInviteSessionHandler::onNewSession(ServerInviteSessionHandle sis, InviteSession::OfferAnswerType oat, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onNewSession");
   DebugLog(<< "ServerInviteSession-onNewSession - " << msg.brief());
   DebugLog(<< "Sending 180 Ringing response");
   mSis = sis;
   sis->provisional(180);
}

void
WsInviteSessionHandler::onFailure(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onFailure");
}

void
WsInviteSessionHandler::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const SdpContents&) {
   DebugLog(<< "WsInviteSessionHandler::onEarlyMedia");
}

void
WsInviteSessionHandler::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const Contents&) {
   DebugLog(<< "WsInviteSessionHandler::onEarlyMedia");
}

void
WsInviteSessionHandler::onProvisional(ClientInviteSessionHandle, const SipMessage&) {
   DebugLog(<< "WsInviteSessionHandler::onProvisional");
}

void
WsInviteSessionHandler::onConnected(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onConnected");
}

void
WsInviteSessionHandler::onConnected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onConnected");
}

void
WsInviteSessionHandler::onConnectedConfirmed(InviteSessionHandle, const SipMessage &msg) {
   DebugLog(<< "WsInviteSessionHandler::onConnectedConfirmed");
}

void
WsInviteSessionHandler::onPrack(ServerInviteSessionHandle, const SipMessage &msg) {
   DebugLog(<< "WsInviteSessionHandler::onPrack");
}

void
WsInviteSessionHandler::onStaleCallTimeout(ClientInviteSessionHandle h) {
   DebugLog(<< "WsInviteSessionHandler::onStaleCallTimeout");
}

void
WsInviteSessionHandler::terminate(ClientInviteSessionHandle h) {
   DebugLog(<< "WsInviteSessionHandler::terminate");
}

void
WsInviteSessionHandler::onTerminated(InviteSessionHandle is, InviteSessionHandler::TerminatedReason reason, const SipMessage* related) {
   DebugLog(<< "WsInviteSessionHandler::onTerminated");
   DebugLog(<< "ServerInviteSession-onTerminated");
}

void
WsInviteSessionHandler::onForkDestroyed(ClientInviteSessionHandle) {
   DebugLog(<< "WsInviteSessionHandler::onForkDestroyed");
}

void
WsInviteSessionHandler::onRedirected(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onRedirected");
}

void
WsInviteSessionHandler::onReadyToSend(InviteSessionHandle, SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onReadyToSend");
}

void
WsInviteSessionHandler::onAnswer(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   DebugLog(<< "WsInviteSessionHandler::onAnswer");
}

void
WsInviteSessionHandler::onAnswer(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   DebugLog(<< "WsInviteSessionHandler::onAnswer");
}

void
WsInviteSessionHandler::onOffer(InviteSessionHandle is, const SipMessage& msg, const SdpContents& sdp) {
   DebugLog(<< "WsInviteSessionHandler::onOffer");
}      

void
WsInviteSessionHandler::onOffer(InviteSessionHandle is, const SipMessage& msg, const Contents& sdp) {
   DebugLog(<< "WsInviteSessionHandler::onOffer");
   DebugLog(<< "ServerInviteSession-onNewSession-onOffer(SDP)");
#ifdef SDP_PRINT
   sdp->encode(cout);
#endif
   DebugLog(<< "Sending 200 respond with SDP answer");
   is->provideAnswer(sdp);
   mSis->accept();
}      

void
WsInviteSessionHandler::onRemoteSdpChanged(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   DebugLog(<< "WsInviteSessionHandler::onRemoteSdpChanged");
}

void
WsInviteSessionHandler::onRemoteAnswerChanged(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   DebugLog(<< "WsInviteSessionHandler::onRemoteAnswerChanged");
}  

void
WsInviteSessionHandler::onOfferRequestRejected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onOfferRequestRejected");
}

void
WsInviteSessionHandler::onOfferRequired(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onOfferRequired");
}      

void
WsInviteSessionHandler::onOfferRejected(InviteSessionHandle, const SipMessage* msg) {
   DebugLog(<< "WsInviteSessionHandler::onOfferRejected");
}

void
WsInviteSessionHandler::onInfo(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onInfo");
}

void
WsInviteSessionHandler::onInfoSuccess(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onInfoSuccess");
}

void
WsInviteSessionHandler::onInfoFailure(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onInfoFailure");
}

void
WsInviteSessionHandler::onMessage(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onMessage");
}

void
WsInviteSessionHandler::onMessageSuccess(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onMessageSuccess");
}

void
WsInviteSessionHandler::onMessageFailure(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onMessageFailure");
}

void
WsInviteSessionHandler::onRefer(InviteSessionHandle, ServerSubscriptionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onRefer");
}

void
WsInviteSessionHandler::onReferNoSub(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onReferNoSub");
}

void
WsInviteSessionHandler::onReferRejected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onReferRejected");
}

void
WsInviteSessionHandler::onReferAccepted(InviteSessionHandle, ClientSubscriptionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onReferAccepted");
}

void
WsInviteSessionHandler::onAckReceived(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onAckReceived");
}

void
WsInviteSessionHandler::onAckNotReceived(InviteSessionHandle) {
   DebugLog(<< "WsInviteSessionHandler::onAckNotReceived");
}

void
WsInviteSessionHandler::onStaleReInviteTimeout(InviteSessionHandle h) {
   DebugLog(<< "WsInviteSessionHandler::onStaleReInviteTimeout");
}

void
WsInviteSessionHandler::onIllegalNegotiation(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsInviteSessionHandler::onIllegalNegotiation");
}     

void
WsInviteSessionHandler::onSessionExpired(InviteSessionHandle) {
   DebugLog(<< "WsInviteSessionHandler::onSessionExpired");
}

void
WsInviteSessionHandler::onFlowTerminated(InviteSessionHandle) {
   DebugLog(<< "WsInviteSessionHandler::onFlowTerminated");
}
