#include "analyzer_createobjects.h"

//----------------------------analyzer_createobjects
analyzer_createobjects::analyzer_createobjects()
{
}

//----------------------------~analyzer_createobjects
analyzer_createobjects::~analyzer_createobjects()
{
}


//----------------------------analyzer_createobjects

//-------------------------muon_passID
std::vector<int> analyzer_createobjects::muon_passID( int bitnr, Float_t muPtCut1, Float_t muPtCut2, Float_t muEtaCut, TString sysbinname)
{//------ btnr depricated can we remove?
 std::vector<int> mulist;

 for(int i = 0; i < AOD_muPt->size(); i++)
 {

  Float_t muonPt = getMuonPt(i,sysbinname);
  bool pass_kin = false;
  if( i==0 ) pass_kin = (muonPt > muPtCut1) && ( fabs(AOD_muEta->at(i)) < muEtaCut ) ;
  else       pass_kin = (muonPt > muPtCut2) && ( fabs(AOD_muEta->at(i)) < muEtaCut ) ;

  bool pass_bit = AOD_muPassLooseID->at(i);//------should probably make if/else groups for other ID's

  if (muoid == "Loose")  muoisoval = 0.25 ;
  if (muoid == "Medium") muoisoval = 0.25 ;
  if (muoid == "Tight")  muoisoval = 0.15 ;
  bool pass_iso = AOD_muPFdBetaIsolation->at(i) < muoisoval ;

  if( pass_bit && pass_kin && pass_iso )
  {
   nSelectedMuo++;
   mulist.push_back(i);
  } // if pass_bit && pass_kin && pass_iso
 } // loop over muons
 return mulist;
}

//-------------------------electron_passID
std::vector<int> analyzer_createobjects::electron_passID( int bitnr, Float_t elePtCut1, Float_t elePtCut2, Float_t eleEtaCut, TString sysbinname)
{

 std::vector<int> elelist;
 std::vector<int> elelist_preSort;
 //Get List to Sort
 for(int i = 0; i < nAODEle; i++) {elelist_preSort.push_back(i);} 
 std::sort(elelist_preSort.begin(),elelist_preSort.end(),
          [&]( int a, int b ) { return AOD_elePt->at(a) > AOD_elePt->at(b); });

 //Loop overSortedList
 for(int j = 0; j < elelist_preSort.size(); j++)
 {
 int i = elelist_preSort[j]; 

  Float_t electronPt = getElectronPt(i,sysbinname);

  bool pass_kin = false;
  if( i==0 ) pass_kin =  (electronPt > elePtCut1) && ( fabs(AOD_eleEta->at(i)) < eleEtaCut ) ;
  else       pass_kin =  (electronPt > elePtCut2) && ( fabs(AOD_eleEta->at(i)) < eleEtaCut ) ;

  bool pass_convsersion_veto = (AOD_elePassConversionVeto->at(i) > 0); //could have been bool

  bool pass_bit = AOD_eleIDbit->at(i) >> bitnr & 0x1 == 1;

  bool pass_overlap = true;
  bool pass_crack = (fabs(AOD_eleEta->at(i))<1.442) ||  (fabs(AOD_eleEta->at(i))>1.566);

  if( pass_bit && pass_kin && pass_overlap && pass_convsersion_veto && pass_crack )
  {
   nSelectedEle++;
   elelist.push_back(i);
  } // if pass_bit && pass_kin
 } // loop over electrons

 return elelist;
}


//-------------------------jet_passTagger
std::vector<int> analyzer_createobjects::jet_passTagger( ) {

  std::vector<int> taglist;

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   if( Shifted_CaloJetMedianLog10IPSig.at(aodcalojetindex)      >=  tag_minIPsig  &&
       Shifted_CaloJetMedianLog10TrackAngle.at(aodcalojetindex) >=  tag_minTA     &&
       Shifted_CaloJetAlphaMax.at(aodcalojetindex)              <=  tag_maxAmax   &&
       Shifted_CaloJetAlphaMax.at(aodcalojetindex)              >=  0.0  )
    {
     taglist.push_back(aodcalojetindex);
    }
  }
  return taglist;
}


bool analyzer_createobjects::AL_SG(int i){
  if(Shifted_CaloJetAlphaMax.at(i)<tag_maxAmax) return true;
  else return false;
}

bool analyzer_createobjects::AL_SB(int i){
  if(Shifted_CaloJetAlphaMax.at(i)>tag_maxAmax) return true;
  else return false;
}

bool analyzer_createobjects::AL_SBL(int i){
  if(Shifted_CaloJetAlphaMax.at(i) < 1.0 && Shifted_CaloJetAlphaMax.at(i)>tag_maxAmax) return true;
  else return false;
}

bool analyzer_createobjects::IP_SG(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) > tag_minIPsig) return true;
  else return false;
}

bool analyzer_createobjects::IP_SB(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) < tag_minIPsig) return true;
  else return false;
}

bool analyzer_createobjects::IP_SBa(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) > 0.7 && Shifted_CaloJetMedianLog10IPSig.at(i) < tag_minIPsig) return true;
  else return false;
}

bool analyzer_createobjects::IP_SBb(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) > 0.4 && Shifted_CaloJetMedianLog10IPSig.at(i) < .7) return true;
  else return false;
}

bool analyzer_createobjects::IP_SBc(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) > 0.1 && Shifted_CaloJetMedianLog10IPSig.at(i) < .4) return true;
  else return false;
}

bool analyzer_createobjects::IP_SBL(int i){
  if(Shifted_CaloJetMedianLog10IPSig.at(i) > 0.2 && Shifted_CaloJetMedianLog10IPSig.at(i) < tag_minIPsig) return true;
  else return false;
}

bool analyzer_createobjects::TA_SG(int i){
  if(Shifted_CaloJetMedianLog10TrackAngle.at(i) > tag_minTA) return true;
  else return false;
}

bool analyzer_createobjects::TA_SB(int i){
  if(Shifted_CaloJetMedianLog10TrackAngle.at(i) < tag_minTA) return true;
  else return false;
}

bool analyzer_createobjects::TA_SBL(int i){
  if(Shifted_CaloJetMedianLog10TrackAngle.at(i) > -2.4 && Shifted_CaloJetMedianLog10TrackAngle.at(i) < tag_minTA) return true;
  else return false;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB1( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SG(j) && TA_SB(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB2( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SB(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB3( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SB(j) && TA_SB(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB4( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SB(j) && IP_SG(j) && TA_SB(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB5( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SB(j) && IP_SB(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB6( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SB(j) && IP_SB(j) && TA_SB(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB7( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SB(j) && IP_SG(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL1( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SG(j) && TA_SBL(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL2( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SBL(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL3( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SBL(j) && TA_SBL(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL4( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SBL(j) && IP_SG(j) && TA_SBL(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL5( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SBL(j) && IP_SBL(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL6( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SBL(j) && IP_SBL(j) && TA_SBL(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBL7( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SBL(j) && IP_SG(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB2a( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SBa(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB2b( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SBb(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSB2c( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( AL_SG(j) && IP_SBc(j) && TA_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerIP( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( IP_SG(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBIPa( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( IP_SBa(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBIPb( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( IP_SBb(j) ) taglist.push_back(j);
  }
  return taglist;
}

std::vector<int> analyzer_createobjects::jet_passTaggerSBIPc( ) {
  std::vector<int> taglist;
  for(int i=0; i<aodcalojet_list.size(); ++i){
    int j = aodcalojet_list[i];
    if( IP_SBc(j) ) taglist.push_back(j);
  }
  return taglist;
}



std::vector<int> analyzer_createobjects::jet_passTagger_L1PF( ) {

  std::vector<int> taglist;

  for(int i=0; i<aodcalojet_L1PF_list.size(); ++i){
   int aodcalojetindex = aodcalojet_L1PF_list[i];
   if( Shifted_CaloJetMedianLog10IPSig.at(aodcalojetindex)      >  tag_minIPsig  &&
       Shifted_CaloJetMedianLog10TrackAngle.at(aodcalojetindex) >  tag_minTA     &&
       Shifted_CaloJetAlphaMax.at(aodcalojetindex)              <  tag_maxAmax  )
    {
     taglist.push_back(aodcalojetindex);
    }
  }
  if(aodcalojet_L1PF_list.size()>0) return taglist;
  else {taglist.push_back(-1);      return taglist;}
}

//-------------------------jet_minDR
// Finds Delta R of closest "good" jet
std::vector<float> analyzer_createobjects::jet_minDR( ) {

  std::vector<float> minDR_list;

  for(int i = 0; i < AODnCaloJet; i++){//all jets

    float min_dR = -1;

    for(int j=0; j<aodcalojet_list.size(); ++j){//good jets

      if(i == aodcalojet_list[j]) continue;//don't allow check with itself

      float my_dR = dR(AODCaloJetEta->at(i), AODCaloJetPhi->at(i), AODCaloJetEta->at(aodcalojet_list[j]), AODCaloJetPhi->at(aodcalojet_list[j]));
      if(my_dR < min_dR || min_dR<0){
	min_dR = my_dR;
      }

    }//j
    minDR_list.push_back(min_dR);
  }//i

  return minDR_list;
}


//-------------------------jet_passID
std::vector<int> analyzer_createobjects::jet_passID( int bitnr, TString jettype, Float_t jetPtCut, Float_t jetEtaCut, TString sysbinname ) {

  std::vector<int> jetlist;

  // set parameters based on jet collection
  int njets = AODnCaloJet;
  bool  passID;
  float jetpt;
  float jeteta;
  float jetphi;
  //float emEnergyFrac;
  //float hadEnergyFrac;
  //bool  ID;
  for(int i = 0; i < njets; i++)
  {
   jetpt  = AODCaloJetPt ->at(i);
   jeteta = AODCaloJetEta->at(i);
   jetphi = AODCaloJetPhi->at(i);
   passID = AODCaloJetID ->at(i);

   //emEnergyFrac  = AODCaloJet_emEnergyFraction       ->at(i);
   //hadEnergyFrac = AODCaloJet_energyFractionHadronic ->at(i);
   //ID = false;
   //if( emEnergyFrac  <=0.9
   // && emEnergyFrac  >=0.0
   // && hadEnergyFrac <=0.9
   // && hadEnergyFrac >=0.0
   // )   ID  = true;
  
   //if(ID!=passID) std::cout<< "Event: "<<event<<"   ,ID: "<<ID<<"   , passID: "<<passID<<"    ,njets: "<<njets <<std::endl;
   if(!passID) continue;
   bool pass_overlap = true;
   //check overlap with electrons
   if(electron_list.size()>0){
    for(int d=0; d<electron_list.size(); ++d){
     int eleindex = electron_list[d];
     if( dR( AOD_eleEta->at(eleindex), AOD_elePhi->at(eleindex), jeteta, jetphi ) < objcleandRcut )
     {
      pass_overlap=false; // printf(" OL w electron\n");
     } // if overlap
    }//end electrons
   } // if electrons
   //check overlap with muons
   if(muon_list.size()>0){
    for(int d=0; d<muon_list.size(); ++d){
     int muindex = muon_list[d];
     if(muindex<= (AOD_muEta->size()-1)&&muindex<= (AOD_muPhi->size()-1)){
      if( dR( AOD_muEta->at(muindex),AOD_muPhi->at(muindex), jeteta, jetphi ) < objcleandRcut )
      {
       pass_overlap=false; //printf(" OL w muon\n");
      } // if overlap     }
     }
    }//end muons
   } // if muons

   bool pass_kin = jetpt > jetPtCut && ( fabs(jeteta) < jetEtaCut ) ;
   bool HEMFailure = false; //part of the HEM failure of 2018
   if( ( jetphi >= -1.57 && jetphi <= -0.87 ) && ( jeteta <= -1.3 && jeteta >= -3.0 ) ) HEMFailure=true;
   if( pass_kin && pass_overlap && passID /*&& !HEMFailure*/ )
   {
    jetlist.push_back(i);
   } // if pass_bit && pass_kin
  }// for(int i = 0; i < nJet; i++)

  return jetlist;

}

//-------------------------dR
double analyzer_createobjects::dR(double eta1, double phi1, double eta2, double phi2)
{
  double deltaeta = abs(eta1 - eta2);
  double deltaphi = DeltaPhi(phi1, phi2);
  double deltar = sqrt(deltaeta*deltaeta + deltaphi*deltaphi);
  return deltar;
}

//-------------------------DeltaPhi
double analyzer_createobjects::DeltaPhi(double phi1, double phi2)
//Gives the (minimum) separation in phi between the specified phi values
//Must return a positive value
{
  double pi = TMath::Pi();
  double dphi = fabs(phi1-phi2);
  if(dphi>pi)
    dphi = 2.0*pi - dphi;
  return dphi;
}

//-------------------------getMuonPt
Float_t analyzer_createobjects::getMuonPt(int i, TString sysbinname){

  if(!isMC){ return AOD_muPt->at(i); }
  else{
    //Muon passes pt cut
    Float_t muonPt = AOD_muPt->at(i);
    Float_t muonEnergy = muonPt*TMath::CosH( AOD_muEta->at(i) );
    if(sysbinname=="_MESUp" )
	{
	if(fabs(AOD_muEta->at(i)<2.1)) {muonEnergy*=(1.0 + 0.003); }
	else	{ muonEnergy*=(1.0 + 0.010); }
	}
    if(sysbinname=="_MESDown")
	{
	if(fabs(AOD_muEta->at(i)<2.1))	{ muonEnergy*=(1.0 - 0.003); }
	else	{ muonEnergy*=(1.0 - 0.010); }
	}
    muonPt = muonEnergy/TMath::CosH( AOD_muEta->at(i) );
    return muonPt;
  }
}

//-------------------------getElectronPt
Float_t analyzer_createobjects::getElectronPt(int i, TString sysbinname){

  if(!isMC){ return AOD_elePt->at(i); }
  else{
    //Electron passes pt cut
    Float_t electronPt = AOD_elePt->at(i);
    Float_t electronEnergy = electronPt*TMath::CosH( AOD_eleEta->at(i) );
    if(sysbinname=="_EGSUp"  ){ electronEnergy*=(1.0 + 0.020); }
    if(sysbinname=="_EGSDown"){ electronEnergy*=(1.0 - 0.020); }

    electronPt = electronEnergy/TMath::CosH( AOD_eleEta->at(i) );
    return electronPt;
  }
}

//-------------------------calculateHT
void analyzer_createobjects::calculateHT(){
  // calculate ht
  htall  = 0.;
  htaodcalojets = 0.;

  for(int i=0; i<electron_list.size(); ++i){
   int eleindex = electron_list[i];
   htall += Shifted_elePt.at(eleindex);
  }

  for(int i=0; i<muon_list.size(); ++i){
   int muindex = muon_list[i];
   htall += Shifted_muPt.at(muindex);
  }

  for(int i=0; i<aodcalojet_list.size(); ++i){
   int aodcalojetindex = aodcalojet_list[i];
   htall  += AODCaloJetPt->at(aodcalojetindex);
   htaodcalojets += AODCaloJetPt->at(aodcalojetindex);
  }

  return;
}


//-------------------------makeDiLepton
void analyzer_createobjects::makeDiLepton(){

  // make dilepton pair
  fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  fourVec_l2.SetPtEtaPhiE(0,0,0,0);

  // get electrons and muons and put into 4vectors
  makeDilep(&fourVec_l1, &fourVec_l2, &fourVec_ee, &fourVec_mm);
  // make dilepton object
  fourVec_ll = fourVec_l1 + fourVec_l2;
  dilep_mass = fourVec_ll.M();
  dilep_pt   = fourVec_ll.Pt();

  // So it looks like these are only used for this calculation, so I will recycle for OSOF
  fourVec_l1.SetPtEtaPhiE(0,0,0,0);
  fourVec_l2.SetPtEtaPhiE(0,0,0,0);

  makeDilep(&fourVec_l1, &fourVec_l2, &fourVec_em);
  OSOF_mass = fourVec_em.M();
  OSOF_pt   = fourVec_em.Pt();

}

void analyzer_createobjects::makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_em)
{
  TLorentzVector e, m;
  e.SetPtEtaPhiE( 0,0,0,0 );
  m.SetPtEtaPhiE( 0,0,0,0 );

  // Require exactly 1 electron and 1 muon
  if ( !( (electron_list.size()==1 && muon_list.size()==1) ) ) return;

  //Set the electron and muon fourvectors if they have opposite sign otherwise we will use the dummy vectors.
  if(AOD_eleCharge->at(electron_list[0])*AOD_muCharge->at(muon_list[0])==-1)
  {
    e.SetPtEtaPhiE( Shifted_elePt.at(electron_list[0]), AOD_eleEta->at(electron_list[0]), AOD_elePhi->at(electron_list[0]), AOD_eleEn->at(electron_list[0]) );
    m.SetPtEtaPhiE( Shifted_muPt.at(    muon_list[0]), AOD_muEta ->at(    muon_list[0]), AOD_muPhi ->at(    muon_list[0]), AOD_muEn ->at(    muon_list[0]) );
  }

  *fv_1  = e;
  *fv_2  = m;
  *fv_em = e+m;
  return;
}

//-------------------------makeDilep
void analyzer_createobjects::makeDilep(TLorentzVector *fv_1, TLorentzVector *fv_2, TLorentzVector *fv_ee, TLorentzVector *fv_mm)
{

  TLorentzVector e1, e2, ee;
  TLorentzVector m1, m2, mm;
  e1.SetPtEtaPhiE( 0,0,0,0 );
  e2.SetPtEtaPhiE( 0,0,0,0 );
  m1.SetPtEtaPhiE( 0,0,0,0 );
  m2.SetPtEtaPhiE( 0,0,0,0 );

  // Require exactly 2 electrons and no muons xor exactly 2 muons and no electrons
  if ( !( (electron_list.size()==2 && muon_list.size()==0) || (electron_list.size()==0 && muon_list.size()==2) ) ) return;

  //The following code selects the OSSF pair with mass closest to Z mass.
  //Previous cut on electron_list and muon_list sizes means there is at max one pair, so no real choice
  //But we leave this code as is in case we want to use this feature at some point.  It works for the simple case, too.

   // electrons
   double best_ee_mass = 9e9;
   if( electron_list.size()>1 ){
     for(int i=0; i<electron_list.size(); ++i)
       {
         for(int j=i+1; j<electron_list.size(); ++j)
           {
             if( AOD_eleCharge->at(electron_list[i])*AOD_eleCharge->at(electron_list[j])==-1 )
       	{
       	  TLorentzVector temp1, temp2, temp12;
       	  temp1.SetPtEtaPhiE( Shifted_elePt.at(electron_list[i]), AOD_eleEta->at(electron_list[i]), AOD_elePhi->at(electron_list[i]), AOD_eleEn->at(electron_list[i]) );
       	  temp2.SetPtEtaPhiE( Shifted_elePt.at(electron_list[j]), AOD_eleEta->at(electron_list[j]), AOD_elePhi->at(electron_list[j]), AOD_eleEn->at(electron_list[j]) );
       	  temp12 = temp1+temp2;
       	  if( fabs(91.1876-temp12.M()) < fabs(91.1876 - best_ee_mass) ){
       	    best_ee_mass = temp12.M();
            e1.SetPtEtaPhiE( Shifted_elePt.at(electron_list[i]), AOD_eleEta->at(electron_list[i]), AOD_elePhi->at(electron_list[i]), AOD_eleEn->at(electron_list[i]) );
            e2.SetPtEtaPhiE( Shifted_elePt.at(electron_list[j]), AOD_eleEta->at(electron_list[j]), AOD_elePhi->at(electron_list[j]), AOD_eleEn->at(electron_list[j]) );
       	  }
       	}
           }
       }
     ee = e1 + e2;
   }//electron size > 1

   // muons
   double best_mm_mass = 9e9;
   int best_mm_i=-1, best_mm_j=-1;
   if( muon_list.size()>1 ){
     for(int i=0; i<muon_list.size(); ++i)
       {
         for(int j=i+1; j<muon_list.size(); ++j)
           {
             if( AOD_muCharge->at(muon_list[i])*AOD_muCharge->at(muon_list[j])==-1 )
       	{
       	  TLorentzVector temp1, temp2, temp12;
       	  temp1.SetPtEtaPhiE( Shifted_muPt.at(muon_list[i]), AOD_muEta->at(muon_list[i]), AOD_muPhi->at(muon_list[i]), AOD_muEn->at(muon_list[i]) );
       	  temp2.SetPtEtaPhiE( Shifted_muPt.at(muon_list[j]), AOD_muEta->at(muon_list[j]), AOD_muPhi->at(muon_list[j]), AOD_muEn->at(muon_list[j]) );
       	  temp12 = temp1+temp2;
       	  if( fabs(91.1876-temp12.M()) < fabs(91.1876 - best_mm_mass) ){
       	    best_mm_mass = temp12.M();
            m1.SetPtEtaPhiE( Shifted_muPt.at(muon_list[i]), AOD_muEta->at(muon_list[i]), AOD_muPhi->at(muon_list[i]), AOD_muEn->at(muon_list[i]) );
            m2.SetPtEtaPhiE( Shifted_muPt.at(muon_list[j]), AOD_muEta->at(muon_list[j]), AOD_muPhi->at(muon_list[j]), AOD_muEn->at(muon_list[j]) );
       	  }
       	}
           }
       }
     mm = m1 + m2;
   }//muon size > 1

   *fv_ee = ee;
   *fv_mm = mm;

   // take pair closest to Z mass
   if( fabs(91.1876-ee.M()) < fabs(91.1876-mm.M()) ){
     *fv_1 = e1;
     *fv_2 = e2;
   }
   else{
     *fv_1 = m1;
     *fv_2 = m2;
   }

   return;

}

void analyzer_createobjects::shiftCollections( TString uncbin )
{

  Shifted_elePt                       .clear();
  Shifted_muPt                        .clear();
  Shifted_CaloJetPt                   .clear();
  Shifted_CaloJetAlphaMax             .clear();
  Shifted_CaloJetMedianLog10IPSig     .clear();
  Shifted_CaloJetMedianLog10TrackAngle.clear();

  //Objects: do shift inside get function
  for(unsigned int i=0; i<AOD_elePt->size(); ++i){
    Shifted_elePt.push_back( getElectronPt(i,uncbin) );
  }
  for(unsigned int i=0; i<AOD_muPt->size(); ++i){
    Shifted_muPt.push_back( getMuonPt(i,uncbin) );
  }
  for(unsigned int i=0; i<AODCaloJetPt->size(); ++i){
    Shifted_CaloJetPt.push_back( AODCaloJetPt->at(i));//no correction yet
  }

  ///////////////
  //  Tag Vars
  ///////////////

  for(unsigned int i=0; i<AODCaloJetAlphaMax->size(); ++i){
    Shifted_CaloJetAlphaMax.push_back( AODCaloJetAlphaMax->at(i));
  }
  for(unsigned int i=0; i<AODCaloJetMedianLog10IPSig->size(); ++i){
    Shifted_CaloJetMedianLog10IPSig.push_back( AODCaloJetMedianLog10IPSig->at(i));
  }
  for(unsigned int i=0; i<AODCaloJetMedianLog10TrackAngle->size(); ++i){
    Shifted_CaloJetMedianLog10TrackAngle.push_back( AODCaloJetMedianLog10TrackAngle->at(i));
  }


  if(isMC){

    float deltaAmax  = ( tag_maxAmax  / tag_shiftmaxAmax  ) - 1.    ;
    float deltaIPsig = ( tag_minIPsig / tag_shiftminIPsig ) - 1.  ;
    float deltaTA    = ( tag_minTA    / tag_shiftminTA    ) - 1.        ;
    // shift tagging variable central value for "unshifted"
    // then _Down is unshifted and _Up is shifted 2x

    // unshifted
    if( ! (
	   uncbin.Contains("TagVars") ||
	   uncbin.Contains("AMax")    ||
	   uncbin.Contains("IPSig")   ||
	   uncbin.Contains("TA")
	   )  ){
      for(unsigned int i=0; i<Shifted_CaloJetAlphaMax.size(); ++i){
	Shifted_CaloJetAlphaMax.at(i) = Shifted_CaloJetAlphaMax.at(i) * (1+deltaAmax) ;
	Shifted_CaloJetMedianLog10IPSig.at(i) = Shifted_CaloJetMedianLog10IPSig.at(i) * (1+deltaIPsig) ;
	Shifted_CaloJetMedianLog10TrackAngle.at(i) = Shifted_CaloJetMedianLog10TrackAngle.at(i) * (1+deltaTA) ;
      }
    }

    // AlphaMax
    for(unsigned int i=0; i<Shifted_CaloJetAlphaMax.size(); ++i){
      if(uncbin.Contains("AMaxUp")||uncbin.Contains("TagVarsUp")){
	Shifted_CaloJetAlphaMax.at(i) = Shifted_CaloJetAlphaMax.at(i) * (1+2*deltaAmax) ;
      }
      if(uncbin.Contains("TA")||uncbin.Contains("IPSig")){
	Shifted_CaloJetAlphaMax.at(i) = Shifted_CaloJetAlphaMax.at(i) * (1+deltaAmax) ;
      }
    }
    // IPSig
    for(unsigned int i=0; i<Shifted_CaloJetMedianLog10IPSig.size(); ++i){
      if(uncbin.Contains("IPSigUp")||uncbin.Contains("TagVarsUp")){
	Shifted_CaloJetMedianLog10IPSig.at(i) = Shifted_CaloJetMedianLog10IPSig.at(i) * (1+2*deltaIPsig) ;
      }
      if(uncbin.Contains("TA")||uncbin.Contains("AMax")){
	Shifted_CaloJetMedianLog10IPSig.at(i) = Shifted_CaloJetMedianLog10IPSig.at(i) * (1+deltaIPsig) ;
      }
    }
    // TA
    for(unsigned int i=0; i<Shifted_CaloJetMedianLog10TrackAngle.size(); ++i){
      if(uncbin.Contains("TAUp")||uncbin.Contains("TagVarsUp")){
	Shifted_CaloJetMedianLog10TrackAngle.at(i) = Shifted_CaloJetMedianLog10TrackAngle.at(i) * (1+2*deltaTA) ;
      }
      if(uncbin.Contains("AMax")||uncbin.Contains("IPSig")){
	Shifted_CaloJetMedianLog10TrackAngle.at(i) = Shifted_CaloJetMedianLog10TrackAngle.at(i) * (1+deltaTA) ;
      }
    }
  }

  return;

}
