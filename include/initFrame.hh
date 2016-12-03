#ifndef INITFRAME_HH
#define INITFRAME_HH 1

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

class initFrame : public TGMainFrame
{
private:
  TGVerticalFrame   *pMain;
  TGGroupFrame *pGInit,*pGbabies;
  TGHorizontalFrame *pfi,*pfb;
  TGTextEntry       *pInitPath,*pBabiesPath;
  TGTextButton      *pBInit,*pBBabies;
  TGTextViewostream *pTextView;
public:
  initFrame(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~initFrame();
  void DoInit();
  void DoBabies();

  ClassDef(initFrame,0)
};
#endif