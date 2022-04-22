#ifndef _CRD_CALOHIT_LONGICLUS_H
#define _CRD_CALOHIT_LONGICLUS_H
#include <vector>
#include <map>
#include "Objects/CRDCaloBarShower.h"
#include "Objects/TrackFitInEcal.h"
#include "TVector3.h"

namespace CRDEcalEDM{

  class CRDCaloHitLongiCluster{
  public: 	
    CRDCaloHitLongiCluster(){};
    ~CRDCaloHitLongiCluster(){};

  void Clear() { axis.SetXYZ(0.,0.,0.); barShowerCol.clear(); }
  inline bool operator == (const CRDCaloHitLongiCluster &x) const{
    return barShowerCol == x.barShowerCol;
  }  

  TVector3 getPos() const; 
  TVector3 getAxis() { FitAxis(); return axis; }
  double getE() const; 
  int getSlayer() const; 
  std::vector<CRDEcalEDM::CRDCaloBarShower> getBarShowers() const { return barShowerCol; }
  std::vector<CRDEcalEDM::CRDCaloBarShower> getBarShowersInLayer(int _layer) const; 
  double getHoughAlpha() const { return Hough_alpha; }
  double getHoughRho() const { return Hough_rho; }
  double getHoughIntercept() const { return Hough_intercept; }
  double getFitTrkDr() { FitAxis(); return trk_dr; }
  double getFitTrkDz() { FitAxis(); return trk_dz; }

  int getBeginningDlayer() const; 
  int getEndDlayer() const; 
  TVector3 getExpPos(int& dlayer) const; 
  bool isContinue() const; 
  bool isContinueN(int n) const; 
  bool isSubset( CRDCaloHitLongiCluster& clus) const; 
  double OverlapRatioE( CRDCaloHitLongiCluster& clus ) const;

  void FitAxis(); 
  void AddBarShower( CRDEcalEDM::CRDCaloBarShower _shower ) { barShowerCol.push_back(_shower); FitAxis(); }
  void SortBarShowersByLayer() { std::sort(barShowerCol.begin(), barShowerCol.end(), compLayer); }
  void SetBarShowers( std::vector<CRDEcalEDM::CRDCaloBarShower> _barshwoers ) { barShowerCol = _barshwoers; }
  void SetHoughPars(double _a, double _r) { Hough_alpha=_a; Hough_rho=_r; }
  void SetIntercept(double _in) { Hough_intercept=_in; }
  void MergeCluster( CRDCaloHitLongiCluster& clus ); 
  void RemoveShowers( std::vector<CRDEcalEDM::CRDCaloBarShower>& _showers ); 

  private:
    TVector3 axis; 
    double trk_dr; 
    double trk_dz;
    double Hough_alpha;
    double Hough_rho;
    double Hough_intercept;
    std::vector<CRDEcalEDM::CRDCaloBarShower> barShowerCol;
    TrackFitInEcal* track = new TrackFitInEcal();

    static bool compLayer( CRDEcalEDM::CRDCaloBarShower& hit1, CRDEcalEDM::CRDCaloBarShower& hit2 ) 
      { return hit1.getDlayer() < hit2.getDlayer(); }

  };


};
#endif
