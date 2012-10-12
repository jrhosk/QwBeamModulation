//
// Plotting some shizzle
//

#include <vector>
#include "Riostream.h"
#include "TLine.h"

void in_out_plot_lrb() {

  enum {raw_in, corr_in, raw_out, corr_out};

  fstream file_in;
  fstream file_out;

  std::vector <Double_t> fit;
  std::vector <Double_t> error;
  std::vector <Double_t> chisquareNDF;

  Bool_t average = true;

//   file_in.open("../slug/slug_average_asym_qwk_mdallbars_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md1barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md2barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md3barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md4barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md5barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md6barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md7barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/slug_average_asym_qwk_md8barsum_in.dat", fstream::in | fstream::out );

  file_in.open("../slug/lrb_slug_average_asym_qwk_mdallbars_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md1barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md2barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md3barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md4barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md5barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md6barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md7barsum_in.dat", fstream::in | fstream::out );
//   file_in.open("../slug/lrb_slug_average_asym_qwk_md8barsum_in.dat", fstream::in | fstream::out );

  if( file_in.fail() ){
    std::cout << "Error opening file :: in\n" << std::endl;
    exit(1);
  }

//   file_out.open("../slug/slug_average_asym_qwk_mdallbars_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md1barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md2barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md3barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md4barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md5barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md6barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md7barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/slug_average_asym_qwk_md8barsum_out.dat", fstream::in | fstream::out );

  file_out.open("../slug/lrb_slug_average_asym_qwk_mdallbars_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md1barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md2barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md3barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md4barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md5barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md6barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md7barsum_out.dat", fstream::in | fstream::out );
//   file_out.open("../slug/lrb_slug_average_asym_qwk_md8barsum_out.dat", fstream::in | fstream::out );
  
  if( file_out.fail() ){
    std::cout << "Error opening file :: out\n" << std::endl;
    exit(1);
  }

  Double_t max;
  Double_t min;
 
  TVectorD slug_number_in(0);
  TVectorD slug_number_out(0);
  TVectorD entries_in(0);
  TVectorD entries_out(0);
  //
  // IN state
  //
  TVectorD raw_asym_in(0);
  TVectorD raw_error_in(0);
  TVectorD corr_asym_in(0);
  TVectorD corr_error_in(0);
  TVectorD raw_null_in(0);
  TVectorD raw_null_error_in(0);
  TVectorD corr_null_in(0);
  TVectorD corr_null_error_in(0);
  //
  // OUT state
  //
  TVectorD raw_asym_out(0);
  TVectorD raw_error_out(0);
  TVectorD corr_asym_out(0);
  TVectorD corr_error_out(0);
  TVectorD raw_null_out(0);
  TVectorD raw_null_error_out(0);
  TVectorD corr_null_out(0);
  TVectorD corr_null_error_out(0);

  TVectorD zero_error(0);

  Int_t nlines = 0;

  TF1 *line = new TF1("line", "[0]", 0, 1);

  TCanvas *canvas = new TCanvas("canvas", "IN-OUT Slug Plot",1000, 600); 
  //
  //  Read in  IN state data
  //


  std::cout << "Reading IN data..." << std::endl;

  while( !file_in.eof() )
   {

     slug_number_in.ResizeTo(nlines + 1);
     entries_in.ResizeTo(nlines + 1);
     raw_asym_in.ResizeTo(nlines + 1);
     raw_error_in.ResizeTo(nlines + 1);
     corr_asym_in.ResizeTo(nlines + 1);
     corr_error_in.ResizeTo(nlines + 1);
     raw_null_in.ResizeTo(nlines + 1);
     raw_null_error_in.ResizeTo(nlines + 1);
     corr_null_in.ResizeTo(nlines + 1);
     corr_null_error_in.ResizeTo(nlines + 1);

     zero_error.ResizeTo(nlines + 1);
     
     file_in >> slug_number_in[nlines] 
	     >> raw_asym_in[nlines]  >> raw_error_in[nlines] 
	     >> corr_asym_in[nlines] >> corr_error_in[nlines];

//      std::cout << slug_number_in[nlines] << " "
// 	       << raw_asym_in[nlines] << " " << raw_error_in[nlines] << " "
// 	       << corr_asym_in[nlines] << " " << corr_error_in[nlines] << std::endl;
      
     zero_error.Zero();
     nlines++;     
   }

  nlines = 0;

  //
  // Read in OUT state data
  //

  std::cout << "Reading OUT data..." << std::endl;

  while( !file_out.eof() )
   {

     slug_number_out.ResizeTo(nlines + 1);
     entries_out.ResizeTo(nlines + 1);
     raw_asym_out.ResizeTo(nlines + 1);
     raw_error_out.ResizeTo(nlines + 1);
     corr_asym_out.ResizeTo(nlines + 1);
     corr_error_out.ResizeTo(nlines + 1);
     raw_null_out.ResizeTo(nlines + 1);
     raw_null_error_out.ResizeTo(nlines + 1);
     corr_null_out.ResizeTo(nlines + 1);
     corr_null_error_out.ResizeTo(nlines + 1);

     zero_error.ResizeTo(nlines + 1);
     
     file_out >> slug_number_out[nlines] 
	      >> raw_asym_out[nlines]  >> raw_error_out[nlines] 
	      >> corr_asym_out[nlines] >> corr_error_out[nlines];

//      std::cout << slug_number_out[nlines] << " "
// 	       << raw_asym_out[nlines] << " " << raw_error_out[nlines] << " "
// 	       << corr_asym_out[nlines] << " " << corr_error_out[nlines] << std::endl;

     zero_error.Zero();
     nlines++;     
   }

  //
  //  Plot IN-OUT slug-by-slug
  //
  TMultiGraph *mgraph = new TMultiGraph();

  std::cout << "Making plots..." << std::endl;
  
  TGraphErrors *raw_slug_in = new TGraphErrors(slug_number_in, 1e6*raw_asym_in, zero_error, 1e6*raw_error_in);

  raw_slug_in->SetMarkerColor(4);
  raw_slug_in->SetMarkerSize(1.0);
  raw_slug_in->SetMarkerStyle(24);
//   raw_slug_in->SetTitle("");
//   raw_slug_in->GetXaxis()->SetTitle("slug number");
//   raw_slug_in->GetYaxis()->SetTitle("Asymmetry (ppm)");
  //  raw_slug_in->GetYaxis()->SetRangeUser(-2000., 2000.);
  raw_slug_in->Draw("GOFF");
  line->SetLineColor(4);
  line->SetLineStyle(7);
  raw_slug_in->Fit("line");

  fit.push_back(line->GetParameter(0));
  error.push_back(line->GetParError(0));
  chisquareNDF.push_back(line->GetChisquare()/line->GetNDF());

  mgraph->Add(raw_slug_in);


  TGraphErrors *corr_slug_in = new TGraphErrors(slug_number_in, 1e6*corr_asym_in, zero_error, 1e6*corr_error_in);

  corr_slug_in->SetMarkerColor(4);
  corr_slug_in->SetMarkerSize(1.0);
  corr_slug_in->SetMarkerStyle(20);
//   corr_slug_in->SetTitle("");
//   corr_slug_in->GetXaxis()->SetTitle("slug number");
//   corr_slug_in->GetYaxis()->SetTitle("Asymmetry (ppm)");
  //  corr_slug_in->GetYaxis()->SetRangeUser(-2000., 2000.);
  corr_slug_in->Draw("GOFF");
  line->SetLineColor(4);
  line->SetLineStyle(1);
  corr_slug_in->Fit("line");

  fit.push_back(line->GetParameter(0));
  error.push_back(line->GetParError(0));
  chisquareNDF.push_back(line->GetChisquare()/line->GetNDF());

  mgraph->Add(corr_slug_in);


  TGraphErrors *raw_slug_out = new TGraphErrors(slug_number_out, 1e6*raw_asym_out, zero_error, 1e6*raw_error_out);

  raw_slug_out->SetMarkerColor(6);
  raw_slug_out->SetMarkerSize(1.0);
  raw_slug_out->SetMarkerStyle(25);
//   raw_slug_out->SetTitle("");
//   raw_slug_out->GetXaxis()->SetTitle("slug number");
//   raw_slug_out->GetYaxis()->SetTitle("Asymmetry (ppm)");
  //  raw_slug_out->GetYaxis()->SetRangeUser(-2000., 2000.);
  raw_slug_out->Draw("GOFF");
  line->SetLineColor(6);
  line->SetLineStyle(7);
  raw_slug_out->Fit("line");

  fit.push_back(line->GetParameter(0));
  error.push_back(line->GetParError(0));
  chisquareNDF.push_back(line->GetChisquare()/line->GetNDF());

  mgraph->Add(raw_slug_out);

  TGraphErrors *corr_slug_out = new TGraphErrors(slug_number_out, 1e6*corr_asym_out, zero_error, 1e6*corr_error_out);

  corr_slug_out->SetMarkerColor(6);
  corr_slug_out->SetMarkerSize(1.0);
  corr_slug_out->SetMarkerStyle(21);
//   corr_slug_out->SetTitle("");
//   corr_slug_out->GetXaxis()->SetTitle("slug number");
//   corr_slug_out->GetYaxis()->SetTitle("Asymmetry (ppm)");
  //  corr_slug_out->GetYaxis()->SetRangeUser(-2000., 2000.);
  corr_slug_out->Draw("GOFF");
  line->SetLineColor(6);
  line->SetLineStyle(1);
  corr_slug_out->Fit("line");

  fit.push_back(line->GetParameter(0));
  error.push_back(line->GetParError(0));
  chisquareNDF.push_back(line->GetChisquare()/line->GetNDF());

  mgraph->Add(corr_slug_out);

  gStyle->SetOptFit(0000);
  gStyle->SetOptStat(0000);

  canvas->SetGrid();
  canvas->GetFrame()->SetBorderSize(12);
  canvas->cd();

  gPad->SetGridx();
  gPad->SetGridy();

  mgraph->Draw("ap");

  mgraph->GetXaxis()->SetLabelSize(0.02);
  mgraph->GetYaxis()->SetLabelSize(0.02);
  mgraph->GetXaxis()->SetTitleSize(0.02);
  mgraph->GetYaxis()->SetTitleSize(0.02);
  mgraph->GetXaxis()->SetTitleOffset(1.5);
  mgraph->GetYaxis()->SetTitleOffset(1.5);
  mgraph->GetYaxis()->SetRangeUser(-0.5, 0.5);
  mgraph->GetXaxis()->SetTitle("Slug Number");
  mgraph->GetYaxis()->SetTitle("Asymmetry (ppm)");


  TLegend *legend = new TLegend(0.1, 0.9, 0.3, 0.7);
  legend->SetHeader("MultiGraph Legend");
    
  legend->AddEntry(raw_slug_in, Form("Raw IN: %4.4f +- %4.4f", fit[raw_in], error[raw_in]),"pl");
  legend->AddEntry(raw_slug_in, Form("Chi^2/NDF: %4.4f", chisquareNDF[raw_in]),"pl");

  legend->AddEntry(corr_slug_in, Form("Corr IN: %4.4f +- %4.4f", fit[corr_in], error[corr_in]),"pl");
  legend->AddEntry(corr_slug_in, Form("Chi^2/NDF: %4.4f", chisquareNDF[corr_in]),"pl");
  
  legend->AddEntry(raw_slug_out, Form("Raw OUT: %4.4f +- %4.4f", fit[raw_out], error[raw_out]),"pl");
  legend->AddEntry(raw_slug_out, Form("Chi^2/NDF: %4.4f", chisquareNDF[raw_out]),"pl");
  
  legend->AddEntry(corr_slug_out, Form("Corr OUT: %4.4f +- %4.4f", fit[corr_out], error[corr_out]),"pl");
  legend->AddEntry(corr_slug_out, Form("Chi^2/NDF: %4.4f", chisquareNDF[corr_out]),"pl");
  
  legend->Draw();

  nlines = 0;

  file_in.close();
  file_out.close();


  //
  //  If we want to look at the NULL/PHYS results for the data
  //

  if(average){

    TCanvas *canvas_av = new TCanvas("canvas_av", "canvas_av", 1000, 600);

    TVectorD av_raw_in(1);  
    av_raw_in[0] = fit[raw_in];

    TVectorD av_corr_in(1);
    av_corr_in[0] = fit[corr_in];    

    TVectorD av_raw_out(1);
    av_raw_out[0]  = fit[raw_out];
    TVectorD av_corr_out(1);
    av_corr_out[0] = fit[corr_out];

    TVectorD av_raw_in_error(1);  
    av_raw_in_error[0] = error[raw_in];
    TVectorD av_corr_in_error(1);
    av_corr_in_error[0] = error[corr_in];    

    TVectorD av_raw_out_error(1);
    av_raw_out_error[0]  = error[raw_out];
    TVectorD av_corr_out_error(1);
    av_corr_out_error[0] = error[corr_out];
    
    TVectorD av_raw_null(1); 
    TVectorD av_corr_null(1);
    TVectorD av_raw_null_error(1); 
    TVectorD av_corr_null_error(1);
    
    TVectorD av_raw_phys(1); 
    TVectorD av_corr_phys(1);
    TVectorD av_raw_phys_error(1); 
    TVectorD av_corr_phys_error(1);

    TVectorD data(1); 

    //
    //  Compute NULL/PHYS values
    //

    TMultiGraph *av_mgraph = new TMultiGraph();
    
    Double_t null_temp = av_raw_in[0]/TMath::Power(av_raw_in_error[0],2) + av_raw_out[0]/TMath::Power(av_raw_out_error[0],2);
    Double_t inv_error = 1/TMath::Power(av_raw_in_error[0],2) + 1/TMath::Power(av_raw_out_error[0],2);

    av_raw_null[0] = null_temp/inv_error;
    av_raw_null_error[0] = TMath::Sqrt(1/inv_error);

    null_temp = av_corr_in[0]/TMath::Power(av_corr_in_error[0],2) + av_corr_out[0]/TMath::Power(av_corr_out_error[0],2);
    inv_error = 1/TMath::Power(av_corr_in_error[0],2) + 1/TMath::Power(av_corr_out_error[0],2);

    av_corr_null[0] = null_temp/inv_error;
    av_corr_null_error[0] = TMath::Sqrt(1/inv_error);

    Double_t phys_temp = av_raw_in[0]/TMath::Power(av_raw_in_error[0],2) - av_raw_out[0]/TMath::Power(av_raw_out_error[0],2);
    inv_error = 1/TMath::Power(av_raw_in_error[0],2) + 1/TMath::Power(av_raw_out_error[0],2);

    av_raw_phys[0] = phys_temp/inv_error;
    av_raw_phys_error[0] = TMath::Sqrt(1/inv_error);

    phys_temp = av_corr_in[0]/TMath::Power(av_corr_in_error[0],2) - av_corr_out[0]/TMath::Power(av_corr_out_error[0],2);
    inv_error = 1/TMath::Power(av_corr_in_error[0],2) + 1/TMath::Power(av_corr_out_error[0],2);

    av_corr_phys[0] = phys_temp/inv_error;
    av_corr_phys_error[0] = TMath::Sqrt(1/inv_error);

    //
    // Plot everything
    //
    data[0] = 0;
    TGraphErrors *av_raw_slug_in = new TGraphErrors(data, av_raw_in, zero_error, av_raw_in_error);

    av_raw_slug_in->SetMarkerColor(4);
    av_raw_slug_in->SetMarkerSize(1.0);
    av_raw_slug_in->SetMarkerStyle(24);
    av_raw_slug_in->Draw("GOFF");
    
    av_mgraph->Add(av_raw_slug_in);
    data[0] = 0;
    TGraphErrors *av_corr_slug_in = new TGraphErrors(data, av_corr_in, zero_error, av_corr_in_error);

    av_corr_slug_in->SetMarkerColor(4);
    av_corr_slug_in->SetMarkerSize(1.0);
    av_corr_slug_in->SetMarkerStyle(20);
    av_corr_slug_in->Draw("GOFF");

    av_mgraph->Add(av_corr_slug_in);
    data[0] = 1;
    TGraphErrors *av_raw_slug_out = new TGraphErrors(data, av_raw_out, zero_error, av_raw_out_error);

    av_raw_slug_out->SetMarkerColor(6);
    av_raw_slug_out->SetMarkerSize(1.0);
    av_raw_slug_out->SetMarkerStyle(25);
    av_raw_slug_out->Draw("GOFF");
    
    av_mgraph->Add(av_raw_slug_out);
    data[0] = 1;
    TGraphErrors *av_corr_slug_out = new TGraphErrors(data, av_corr_out, zero_error, av_corr_out_error);

    av_corr_slug_out->SetMarkerColor(6);
    av_corr_slug_out->SetMarkerSize(1.0);
    av_corr_slug_out->SetMarkerStyle(21);
    av_corr_slug_out->Draw("GOFF");
    
    av_mgraph->Add(av_corr_slug_out);

    data[0] = 2;
    TGraphErrors *av_raw_slug_null = new TGraphErrors(data, av_raw_null, zero_error, av_raw_null_error);

    av_raw_slug_null->SetMarkerColor(8);
    av_raw_slug_null->SetMarkerSize(1.0);
    av_raw_slug_null->SetMarkerStyle(26);
    av_raw_slug_null->Draw("GOFF");
    
    av_mgraph->Add(av_raw_slug_null);
    data[0] = 2;
    TGraphErrors *av_corr_slug_null = new TGraphErrors(data, av_corr_null, zero_error, av_corr_null_error);

    av_corr_slug_null->SetMarkerColor(8);
    av_corr_slug_null->SetMarkerSize(1.0);
    av_corr_slug_null->SetMarkerStyle(22);
    av_corr_slug_null->Draw("GOFF");
    
    av_mgraph->Add(av_corr_slug_null);

    data[0] = 3;
    TGraphErrors *av_raw_slug_phys = new TGraphErrors(data, av_raw_phys, zero_error, av_raw_phys_error);

    av_raw_slug_phys->SetMarkerColor(9);
    av_raw_slug_phys->SetMarkerSize(1.0);
    av_raw_slug_phys->SetMarkerStyle(32);
    av_raw_slug_phys->Draw("GOFF");
    
    av_mgraph->Add(av_raw_slug_phys);
    data[0] = 3;
    TGraphErrors *av_corr_slug_phys = new TGraphErrors(data, av_corr_phys, zero_error, av_corr_phys_error);

    av_corr_slug_phys->SetMarkerColor(9);
    av_corr_slug_phys->SetMarkerSize(1.0);
    av_corr_slug_phys->SetMarkerStyle(23);
    av_corr_slug_phys->Draw("GOFF");
    
    av_mgraph->Add(av_corr_slug_phys);

    canvas_av->cd();
    canvas_av->SetGrid();
    canvas_av->GetFrame()->SetBorderSize(12);
    gPad->SetGridx();
    gPad->SetGridy();

    av_mgraph->Draw("ap");

    av_mgraph->GetXaxis()->SetLabelSize(0.02);
    av_mgraph->GetYaxis()->SetLabelSize(0.02);
    av_mgraph->GetXaxis()->SetTitleSize(0.02);
    av_mgraph->GetYaxis()->SetTitleSize(0.02);
    av_mgraph->GetXaxis()->SetTitleOffset(1.5);
    av_mgraph->GetYaxis()->SetTitleOffset(1.5);
    av_mgraph->GetYaxis()->SetRangeUser(-0.3, 0.3);
    av_mgraph->GetXaxis()->SetNdivisions(4);
    av_mgraph->GetYaxis()->SetTitle("Asymmetry (ppm)");

  TLegend *legend_av = new TLegend(0.1, 0.9, 0.3, 0.7);
  legend_av->SetHeader("MultiGraph Legend");
    
  legend_av->AddEntry(raw_slug_in, Form("Raw IN: %4.4f +- %4.4f", fit[raw_in], error[raw_in]),"p");
  legend_av->AddEntry(corr_slug_in, Form("Corr IN: %4.4f +- %4.4f", fit[corr_in], error[corr_in]),"p");
  
  legend_av->AddEntry(raw_slug_out, Form("Raw OUT: %4.4f +- %4.4f", fit[raw_out], error[raw_out]),"p");
  legend_av->AddEntry(corr_slug_out, Form("Corr OUT: %4.4f +- %4.4f", fit[corr_out], error[corr_out]),"p");

  legend_av->AddEntry(av_raw_slug_null, Form("Raw NULL: %4.4f +- %4.4f", av_raw_null[0], av_raw_null_error[0]),"p");
  legend_av->AddEntry(av_corr_slug_null, Form("Corr NULL: %4.4f +- %4.4f", av_corr_null[0], av_corr_null_error[0]),"p");

  legend_av->AddEntry(av_raw_slug_phys, Form("Raw PHYS: %4.4f +- %4.4f", av_raw_phys[0], av_raw_phys_error[0]),"p");
  legend_av->AddEntry(av_corr_slug_phys, Form("Corr PHYS: %4.4f +- %4.4f", av_corr_phys[0], av_corr_phys_error[0]),"p");
  
  legend_av->Draw();
    
  }

  /*
  TCanvas *rms_canvas = new TCanvas("rms_canvas", "rms_canvas", 1000, 800);

  TMultiGraph *lrb_rms_mgraph = new TMultiGraph();
  TMultiGraph *rms_mgraph = new TMultiGraph();


  TVectorD v_raw_rms(0);
  TVectorD v_corr_rms(0);

  TVectorD slug(0);

  Double_t raw_fit;
  Double_t raw_fit_error;
  Double_t corr_fit;
  Double_t corr_fit_error;

  for(Int_t i = 0; i < entries_in.GetNrows(); i++){
    zero_error.ResizeTo(i + i);
    zero_error.Zero();

    slug.ResizeTo(i + 1);
    slug[i] = slug_number_in[i];
    v_raw_rms.ResizeTo(i + 1);
    v_raw_rms[i] = 1e6*raw_error_in[i]*TMath::Sqrt(entries_in[i]);
    v_corr_rms.ResizeTo(i + 1);
    v_corr_rms[i] = 1e6*corr_error_in[i]*TMath::Sqrt(entries_in[i]);
  }

  Int_t offset = entries_in.GetNrows();

  for(Int_t i = offset; i < (entries_out.GetNrows() + offset); i++){
    zero_error.ResizeTo(i + i);
    zero_error.Zero();

    slug.ResizeTo(i + 1);
    slug[i] = slug_number_out[i - offset];
    v_raw_rms.ResizeTo(i + 1);
    v_raw_rms[i] = 1e6*raw_error_out[i - offset]*TMath::Sqrt(entries_out[i - offset]);
    v_corr_rms.ResizeTo(i + 1);
    v_corr_rms[i] = 1e6*corr_error_out[i - offset]*TMath::Sqrt(entries_out[i - offset]);
  }

  TGraphErrors *raw_rms = new TGraphErrors(slug, v_raw_rms, zero_error, zero_error);

  raw_rms->SetMarkerColor(4);
  raw_rms->SetMarkerSize(1.0);
  raw_rms->SetMarkerStyle(20);
  raw_rms->Draw("GOFF");
  line->SetLineColor(4);
  line->SetLineStyle(1);
  raw_rms->Fit("line");
  raw_fit = line->GetParameter(0);
  raw_fit_error = line->GetParError(0);

  TGraphErrors *corr_rms = new TGraphErrors(slug, v_corr_rms, zero_error, zero_error);

  corr_rms->SetMarkerColor(6);
  corr_rms->SetMarkerSize(1.0);
  corr_rms->SetMarkerStyle(20);
  corr_rms->Draw("GOFF");
  line->SetLineColor(6);
  line->SetLineStyle(1);
  corr_rms->Fit("line");
  corr_fit = line->GetParameter(0);
  corr_fit_error = line->GetParError(0);

  rms_canvas->cd();

  rms_mgraph->Add(raw_rms);
  rms_mgraph->Add(corr_rms);

  rms_mgraph->Draw("AP");
  rms_mgraph->GetXaxis()->SetTitle("Slug");
  rms_mgraph->GetYaxis()->SetTitle("RMS(ppm)");
  rms_mgraph->GetXaxis()->SetLabelSize(0.02);
  rms_mgraph->GetYaxis()->SetLabelSize(0.02);
  rms_mgraph->GetXaxis()->SetTitleSize(0.02);
  rms_mgraph->GetYaxis()->SetTitleSize(0.02);

  TLegend *legend_rms = new TLegend(0.1, 0.9, 0.3, 0.7);
  legend_rms->SetHeader("MultiGraph Legend");
    
  legend_rms->AddEntry(raw_rms, Form("Raw RMS: %4.4f +- %4.4f", raw_fit, raw_fit_error,"pe"));
  legend_rms->AddEntry(corr_rms, Form("Corr RMS: %4.4f +- %4.4f", corr_fit, corr_fit_error,"pe"));

  legend_rms->Draw();
  */
  return;
}


