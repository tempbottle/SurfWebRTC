#if !defined(WSINVITESESSIONHANDLER_HXX)
#define WSINVITESESSIONHANDLER_HXX 

#include "/usr/local/include/resip/dum/Handle.hxx"
#include "/usr/local/include/resip/dum/DialogUsageManager.hxx"
#include "/usr/local/include/resip/dum/InviteSessionHandler.hxx"
#include "/usr/local/include/resip/dum/MasterProfile.hxx"

#include "/usr/local/include/rutil/Logger.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;

namespace server 
{
class WsInviteSessionHandler : public resip::InviteSessionHandler 
{
public:
   WsInviteSessionHandler(); 

   ~WsInviteSessionHandler();
        
   virtual void onNewSession(ClientInviteSessionHandle, InviteSession::OfferAnswerType oat, const SipMessage& msg);

   virtual void onNewSession(ServerInviteSessionHandle, InviteSession::OfferAnswerType oat, const SipMessage& msg);

   virtual void onFailure(ClientInviteSessionHandle, const SipMessage& msg);
   
   virtual void onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const SdpContents&);

   virtual void onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const Contents&);

   virtual void onProvisional(ClientInviteSessionHandle, const SipMessage&);

   virtual void onConnected(ClientInviteSessionHandle, const SipMessage& msg);

   virtual void onConnected(InviteSessionHandle, const SipMessage& msg);

   virtual void onConnectedConfirmed(InviteSessionHandle, const SipMessage &msg);

   virtual void onPrack(ServerInviteSessionHandle, const SipMessage &msg);

   virtual void onStaleCallTimeout(ClientInviteSessionHandle h);

   virtual void terminate(ClientInviteSessionHandle h);
   
   virtual void onTerminated(InviteSessionHandle, InviteSessionHandler::TerminatedReason reason, const SipMessage* related);

   virtual void onForkDestroyed(ClientInviteSessionHandle);

   virtual void onRedirected(ClientInviteSessionHandle, const SipMessage& msg);

   virtual void onReadyToSend(InviteSessionHandle, SipMessage& msg);

   virtual void onAnswer(InviteSessionHandle, const SipMessage& msg, const SdpContents&);

   virtual void onAnswer(InviteSessionHandle, const SipMessage& msg, const Contents&);

   virtual void onOffer(InviteSessionHandle, const SipMessage& msg, const SdpContents&);      

   virtual void onOffer(InviteSessionHandle, const SipMessage& msg, const Contents&);      

   virtual void onRemoteSdpChanged(InviteSessionHandle, const SipMessage& msg, const SdpContents&);

   virtual void onRemoteAnswerChanged(InviteSessionHandle, const SipMessage& msg, const Contents&);  

   virtual void onOfferRequestRejected(InviteSessionHandle, const SipMessage& msg);

   virtual void onOfferRequired(InviteSessionHandle, const SipMessage& msg);      
   
   virtual void onOfferRejected(InviteSessionHandle, const SipMessage* msg);
   
   virtual void onInfo(InviteSessionHandle, const SipMessage& msg);

   virtual void onInfoSuccess(InviteSessionHandle, const SipMessage& msg);
   
   virtual void onInfoFailure(InviteSessionHandle, const SipMessage& msg);

   virtual void onMessage(InviteSessionHandle, const SipMessage& msg);

   virtual void onMessageSuccess(InviteSessionHandle, const SipMessage& msg);

   virtual void onMessageFailure(InviteSessionHandle, const SipMessage& msg);

   virtual void onRefer(InviteSessionHandle, ServerSubscriptionHandle, const SipMessage& msg);

   virtual void onReferNoSub(InviteSessionHandle, const SipMessage& msg);

   virtual void onReferRejected(InviteSessionHandle, const SipMessage& msg);

   virtual void onReferAccepted(InviteSessionHandle, ClientSubscriptionHandle, const SipMessage& msg);

   virtual void onAckReceived(InviteSessionHandle, const SipMessage& msg);

   virtual void onAckNotReceived(InviteSessionHandle);

   virtual void onStaleReInviteTimeout(InviteSessionHandle h);

   virtual void onIllegalNegotiation(InviteSessionHandle, const SipMessage& msg);     

   virtual void onSessionExpired(InviteSessionHandle);

   virtual void onFlowTerminated(InviteSessionHandle);

   void bridge();

private:
   ServerInviteSessionHandle mSisFirstCaller;
   ServerInviteSessionHandle mSisSecondCaller;
   SdpContents *mSdpFirstCaller;
   SdpContents *mSdpSecondCaller;
   InviteSessionHandle mInviteSessionHandleFirstCaller;   
   InviteSessionHandle mInviteSessionHandleSecondCaller;   
   int mCallCount;
};
}

#endif
