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

class mainFrame : public TGMainFrame
{
private:
  TGTextButton      *pReset,*pExit,*pStart,*pStop;
  TGTextViewostream *pTextView;
  TGVerticalFrame   *pMain;
  TGHorizontalFrame *pFunctionFrame,*pButtonFrame,*pCommandFrame,*pPathFrame;
  TGTextEntry       *pCommand,*pPath;
public:
  mainFrame(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~mainFrame();
  void Reset();
  void HandleReturn();
  void Start();
  void Stop();

  ClassDef(mainFrame,0)
};
#endif