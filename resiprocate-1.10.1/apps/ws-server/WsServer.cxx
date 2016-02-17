#include <iostream>

#include "WsServer.hxx"

#include "/usr/local/include/rutil/Log.hxx"
#include "/usr/local/include/rutil/Logger.hxx"
#include "/usr/local/include/rutil/ResipAssert.h"

#include "/usr/local/include/resip/dum/DumThread.hxx"
#include "/usr/local/include/resip/dum/MasterProfile.hxx"
#include "/usr/local/include/resip/dum/Handles.hxx"
#include "/usr/local/include/resip/dum/InviteSessionHandler.hxx"
#include "/usr/local/include/resip/dum/ClientInviteSession.hxx"
#include "/usr/local/include/resip/dum/ServerInviteSession.hxx"
#include "/usr/local/include/resip/dum/DialogUsageManager.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace server;
using namespace std;

WsServer::WsServer()
   : mRunning(false)
   , mSipStack(0)
   , mDum(0)
   , mDumThread(0)
   , mCallCount(0)
{
}

WsServer::~WsServer()
{
   if (mRunning) {
        shutdown();
   }
}

bool
WsServer::run(int argc, char** argv)
{
   if (mRunning) {
      return false;
   }

   // Initialize logger
   Log::initialize(Log::Cout, resip::Log::Debug, argv[0]);

   InfoLog(<< "Starting WsServer");

   // Create SipStack and associated objects
   resip_assert(!mSipStack);
   mSipStack = new SipStack();

   mSipStack->addTransport(UDP, 7000);
   mSipStack->addTransport(WS, 7002);

   // Create DialogeUsageManager 
   SharedPtr<MasterProfile> profile(new MasterProfile);

   resip_assert(!mDum);
   resip_assert(!mDumThread);
   mDum = new DialogUsageManager(*mSipStack);
   mDum->setMasterProfile(profile);

   // Set Invite Session Handler
   mDum->setInviteSessionHandler(this);

   mDumThread = new DumThread(*mDum);

   // Make it all go - startup all threads
   mSipStack->run();

   if (mDumThread) {
      mDumThread->run();
   }

   mRunning = true;

   return true;
}

void 
WsServer::shutdown()
{
   if (!mRunning) {
      return;
   }

   // Tell all threads to shutdown
   if (mDumThread) {
      mDumThread->shutdown();
   }

   mSipStack->shutdownAndJoinThreads();

   if(mDumThread) {
      mDumThread->join();
   }

   cleanupObjects();
   mRunning = false;
}

void
WsServer::cleanupObjects()
{
   delete mDumThread; mDumThread = 0;
   delete mDum; mDum = 0;
   delete mSipStack; mSipStack = 0;
}

void
WsServer::onNewSession(ClientInviteSessionHandle, InviteSession::OfferAnswerType oat, const SipMessage& msg) {
   DebugLog(<< "WsServer::onNewSession");
}

void
WsServer::onNewSession(ServerInviteSessionHandle sis, InviteSession::OfferAnswerType oat, const SipMessage& msg) {
   DebugLog(<< "WsServer::onNewSession");
   DebugLog(<< "ServerInviteSession-onNewSession - " << msg.brief());

   // Increment call count
   mCallCount++;

   // Save server invite session handles
   if (mCallCount == 1) {
      mSisFirstCaller = sis;
   } else if (mCallCount == 2) {
      mSisSecondCaller = sis;
   }

   DebugLog(<< "Sending 180 Ringing response");
   sis->provisional(180);
}

void
WsServer::onFailure(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onFailure");
}

void
WsServer::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const SdpContents&) {
   DebugLog(<< "WsServer::onEarlyMedia");
}

void
WsServer::onEarlyMedia(ClientInviteSessionHandle, const SipMessage&, const Contents&) {
   DebugLog(<< "WsServer::onEarlyMedia");
}

void
WsServer::onProvisional(ClientInviteSessionHandle, const SipMessage&) {
   DebugLog(<< "WsServer::onProvisional");
}

void
WsServer::onConnected(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onConnected");
}

void
WsServer::onConnected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onConnected");
}

void
WsServer::onConnectedConfirmed(InviteSessionHandle, const SipMessage &msg) {
   DebugLog(<< "WsServer::onConnectedConfirmed");
}

void
WsServer::onPrack(ServerInviteSessionHandle, const SipMessage &msg) {
   DebugLog(<< "WsServer::onPrack");
}

void
WsServer::onStaleCallTimeout(ClientInviteSessionHandle h) {
   DebugLog(<< "WsServer::onStaleCallTimeout");
}

void
WsServer::terminate(ClientInviteSessionHandle h) {
   DebugLog(<< "WsServer::terminate");
}

void
WsServer::onTerminated(InviteSessionHandle is, InviteSessionHandler::TerminatedReason reason, const SipMessage* related) {
   DebugLog(<< "WsServer::onTerminated");
   DebugLog(<< "ServerInviteSession-onTerminated");
   
   // Decrement active call count
   mCallCount--;

   // Hung up both bridged calls if one of them hangs the call
   if (is == mInviteSessionHandleFirstCaller) {
           mInviteSessionHandleSecondCaller->end();
   } else if (is == mInviteSessionHandleSecondCaller) {
           mInviteSessionHandleFirstCaller->end();
   }
}

void
WsServer::onForkDestroyed(ClientInviteSessionHandle) {
   DebugLog(<< "WsServer::onForkDestroyed");
}

void
WsServer::onRedirected(ClientInviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onRedirected");
}

void
WsServer::onReadyToSend(InviteSessionHandle, SipMessage& msg) {
   DebugLog(<< "WsServer::onReadyToSend");
}

void
WsServer::onAnswer(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   DebugLog(<< "WsServer::onAnswer");
}

void
WsServer::onAnswer(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   DebugLog(<< "WsServer::onAnswer");
}

void
WsServer::onOffer(InviteSessionHandle is, const SipMessage& msg, const SdpContents& sdp) {
   DebugLog(<< "WsServer::onOffer");
}      

void
WsServer::onOffer(InviteSessionHandle is, const SipMessage& msg, const Contents& sdp) {
   DebugLog(<< "WsServer::onOffer");
   DebugLog(<< "ServerInviteSession-onNewSession-onOffer(SDP)");

   // Save SDP & Invite session handles
   if (mCallCount == 1) {
      mInviteSessionHandleFirstCaller = is;
      mSdpFirstCaller = reinterpret_cast<SdpContents *>(sdp.clone()); 
   } else if (mCallCount == 2) {
      mInviteSessionHandleSecondCaller = is;
      mSdpSecondCaller = reinterpret_cast<SdpContents *>(sdp.clone()); 
      bridge();
   }
}      

void
WsServer::onRemoteSdpChanged(InviteSessionHandle, const SipMessage& msg, const SdpContents&) {
   DebugLog(<< "WsServer::onRemoteSdpChanged");
}

void
WsServer::onRemoteAnswerChanged(InviteSessionHandle, const SipMessage& msg, const Contents&) {
   DebugLog(<< "WsServer::onRemoteAnswerChanged");
}  

void
WsServer::onOfferRequestRejected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onOfferRequestRejected");
}

void
WsServer::onOfferRequired(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onOfferRequired");
}      

void
WsServer::onOfferRejected(InviteSessionHandle, const SipMessage* msg) {
   DebugLog(<< "WsServer::onOfferRejected");
}

void
WsServer::onInfo(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onInfo");
}

void
WsServer::onInfoSuccess(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onInfoSuccess");
}

void
WsServer::onInfoFailure(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onInfoFailure");
}

void
WsServer::onMessage(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onMessage");
}

void
WsServer::onMessageSuccess(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onMessageSuccess");
}

void
WsServer::onMessageFailure(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onMessageFailure");
}

void
WsServer::onRefer(InviteSessionHandle, ServerSubscriptionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onRefer");
}

void
WsServer::onReferNoSub(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onReferNoSub");
}

void
WsServer::onReferRejected(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onReferRejected");
}

void
WsServer::onReferAccepted(InviteSessionHandle, ClientSubscriptionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onReferAccepted");
}

void
WsServer::onAckReceived(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onAckReceived");
}

void
WsServer::onAckNotReceived(InviteSessionHandle) {
   DebugLog(<< "WsServer::onAckNotReceived");
}

void
WsServer::onStaleReInviteTimeout(InviteSessionHandle h) {
   DebugLog(<< "WsServer::onStaleReInviteTimeout");
}

void
WsServer::onIllegalNegotiation(InviteSessionHandle, const SipMessage& msg) {
   DebugLog(<< "WsServer::onIllegalNegotiation");
}     

void
WsServer::onSessionExpired(InviteSessionHandle) {
   DebugLog(<< "WsServer::onSessionExpired");
}

void
WsServer::onFlowTerminated(InviteSessionHandle) {
   DebugLog(<< "WsServer::onFlowTerminated");
}

void
WsServer::bridge() {
   // Bridge the calls
   mInviteSessionHandleFirstCaller->provideAnswer(*mSdpSecondCaller);
   mSisFirstCaller->accept();

   mInviteSessionHandleSecondCaller->provideAnswer(*mSdpFirstCaller);
   mSisSecondCaller->accept();
}
