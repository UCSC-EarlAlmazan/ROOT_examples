#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooLandau.h"
#include "RooFFTConvPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TH1.h"

#include "header.hh"
// I added this line so that you don't have to include any class here.

using namespace RooFit ;

void example_5()
{
  // S e t u p   c o m p o n e n t   p d f s
  // ---------------------------------------

  // Construct observable
  RooRealVar mgg("mgg","mgg",100,160) ;

  // Construct gauss(t,mg,sg)

  RooRealVar mean("mean","mean",125,110,140) ;
  RooRealVar sigma("sigma","sigma",1.6,0.1,10) ;
  RooGaussian sig_pdf("sig_pdf","sig_pdf",mgg,mean,sigma) ;

  RooRealVar mean2("mean2","mean",135,110,140) ;
  RooRealVar sigma2("sigma2","sigma",1.6,0.1,10) ;
  RooGaussian sig_pdf2("sig_pdf2","sig_pdf",mgg,mean2,sigma2) ;

  //Construct a background pdf with RooExponential

  RooRealVar slope("slope","slope",-0.02,-5.0,0.0);
  RooExponential bkg_pdf("bkg_pdf","bkg_pdf",mgg,slope);

  //Construct an "extended pdf"

  RooRealVar nsig("nsig","nsig",50,0,1400) ;
  nsig.setVal(99);

  RooRealVar nsig2("nsig2","nsig2",40,0,1400) ;
  RooRealVar nbkg("nbkg","nbkg",500,0,14000) ;

  RooAddPdf s_plus_b_pdf("s_plus_b_pdf","s_plus_b_pdf",RooArgList(sig_pdf,sig_pdf2,bkg_pdf),RooArgList(nsig,nsig2, nbkg));

  RooDataSet* data = s_plus_b_pdf.generate(mgg,10000) ;

  s_plus_b_pdf.fitTo(*data) ;

  cout << nsig.getVal() << "" << nsig.getError() << endl;

  // Plot data
  RooPlot* frame = mgg.frame(Title("Fit")) ;
  data->plotOn(frame) ;
  s_plus_b_pdf.plotOn(frame);

  // bkg pdf normalization scale factor
  double scale = nbkg.getVal() / ( nsig.getVal() + nbkg.getVal() );
  bkg_pdf.plotOn(frame,LineStyle(kDashed), Normalization(scale)) ;

  // Draw frame on canvas
  TCanvas*c = new TCanvas("c","c",800,600) ;
  gPad->SetLeftMargin(0.15) ; frame->GetYaxis()->SetTitleOffset(1.4) ; frame->Draw() ;
  c->SaveAs("Roofit_example_DataSample_and_Fit.png");

}