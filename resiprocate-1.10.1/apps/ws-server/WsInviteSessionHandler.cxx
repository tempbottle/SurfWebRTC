#include "WsInviteSessionHandler.hxx"

#include "/usr/local/include/rutil/Logger.hxx"

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
   InfoLog(<< "WsInviteSessionHandler::onNewSession");
}

void
WsInviteSessionHandler::onNewSession(ServerInviteSessionHandle, InviteSession::OfferAnswerType oat, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onNewSession");
}

void
WsInviteSessionHandler::onFailure(ClientInviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onFailure");
}

void
WsInviteSessionHandler::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const SdpContents&) {
   InfoLog(<< "WsInviteSessionHandler::onEarlyMedia");
}

void
WsInviteSessionHandler::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const Contents&) {
   InfoLog(<< "WsInviteSessionHandler::onEarlyMedia");
}

void
WsInviteSessionHandler::onProvisional(ClientInviteSessionHandle, const SipMessage&) {
   InfoLog(<< "WsInviteSessionHandler::onProvisional");
}

void
WsInviteSessionHandler::onConnected(ClientInviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onConnected");
}

void
WsInviteSessionHandler::onConnected(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onConnected");
}

void
WsInviteSessionHandler::onConnectedConfirmed(InviteSessionHandle, const SipMessage &msg) {
   InfoLog(<< "WsInviteSessionHandler::onConnectedConfirmed");
}

void
WsInviteSessionHandler::onPrack(ServerInviteSessionHandle, const SipMessage &msg) {
   InfoLog(<< "WsInviteSessionHandler::onPrack");
}

void
WsInviteSessionHandler::onStaleCallTimeout(ClientInviteSessionHandle h) {
   InfoLog(<< "WsInviteSessionHandler::onStaleCallTimeout");
}

void
WsInviteSessionHandler::terminate(ClientInviteSessionHandle h) {
   InfoLog(<< "WsInviteSessionHandler::terminate");
}

void
WsInviteSessionHandler::onTerminated(InviteSessionHandle, InviteSessionHandler::TerminatedReason reason, const SipMessage* related) {
   InfoLog(<< "WsInviteSessionHandler::onTerminated");
}

void
WsInviteSessionHandler::onForkDestroyed(ClientInviteSessionHandle) {
   InfoLog(<< "WsInviteSessionHandler::onForkDestroyed");
}

void
WsInviteSessionHandler::onRedirected(ClientInviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onRedirected");
}

void
WsInviteSessionHandler::onReadyToSend(InviteSessionHandle, SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onReadyToSend");
}

void
WsInviteSessionHandler::onAnswer(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   InfoLog(<< "WsInviteSessionHandler::onAnswer");
}

void
WsInviteSessionHandler::onAnswer(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   InfoLog(<< "WsInviteSessionHandler::onAnswer");
}

void
WsInviteSessionHandler::onOffer(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   InfoLog(<< "WsInviteSessionHandler::onOffer");
}      

void
WsInviteSessionHandler::onOffer(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   InfoLog(<< "WsInviteSessionHandler::onOffer");
}      

void
WsInviteSessionHandler::onRemoteSdpChanged(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   InfoLog(<< "WsInviteSessionHandler::onRemoteSdpChanged");
}

void
WsInviteSessionHandler::onRemoteAnswerChanged(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   InfoLog(<< "WsInviteSessionHandler::onRemoteAnswerChanged");
}  

void
WsInviteSessionHandler::onOfferRequestRejected(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onOfferRequestRejected");
}

void
WsInviteSessionHandler::onOfferRequired(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onOfferRequired");
}      

void
WsInviteSessionHandler::onOfferRejected(InviteSessionHandle, const SipMessage* msg) {
   InfoLog(<< "WsInviteSessionHandler::onOfferRejected");
}

void
WsInviteSessionHandler::onInfo(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onInfo");
}

void
WsInviteSessionHandler::onInfoSuccess(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onInfoSuccess");
}

void
WsInviteSessionHandler::onInfoFailure(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onInfoFailure");
}

void
WsInviteSessionHandler::onMessage(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onMessage");
}

void
WsInviteSessionHandler::onMessageSuccess(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onMessageSuccess");
}

void
WsInviteSessionHandler::onMessageFailure(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onMessageFailure");
}

void
WsInviteSessionHandler::onRefer(InviteSessionHandle, ServerSubscriptionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onRefer");
}

void
WsInviteSessionHandler::onReferNoSub(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onReferNoSub");
}

void
WsInviteSessionHandler::onReferRejected(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onReferRejected");
}

void
WsInviteSessionHandler::onReferAccepted(InviteSessionHandle, ClientSubscriptionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onReferAccepted");
}

void
WsInviteSessionHandler::onAckReceived(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onAckReceived");
}

void
WsInviteSessionHandler::onAckNotReceived(InviteSessionHandle) {
   InfoLog(<< "WsInviteSessionHandler::onAckNotReceived");
}

void
WsInviteSessionHandler::onStaleReInviteTimeout(InviteSessionHandle h) {
   InfoLog(<< "WsInviteSessionHandler::onStaleReInviteTimeout");
}

void
WsInviteSessionHandler::onIllegalNegotiation(InviteSessionHandle, const SipMessage& msg) {
   InfoLog(<< "WsInviteSessionHandler::onIllegalNegotiation");
}     

void
WsInviteSessionHandler::onSessionExpired(InviteSessionHandle) {
   InfoLog(<< "WsInviteSessionHandler::onSessionExpired");
}

void
WsInviteSessionHandler::onFlowTerminated(InviteSessionHandle) {
   InfoLog(<< "WsInviteSessionHandler::onFlowTerminated");
}
