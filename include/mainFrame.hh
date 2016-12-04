#ifndef MAINFRAME_HH
#define MAINFRAME_HH 1

#include <stdio.h>

#include <TApplication.h>
#include <TSystem.h>
#include <TGFrame.h>
#include <TFrame.h>
#include <TGButton.h>
#include <TGTextViewStream.h>
#include <TGStatusBar.h>
#include <TGNumberEntry.h>
#include <TGLabel.h>
#include <TString.h>
#include <TTimer.h>
#include <TRandom3.h>

class mainFrame : public TGMainFrame
{
private:
  TGTextButton      *pReset,*pStart,*pStop;
  TGCheckButton     *pRecord;
  TGTextViewostream *pTextView;
  TGVerticalFrame   *pMain;
  TGHorizontalFrame *pFunctionFrame,*pButtonFrame,*pCommandFrame,*pPathFrame;
  TGTextEntry       *pCommand,*pPath;
  TGStatusBar *pStatus;
  TTimer *pTimer;
  Bool_t isRecord;
public:
  mainFrame(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~mainFrame();
  void Reset();
  void HandleReturn();
  void Start();
  void Stop();
  void SetRecord(Bool_t r);
  void Test();

  ClassDef(mainFrame,0)
};
#endif