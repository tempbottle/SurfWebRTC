#include <iostream>

#include "WsServer.hxx"
#include "/usr/local/include/rutil/Log.hxx"
#include "/usr/local/include/rutil/Logger.hxx"
#include "/usr/local/include/rutil/ResipAssert.h"

#include "/usr/local/include/resip/dum/DumThread.hxx"
#include "/usr/local/include/resip/dum/MasterProfile.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace server;
using namespace std;

WsServer::WsServer()
   : mRunning(false)
   , mSipStack(0)
   , mDum(0)
   , mDumThread(0)
   , mWsInviteSessionHandler(0)             
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
   mWsInviteSessionHandler = new WsInviteSessionHandler;
   resip_assert(mWsInviteSessionHandler);

   mDum->setInviteSessionHandler(mWsInviteSessionHandler);

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
   delete mWsInviteSessionHandler; mWsInviteSessionHandler = 0;
}
