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

//   Double_t sens[5] = {-0.00050749, 26.97035, -4.47685, 0.000022513, 2.01902};      // lrb
//   Double_t sens[5] = {-0.00069852, 30.5154, -4.87166, 3.12448e-5, 3.21735};        // lrb run
//   Double_t sens[5] = {-0.001278, 70.19, -0.001464, -0.0009082, 40.41};             // set 4
//   Double_t sens[5] = {-0.000672108, 55.1904, -0.00139563, -0.0004136395, 15.4301};             // lrb_bmod 10100
//   Double_t sens[5] = {-0.0007965, 55.94, -0.001438, -3.149e-5, 7.036};             // lrb_bmod 10110 *best*
//   Double_t sens[5] = {0.004119, 239.3, -0.00182, 0.001436, -193.4};                // md5 set kent
//   Double_t sens[5] = {-0.004529, 219, -0.001418, 3.667e-5, 4.14};                  // set 8

// ***********************************************************************
// This should be done using an external config file but I am in a hurry...
// ***********************************************************************

//   Double_t s[2][5] = {{-0.00204, 134.5, -0.001472, 0.005529, -22.83},
// 		      {0.004119, 239.5, -0.00182, 0.001436, -193.4 }};      
//   Double_t e[2][5] = {{0.0003687, 78.23, 0.0001264, 0.001145, 128.2},
// 			  {0.000416, 105.9, 0.0001685, 0.001555, 175}};
      
//   std::vector < std::vector <Double_t> > sens;
//   std::vector < std::vector <Double_t> > error;

//   sens.resize(2);
//   error.resize(2);

//   for(Int_t det = 0; det < 2; det++){
//     sens[det].resize(5);
//     error[det].resize(5);
//     for(Int_t mon = 0; mon < 5; mon++){
//       sens[det][mon] = s[det][mon];
//       error[det][mon] = e[det][mon];
//     }
//   }

  // ***********************************************************************
  //
  // ***********************************************************************

  TString file_directory;

  file_directory = gSystem->Getenv("QW_ROOTFILES");

  if(argv[1] == NULL){
    //    slug->PrintError("Error Loading:  no run number specified");
    exit(1);
  }
  slug->Init(slug_tree);
  slug->GetOptions(argv);

  slug_number = atoi(argv[1]);
  filename = Form("slug%i.root", slug_number);
  slug->LoadRootFile(filename, slug_tree);
  slug_tree->AddFriend("slug_std = slug",Form("%s/slug%i_lrb_std.root", file_directory.Data(), slug_number)); 

  slug->ReadConfig();
  slug->ReadSensitivities();
  std::cout << "Setting branch addresses." << std::endl;
  slug->SetupBranchAddress();
  std::cout << "Setting sensitivities." << std::endl;
  std::cout << "Calculating corrected asymmetry." << std::endl;
  slug->ComputeCorrectedAsymmetry();
  
  return 0;

}
