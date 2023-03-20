/*
Particle codes:
MuonPlus=  -13;
MuonMinus=   13;
Electron=   11;
Positron=  -11;
Gamma=   22;
Proton= 2212;
Neutron= 2112;
PionMinus= -211;
PionPlus=  211;
*/


#define SiSpect_cxx
#include "SiSpect.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>
#include <TROOT.h>
#include <TKey.h>
#include <TFile.h>
#include <TSystem.h>
#include <TTree.h>

/*
To use
TFile* fin=new TFile("data/musr_1021.root");
.L SiSpect.C
SiSpect t
t.CreateIO(1,0.0)
 */

void SiSpect::Loop()
{
}

void SiSpect::CreateIO( Bool_t   FigFlag, Double_t eCut )
{
  //   Double_t eCut    = 0.7; //minimum energy deposition in scintillators [MeV]
   Bool_t   tofFlag = 0;
   if (fChain == 0) return;

   //DEFINE HISTOGRAMS
   TH1F* hEdeposited = new TH1F("hEdeposited","Energy spectrum; E [MeV]",        250,0.,0.5);
   TH1F* hEdepositMuI = new TH1F("hEdepositMuI","Energy spectrum Mu/Pos; E [MeV]",     250,0.,0.5);
   TH1F* hEdepositMuO = new TH1F("hEdepositMuO","Energy spectrum Mu/Pos; E [MeV]",     250,0.,0.5);
   TH1F* hEdepositCF = new TH1F("hEdepositCF","Energy spectrum; E [keV]",        500,0.,20.0);
   TH1F* hEdepTrig   = new TH1F("hEdepTrig",  "Radioactive electron kin. energy",250,0.,2.5);
   TH1F* hEdepoTest  = new TH1F("hEdepoTest", "Number of events in coincidence", 100,0.,1.);
   TH1F* hTof        = new TH1F("hTof", "time-of-flight (#mus)", 1000, 0., 1.);
   TH2F* hBeamSpot   = new TH2F("hBeamSpot", " x,y", 40, -40., 40., 40, -40., 40.);
   TH1F* hDetz       = new TH1F("hDetz", "z detector [mm]", 100, -60., 60.);
   TH1F* hDetzI      = new TH1F("hDetzI", "z I detector [mm]", 100, -40., 40.);
   TH1F* hDetzO      = new TH1F("hDetzO", "z O detector [mm]", 100, -40., 40.);
   TH1F* hEventID    = new TH1F("hEventID", "Event ID", 10001, -0.5, 10000.5);

   // Back inner histogram (501)
   TH1F* hBackI       = new TH1F("hBackI","Back I (#mus)",1300,0.,13.);
   // Forward inner histogram (502)
   TH1F* hForwI       = new TH1F("hForwI","Forw I (#mus)",1300,0.,13.);
   // Top inner histogram (503)
   TH1F* hTopI       = new TH1F("hTopI","Top I (#mus)",1300,0.,13.);
   // Down inner histogram (504)
   TH1F* hDownI       = new TH1F("hDownI","Down I (#mus)",1300,0.,13.);
   // Back outer histogram (601)
   TH1F* hBackO       = new TH1F("hBackO","Back O (#mus)",1300,0.,13.);
   // Forward outer histogram (602)
   TH1F* hForwO       = new TH1F("hForwO","Forw O (#mus)",1300,0.,13.);
   // Top outer histogram (603)
   TH1F* hTopO       = new TH1F("hTopO","Top O (#mus)",1300,0.,13.);
   // Down outer histogram (604)
   TH1F* hDownO       = new TH1F("hDownO","Down O (#mus)",1300,0.,13.);


   Long64_t NFI,NFO,NBI,NBO,NTI,NTO,NDI,NDO;

   hEdeposited->Sumw2();
   hEdepositCF->Sumw2();
   hEdepTrig->Sumw2();
   
   Long64_t nentries = fChain->GetEntriesFast();
   //nentries=1000;
   //cout << "nentries = " << nentries << end;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      tofFlag = 0;
/*      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;*/
      nb = fChain->GetEntry(jentry); nbytes += nb;

      // FILL IN HISTOGRAMS
      hEdepositCF->Fill(save_ke[0]/1000.);
      hBeamSpot->Fill(save_x[0], save_y[0]);
      
      //for (Int_t i=0; i<det_n; i++)
      //  { if (det_ID[i]==623) { hEdeposited->Fill(save_ke[i]);}
      //  }

      hTof->Fill(muTargetTime);
      //if (muTargetTime>0.23) tofFlag = 1;
      //tofFlag = 1.;
      for (Int_t i=0; i<det_n; i++) {
	// Only muons
	if (det_ID[i] == 501 && det_VrtxParticleID[i]==-13) {
	  hEdepositMuI->Fill(det_edep[i]);
	  break; //fill only once
	}
      }

      for (Int_t i=0; i<det_n; i++) {
	// Only muons
	if (det_ID[i] == 601 && det_VrtxParticleID[i]==-13) {
	  hEdepositMuO->Fill(det_edep[i]);
	  break; //fill only once
	}
      }

      
      // Hist in Back I detector (501)
      for (Int_t i=0; i<det_n; i++) {
	// Only positrons
	if (jentry > 1000 && jentry < 1100) {
	  cout << "entry = " << jentry << "det_ID = " << det_ID[i] << "det_Vrtx = " << det_VrtxParticleID[i] << endl;
	}
	if (det_ID[i] == 501 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hBackI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Forw I detector (502)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 502 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hForwI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Top I detector (503)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 503 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hTopI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Down I detector (504)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 504 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hDownI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Back O detector (601)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 601 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  // Only positrons
	  if (det_edep[i]>eCut){
	    hBackO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Forw O detector (602)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 602 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hForwO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }

      // Hist in Top O detector (603)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 603 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hTopO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Down O detector (604)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] == 604 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hDownO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
   }

   //  Calculate Asymmetry
   // Temporary F and B histograms
   TH1F *hFtemp = (TH1F*) hForwI->Clone(); hFtemp->SetName("hFtemp");
   TH1F *hBtemp = (TH1F*) hBackI->Clone(); hBtemp->SetName("hBtemp");
   
   // Sum and difference F and B
   TH1F *hSumFB = (TH1F*) hForwI->Clone(); hSumFB->SetName("hSumFB");
   hSumFB->Sumw2();  
   TH1F *hDifFB = (TH1F*) hForwI->Clone(); hDifFB->SetName("hDifFB");
   hDifFB->Sumw2();  
   
   // Asymmetry histograms!
   TH1F *hAsyFB = (TH1F*) hForwI->Clone(); hAsyFB->SetName("hAsyFB");
   hAsyFB->SetTitle("Muon decay asymmetry F-B; Time (#mus); Asymmetry");
   hAsyFB->Sumw2();  
 
   // Calculate difference and sum, then divide
   hDifFB->Add(hFtemp,hBtemp,1.,-1.);
   hSumFB->Add(hFtemp,hBtemp,1., 1.);
   hAsyFB->Divide(hDifFB,hSumFB,1.,1.);
      
   if (FigFlag) {
     TCanvas* c1= new TCanvas("c1","canvas 1");
     c1->Divide(3,2);
     c1->cd(1);
     hForwI->Draw();
     hForwI->SetLineColor(kBlack);
     hBackI->Draw("sames");
     hBackI->SetLineColor(kRed);
     //     hBackI->SetX1NDC(10);
     //     hBackI->SetX2NDC(20);
     hTopI->Draw("sames");
     hTopI->SetLineColor(kGreen);
     hDownI->Draw("sames");
     hDownI->SetLineColor(kBlue);
     gStyle->SetOptStat("ne");
     c1->cd(2);
     hForwO->Draw();
     hForwO->SetLineColor(kBlack);
     hBackO->Draw("sames");
     hBackO->SetLineColor(kRed);
     hTopO->Draw("sames");
     hTopO->SetLineColor(kGreen);
     hDownO->Draw("sames");
     hDownO->SetLineColor(kBlue);
     gStyle->SetOptStat("ne");
     c1->cd(3);
     hAsyFB->Draw();
     hAsyFB -> Fit("pol0","Q","",0.6, 13.);
     gStyle->SetOptStat(1001111);
     gStyle->SetOptFit(0001);
     gStyle->SetLineColor(2);
     c1->cd(4);
     hEdeposited->Draw();
     hEdepositMuO->Draw("sames");
     hEdepositMuO->SetLineColor(kRed);
     hEdepositMuI->Draw("sames");
     hEdeposited->SetLineColor(kGreen);
     //gStyle->SetOptStat("nemr");
     c1->cd(5);
     hDetz->Draw();
     hDetzI->Draw("sames");
     hDetzI->SetLineColor(kRed);
     hDetzO->Draw("sames");
     hDetzO->SetLineColor(kGreen);
   } else {
     hAsyFB -> Fit("pol0","NQ","",0.6, 13.);
   }
   
   TF1 *pol0;
   pol0 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol0");
   Double_t chi2=pol0->GetChisquare();
   Double_t p1=pol0->GetParameter(0);
   Double_t e1=pol0->GetParError(0);

   //   printf("Chi=%g\tP1=%g +/- %g\n",chi2,p1,e1);
   //printf("%g\t%g\t%g\n",p1,e1,chi2);
}

void SiSpect::CoinIO( Bool_t FigFlag, Double_t aCut)
{
  Double_t eCut    = 0.0; //minimum energy deposition in Si pixel [MeV]
  Bool_t   tofFlag = 0;
  Bool_t   vetoFlag = 0;
  Int_t    savek = 0;
  if (fChain == 0) return;
  
  //DEFINE HISTOGRAMS
  TH1F* hEdeposited = new TH1F("hEdeposited","Energy spectrum; E [MeV]",        250,0.,0.5);
  TH1F* hEdepositMuI = new TH1F("hEdepositMuI","Energy spectrum Mu inner; E [MeV]",     250,0.,0.5);
  TH1F* hEdepositMuO = new TH1F("hEdepositMuO","Energy spectrum Mu outer; E [MeV]",     250,0.,0.5);
  TH1F* hEdepositCF = new TH1F("hEdepositCF","Energy spectrum; E [keV]",        500,0.,20.0);
  TH1F* hEdepTrig   = new TH1F("hEdepTrig",  "Radioactive electron kin. energy",250,0.,2.5);
  TH1F* hEdepoTest  = new TH1F("hEdepoTest", "Number of events in coincidence", 100,0.,1.);
  TH1F* hTof        = new TH1F("hTof", "time-of-flight (#mus)", 1000, 0., 1.);
  TH2F* hBeamSpot   = new TH2F("hBeamSpot", "Beam on sample x,y", 200, -40., 40., 200, -40., 40.);
  TH1F* hDetz       = new TH1F("hDetz", "z detector [mm]", 100, -60., 60.);
  TH1F* hEventID    = new TH1F("hEventID", "Event ID", 10001, -0.5, 10000.5);
  TH2F* hMuIxy      = new TH2F("hMuIxy", "Beam in inner x,y", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuOxy      = new TH2F("hMuOxy", "Beam on outer x,y", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuIOxy     = new TH2F("hMuIOxy", "Diff. between reconstucted-actual Mu position with veto", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuSamxy    = new TH2F("hMuSamxy", "Beam extrapolated on sample with veto", 200, -40., 40., 200, -40., 40.);
  
  // Back histogram, i.e. all counts in coincedence 501-601
  TH1F* hBack       = new TH1F("hBack","Back (#mus)",130,0.,13.);
  // Forward histogram, i.e. all counts in coincedence 502-602
  TH1F* hForw       = new TH1F("hForw","Forw (#mus)",130,0.,13.);
  // Top histogram, i.e. all counts in coincedence 503-603
  TH1F* hTop        = new TH1F("hTop","Top (#mus)",130,0.,13.);
  // Down histogram, i.e. all counts in coincedence 504-604
  TH1F* hDown       = new TH1F("hDown","Down (#mus)",130,0.,13.);
  // Mu counter, i.e. all counts in coincedence 501-601
  TH1F* hMu         = new TH1F("hMu","Muons (#mus)",130,0.,13.);
  
  Double_t xo,yo,zo,xi,yi,zi,xs,ys,zs,ax,ay;
  // Sample position
  zs = 0.0;
   
  hEdeposited->Sumw2();
  hEdepositCF->Sumw2();
  hEdepTrig->Sumw2();
  
  Long64_t nentries = fChain->GetEntriesFast();
  /*   nentries=50000;*/
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tofFlag = 1;
    /*      Long64_t ientry = LoadTree(jentry);
	    if (ientry < 0) break;*/
    nb = fChain->GetEntry(jentry); nbytes += nb;
    
    // FILL IN HISTOGRAMS
    hEdepositCF->Fill(save_ke[0]/1000.);
    hBeamSpot->Fill(save_x[0], save_y[0]);
    
    //for (Int_t i=0; i<det_n; i++)
    //  { if (det_ID[i]==623) { hEdeposited->Fill(save_ke[i]);}
    //  }
    
    hTof->Fill(muTargetTime);
    //if (muTargetTime>0.23) tofFlag = 1;
    //tofFlag = 1.;
    
    // Hist in Muon detector (501) coincidence (601)
    // Ignore Muons that missed the target (i.e. have a hit in 502, 602, 503, 603, 504 or 604)
    for (Int_t i=0; i<det_n; i++) {
      if (det_ID[i]==601 && det_VrtxParticleID[i]==-13) {
	// Mu outer hit
	xo=det_x[i];
	yo=det_y[i];
	zo=det_z[i];
	hMuOxy->Fill(xo, yo);
	hEdepositMuO->Fill(det_edep[i]);
	hDetz->Fill(det_z[i]);
	for (Int_t j=0; j<det_n; j++){ 
	  if (det_ID[j]==501  && det_VrtxParticleID[j]==-13) {
	    // Mu inner hit
	    xi=det_x[j];
	    yi=det_y[j];
	    zi=det_z[j];
	    hMuIxy->Fill(xi, yi);
	    hEdepositMuI->Fill(det_edep[j]);
	    hMu->Fill(det_time_start[j]);
	    hDetz->Fill(det_z[j]);
	    hEventID->Fill(eventID);
	    vetoFlag = 0;
	    // Check if this event continued to hit other detectors as a scattered muon
	    for (Int_t k=0; k<det_n; k++){
	      if ((det_ID[k]==502  && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]==602  && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]==503  && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]==603  && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]==504  && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]==604  && det_VrtxParticleID[k]==-13)) {
		vetoFlag = 1;
		break; // don't waste time.
	      }
	      /*
		if (jentry==1000) {
		printf("det_ID[k]=%d and det_VrtxParticleID[k]=%d\n",det_ID[k],det_VrtxParticleID[k]);
		printf("Event ID = %d Vetoed? %d\n",eventID,vetoFlag);
		}
	      */
	    }
	    // Propagate Mu trajectory on sample for non-vetoed events
	    if (!vetoFlag) {
	      // Calculate trajectory slope, sharp angles are probably not good
	      ax=(xi-xo)/(zi-zo);
	      ay=(yi-yo)/(zi-zo);
	      // Get the muon hit in the target, usually save_detID[0]
	      for (Int_t k=0; k<save_n; k++){
		if (save_detID[k] == 253 && save_particleID[k] == -13) {
		  savek = k;
		  break;
		}
	      }
	      
	      // We can make a cut for trajectories deflected by slope aCut
	      if ((aCut == 0) || (TMath::Abs(ax)<aCut && TMath::Abs(ay)<aCut)) {
		if (savek != 0) cout << "Event # " << jentry << " savek = " << savek << endl;
		xs=xi+ax*(zs-zi);
		ys=yi+ay*(zs-zi);
		hMuIOxy->Fill(xs-save_x[savek], ys-save_y[savek]);
		hMuSamxy->Fill(xs, ys);
	      }
	    }
	    break; //fill only once
	  }
	}
	break;
      }
    }
    
    // Hist in Back detector (501) coincidence (601)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]==601 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]==501 && det_VrtxParticleID[j]==-11) {
		hEdeposited->Fill(det_edep[j]);
		if (det_edep[j]>eCut){
		  hBack->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once		  
	      }
	    }
	  }
	}
      }

      // Hist in Forw detector (502) coincidence (602)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]==602 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]==502 && det_VrtxParticleID[j]==-11) {
		if (det_edep[j]>eCut){
		  hForw->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once
	      }
	    }
	  }
	}
      }

      // Hist in Top detector (503) coincidence (603)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]==603 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]==503 && det_VrtxParticleID[j]==-11) {
		if (det_edep[j]>eCut){
		  hTop->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once
	      }
	    }
	  }
	}
      }

      // Hist in Down detector (504) coincidence (604)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]==604 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]==504 && det_VrtxParticleID[j]==-11) {
		if (det_edep[j]>eCut){
		  hDown->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once
	      }
	    }
	  }
	}
      }


   }

  TH1F *hAsyFB = (TH1F*) hForw->Clone(); hAsyFB->SetName("hAsyFB");
  //  Calculate Asymmetry
  if (hForw->GetEntries() != 0 || hForw->GetEntries() != 0) {
    // Temporary F and B histograms
    TH1F *hFtemp = (TH1F*) hForw->Clone(); hFtemp->SetName("hFtemp");
    TH1F *hBtemp = (TH1F*) hBack->Clone(); hBtemp->SetName("hBtemp");

    // Sum and difference F and B
    TH1F *hSumFB = (TH1F*) hForw->Clone(); hSumFB->SetName("hSumFB");
    hSumFB->Sumw2();  
    TH1F *hDifFB = (TH1F*) hForw->Clone(); hDifFB->SetName("hDifFB");
    hDifFB->Sumw2();  

    // Asymmetry histograms!
    hAsyFB->SetTitle("Muon decay asymmetry F-B; Time (#mus); Asymmetry");
    hAsyFB->Sumw2();  

    // Calculate difference and sum, then divide
    hDifFB->Add(hFtemp,hBtemp,1.,-1.);
    hSumFB->Add(hFtemp,hBtemp,1., 1.);
    hAsyFB->Divide(hDifFB,hSumFB,1.,1.);
  }
  
  TH1F *hAsyTD = (TH1F*) hTop->Clone(); hAsyTD->SetName("hAsyTD");
  if (hTop->GetEntries() != 0 || hDown->GetEntries() != 0) {
    // Temporary T and D histograms
    TH1F *hTtemp = (TH1F*) hTop->Clone(); hTtemp->SetName("hTtemp");
    TH1F *hDtemp = (TH1F*) hDown->Clone(); hDtemp->SetName("hDtemp");
    
    // Sum and difference T and D
    TH1F *hSumTD = (TH1F*) hTop->Clone(); hSumTD->SetName("hSumTD");
    hSumTD->Sumw2();  
    TH1F *hDifTD = (TH1F*) hDown->Clone(); hDifTD->SetName("hDifTD");
    hDifTD->Sumw2();  
    
    hAsyTD->SetTitle("Muon decay asymmetry T-D; Time (#mus); Asymmetry");
    hAsyTD->Sumw2();  
      
    // Calculate difference and sum, then divide
    hDifTD->Add(hTtemp,hDtemp,1.,-1.);
    hSumTD->Add(hTtemp,hDtemp,1., 1.);
    hAsyTD->Divide(hDifTD,hSumTD,1.,1.);
  }
  
  if (FigFlag) {
    TCanvas* c1= new TCanvas("c1","canvas 1",1200,1200);
     c1->Divide(3,3);
     c1->cd(1);
     hBack->Draw();
     hBack->SetLineColor(kBlack);
     hForw->Draw("sames");
     hForw->SetLineColor(kRed);
     //gStyle->SetStatTextColor(kRed);
     hTop->Draw("sames");
     hTop->SetLineColor(kGreen);
     hDown->Draw("sames");
     hDown->SetLineColor(kBlue);
     c1->cd(2);
     if (hAsyFB->GetEntries() != 0) {
       hAsyFB->Draw("sames");
       hAsyFB -> Fit("pol0","Q","",0.1, 13.);
       gStyle->SetOptStat(1001111);
       gStyle->SetOptFit(0001);
       gStyle->SetLineColor(2);
     }
     if (hAsyTD->GetEntries() != 0) {
       hAsyTD->Draw("sames");
       hAsyTD -> Fit("pol0","Q","",0.1, 13.);
       gStyle->SetOptStat(1001111);
       gStyle->SetOptFit(0001);
       gStyle->SetLineColor(2);
     }
     c1->cd(3);
     hDetz->Draw();
     c1->cd(4);
     hBeamSpot->Draw();
     hBeamSpot->Draw("cont0 same");
     THStack* hs= new THStack("hs","Energy spectrum Mu/Pos; E [MeV]");
     hs->Add(hEdeposited,"sames");
     hs->Add(hEdepositMuI,"sames");
     hEdepositMuI->SetLineColor(kRed);
     hs->Add(hEdepositMuO,"sames");
     hEdepositMuO->SetLineColor(kGreen);
     c1->cd(5);
     hs->Draw("nostack");
     /*
     hEdeposited->Draw();
     hEdepositMuI->Draw("sames nostack");
     hEdepositMuO->Draw("sames nostack");
     det_edep_pos->Draw("sames");
     det_edep_pos->SetLineColor(kGreen);
     det_edep_mup->Draw("sames");
     det_edep_mup->SetLineColor(kPink);*/
     c1->cd(6);
     hMuIOxy->Draw();
     hMuIOxy->Draw("cont0 same");
     c1->cd(7);
     hMuSamxy->Draw();
     hMuSamxy->Draw("cont0 same");
     c1->cd(8);
     
     c1->cd(9);
   } 
   
   TF1 *pol0;
   pol0 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol0");
   Double_t chi2=pol0->GetChisquare();
   Double_t p1=pol0->GetParameter(0);
   Double_t e1=pol0->GetParError(0);
   Double_t NDet=hDetz->GetSum();

   //   printf("Chi=%g\tP1=%g +/- %g\n",chi2,p1,e1);
   //printf("%g\t%g\t%g\t%g\n",p1,e1,chi2,NDet);

   Double_t NhF = hBack->GetEntries();
   Double_t NhB = hForw->GetEntries();
   Double_t asymFB = (NhB-NhF)/(NhB+NhF);
   Double_t NhT = hTop->GetEntries();
   Double_t NhD = hDown->GetEntries();
   Double_t asymTD = (NhT-NhD)/(NhT+NhD);

   //cout << "FB Asymmetry = " << asymFB << endl;
   //cout << "TD Asymmetry = " << asymTD << endl;
}

void SiSpect::QCreateIO( Bool_t   FigFlag, Double_t eCut )
{
  //   Double_t eCut    = 0.7; //minimum energy deposition in scintillators [MeV]
   Bool_t   tofFlag = 0;
   if (fChain == 0) return;

   //DEFINE HISTOGRAMS
   TH1F* hEdeposited = new TH1F("hEdeposited","Energy spectrum; E [MeV]",        250,0.,0.5);
   TH1F* hEdepositMuI = new TH1F("hEdepositMuI","Energy spectrum Mu/Pos; E [MeV]",     250,0.,0.5);
   TH1F* hEdepositMuO = new TH1F("hEdepositMuO","Energy spectrum Mu/Pos; E [MeV]",     250,0.,0.5);
   TH1F* hEdepositCF = new TH1F("hEdepositCF","Energy spectrum; E [keV]",        500,0.,20.0);
   TH1F* hEdepTrig   = new TH1F("hEdepTrig",  "Radioactive electron kin. energy",250,0.,2.5);
   TH1F* hEdepoTest  = new TH1F("hEdepoTest", "Number of events in coincidence", 100,0.,1.);
   TH1F* hTof        = new TH1F("hTof", "time-of-flight (#mus)", 1000, 0., 1.);
   TH2F* hBeamSpot   = new TH2F("hBeamSpot", " x,y", 40, -40., 40., 40, -40., 40.);
   TH1F* hDetz       = new TH1F("hDetz", "z detector [mm]", 100, -60., 60.);
   TH1F* hDetzI      = new TH1F("hDetzI", "z I detector [mm]", 100, -40., 40.);
   TH1F* hDetzO      = new TH1F("hDetzO", "z O detector [mm]", 100, -40., 40.);
   TH1F* hEventID    = new TH1F("hEventID", "Event ID", 10001, -0.5, 10000.5);

   // Back inner histogram (501-504)
   TH1F* hBackI       = new TH1F("hBackI","Back I (#mus)",1300,0.,13.);
   // Forward inner histogram (505-508)
   TH1F* hForwI       = new TH1F("hForwI","Forw I (#mus)",1300,0.,13.);
   // Back outer histogram (601-604)
   TH1F* hBackO       = new TH1F("hBackO","Back O (#mus)",1300,0.,13.);
   // Forward outer histogram (605-608)
   TH1F* hForwO       = new TH1F("hForwO","Forw O (#mus)",1300,0.,13.);


   Long64_t NFI,NFO,NBI,NBO,NTI,NTO,NDI,NDO;

   hEdeposited->Sumw2();
   hEdepositCF->Sumw2();
   hEdepTrig->Sumw2();
   
   Long64_t nentries = fChain->GetEntriesFast();
   //nentries=1000;
   //cout << "nentries = " << nentries << end;
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      tofFlag = 0;
/*      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;*/
      nb = fChain->GetEntry(jentry); nbytes += nb;

      // FILL IN HISTOGRAMS
      hEdepositCF->Fill(save_ke[0]/1000.);
      hBeamSpot->Fill(save_x[0], save_y[0]);
      
      //for (Int_t i=0; i<det_n; i++)
      //  { if (det_ID[i]==623) { hEdeposited->Fill(save_ke[i]);}
      //  }

      hTof->Fill(muTargetTime);
      //if (muTargetTime>0.23) tofFlag = 1;
      //tofFlag = 1.;
      for (Int_t i=0; i<det_n; i++) {
	// Only muons
	if (det_ID[i] <= 504 && det_ID[i] >= 501 && det_VrtxParticleID[i]==-13) {
	  hEdepositMuI->Fill(det_edep[i]);
	  break; //fill only once
	}
      }

      for (Int_t i=0; i<det_n; i++) {
	// Only muons
	if (det_ID[i] <= 604 && det_ID[i] >= 601 && det_VrtxParticleID[i]==-13) {
	  hEdepositMuO->Fill(det_edep[i]);
	  break; //fill only once
	}
      }

      
      // Hist in Back I detector (501-504)
      for (Int_t i=0; i<det_n; i++) {
	// Only positrons
	if (jentry > 1000 && jentry < 1100) {
	  cout << "entry = " << jentry << "det_ID = " << det_ID[i] << "det_Vrtx = " << det_VrtxParticleID[i] << endl;
	}
	if (det_ID[i] <= 504 && det_ID[i] >= 501 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hBackI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Forw I detector (505-508)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] <= 508 && det_ID[i] >= 505 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hForwI->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzI->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      
      // Hist in Back O detector (601-604)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] <= 604 && det_ID[i] >= 601 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  // Only positrons
	  if (det_edep[i]>eCut){
	    hBackO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }
      
      // Hist in Forw O detector (605-608)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i] <= 608 && det_ID[i] >= 605 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  if (det_edep[i]>eCut){
	    hForwO->Fill(det_time_start[i]);
	    hDetz->Fill(det_z[i]);
	    hDetzO->Fill(det_z[i]);
	    hEventID->Fill(eventID);
	    break; //fill only once
	  }
	}
      }

   }

   //  Calculate Asymmetry
   // Temporary F and B histograms
   TH1F *hFtemp = (TH1F*) hForwI->Clone(); hFtemp->SetName("hFtemp");
   TH1F *hBtemp = (TH1F*) hBackI->Clone(); hBtemp->SetName("hBtemp");
   
   // Sum and difference F and B
   TH1F *hSumFB = (TH1F*) hForwI->Clone(); hSumFB->SetName("hSumFB");
   hSumFB->Sumw2();  
   TH1F *hDifFB = (TH1F*) hForwI->Clone(); hDifFB->SetName("hDifFB");
   hDifFB->Sumw2();  
   
   // Asymmetry histograms!
   TH1F *hAsyFB = (TH1F*) hForwI->Clone(); hAsyFB->SetName("hAsyFB");
   hAsyFB->SetTitle("Muon decay asymmetry F-B; Time (#mus); Asymmetry");
   hAsyFB->Sumw2();  
 
   // Calculate difference and sum, then divide
   hDifFB->Add(hFtemp,hBtemp,1.,-1.);
   hSumFB->Add(hFtemp,hBtemp,1., 1.);
   hAsyFB->Divide(hDifFB,hSumFB,1.,1.);
      
   if (FigFlag) {
     TCanvas* c1= new TCanvas("c1","canvas 1");
     c1->Divide(3,2);
     c1->cd(1);
     hForwI->Draw();
     hForwI->SetLineColor(kBlack);
     hBackI->Draw("sames");
     hBackI->SetLineColor(kRed);
     //     hBackI->SetX1NDC(10);
     //     hBackI->SetX2NDC(20);
     gStyle->SetOptStat("ne");
     c1->cd(2);
     hForwO->Draw();
     hForwO->SetLineColor(kBlack);
     hBackO->Draw("sames");
     hBackO->SetLineColor(kRed);
     gStyle->SetOptStat("ne");
     c1->cd(3);
     hAsyFB->Draw();
     hAsyFB -> Fit("pol0","Q","",0.6, 13.);
     gStyle->SetOptStat(1001111);
     gStyle->SetOptFit(0001);
     gStyle->SetLineColor(2);
     c1->cd(4);
     hEdeposited->Draw();
     hEdepositMuO->Draw("sames");
     hEdepositMuO->SetLineColor(kRed);
     hEdepositMuI->Draw("sames");
     hEdeposited->SetLineColor(kGreen);
     //gStyle->SetOptStat("nemr");
     c1->cd(5);
     hDetz->Draw();
     hDetzI->Draw("sames");
     hDetzI->SetLineColor(kRed);
     hDetzO->Draw("sames");
     hDetzO->SetLineColor(kGreen);
   } else {
     hAsyFB -> Fit("pol0","NQ","",0.6, 13.);
   }
   
   TF1 *pol0;
   pol0 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol0");
   Double_t chi2=pol0->GetChisquare();
   Double_t p1=pol0->GetParameter(0);
   Double_t e1=pol0->GetParError(0);

   //   printf("Chi=%g\tP1=%g +/- %g\n",chi2,p1,e1);
   //printf("%g\t%g\t%g\n",p1,e1,chi2);
}

void SiSpect::QCoinIO( Bool_t FigFlag, Double_t aCut, int run)
{
  Double_t eCut    = 0.0; //minimum energy deposition in Si pixel [MeV]
  Bool_t   tofFlag = 0;
  Bool_t   vetoFlag = 0;
  Int_t    savek = 0;
  if (fChain == 0) return;
  
  //DEFINE HISTOGRAMS
  TH1F* hEdeposited = new TH1F("hEdeposited","Energy spectrum; E [MeV]",        250,0.,0.5);
  TH1F* hEdepositMuI = new TH1F("hEdepositMuI","Energy spectrum Mu inner; E [MeV]",     250,0.,0.5);
  TH1F* hEdepositMuO = new TH1F("hEdepositMuO","Energy spectrum Mu outer; E [MeV]",     250,0.,0.5);
  TH1F* hEdepositCF = new TH1F("hEdepositCF","Energy spectrum; E [keV]",        500,0.,20.0);
  TH1F* hEdepTrig   = new TH1F("hEdepTrig",  "Radioactive electron kin. energy",250,0.,2.5);
  TH1F* hEdepoTest  = new TH1F("hEdepoTest", "Number of events in coincidence", 100,0.,1.);
  TH1F* hTof        = new TH1F("hTof", "time-of-flight (#mus)", 1000, 0., 1.);
  TH2F* hBeamSpot   = new TH2F("hBeamSpot", "Beam on sample x,y", 200, -40., 40., 200, -40., 40.);
  TH1F* hDetz       = new TH1F("hDetz", "z detector [mm]", 100, -60., 60.);
  TH1F* hEventID    = new TH1F("hEventID", "Event ID", 10001, -0.5, 10000.5);
  TH2F* hMuIxy      = new TH2F("hMuIxy", "Beam in inner x,y", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuOxy      = new TH2F("hMuOxy", "Beam on outer x,y", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuIOxy     = new TH2F("hMuIOxy", "Diff. between reconstucted-actual Mu position with veto", 200, -40., 40., 200, -40., 40.);
  TH2F* hMuSamxy    = new TH2F("hMuSamxy", "Beam extrapolated on sample with veto", 200, -40., 40., 200, -40., 40.);
  
  // Back histogram, i.e. all counts in coincedence 501-504:601-604
  TH1F* hBack       = new TH1F("hBack","Back (#mus)",130,0.,13.);
  // Forward histogram, i.e. all counts in coincedence 505-508:605-608
  TH1F* hForw       = new TH1F("hForw","Forw (#mus)",130,0.,13.);
  // Mu counter, i.e. all muon counts in coincedence 501-504:601-604
  TH1F* hMu         = new TH1F("hMu","Muons (#mus)",130,0.,13.);
  
  Double_t xo,yo,zo,xi,yi,zi,xs,ys,zs,ax,ay;
  // Sample position
  zs = 0.0;
   
  hEdeposited->Sumw2();
  hEdepositCF->Sumw2();
  hEdepTrig->Sumw2();
  
  Long64_t nentries = fChain->GetEntriesFast();
  /*   nentries=50000;*/
  
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    tofFlag = 1;
    /*      Long64_t ientry = LoadTree(jentry);
	    if (ientry < 0) break;*/
    nb = fChain->GetEntry(jentry); nbytes += nb;
    
    // FILL IN HISTOGRAMS
    hEdepositCF->Fill(save_ke[0]/1000.);
    hBeamSpot->Fill(save_x[0], save_y[0]);
    
    //for (Int_t i=0; i<det_n; i++)
    //  { if (det_ID[i]==623) { hEdeposited->Fill(save_ke[i]);}
    //  }
    
    hTof->Fill(muTargetTime);
    //if (muTargetTime>0.23) tofFlag = 1;
    //tofFlag = 1.;
    
    // Hist in Muon detector (501-504) coincidence (601-604)
    // Ignore Muons that missed the target (i.e. have a hit in 505-508 or 605-608)
    for (Int_t i=0; i<det_n; i++) {
      if (det_ID[i]>=601 && det_ID[i]<=604 && det_VrtxParticleID[i]==-13) {
	// Mu outer hit
	xo=det_x[i];
	yo=det_y[i];
	zo=det_z[i];
	hMuOxy->Fill(xo, yo);
	hEdepositMuO->Fill(det_edep[i]);
	hDetz->Fill(det_z[i]);
	for (Int_t j=0; j<det_n; j++){ 
	  if (det_ID[j]>=501  && det_ID[j]<=504 && det_VrtxParticleID[j]==-13) {
	    // Mu inner hit
	    xi=det_x[j];
	    yi=det_y[j];
	    zi=det_z[j];
	    hMuIxy->Fill(xi, yi);
	    hEdepositMuI->Fill(det_edep[j]);
	    hMu->Fill(det_time_start[j]);
	    hDetz->Fill(det_z[j]);
	    hEventID->Fill(eventID);
	    vetoFlag = 0;
	    // Check if this event continued to hit other detectors as a scattered muon
	    for (Int_t k=0; k<det_n; k++){
	      if ((det_ID[k]>=505 && det_ID[k]<=508 && det_VrtxParticleID[k]==-13) ||
		  (det_ID[k]>=605 && det_ID[k]<=608 && det_VrtxParticleID[k]==-13)) {
		vetoFlag = 1;
		break; // don't waste time.
	      }
	      /*
		if (jentry==1000) {
		printf("det_ID[k]=%d and det_VrtxParticleID[k]=%d\n",det_ID[k],det_VrtxParticleID[k]);
		printf("Event ID = %d Vetoed? %d\n",eventID,vetoFlag);
		}
	      */
	    }
	    // Propagate Mu trajectory on sample for non-vetoed events
	    if (!vetoFlag) {
	      // Calculate trajectory slope, sharp angles are probably not good
	      ax=(xi-xo)/(zi-zo);
	      ay=(yi-yo)/(zi-zo);
	      // Get the muon hit in the target, usually save_detID[0]
	      for (Int_t k=0; k<save_n; k++){
		if (save_detID[k] == 253 && save_particleID[k] == -13) {
		  savek = k;
		  break;
		}
	      }
	      
	      // We can make a cut for trajectories deflected by slope aCut
	      if ((aCut == 0) || (TMath::Abs(ax)<aCut && TMath::Abs(ay)<aCut)) {
		if (savek != 0) cout << "Event # " << jentry << " savek = " << savek << endl;
		xs=xi+ax*(zs-zi);
		ys=yi+ay*(zs-zi);
		hMuIOxy->Fill(xs-save_x[savek], ys-save_y[savek]);
		hMuSamxy->Fill(xs, ys);
	      }
	    }
	    break; //fill only once
	  }
	}
	break;
      }
    }
    
    // Hist in Back detector (501-504) coincidence (601-604)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]>=601 && det_ID[i]<=604 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]>=501 && det_ID[j]<=504 && det_VrtxParticleID[j]==-11) {
		hEdeposited->Fill(det_edep[j]);
		if (det_edep[j]>eCut){
		  hBack->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once		  
	      }
	    }
	  }
	}
      }

      // Hist in Forw detector (505-508) coincidence (605-608)
      for (Int_t i=0; i<det_n; i++) {
	if (det_ID[i]>=605 && det_ID[i]<=608 && det_VrtxParticleID[i]==-11) {
	  hEdeposited->Fill(det_edep[i]);
	  hDetz->Fill(det_z[i]);
	  if (det_edep[i]>eCut){
	    for (Int_t j=0; j<det_n; j++){ 
	      if (det_ID[j]>=505 && det_ID[j]<=508 && det_VrtxParticleID[j]==-11) {
		if (det_edep[j]>eCut){
		  hForw->Fill(det_time_start[j]);
		  hDetz->Fill(det_z[j]);
		  hEventID->Fill(eventID);
		}
		break; //fill only once
	      }
	    }
	  }
	}
      }

   }

  TH1F *hAsyFB = (TH1F*) hForw->Clone(); hAsyFB->SetName("hAsyFB");
  //  Calculate Asymmetry
  if (hForw->GetEntries() != 0 || hForw->GetEntries() != 0) {
    // Temporary F and B histograms
    TH1F *hFtemp = (TH1F*) hForw->Clone(); hFtemp->SetName("hFtemp");
    TH1F *hBtemp = (TH1F*) hBack->Clone(); hBtemp->SetName("hBtemp");

    // Sum and difference F and B
    TH1F *hSumFB = (TH1F*) hForw->Clone(); hSumFB->SetName("hSumFB");
    hSumFB->Sumw2();  
    TH1F *hDifFB = (TH1F*) hForw->Clone(); hDifFB->SetName("hDifFB");
    hDifFB->Sumw2();  

    // Asymmetry histograms!
    hAsyFB->SetTitle("Muon decay asymmetry F-B; Time (#mus); Asymmetry");
    hAsyFB->Sumw2();  

    // Calculate difference and sum, then divide
    hDifFB->Add(hFtemp,hBtemp,1.,-1.);
    hSumFB->Add(hFtemp,hBtemp,1., 1.);
    hAsyFB->Divide(hDifFB,hSumFB,1.,1.);
  }
  
   if (FigFlag) {
    TCanvas* c1= new TCanvas("c1","canvas 1",1200,1200);
     c1->Divide(3,3);
     c1->cd(1);
     hBack->Draw();
     hBack->SetLineColor(kBlack);
     hForw->Draw("sames");
     hForw->SetLineColor(kRed);
     //gStyle->SetStatTextColor(kRed);
     c1->cd(2);
     if (hAsyFB->GetEntries() != 0) {
       hAsyFB->Draw("sames");
       hAsyFB -> Fit("pol0","Q","",0.1, 13.);
       gStyle->SetOptStat(1001111);
       gStyle->SetOptFit(0001);
       gStyle->SetLineColor(2);
     }
     c1->cd(3);
     hDetz->Draw();
     c1->cd(4);
     hBeamSpot->Draw();
     hBeamSpot->Draw("cont0 same");
     THStack* hs= new THStack("hs","Energy spectrum Mu/Pos; E [MeV]");
     hs->Add(hEdeposited,"sames");
     hs->Add(hEdepositMuI,"sames");
     hEdepositMuI->SetLineColor(kRed);
     hs->Add(hEdepositMuO,"sames");
     hEdepositMuO->SetLineColor(kGreen);
     c1->cd(5);
     hs->Draw("nostack");
     /*
     hEdeposited->Draw();
     hEdepositMuI->Draw("sames nostack");
     hEdepositMuO->Draw("sames nostack");
     det_edep_pos->Draw("sames");
     det_edep_pos->SetLineColor(kGreen);
     det_edep_mup->Draw("sames");
     det_edep_mup->SetLineColor(kPink);*/
     c1->cd(6);
     hMuIOxy->Draw();
     hMuIOxy->Draw("cont0 same");
     c1->cd(7);
     hMuSamxy->Draw();
     hMuSamxy->Draw("cont0 same");
     c1->cd(8);
     
     c1->cd(9);

     c1->SaveAs(Form("output/SiSpect-QCoinIO-%d.pdf", run));
   } 
   
   TF1 *pol0;
   pol0 = (TF1*)gROOT->GetListOfFunctions()->FindObject("pol0");
   Double_t chi2=pol0->GetChisquare();
   Double_t p1=pol0->GetParameter(0);
   Double_t e1=pol0->GetParError(0);
   Double_t NDet=hDetz->GetSum();

   //   printf("Chi=%g\tP1=%g +/- %g\n",chi2,p1,e1);
   //printf("%g\t%g\t%g\t%g\n",p1,e1,chi2,NDet);

   Double_t NhF = hBack->GetEntries();
   Double_t NhB = hForw->GetEntries();
   Double_t asymFB = (NhB-NhF)/(NhB+NhF);

   //cout << "FB Asymmetry = " << asymFB << endl;
   //cout << "TD Asymmetry = " << asymTD << endl;
}
/*
ax=(x2-x1)/(z2-z1)
ay=(y2-y1)/(z2-z1)
x3=x2+ax*(z3-z2)
y3=y2+ay*(x3-z2)
*/
