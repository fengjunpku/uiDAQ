#include "initFrame.hh"

initFrame::initFrame(const TGWindow *p,UInt_t w,UInt_t h) : TGMainFrame(p,w,h)
{
  //frames
  pMain = new TGVerticalFrame(this);
  pGInit = new TGGroupFrame(pMain, "Init DAQ");
  pfi = new TGHorizontalFrame(pGInit);
  pGbabies = new TGGroupFrame(pMain, "Init DAQ");
  pfb = new TGHorizontalFrame(pGbabies);

  //Init Frame
  pInitPath = new TGTextEntry(pfi,(const char *)"",20);
  pInitPath->SetText("/home/daq/DAQConfig/bbcaenvme/init/daqinit.sh");
  pfi->AddFrame(new TGLabel(pfi, "Init Path: "),
                          new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  pInitPath->Resize(350,20);
  pfi->AddFrame(pInitPath,new TGLayoutHints(kLHintsExpandX | kLHintsRight, 5, 5, 5, 5));
  pGInit->AddFrame(pfi, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

  pBInit = new TGTextButton(pGInit,"&Init");
  pBInit->SetToolTipText("Init DAQ");
  pBInit->Connect("Clicked()","initFrame",this,"DoInit()");
  pGInit->AddFrame(pBInit,new TGLayoutHints(kLHintsBottom | kLHintsRight, 5, 5, 5, 5));

  pMain->AddFrame(pGInit, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  //babies frame
  pMain->AddFrame(pGbabies, new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));
  pBabiesPath = new TGTextEntry(pfb,(const char *)"",20);
  pBabiesPath->SetText("/home/daq/DAQConfig/bbcaenvme/babies/babies");
  pfb->AddFrame(new TGLabel(pfb, "Babies Path: "),
                          new TGLayoutHints(kLHintsCenterY | kLHintsLeft, 5, 5, 5, 5));
  pfb->AddFrame(pBabiesPath,new TGLayoutHints(kLHintsExpandX | kLHintsRight, 5, 5, 5, 5));
  pGbabies->AddFrame(pfb,new TGLayoutHints(kLHintsExpandX, 5, 5, 5, 5));

  pBBabies = new TGTextButton(pGbabies,"&Babies");
  pBBabies->SetToolTipText("Babies");
  pBBabies->Connect("Clicked()","initFrame",this,"DoBabies()");
  pGbabies->AddFrame(pBBabies,new TGLayoutHints(kLHintsBottom | kLHintsRight, 5, 5, 5, 5));

  //textView
  pTextView = new TGTextViewostream(pMain,400,200);
  pMain->AddFrame(pTextView, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 5, 5, 5, 0));

  //pMain
  Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
  DontCallClose();
  AddFrame(pMain,new TGLayoutHints(kLHintsTop | kLHintsExpandX | kLHintsExpandY));
  MapSubwindows();
  Resize(GetDefaultSize());

  SetWindowName("DAQ demo");
  MapRaised();
}

initFrame::~initFrame()
{
  Cleanup();
}

void initFrame::DoInit()
{
  *pTextView<<"Init DAQ"<<std::endl;
  TString cmd("sh ");
  cmd += pInitPath->GetText();
  *pTextView<<cmd.Data()<<std::endl;
}

void initFrame::DoBabies()
{
  *pTextView<<"Babies"<<std::endl;
  TString cmd(pBabiesPath->GetText());
  *pTextView<<cmd.Data()<<std::endl;
}