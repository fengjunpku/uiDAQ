#include "mainFrame.hh"

mainFrame::mainFrame(const TGWindow *p,UInt_t w,UInt_t h) : TGMainFrame(p,w,h)
{ 
  isRecord = kFALSE;
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
  pCommandFrame->AddFrame(new TGLabel(pCommandFrame, "Command: "), new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  pCommandFrame->AddFrame(pCommand,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  pMain->AddFrame(pCommandFrame,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  //check button
  pRecord = new TGCheckButton(pFunctionFrame, "Record\nOn/Off");
  pRecord->SetOn(0);
  pRecord->Connect("Toggled(Bool_t)","mainFrame",this,"SetRecord(Bool_t)");
  pFunctionFrame->AddFrame(pRecord, new TGLayoutHints(kLHintsLeft| kLHintsTop, 5, 5, 5, 5));
  //buttons
  pStart = new TGTextButton(pFunctionFrame,"&Start");
  pStart->SetToolTipText("Start DAQ");
  pStart->Connect("Clicked()","mainFrame",this,"Start()");
  pFunctionFrame->AddFrame(pStart,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));

  pStop = new TGTextButton(pFunctionFrame,"&Stop");
  pStop->SetToolTipText("Stop DAQ");
  pStop->Connect("Clicked()","mainFrame",this,"Stop()");
  pStop->SetEnabled(0);
  pFunctionFrame->AddFrame(pStop,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));


  pReset = new TGTextButton(pFunctionFrame,"&CLear");
  pReset->SetToolTipText("Press to clear the command entry\nand the TextView",200);
  pReset->Connect("Clicked()","mainFrame",this,"Reset()");
  pFunctionFrame->AddFrame(pReset,new TGLayoutHints(kLHintsExpandX | kLHintsTop, 5, 5, 5, 5));


  pMain->AddFrame(pFunctionFrame,new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));
  pMain->AddFrame(pButtonFrame,new TGLayoutHints(kLHintsTop | kLHintsExpandX, 0, 0, 0, 0));
  //status
  Int_t parts[] = {25,25,25,25};
  pStatus = new TGStatusBar(pMain,300,20,kVerticalFrame);
  pStatus->SetParts(parts,4);
  pStatus->Draw3DCorner(kFALSE);
  pMain->AddFrame(pStatus, new TGLayoutHints(kLHintsExpandX, 0, 0, 0, 0));
  //main
  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();

  AddFrame(pMain,new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY));
  MapSubwindows();
  Resize(GetDefaultSize());

  SetWindowName("DAQ demo");
  MapRaised();
  //timer
  pTimer = new TTimer(2000);
  pTimer->Connect("Timeout()", "mainFrame", this, "Test()");
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
  if(isRecord)
    cmd += " localhost start";
  else
    cmd += " localhost nssta";
  *pTextView<<cmd.Data()<<std::endl;
  pTextView->ShowBottom();
  pStart->SetEnabled(0);
  pStop->SetEnabled();

  pTimer->TurnOn();
}

void mainFrame::Stop()
{
  TString cmd(pPath->GetText());
  cmd += " localhost stop";
  *pTextView<<cmd.Data()<<std::endl;
  pTextView->ShowBottom();
  pStart->SetEnabled();
  pStop->SetEnabled(0);

  pTimer->TurnOff();
}
void mainFrame::HandleReturn()
{
   TString dir(pPath->GetText());
   TString cmd(pCommand->GetText());
   cmd = dir+cmd;
   *pTextView << gSystem->GetFromPipe(cmd).Data() << std::endl;
   pTextView->ShowBottom();
   pCommand->Clear();
}
void mainFrame::SetRecord(Bool_t r)
{
  isRecord = r;
  //*pTextView << isRecord << std::endl;
}

void mainFrame::Test()
{
  pStatus->SetText("data0001.ridf",0);
  int i=0;
  TRandom3 r(0);
  char buff[20];
  sprintf(buff,"%02.4f",r.Uniform());
  pStatus->SetText(buff,1);
}