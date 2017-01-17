//
//  ClusterNodes.h
//  BoundaryCalculator
//
//  Created by Adam Kohl on 12/12/16.
//  Copyright © 2016 Adam Kohl. All rights reserved.
//

#ifndef ClusterNodes_h
#define ClusterNodes_h

// Local includes
#include "NodeCalculations.h"

// Standard includes
#include <vector> 
#include <string>
#include <map>


struct Cluster
{
    // <neighbor cluster #, value>
    std::map<int, float>    sep_rate;
    std::map<int, float>    neigh_cdbw;
    
    // <neighbor node #, current cluster pt vector, neighbor cluster pt vector>
    std::map<int, std::pair<std::vector<float>, std::vector<float> > >    pairpts;
    
    // <sample pt reference, class identifier, point value>
    std::map<int, std::pair<std::string, std::vector<float> > >    pts;
    
    std::vector<float>      compstd;
    std::vector<float>      compmean;
    std::vector<float>      all_positions;
    
    float      intra_density;
    float      inter_density;
    float      avgstd;
    float      numpts;
    
    int        nodeID;
    
};


class ClusterNodes
{
    
public:
    
    ClusterNodes(){};
    
    ~ClusterNodes(){};
    
    void addNewClusterNode(std::map<int, std::pair<std::string, std::vector<float> > > new_pts, int pos, int map_pos);
    
    void addExistingCluster(Cluster new_cluster){ _clusters.push_back(new_cluster);};
    
    void process_cluster_relations(void);
    
    void calcPairPoints(void);
    
    void calcAvgStd(void);
    
    void calcIntraDensity(void);
    
    void calcSeperationRate(void);

    void setNodeNeighbors(void);
    
    const std::vector<Cluster>& clusters() const { return _clusters; }
    
protected:
    
    NodeCalculator*     _calculator;
    
    std::vector<Cluster>      _clusters;
};

#endif /* ClusterNodes_h */
