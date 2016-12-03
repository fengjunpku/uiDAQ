#ifndef UDTAB_HH
#define UDTAB_HH 1

#include <TApplication.h>
#include <TGFrame.h>
#include <TFrame.h>
#include <TGTab.h>

#include "mainFrame.hh"
#include "initFrame.hh"

class udTab : public TGMainFrame
{
private:
  TGTextButton      *pExit;
  TGTab *pTab;
  mainFrame *pContent;
  initFrame *pInit;
public:
  udTab(const TGWindow *p,UInt_t w,UInt_t h);
  virtual ~udTab();

  //ClassDef(udTab,0)
};

#endif