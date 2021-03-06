//
// Plotting some shizzle
//

#include <vector>
#include "Riostream.h"

void bcmplot() {

  fstream file;

//   file.open("monitor_slopes_bcm1.dat", fstream::in | fstream::out );
  file.open("mdout.dat", fstream::in | fstream::out );
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

  TCanvas *c = new TCanvas("c", "BCM plot",800, 800);
  TCanvas *c_std = new TCanvas("c_std", "Z BCM plot",800, 800);

  TH1D *histy = new TH1D("histy", "histy", 100, -0.005, 0.005);
  TH1D *histyp = new TH1D("histyp", "histyp", 100, -200., 200.);

  TH1D *histy_std = new TH1D("histy_std", "histy_std", 25, -5., 5.);
  TH1D *histyp_std = new TH1D("histyp_std", "histyp_std", 25, -5., 5.);

  c->Divide(1,2);

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

  TVectorD mean(5);
  
  for(Int_t i = 0; i < run_number.GetNrows(); i++)
    {
      histy->Fill(ysens[i]);
      histyp->Fill(ypsens[i]);

      mean[0]  += xsens[i];
      mean[1] += xpsens[i];
      mean[2]  += esens[i];
      mean[3]  += ysens[i];
      mean[4] += ypsens[i];

    }
  for(Int_t i = 0; i < 5; i++)
    mean[i]  /= nlines;

  c->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  histy->SetTitle("Y Sensitivities");
  histy->Draw();
  histy->Fit("gaus");

  Double_t rmsy  = histy->GetRMS(); 

  c->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  histyp->SetTitle("Y' Sensitivities");
  histyp->Draw();
  histyp->Fit("gaus");

  Double_t rmsyp  = histyp->GetRMS(); 


  for(Int_t i = 0; i < run_number.GetNrows(); i++)
    {
      histy_std->Fill( (ysens[i] - mean[3])/rmsy );
      histyp_std->Fill( (ypsens[i] - mean[4])/rmsyp );

//       std::cout << "Z_y:\t" << (ysens[i] - meany)/rmsy << "\tZ_yp:\t " << (ypsens[i] - meanyp)/rmsyp << std::endl;

    }

  c_std->Divide(1,2);

  gStyle->SetOptFit(0001);

  c_std->SetGrid();
  c_std->GetFrame()->SetBorderSize(12);

  c_std->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  histy_std->SetTitle("Y Standard Score");
  histy_std->Draw();
  histy_std->Fit("gaus");

  c_std->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();
  gPad->SetLogy();
  histyp_std->SetTitle("Y' Standard Score");
  histyp_std->Draw();
  histyp_std->Fit("gaus");
  
  //
  // Calculate Pearson Coefficient
  //

  TVectorD varsqr(5);
  TMatrixD sens(5, nlines);
  TMatrixD covar(5,5);
  TMatrixD correlation(5,5);

  for(Int_t i = 0; i < run_number.GetNrows(); i++){
    sens(0,i) = xsens[i];
    sens(1,i) = xpsens[i];
    sens(2,i) = esens[i];
    sens(3,i) = ysens[i];
    sens(4,i) = ypsens[i];
  }
  for(Int_t i = 0; i < run_number.GetNrows(); i++){
    for(Int_t m = 0; m < 5; m++){
      for(Int_t n = 0; n < 5; n++){
	covar(m, n) += (sens(m, i) - mean[m])*(sens(n, i) - mean[n]);
      }
      varsqr[m] += TMath::Power(sens(m, i) - mean[m], 2);
    }
  }

  for(Int_t m = 0; m < 5; m++){
    for(Int_t n = 0; n < 5; n++){
      correlation(m, n) = covar(m, n)/(TMath::Sqrt(varsqr[m])*TMath::Sqrt(varsqr[n]));
    }
  }

  correlation.Print();

  nlines = 0;

  file.close();

  return;
}


