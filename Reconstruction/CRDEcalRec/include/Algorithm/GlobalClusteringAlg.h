#ifndef GLOBALCLUSTERING_ALG_H
#define GLOBALCLUSTERING_ALG_H

#include "Tools/Algorithm.h"

using namespace PandoraPlus;

class GlobalClusteringAlg : public PandoraPlus::Algorithm{
public: 

  GlobalClusteringAlg(){};
  ~GlobalClusteringAlg(){};
 
  class Factory : public PandoraPlus::AlgorithmFactory
  {
  public:
    PandoraPlus::Algorithm* CreateAlgorithm() const{ return new GlobalClusteringAlg(); }
 
  };
 
  StatusCode ReadSettings(PandoraPlus::Settings& m_settings); 
  StatusCode Initialize();
  StatusCode RunAlgorithm( PandoraPlusDataCol& m_datacol );
  StatusCode ClearAlgorithm();

  template<typename T1, typename T2> StatusCode Clustering(std::vector<T1*>& m_input, std::vector<T2*>& m_output);
  bool ifAdjacent(PandoraPlus::CaloBar* m_uncluster, PandoraPlus::Calo1DCluster* m_1dcluster);
  bool ifAdjacent(PandoraPlus::Calo1DCluster* m_1dcluster, PandoraPlus::Calo2DCluster* m_2dcluster);
  bool ifAdjacent(PandoraPlus::Calo2DCluster* m_2dcluster, PandoraPlus::Calo3DCluster* m_3dcluster);
  template<typename T1, typename T2> bool ifSameTower(T1* m_uncluster, T2* m_incluster);
  bool ifModuleAdjacent(const PandoraPlus::CaloBar* bar_2d, const PandoraPlus::CaloBar* bar_3d);
  StatusCode Towering(std::vector<PandoraPlus::Calo3DCluster*>& m_3dcluster,std::vector<PandoraPlus::CaloTower*>& m_tower);
  bool ifAdjacent(PandoraPlus::CaloBar &bob, PandoraPlus::CaloBar &alice);
  //geometry construction
/*   int m_module = settings.map_intPars["m_module"];
  int m_modulestart = settings.map_intPars["m_modulestart"];
  int m_part = settings.map_intPars["m_part"];
  int m_stave = settings.map_intPars["m_stave"];
  int m_superlayer = settings.map_intPars["m_superlayer"];
  int m_startnumber = settings.map_intPars["m_startnumber"];
  int m_phibarnumber = settings.map_intPars["m_phibarnumber"];
  int m_zbarnumber = settings.map_intPars["m_zbarnumber"]; */

private:

  static const int m_module = 7;
  static const int m_modulestart = 0;
  static const int m_part = 4;
  static const int m_stave = 11;
  static const int m_superlayer = 14;
  static const int m_startnumber = 1;
  static const int m_phibarnumber = 60;
  static const int m_zbarnumber = 47;
  
};
#endif
