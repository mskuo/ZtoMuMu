//This is the cade with selection that each event has only a pair of muon

#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std ;

int main()
{
	//Load the data
	TFile *in = TFile::Open("myfile.root");
	//create the new file to store the result
	TFile *out = new TFile("Zboson.root" , "recreate" ) ;
	TTree *Candidates ;


	//result histogram
	TH1F *h1 = new TH1F("Zbosons_from_muons" , "Zbosons_from_muons" , 240 , 0. , 240. ) ;
	TH1F *h2 = new TH1F("Zbosons_from_electrons" , "Zbosons_from_electrons" , 240 , 0. , 240. ) ;
	TH1F *h3 = new TH1F("Pt_rate_around_muon " , " Pt_rate_around_muon " , 40 , 0. , 10. ) ; 

	h1 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h1 -> GetYaxis() -> SetTitle ( "Number of pairs " ) ; 

	h2 -> GetXaxis() -> SetTitle ( "Mass  (in GeV) " ) ;
	h2 -> GetYaxis() -> SetTitle ( "Number of pairs " ) ; 

	h3 -> GetXaxis() -> SetTitle ( " Pt rate " ) ;
	h3 -> GetYaxis() -> SetTitle ( "Number of muons " ) ; 
	
	//Load the data into Candidates
	in -> GetObject( "Candidates" , Candidates ) ;
        int nparticles ;
	int type[3000] ;
	int charge[3000] ;
        double e[3000] , px[3000], py[3000], pz[3000], pt[3000], eta[3000], phi[3000] ;
 
	double s_electron ;
	double s_muon ;

//	double Pt_plus ;
//	double Pt_minus ;

	//For particles
	TLorentzVector LV_particles_variables ; 
	vector<TLorentzVector> LV_particles ;

	//For muons
	TLorentzVector LV_dimuon ; 
	vector<TLorentzVector> LV_muon_plus ;
	vector<TLorentzVector> LV_muon_minus ;

	//For electrons
	TLorentzVector LV_dielectron ; 
	vector<TLorentzVector> LV_electron_plus ;
	vector<TLorentzVector> LV_electron_minus ;


        Candidates -> SetBranchAddress("nparticles" , &nparticles) ;
	Candidates -> SetBranchAddress("type" , type ) ;
	Candidates -> SetBranchAddress("charge" , charge ) ;
	Candidates -> SetBranchAddress("e" , e ) ;
	Candidates -> SetBranchAddress("px" , px ) ;
	Candidates -> SetBranchAddress("py" , py ) ;
	Candidates -> SetBranchAddress("pz" , pz ) ;
	Candidates -> SetBranchAddress("pt" , pt ) ;
	Candidates -> SetBranchAddress("eta" , eta ) ;
	Candidates -> SetBranchAddress("phi" , phi ) ;

	//For only a pair in an event
//	int c_m_plus ;	
//	int c_m_minus ;

//	int c_e_plus ;
//	int c_e_minus ;

	//Loop all events
	for ( int evt = 0 ; evt < Candidates -> GetEntries() ; evt++ ) 
	{
		Candidates -> GetEntry(evt) ;

		LV_particles.clear() ;
		LV_muon_plus.clear() ;
		LV_muon_minus.clear() ;

//		c_m_plus = 0 ;
//		c_m_minus = 0 ;	

//		c_e_plus = 0 ;
//		c_e_minus = 0 ;

		//Loop for all particles in an event
		for ( int i = 0 ; i < nparticles ; i++ ) 
		{
			LV_particles_variables.SetPxPyPzE  ( px[i] , py[i] , pz[i] , e[i] ) ; 
	
			if ( type[i] == 3 )
			{
				if ( pt[i] > 30. && eta[i] < 1.4 )
				{
					if ( charge[i] == 1 )
					{
						LV_muon_plus.push_back ( LV_particles_variables ) ;	
//						c_m_plus++ ;
					}
	
					if ( charge[i] == -1 )
					{
						LV_muon_minus.push_back ( LV_particles_variables ) ;	
//						c_m_minus++ ;
					}
				}
			}

			else if ( type[i] == 2 )
			{
				if ( pt[i] > 30. && eta[i] < 1.4 )
				{
					if ( charge[i] == 1 )
					{
						LV_electron_plus.push_back ( LV_particles_variables ) ;	
//						c_e_plus++ ;
					}
	
					if ( charge[i] == -1 )
					{
						LV_electron_minus.push_back ( LV_particles_variables ) ;	
//						c_e_minus++ ;
					}
				}
			}


			else
			{
				LV_particles.push_back ( LV_particles_variables ) ;		
			}	


		}

//		if ( (c_m_plus != 1) && (c_m_minus != 1 )  ) 
//		{
//			if ( (c_e_plus != 1) && (c_e_minus != 1 )  ) 
//			{
//			continue;
//			}
//		}

		for ( int i = 0 ; i < int(LV_muon_plus.size() ) ; i++ )
		{
			for ( int j = 0 ; j < int(LV_muon_minus.size() ) ; j++ )
			{
				//isolated
//				Pt_plus = 0. ;
//				Pt_minus = 0. ;
//				for ( int k = 0 ; k < int(LV_particles.size() ) ; k++ )
//				{
//					//If deltaR < 0.3 , pt_all / pt_muon 
//					if ( LV_muon_plus[i].DeltaR(LV_particles[k] ) < 0.3 ) 
//					{
//						Pt_plus += LV_particles[k].Pt() ;
//					}
//					if ( LV_muon_minus[i].DeltaR(LV_particles[k] ) < 0.3 ) 
//					{
//						Pt_minus += LV_particles[k].Pt() ;
//					}
						
//				}
	
//				Pt_plus /=  LV_muon_plus[i].Pt() ;
//				Pt_minus /= LV_muon_minus[j].Pt() ;

//				h3 -> Fill(Pt_plus) ;
//				h3 -> Fill(Pt_minus) ;

//				if ( Pt_plus < 0.2 && Pt_minus < 0.2 )
//				{
					LV_dimuon = LV_muon_plus[i] + LV_muon_minus[j] ;
					s_muon = LV_dimuon.M() ;
					h1 -> Fill(s_muon) ;		 
//				}
			}
		}

		for ( int i = 0 ; i < int(LV_electron_plus.size() ) ; i++ )
		{
			for ( int j = 0 ; j < int(LV_electron_minus.size() ) ; j++ )
			{
				LV_dielectron = LV_electron_plus[i] + LV_electron_minus[j] ;
				s_electron = LV_dielectron.M() ;
				h2 -> Fill(s_electron) ;		 
			}
		}
	}

	in -> Close() ;
	out -> Write() ;
	out -> Close() ;
}	
