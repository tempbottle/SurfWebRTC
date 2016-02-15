#if !defined(WSSERVER_HXX)
#define WSSERVER_HXX 

#include <memory>

#include "/usr/local/include/rutil/Data.hxx"
#include "/usr/local/include/rutil/ServerProcess.hxx"

#include "/usr/local/include/resip/dum/InviteSessionHandler.hxx"

#include "WsInviteSessionHandler.hxx"

namespace resip
{
   class TransactionUser;
   class SipStack;
   class RegistrationPersistenceManager;
   class PublicationPersistenceManager;
   class FdPollGrp;
   class AsyncProcessHandler;
   class ThreadIf;
   class DialogUsageManager;
   class CongestionManager;
}

namespace server 
{
class InviteSessionHandler;

class WsServer : public resip::ServerProcess
{
public:
   WsServer();
   virtual ~WsServer();

   virtual bool run(int argc, char** argv);
   virtual void shutdown();
   virtual void cleanupObjects();

private:
   bool mRunning;
   bool mRestarting;
   int mArgc;
   char** mArgv;
   resip::SipStack* mSipStack;
   resip::DialogUsageManager* mDum;
   resip::ThreadIf* mDumThread;
   WsInviteSessionHandler* mWsInviteSessionHandler;
};
}

#endif
