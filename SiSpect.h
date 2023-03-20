//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Oct 26 16:55:39 2007 by ROOT version 5.08/00
// from TTree t1/a simple Tree with simple variables
// found on file: musr_200003.root
//////////////////////////////////////////////////////////

#ifndef SiSpect_h
#define SiSpect_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class SiSpect {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           runID;
   Int_t           eventID;
   Double_t        BFieldAtDecay_Bx;
   Double_t        BFieldAtDecay_By;
   Double_t        BFieldAtDecay_Bz;
   Double_t        BFieldAtDecay_B3;
   Double_t        BFieldAtDecay_B4;
   Double_t        BFieldAtDecay_B5;
   Double_t        muIniPosX;
   Double_t        muIniPosY;
   Double_t        muIniPosZ;
   Double_t        muIniMomX;
   Double_t        muIniMomY;
   Double_t        muIniMomZ;
   Double_t        muIniPolX;
   Double_t        muIniPolY;
   Double_t        muIniPolZ;
   Int_t           muDecayDetID;
   Double_t        muDecayPosX;
   Double_t        muDecayPosY;
   Double_t        muDecayPosZ;
   Double_t        muDecayTime;
   Double_t        muDecayPolX;
   Double_t        muDecayPolY;
   Double_t        muDecayPolZ;
   Double_t        muTargetTime;
   Double_t        muTargetPolX;
   Double_t        muTargetPolY;
   Double_t        muTargetPolZ;
   Double_t        fieldNomVal;
   Int_t           det_n;
   Int_t           det_ID[100];   //[det_n]
   Double_t        det_edep[100];   //[det_n]
   Int_t           det_nsteps[100];   //[det_n]
   Double_t        det_length[100];   //[det_n]
   Double_t        det_time_start[100];   //[det_n]
   Double_t        det_time_end[100];   //[det_n]
   Double_t        det_x[100];   //[det_n]
   Double_t        det_y[100];   //[det_n]
   Double_t        det_z[100];   //[det_n]
   Int_t           det_VrtxParticleID[100];   //[det_n]
   Int_t           save_n;
   Int_t           save_detID[100];   //[save_n]
   Int_t           save_particleID[100];   //[save_n]
   Double_t        save_ke[100];   //[save_n]
   Double_t        save_x[100];   //[save_n]
   Double_t        save_y[100];   //[save_n]
   Double_t        save_z[100];   //[save_n]
   Double_t        save_px[100];   //[save_n]
   Double_t        save_py[100];   //[save_n]
   Double_t        save_pz[100];   //[save_n]


   // List of branches
   TBranch        *b_runID;   //!
   TBranch        *b_eventID;   //!
   TBranch        *b_BFieldAtDecay;   //!
   TBranch        *b_muIniPosX;   //!
   TBranch        *b_muIniPosY;   //!
   TBranch        *b_muIniPosZ;   //!
   TBranch        *b_muIniMomX;   //!
   TBranch        *b_muIniMomY;   //!
   TBranch        *b_muIniMomZ;   //!
   TBranch        *b_muIniPolX;   //!
   TBranch        *b_muIniPolY;   //!
   TBranch        *b_muIniPolZ;   //!
   TBranch        *b_muDecayDetID;   //!
   TBranch        *b_muDecayPosX;   //!
   TBranch        *b_muDecayPosY;   //!
   TBranch        *b_muDecayPosZ;   //!
   TBranch        *b_muDecayTime;   //!
   TBranch        *b_muDecayPolX;   //!
   TBranch        *b_muDecayPolY;   //!
   TBranch        *b_muDecayPolZ;   //!
   TBranch        *b_muTargetTime;   //!
   TBranch        *b_muTargetPolX;   //!
   TBranch        *b_muTargetPolY;   //!
   TBranch        *b_muTargetPolZ;   //!
   TBranch        *b_fieldNomVal;   //!
   TBranch        *b_det_n;   //!
   TBranch        *b_det_ID;   //!
   TBranch        *b_det_edep;   //!
   TBranch        *b_det_nsteps;   //!
   TBranch        *b_det_length;   //!
   TBranch        *b_det_time_start;   //!
   TBranch        *b_det_time_end;   //!
   TBranch        *b_det_x;   //!
   TBranch        *b_det_y;   //!
   TBranch        *b_det_z;   //!
   TBranch        *b_save_n;   //!
   TBranch        *b_save_detID;   //!
   TBranch        *b_save_particleID;   //!
   TBranch        *b_save_ke;   //!
   TBranch        *b_save_x;   //!
   TBranch        *b_save_y;   //!
   TBranch        *b_save_z;   //!
   TBranch        *b_save_px;   //!
   TBranch        *b_save_py;   //!
   TBranch        *b_save_pz;   //!

   
   SiSpect(TTree *tree=0);
   virtual ~SiSpect();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
  // For unsegmented pixels.
   virtual void     CreateIO(Bool_t   FigFlag, Double_t eCut );
   virtual void     CoinIO( Bool_t   FigFlag, Double_t eCut );
  // For Quad segmented pixels.
   virtual void     QCreateIO(Bool_t   FigFlag, Double_t eCut );
   virtual void     QCoinIO( Bool_t   FigFlag, Double_t eCut, int run );
};

#endif

#ifdef SiSpect_cxx
SiSpect::SiSpect(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("data/lem4_1049.root");
      //if (!f) {
         //f = new TFile("musr_200003.root");
      // f = new TFile("data/lem4_1051.root");	 //1049
      //}
      tree = (TTree*)gDirectory->Get("t1");

   }
   Init(tree);
}

SiSpect::~SiSpect()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t SiSpect::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t SiSpect::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void SiSpect::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runID",&runID);
   fChain->SetBranchAddress("eventID",&eventID);
   fChain->SetBranchAddress("BFieldAtDecay",&BFieldAtDecay_Bx);
   fChain->SetBranchAddress("muIniPosX",&muIniPosX);
   fChain->SetBranchAddress("muIniPosY",&muIniPosY);
   fChain->SetBranchAddress("muIniPosZ",&muIniPosZ);
   fChain->SetBranchAddress("muIniMomX",&muIniMomX);
   fChain->SetBranchAddress("muIniMomY",&muIniMomY);
   fChain->SetBranchAddress("muIniMomZ",&muIniMomZ);
   fChain->SetBranchAddress("muIniPolX",&muIniPolX);
   fChain->SetBranchAddress("muIniPolY",&muIniPolY);
   fChain->SetBranchAddress("muIniPolZ",&muIniPolZ);
   fChain->SetBranchAddress("muDecayDetID",&muDecayDetID);
   fChain->SetBranchAddress("muDecayPosX",&muDecayPosX);
   fChain->SetBranchAddress("muDecayPosY",&muDecayPosY);
   fChain->SetBranchAddress("muDecayPosZ",&muDecayPosZ);
   fChain->SetBranchAddress("muDecayTime",&muDecayTime);
   fChain->SetBranchAddress("muDecayPolX",&muDecayPolX);
   fChain->SetBranchAddress("muDecayPolY",&muDecayPolY);
   fChain->SetBranchAddress("muDecayPolZ",&muDecayPolZ);
   fChain->SetBranchAddress("muTargetTime",&muTargetTime);
   fChain->SetBranchAddress("muTargetPolX",&muTargetPolX);
   fChain->SetBranchAddress("muTargetPolY",&muTargetPolY);
   fChain->SetBranchAddress("muTargetPolZ",&muTargetPolZ);
   fChain->SetBranchAddress("fieldNomVal",&fieldNomVal);
   fChain->SetBranchAddress("det_n",&det_n);
   fChain->SetBranchAddress("det_ID",det_ID);
   fChain->SetBranchAddress("det_edep",det_edep);
   fChain->SetBranchAddress("det_nsteps",det_nsteps);
   fChain->SetBranchAddress("det_length",det_length);
   fChain->SetBranchAddress("det_time_start",det_time_start);
   fChain->SetBranchAddress("det_time_end",det_time_end);
   fChain->SetBranchAddress("det_x",det_x);
   fChain->SetBranchAddress("det_y",det_y);
   fChain->SetBranchAddress("det_z",det_z);
   fChain->SetBranchAddress("det_VrtxParticleID",det_VrtxParticleID);
   fChain->SetBranchAddress("save_n", &save_n, &b_save_n);
   fChain->SetBranchAddress("save_detID", save_detID, &b_save_detID);
   fChain->SetBranchAddress("save_particleID", save_particleID, &b_save_particleID);
   fChain->SetBranchAddress("save_ke", save_ke, &b_save_ke);
   fChain->SetBranchAddress("save_x", save_x, &b_save_x);
   fChain->SetBranchAddress("save_y", save_y, &b_save_y);
   fChain->SetBranchAddress("save_z", save_z, &b_save_z);
   fChain->SetBranchAddress("save_px", save_px, &b_save_px);
   fChain->SetBranchAddress("save_py", save_py, &b_save_py);
   fChain->SetBranchAddress("save_pz", save_pz, &b_save_pz);

   Notify();
}

Bool_t SiSpect::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_runID = fChain->GetBranch("runID");
   b_eventID = fChain->GetBranch("eventID");
   b_BFieldAtDecay = fChain->GetBranch("BFieldAtDecay");
   b_muIniPosX = fChain->GetBranch("muIniPosX");
   b_muIniPosY = fChain->GetBranch("muIniPosY");
   b_muIniPosZ = fChain->GetBranch("muIniPosZ");
   b_muIniMomX = fChain->GetBranch("muIniMomX");
   b_muIniMomY = fChain->GetBranch("muIniMomY");
   b_muIniMomZ = fChain->GetBranch("muIniMomZ");
   b_muIniPolX = fChain->GetBranch("muIniPolX");
   b_muIniPolY = fChain->GetBranch("muIniPolY");
   b_muIniPolZ = fChain->GetBranch("muIniPolZ");
   b_muDecayDetID = fChain->GetBranch("muDecayDetID");
   b_muDecayPosX = fChain->GetBranch("muDecayPosX");
   b_muDecayPosY = fChain->GetBranch("muDecayPosY");
   b_muDecayPosZ = fChain->GetBranch("muDecayPosZ");
   b_muDecayTime = fChain->GetBranch("muDecayTime");
   b_muDecayPolX = fChain->GetBranch("muDecayPolX");
   b_muDecayPolY = fChain->GetBranch("muDecayPolY");
   b_muDecayPolZ = fChain->GetBranch("muDecayPolZ");
   b_muTargetTime = fChain->GetBranch("muTargetTime");
   b_muTargetPolX = fChain->GetBranch("muTargetPolX");
   b_muTargetPolY = fChain->GetBranch("muTargetPolY");
   b_muTargetPolZ = fChain->GetBranch("muTargetPolZ");
   b_fieldNomVal = fChain->GetBranch("fieldNomVal");
   b_det_n = fChain->GetBranch("det_n");
   b_det_ID = fChain->GetBranch("det_ID");
   b_det_edep = fChain->GetBranch("det_edep");
   b_det_nsteps = fChain->GetBranch("det_nsteps");
   b_det_length = fChain->GetBranch("det_length");
   b_det_time_start = fChain->GetBranch("det_time_start");
   b_det_time_end = fChain->GetBranch("det_time_end");
   b_det_x = fChain->GetBranch("det_x");
   b_det_y = fChain->GetBranch("det_y");
   b_det_z = fChain->GetBranch("det_z");

   return kTRUE;
}

void SiSpect::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t SiSpect::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef SiSpect_cxx
