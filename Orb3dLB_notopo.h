/**
 * \addtogroup CkLdb
*/
/*@{*/

#ifndef _ORB3DLB_NOTOPO_H_
#define _ORB3DLB_NOTOPO_H_

#include "CentralLB.h"
#include "MapStructures.h"
#include "Orb3dLB_notopo.decl.h"
#include "TaggedVector3D.h"
#include <queue>

void CreateOrb3dLB_notopo();
BaseLB * AllocateOrb3dLB_notopo();

class Orb3dLB_notopo : public CentralLB {
private:
  // pointer to stats->to_proc
  CkVec<int> *mapping;

  CkVec<OrbObject> tps;
  CkVec<float> procload;
  CkVec<OrientedBox<float> > procbox;

  // things are stored in here before work
  // is ever called.
  TaggedVector3D *tpCentroids;
  CkReductionMsg *tpmsg;
  int nrecvd;
  bool haveTPCentroids;

  int nextProc;

  CmiBool QueryBalanceNow(int step);
  void printData(BaseLB::LDStats &stats, int phase, int *revObjMap);

  void orbPartition(CkVec<Event> *events, OrientedBox<float> &box, int procs);
  int partitionRatioLoad(CkVec<Event> &events, float ratio);

public:
  Orb3dLB_notopo(const CkLBOptions &);
  Orb3dLB_notopo(CkMigrateMessage *m):CentralLB(m) { lbname = "Orb3dLB_notopo"; }
  void work(BaseLB::LDStats* stats);
  void receiveCentroids(CkReductionMsg *msg);

};

#endif /* _Orb3dLB_notopo_H_ */

/*@}*/