#include <signal.h>

#include "WsServer.hxx"
#include "/usr/local/include/rutil/Log.hxx"
#include "/usr/local/include/rutil/Time.hxx"
#include "/usr/local/include/rutil/Logger.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace server;
using namespace resip;
using namespace std;

static bool finished = false;
static bool receivedHUP = false;

static void
signalHandler(int signo)
{
   if (signo == SIGHUP) {
      Log::reset();
      receivedHUP = true;
      return;
   }
   std::cerr << "Shutting down" << endl;
   finished = true;
}

int
main(int argc, char** argv)
{
   // Install signal handlers
   if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      cerr << "Couldn't install signal handler for SIGPIPE" << endl;
      exit(-1);
   }
   if (signal(SIGHUP, signalHandler) == SIG_ERR) {
      cerr << "Couldn't install signal handler for SIGHUP" << endl;
      exit(-1);
   }

   if (signal(SIGINT, signalHandler) == SIG_ERR) {
      cerr << "Couldn't install signal handler for SIGINT" << endl;
      exit(-1);
   }

   if (signal(SIGTERM, signalHandler) == SIG_ERR) {
      cerr << "Couldn't install signal handler for SIGTERM" << endl;
      exit(-1);
   }

   WsServer wsServer;

   if(!wsServer.run(argc, argv)) {
      cerr << "Failed to start wsServer, exiting..." << endl;
      exit(-1);
   }

   // Main program thread, just waits here for a signal to shutdown
   while (!finished) {
      sleepMs(1000);

      if (receivedHUP) {
         receivedHUP = false;
      }
   }

   wsServer.shutdown();

   return 0;
}
