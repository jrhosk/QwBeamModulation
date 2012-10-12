//
// Plotting some shizzle
//

#include <vector>
#include "Riostream.h"

void sens_plot() {

  fstream file;

  file.open("monitor_slopes_md1barsum.dat", fstream::in | fstream::out );
  if( file.fail() ){
    std::cout << "Error opening file\n" << std::endl;
    exit(1);
  }

  Double_t max;
  Double_t min;
 
  TVectorD run_number(0);

  TVectorD xsens(0);
  TVectorD xpsens(0);
  TVectorD esens(0);
  TVectorD ysens(0);
  TVectorD ypsens(0);

  TVectorD zero_error(0);

  Int_t nlines = 0;

  TCanvas *c = new TCanvas("c", "Sensitivity",1000, 600);

  c->Divide(3,2);

  gStyle->SetOptFit(0001);

  c->SetGrid();
  c->GetFrame()->SetBorderSize(12);
  
  //
  // Beam Modulation information
  //

  while( !file.eof() )
   {

     run_number.ResizeTo(nlines + 1);
     xsens.ResizeTo(nlines + 1);
     xpsens.ResizeTo(nlines + 1);
     esens.ResizeTo(nlines + 1);
     ysens.ResizeTo(nlines + 1);
     ypsens.ResizeTo(nlines + 1);
     zero_error.ResizeTo(nlines + 1);
     
     file   >> run_number[nlines] 
	    >> xsens[nlines] 
	    >> xpsens[nlines]
            >> esens[nlines] 
	    >> ysens[nlines]
	    >> ypsens[nlines];

     zero_error.Zero();
     nlines++;     
   }

  c->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  
  TGraphErrors *sensx = new TGraphErrors(run_number, 1e6*xsens, zero_error, zero_error);

  sensx->SetMarkerColor(4);
  sensx->SetMarkerSize(0.8);
  sensx->SetMarkerStyle(21);
  sensx->SetTitle("X Sensitivities versus Run");
  sensx->GetXaxis()->SetTitle("Run number in Arbitrary Units");
  sensx->GetYaxis()->SetTitle("Sensitivity (per mm)");
  sensx->GetXaxis()->SetLabelSize(0.02);
  sensx->GetYaxis()->SetLabelSize(0.02);
  //  sensx->GetYaxis()->SetRangeUser(-2000., 2000.);
  sensx->Draw("AP");
  sensx->Fit("pol0");

  c->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *sensy = new TGraphErrors(run_number, 1e6*ysens, zero_error, zero_error);

  sensy->SetMarkerColor(5);
  sensy->SetMarkerSize(0.8);
  sensy->SetMarkerStyle(21);
  sensy->SetTitle("Y Sensitivities versus Run");
  sensy->GetXaxis()->SetTitle("Run number in Arbitrary Units");
  sensy->GetYaxis()->SetTitle("Sensitivity (per mm)");
  sensy->GetXaxis()->SetLabelSize(0.02);
  sensy->GetYaxis()->SetLabelSize(0.02);
  //  sensy->GetYaxis()->SetRangeUser(-2000., 2000.);
  sensy->Draw("AP");
  sensy->Fit("pol0");

  c->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();


  TGraphErrors *sense = new TGraphErrors(run_number, 0.0041*1e6*esens, zero_error, zero_error);

  sense->SetMarkerColor(6);
  sense->SetMarkerSize(0.8);
  sense->SetMarkerStyle(21);
  sense->SetTitle("E Sensitivities versus Run");
  sense->GetXaxis()->SetTitle("Run number in Arbitrary Units");
  sense->GetYaxis()->SetTitle("Sensitivity (per ppm)");
  sense->GetYaxis()->SetRangeUser(-10., 0.);
  sense->GetXaxis()->SetLabelSize(0.02);
  sense->GetYaxis()->SetLabelSize(0.02);
  sense->Draw("AP");
  sense->Fit("pol0");

  c->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *sensxp = new TGraphErrors(run_number, xpsens, zero_error, zero_error);

  sensxp->SetMarkerColor(7);
  sensxp->SetMarkerSize(0.8);
  sensxp->SetMarkerStyle(21);
  sensxp->SetTitle("XP Sensitivities versus Run");
  sensxp->GetXaxis()->SetTitle("Run number in Arbitrary Units");
  sensxp->GetYaxis()->SetTitle("Sensitivity (per urad)");
  sensxp->GetXaxis()->SetLabelSize(0.02);
  sensxp->GetYaxis()->SetLabelSize(0.02);
  //  sensxp->GetYaxis()->SetRangeUser(-100., 100.);
  sensxp->Draw("AP");
  sensxp->Fit("pol0");

  c->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *sensyp = new TGraphErrors(run_number, ypsens, zero_error, zero_error);

  sensyp->SetMarkerColor(8);
  sensyp->SetMarkerSize(0.8);
  sensyp->SetMarkerStyle(21);
  sensyp->SetTitle("YP Sensitivities versus Run");
  sensyp->GetXaxis()->SetTitle("Run number in Arbitrary Units");
  sensyp->GetYaxis()->SetTitle("Sensitivity (per urad)");
  sensyp->GetXaxis()->SetLabelSize(0.02);
  sensyp->GetYaxis()->SetLabelSize(0.02);
  //  sensyp->GetYaxis()->SetRangeUser(-100., 100.);
  sensyp->Draw("AP");
  sensyp->Fit("pol0");

  nlines = 0;

  file.close();

  return;
}


