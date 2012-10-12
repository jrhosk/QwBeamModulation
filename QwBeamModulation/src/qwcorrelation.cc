#include "../include/headers.h"
#include "QwSlug.hh"
#include "QwDataContainer.hh"
#include "QwPlotHelper.hh"
#include <fstream>

Int_t main(Int_t argc, Char_t *argv[])
{

  TString filename;

  TChain *slug_tree = new TChain("slug");

  QwSlug *slug = new QwSlug(slug_tree);

  Int_t slug_number = 0;

  std::fstream slugf;

  if(argv[1] == NULL){
    //    slug->PrintError("Error Loading:  no run number specified");
    exit(1);
  }
  slug->Init(slug_tree);
  slug->GetOptions(argv);

  if(slug->fRunRange){
    TString file_directory;

    for(Int_t i = slug->fLowerRunNumber; i < (slug->fUpperRunNumber + 1); i++){
      filename = Form("slug%i.root", i);
      file_directory = gSystem->Getenv("QW_ROOTFILES");
      if(slug_tree->Add(Form("%s/%s",file_directory.Data(), filename.Data())));
      else{
	slug->PrintError(Form("Failed to find file:\t%s", filename.Data()));
      }
      std::cout << Form("Adding::\t%s", filename.Data()) << std::endl;
      filename.Clear();
    }
  }else{
    slug_number = atoi(argv[1]);
    filename = Form("slug%i.root", slug_number);
    slug->LoadRootFile(filename, slug_tree);
  }

  slug->ReadConfig();
  slug->SetupBranchAddress();
  std::cout << "Calculating Slug Averages..." << std::endl;
  slug->ComputeAverages();

  for(Int_t i = 0; i < slug->fNMonitor; i++){
    std::cout << Form("Average monitor [%s]:\t", slug->MonitorList[i].Data()) << slug->fPositionDiff[i] 
	      << " +- " << slug->fPositionDiffError[i] << std::endl;
  }
  std::cout << "Calculating Pearson Coefficients..." << std::endl;
  slug->ComputePearsonCoefficient();
  
  /*
    if(slug->fRunRange){
    slugf.open(Form("slug/slug_%i-%i.dat", slug->fLowerRunNumber, slug->fUpperRunNumber), std::fstream::out | std::fstream::app);
    }else{
    slugf.open("slug/slug.dat", std::fstream::out | std::fstream::app);
    }
  if(!slugf.is_open()){
    slug->PrintError("Error opening file.");
    exit(1);
  }
  for(Int_t i = 0; i < (Int_t)(slug->fNDetector); i++){
    slugf << slug_number << " " 
	  << slug->fRawDetectorAsym[i] << " " << slug->fRawDetectorAsymError[i] << " " 
	  << slug->fDetectorAsym[i]  << " " << slug->fDetectorAsymError[i] << std::endl;
  }
  slugf.close();
  */

  return 0;

}
