#include "udTab.hh"

udTab::udTab(const TGWindow *p,UInt_t w,UInt_t h) : TGMainFrame(p,w,h)
{
  TGHorizontalFrame *frame1 = new TGHorizontalFrame(this, 300, 20, kFixedWidth);
  TGTextButton *exitButton = new TGTextButton(frame1, "&Exit", 
                                               "gApplication->Terminate(0)");
  frame1->AddFrame(exitButton, new TGLayoutHints(kLHintsTop | kLHintsLeft | 
                                                  kLHintsExpandX, 2, 2, 2, 2));

  frame1->Resize(150, exitButton->GetDefaultHeight());
  AddFrame(frame1, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

  pExit = new TGTextButton(this,"&Exit");
  pExit->SetToolTipText("Terminate the application",200);
  pExit->Connect("Pressed()", "TApplication", gApplication, "Terminate()");
  AddFrame(pExit,new TGLayoutHints(kLHintsExpandX | kLHintsBottom, 5, 5, 5, 5));

  pTab = new TGTab(this);

  //--------- create an tab element
  TGCompositeFrame *tf = pTab->AddTab("DAQ");
  TGCompositeFrame *tabframe = new TGCompositeFrame(tf, 500, 500, kHorizontalFrame);
  pContent = new mainFrame(tabframe,300,300);
  tabframe->AddFrame(pContent,new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX |
                                          kLHintsExpandY, 5, 5, 5, 5));

  tf = pTab->AddTab("Init");

  AddFrame(pTab, new TGLayoutHints(kLHintsTop | kLHintsExpandX |
                                        kLHintsExpandY, 2, 2, 2, 2));

  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();
  MapSubwindows();
  Resize(GetDefaultSize());   // resize to default size
  MapWindow();
}

udTab::~udTab()
{
  Cleanup();
}