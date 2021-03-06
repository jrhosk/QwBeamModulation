#include "../include/headers.h"
#include <iostream>
#include <fstream>
#include "TH1.h"

void CompareErrors()
{

  std::ifstream file;

  file.open("mdout.dat", std::ifstream::in );
  if(!file.is_open()){
    std::cout << "Error opening file: mdout.dat" << std::endl;
    exit(1);
  }

//   file.open("lumiout.dat", std::ifstream::in);
  
//   if(!file.is_open()){
//     std::cout << "Error opening file: lumiout.dat" << std::endl;
//     exit(1);
//   }
  
  // Define integers

  Int_t entry = 0;

  // Define TVectors

  TVectorD run(0);

  TVectorD Xsens(0);
  TVectorD XPsens(0);
  TVectorD Esens(0);
  TVectorD Ysens(0);
  TVectorD YPsens(0);

  TVectorD Xerror(0);
  TVectorD XPerror(0);
  TVectorD Eerror(0);
  TVectorD Yerror(0);
  TVectorD YPerror(0);

  TVectorD Zeros(0);

  // Define Histgrams

  TH1D *xsens = new TH1D("sensx", "sensx", 200, -0.01, 0.005);
  TH1D *xpsens = new TH1D("sensxp", "sensxp", 200, -200., 400.);
  TH1D *esens = new TH1D("sense", "sense", 200, -0.008, 0.002);
  TH1D *ysens = new TH1D("sensy", "sensy", 200, -0.008, 0.008);
  TH1D *ypsens = new TH1D("sensyp", "sensyp", 200, -400., 400.);

  // Define Canvas(es)

  TCanvas *canvas0 = new TCanvas("md", "md", 1200, 800);
  TCanvas *canvas1 = new TCanvas("md_terror", "md_terror", 1200, 800);

  // Define fit options to show

  gStyle->SetOptFit(0001);

  // Read in MD values and errors.

  while(!file.eof()){

    run.ResizeTo(entry + 1);    
    Zeros.ResizeTo(entry + 1);

    Xsens.ResizeTo(entry + 1);
    XPsens.ResizeTo(entry + 1);
    Esens.ResizeTo(entry + 1);
    Ysens.ResizeTo(entry + 1);
    YPsens.ResizeTo(entry + 1);
    
    Xerror.ResizeTo(entry + 1);
    XPerror.ResizeTo(entry + 1);
    Eerror.ResizeTo(entry + 1);
    Yerror.ResizeTo(entry + 1);
    YPerror.ResizeTo(entry + 1);

    file >> run[entry] 
	   >> Xsens[entry]   >> Xerror[entry]
	   >> XPsens[entry]  >> XPerror[entry]
	   >> Esens[entry]   >> Eerror[entry]
	   >> Ysens[entry]   >> Yerror[entry]
	   >> YPsens[entry]  >> YPerror[entry];
   
    Zeros.Zero();

    entry++;
  }

  for(Int_t i = 0; i < run.GetNrows(); i++){
    xsens->Fill(Xsens[i]);
    xpsens->Fill(XPsens[i]);
    esens->Fill(Esens[i]);
    ysens->Fill(Ysens[i]);
    ypsens->Fill(YPsens[i]);
  }   

  canvas0->Divide(2,3);

  canvas0->cd(1);
  xsens->SetLineColor(4);
  xsens->SetTitle("X Sensitivity");
  xsens->Draw();

  canvas0->cd(2);
  xpsens->SetLineColor(5);
  xpsens->SetTitle("XP Sensitivity");
  xpsens->Draw();

  canvas0->cd(3);
  esens->SetLineColor(6);
  esens->SetTitle("E Sensitivity");
  esens->Draw();

  canvas0->cd(4);
  ysens->SetLineColor(7);
  ysens->SetTitle("Y Sensitivity");
  ysens->Draw();

  canvas0->cd(5);
  ypsens->SetLineColor(8);
  ypsens->SetTitle("YP Sensitivity");
  ypsens->Draw();


  canvas1->Divide(2,3);
  canvas1->cd(1);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *x_error_plot = new TGraphErrors(run, Xerror, Zeros, Zeros);
  x_error_plot->SetMarkerColor(4);
  x_error_plot->SetMarkerSize(0.8);
  x_error_plot->SetMarkerStyle(21);
  x_error_plot->SetTitle("X Sensitivities Error versus Run");
  x_error_plot->GetXaxis()->SetTitle("Run number");
  x_error_plot->GetYaxis()->SetTitle("Error");
  x_error_plot->Draw("ap");
  x_error_plot->Fit("pol0");

  canvas1->cd(2);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *xp_error_plot = new TGraphErrors(run, XPerror, Zeros, Zeros);
  xp_error_plot->SetMarkerColor(5);
  xp_error_plot->SetMarkerSize(0.8);
  xp_error_plot->SetMarkerStyle(21);
  xp_error_plot->SetTitle("XP Sensitivities Error versus Run");
  xp_error_plot->GetXaxis()->SetTitle("Run number");
  xp_error_plot->GetYaxis()->SetTitle("Error");
  xp_error_plot->Draw("ap");
  xp_error_plot->Fit("pol0");

  canvas1->cd(3);
  gPad->SetGridx();
  gPad->SetGridy();

  TGraphErrors *e_error_plot = new TGraphErrors(run, Eerror, Zeros, Zeros);
  e_error_plot->SetMarkerColor(6);
  e_error_plot->SetMarkerSize(0.8);
  e_error_plot->SetMarkerStyle(21);
  e_error_plot->SetTitle("E Sensitivities Error versus Run");
  e_error_plot->GetXaxis()->SetTitle("Run number");
  e_error_plot->GetYaxis()->SetTitle("Error");
  e_error_plot->Draw("ap");
  e_error_plot->Fit("pol0");

  canvas1->cd(4);
  gPad->SetGridx();
  gPad->SetGridy();
  TGraphErrors *y_error_plot = new TGraphErrors(run, Yerror, Zeros, Zeros);
  y_error_plot->SetMarkerColor(7);
  y_error_plot->SetMarkerSize(0.8);
  y_error_plot->SetMarkerStyle(21);
  y_error_plot->SetTitle("Y Sensitivities Error versus Run");
  y_error_plot->GetXaxis()->SetTitle("Run number");
  y_error_plot->GetYaxis()->SetTitle("Error");
  y_error_plot->Draw("ap");
  y_error_plot->Fit("pol0");

  canvas1->cd(5);
  gPad->SetGridx();
  gPad->SetGridy();
  TGraphErrors *yp_error_plot = new TGraphErrors(run, YPerror, Zeros, Zeros);
  yp_error_plot->SetMarkerColor(8);
  yp_error_plot->SetMarkerSize(0.8);
  yp_error_plot->SetMarkerStyle(21);
  yp_error_plot->SetTitle("YP Sensitivities Error versus Run");
  yp_error_plot->GetXaxis()->SetTitle("Run number");
  yp_error_plot->GetYaxis()->SetTitle("Error");
  yp_error_plot->Draw("ap");
  yp_error_plot->Fit("pol0");
   
}
