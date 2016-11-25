#include <TApplication.h>
#include <TGClient.h>

#include "mainFrame.hh"
#include "udTab.hh"
int main(int argc, char *argv[])
{
  TApplication *gapp = new TApplication("app",&argc,argv);
  //new mainFrame(gClient->GetRoot(),300,300);
  new udTab(gClient->GetRoot(),500,300);
  gapp->Run();
  return 0;
}