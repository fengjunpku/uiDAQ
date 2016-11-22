#include "mainFrame.hh"

mainFrame::mainFrame(const TGWindow *p,UInt_t w,UInt_t h) : TGMainFrame(p,w,h)
{ 
  //frames
  pMain = new TGVerticalFrame(this);
  pPathFrame = new TGHorizontalFrame(pMain);
  pCommandFrame = new TGHorizontalFrame(pMain);
  pFunctionFrame = new TGHorizontalFrame(pMain);
  pButtonFrame = new TGHorizontalFrame(pMain);
  //filepath
  pPath = new TGTextEntry(pPathFrame,(const char *)"",20);
  pPath->SetText("/home/daq/babirl/babicon/babicmd");
  pPathFrame->AddFrame(new TGLabel(pPathFrame, "CMD Path: "),
                          new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  pPathFrame->AddFrame(pPath,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  pMain->AddFrame(pPathFrame,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  //textView
  pTextView = new TGTextViewostream(pMain,500,300);
  pMain->AddFrame(pTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 0));
  //command
  pCommand = new TGTextEntry(pCommandFrame,(const char *)"",20);
  pCommand->Connect("ReturnPressed()","mainFrame",this,"HandleReturn()");
  pCommandFrame->AddFrame(new TGLabel(pCommandFrame, "Command: "),
                          new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  pCommandFrame->AddFrame(pCommand,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  pMain->AddFrame(pCommandFrame,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  //buttons
  pStart = new TGTextButton(pFunctionFrame,"&Start");
  pStart->SetToolTipText("Start DAQ");
  pStart->Connect("Clicked()","mainFrame",this,"Start()");
  pFunctionFrame->AddFrame(pStart,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));

  pStop = new TGTextButton(pFunctionFrame,"&Stop");
  pStart->SetToolTipText("Stop DAQ");
  pStop->Connect("Clicked()","mainFrame",this,"Stop()");
  pFunctionFrame->AddFrame(pStop,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));


  pReset = new TGTextButton(pButtonFrame,"&Reset");
  pReset->SetToolTipText("Press to clear the command entry\nand the TextView",200);
  pReset->Connect("Clicked()","mainFrame",this,"Reset()");
  pButtonFrame->AddFrame(pReset,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));

  pExit = new TGTextButton(pButtonFrame,"&Exit");
  pExit->SetToolTipText("Terminate the application",200);
  pExit->Connect("Pressed()", "TApplication", gApplication, "Terminate()");
  pButtonFrame->AddFrame(pExit,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));

  pMain->AddFrame(pFunctionFrame,new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));
  pMain->AddFrame(pButtonFrame,new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));
  //main
  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();

  AddFrame(pMain,new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY));
  MapSubwindows();
  Resize(GetDefaultSize());

  SetWindowName("DAQ demo");
  MapRaised();
}

mainFrame::~mainFrame()
{
  Cleanup();
}

void mainFrame::Reset()
{
  pCommand->Clear();
  pTextView->Clear();
}

void mainFrame::Start()
{
  TString cmd(pPath->GetText());
  cmd += " localhost start";
  *pTextView<<cmd.Data()<<std::endl;
  pTextView->ShowBottom();
}

void mainFrame::Stop()
{
  TString cmd(pPath->GetText());
  cmd += " localhost stop";
  *pTextView<<cmd.Data()<<std::endl;
  pTextView->ShowBottom();
}
void mainFrame::HandleReturn()
{
   TString dir(pPath->GetText());
   TString cmd(pCommand->GetText());
   cmd = dir+cmd;
   *pTextView << gSystem->GetFromPipe(cmd).Data() << std::endl;
   pTextView->ShowBottom();
   //pCommand->Clear();
}