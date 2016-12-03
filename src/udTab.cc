#include "udTab.hh"

udTab::udTab(const TGWindow *p,UInt_t w,UInt_t h) : TGMainFrame(p,w,h)
{
  TGHorizontalFrame *ghf = new TGHorizontalFrame(this, 800, 800, kFixedWidth);
  pExit = new TGTextButton(ghf,"&Exit");
  pExit->SetToolTipText("Terminate the application",200);
  pExit->Connect("Pressed()", "TApplication", gApplication, "Terminate()");
  ghf->AddFrame(pExit,new TGLayoutHints(kLHintsExpandX | kLHintsBottom, 5, 5, 5, 5));
  ghf->Resize(150, pExit->GetDefaultHeight());
  AddFrame(ghf, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

  pTab = new TGTab(this,800,800);
  //--------- create an tab element
  TGCompositeFrame *tf = pTab->AddTab("Init");
  TGCompositeFrame *tabinit = new TGCompositeFrame(tf, 500, 500, kHorizontalFrame);
  pInit = new initFrame(tabinit,300,300);
  tabinit->AddFrame(pInit,new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5));
  tf->AddFrame(tabinit,new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));
  //********
  tf = pTab->AddTab("DAQ");
  TGCompositeFrame *tabframe = new TGCompositeFrame(tf, 500, 500, kHorizontalFrame);
  pContent = new mainFrame(tabframe,300,300);
  tabframe->AddFrame(pContent,new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 5));
  tf->AddFrame(tabframe,new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5));

  

  //---------------
  AddFrame(pTab, new TGLayoutHints(kLHintsBottom | kLHintsExpandX | kLHintsExpandY, 2, 2, 2, 2));

  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();
  MapSubwindows();
  SetWindowName("DAQ Demo");
  Resize();   // resize to default size
  MapWindow();
}

udTab::~udTab()
{
  Cleanup();
}