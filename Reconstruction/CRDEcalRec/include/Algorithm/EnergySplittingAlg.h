#ifndef _ENERGYSPLITTING_ALG_H
#define _ENERGYSPLITTING_ALG_H

#include "PandoraPlusDataCol.h"

#include "TVector3.h"
#include "TVector.h"
#include "TMatrix.h"

using namespace CRDEcalEDM;

class EnergySplittingAlg {
public: 

  class Settings {
  public: 
    Settings() {};
    void SetInitialValue();
    void SetDebug(int _debug) { Debug=_debug; }

    //int th_GoodLayer;
    //double th_intercept; 
    double Eth_SeedAbs;
    double th_split;
    int    Debug;
  };

  EnergySplittingAlg(){};
  ~EnergySplittingAlg(){};

  StatusCode Initialize();
  StatusCode RunAlgorithm( EnergySplittingAlg::Settings& m_settings, PandoraPlusDataCol& m_datacol);
  StatusCode ClearAlgorithm(); 

  StatusCode LongiClusterLinking( std::vector<CRDEcalEDM::CRDCaloBlock>& m_blocks, std::vector<CRDEcalEDM::CRDCaloHitLongiCluster>& m_oldClusCol, std::vector<CRDEcalEDM::CRDCaloHitLongiCluster>& m_outClusCol );

  StatusCode Clustering( std::vector<CRDEcalEDM::CRDCaloBar>& barCol, std::vector<CRDEcalEDM::CRDCaloBarCluster>& outClus, std::vector<CRDEcalEDM::CRDCaloHitLongiCluster>& m_longiClusCol );

  StatusCode Clustering( std::vector<CRDEcalEDM::CRDCaloBar>& barCol, std::vector<CRDEcalEDM::CRDCaloBarCluster>& outClus );

  StatusCode ClusterSplitting( CRDEcalEDM::CRDCaloBarCluster& m_cluster, std::vector<CRDEcalEDM::CRDCaloBarShower>& outshCol );

  StatusCode MergeToClosestCluster( CRDEcalEDM::CRDCaloBarCluster& iclus, std::vector<CRDEcalEDM::CRDCaloBarCluster>& clusvec );

  StatusCode MergeToClosestCluster( CRDEcalEDM::CRDCaloBarShower& m_shower, std::vector<CRDEcalEDM::CRDCaloHitLongiCluster>& m_clusters );

  StatusCode findSeeds( CRDEcalEDM::CRDCaloBarCluster& m_cluster, std::vector<CRDEcalEDM::CRDCaloBar>& seedCol );

  std::vector<CRDEcalEDM::CRDCaloBar>  getNeighbors(CRDEcalEDM::CRDCaloBarCluster& m_cluster, CRDEcalEDM::CRDCaloBar& seed); 

  void CalculateInitialEseed( const std::vector<CRDEcalEDM::CRDCaloBar>& Seeds, const dd4hep::Position* pos, double* Eseed);

  double GetShowerProfile(const dd4hep::Position& p_bar, const dd4hep::Position& p_seed );

  Settings settings;

private: 

};


#endif
