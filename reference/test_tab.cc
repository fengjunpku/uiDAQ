#include "TGFrame.h"
#include "TGTab.h"
#include "TGButton.h"
#include "TRootEmbeddedCanvas.h"

void Start()
{
   printf("\"Start Filling Hists\" Button Pressed!\n");
}

void Stop()
{
   printf("\"Stop Filling Hists\" Button Pressed!\n");
}

void test_tab()
{
   TGMainFrame *main = new TGMainFrame(gClient->GetRoot(), 800, 600);

   TGHorizontalFrame *frame1 = new TGHorizontalFrame(main, 60, 20, kFixedWidth);
   TGTextButton *exitButton = new TGTextButton(frame1, "&Exit", 
                                               "gApplication->Terminate(0)");
   frame1->AddFrame(exitButton, new TGLayoutHints(kLHintsTop | kLHintsLeft | 
                                                  kLHintsExpandX, 2, 2, 2, 2));

   frame1->Resize(150, exitButton->GetDefaultHeight());
   main->AddFrame(frame1, new TGLayoutHints(kLHintsBottom | kLHintsRight, 2, 2, 5, 1));

   //--------- create the Tab widget
   TGTab *fTab = new TGTab(main, 300, 300);
   TGLayoutHints *fL3 = new TGLayoutHints(kLHintsTop | kLHintsLeft, 5, 5, 5, 5);
   
   //--------- create an empty tab element
   TGCompositeFrame *tf = fTab->AddTab("Tab 1");

   //-------------- create a tab element with an embedded canvas and buttons
   tf = fTab->AddTab("Tab 2");
   TGCompositeFrame *fF3 = new TGCompositeFrame(tf, 60, 20, kHorizontalFrame);
   TGTextButton *fStartB = new TGTextButton(fF3, "Start &Filling Hists", "Start()");
   TGTextButton *fStopB  = new TGTextButton(fF3, "&Stop Filling Hists", "Stop()");
   fF3->AddFrame(fStartB, fL3);
   fF3->AddFrame(fStopB, fL3);

   TGCompositeFrame *fF5 = new TGCompositeFrame(tf, 60, 60, kHorizontalFrame);

   TGLayoutHints *fL4 = new TGLayoutHints(kLHintsTop | kLHintsLeft | kLHintsExpandX |
                                          kLHintsExpandY, 5, 5, 5, 5);
   TRootEmbeddedCanvas *fEc1 = new TRootEmbeddedCanvas("ec1", fF5, 100, 100);
   fF5->AddFrame(fEc1, fL4);
   TRootEmbeddedCanvas *fEc2 = new TRootEmbeddedCanvas("ec2", fF5, 100, 100);
   fF5->AddFrame(fEc2, fL4);

   tf->AddFrame(fF3, fL3);
   tf->AddFrame(fF5, fL4);

   // make tab yellow
   Pixel_t yellow;
   gClient->GetColorByName("yellow", yellow);
   TGTabElement *tabel = fTab->GetTabTab("Tab 2");;
   tabel->ChangeBackground(yellow);

   //-------------- end embedded canvas

   main->AddFrame(fTab, new TGLayoutHints(kLHintsBottom | kLHintsExpandX |
                                          kLHintsExpandY, 2, 2, 5, 1));

   main->MapSubwindows();
   main->Resize();   // resize to default size
   main->MapWindow();
}