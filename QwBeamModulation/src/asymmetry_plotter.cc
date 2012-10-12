#include "headers.h"
#include "TSpectrum.h"
#include "TApplication.h"
#include "TDirectory.h"
#include "TSystem.h"
#include "Riostream.h"
#include "TStyle.h"

Bool_t FileSearch(TString, TChain*);
void   LoadRootFile(TString, TChain*);

Int_t run_number;

Int_t main(Int_t argc, Char_t *argv[])
{

  TString filename;
  TString dir;

  Int_t run_list[9] = {82, 84, 86, 88, 90, 92, 94, 96, 98};

  dir = gSystem->Getenv("QW_ROOTFILES");
//   TApplication theApp("App", &argc, argv);
  TCanvas *canvas = new TCanvas("canvas", "canvas", 1000, 800);

  run_number = atoi(argv[1]);

//   TChain *mps_tree = new TChain("Hel_Tree");
  TChain *tree = new TChain("slug");
  
//   filename = Form("QwPass*_%i*.trees.root", run_number);
//   LoadRootFile(filename, mps_tree);
  
  for(Int_t i = 0; i < 9; i++){
//     filename = Form("QwPass*_%i*.trees.root", i);

    filename = Form("%s/slug%i.root", dir.Data(), run_list[i]);
    std::cout << "Adding :: " << filename << std::endl;
    tree->Add(filename);
    filename.Clear();
    //    LoadRootFile(filename, tree);
  }

  gStyle->SetOptFit(01011);
  gStyle->SetOptStat("nemm");

  std::cout << "Processing...." << std::endl;

  TH1F *histo = new TH1F("histo","histo", 1000, -0.004, 0.004);
  canvas->Divide(1,3);
  canvas->cd(1);
  gPad->SetLogy();

  tree->Draw("asym_qwk_mdallbars>>histo","ErrorFlag == 0x4018080 && asym_qwk_mdallbars_Device_Error_Code == 0");
  histo = (TH1F *)gDirectory->Get("histo");
  histo->SetTitle("mdallbars Asymmetry including only beam modulation");
  histo->GetXaxis()->SetTitle("asymmetry (ppm)");
  histo->GetXaxis()->SetTitleSize(0.02);
  histo->GetXaxis()->SetLabelSize(0.02);

  if(histo->GetEntries() < 1){
    std::cout << "Null histogram: cancelling." << std::endl;
    exit(1);
  }
  histo->Draw();
  histo->Fit("gaus");

  TH1F *histowo = new TH1F("histowo","histowo", 1000, -0.004, 0.004);
  canvas->cd(2);
  gPad->SetLogy();

  tree->Draw("asym_qwk_mdallbars>>histowo","ErrorFlag == 0  && asym_qwk_mdallbars_Device_Error_Code == 0");
  histowo = (TH1F *)gDirectory->Get("histowo");
  histowo->SetTitle("mdallbars Asymmetry w/o beam modulation");
  histowo->GetXaxis()->SetTitle("asymmetry (ppm)");
  histowo->GetXaxis()->SetTitleSize(0.02);
  histowo->GetXaxis()->SetLabelSize(0.02);

  if(histowo->GetEntries() < 1){
    std::cout << "Null histogram: cancelling." << std::endl;
    exit(1);
  }
  histowo->Draw();
  histowo->Fit("gaus");

  TH1F *histow = new TH1F("histow","histow", 1000, -0.004, 0.004);
  canvas->cd(3);
  gPad->SetLogy();

  tree->Draw("asym_qwk_mdallbars>>histow","(ErrorFlag == 0x4018080 || ErrorFlag == 0) && asym_qwk_mdallbars_Device_Error_Code == 0");
  histow = (TH1F *)gDirectory->Get("histow");
  histow->SetTitle("mdallbars Asymmetry including beam modulation");
  histow->GetXaxis()->SetTitle("asymmetry (ppm)");
  histow->GetXaxis()->SetTitleSize(0.02);
  histow->GetXaxis()->SetLabelSize(0.02);

  if(histo->GetEntries() < 1){
    std::cout << "Null histogram: cancelling." << std::endl;
    exit(1);
  }
  histow->Draw();
  histow->Fit("gaus");

  canvas->SaveAs("asymmetry.png");
  canvas->SaveAs("asymmetry.C");
  std::cout << "Finished" << std::endl;

//   theApp.Run();

  return 0;
}

Bool_t FileSearch(TString filename, TChain *chain)
{

  TString file_directory;
  Bool_t c_status = kFALSE;

  file_directory = gSystem->Getenv("QW_ROOTFILES");

  c_status = chain->Add(Form("%s/%s",file_directory.Data(), filename.Data()));
  std::cout << "Trying to open :: "
            << Form("%s/%s",file_directory.Data(), filename.Data())
            << std::endl;

  if(c_status){
    TString chain_name = chain->GetName();
    TObjArray *fileElements = chain->GetListOfFiles();
    TIter next(fileElements);
    TChainElement *chain_element = NULL;

    while((chain_element = (TChainElement*)next())){
      std::cout << "Adding :: "
		<< filename
		<< " to data chain"
		<< std::endl;
    }
  } 
    return c_status;

}

void LoadRootFile(TString filename, TChain *tree)
{
  Bool_t found = FileSearch(filename, tree);
  
  if(!found){
    filename = Form("Qweak_%d.*.trees.root", run_number);
    found = FileSearch(filename, tree);
    std::cerr << "Couldn't find QwPass<#>_*.trees.root trying "
	      << filename
	      << std::endl;
    if(!found){
      std::cerr << "Unable to locate requested file :: "
		<< filename
		<< std::endl;
      //      exit(1);
    }
  }
}
