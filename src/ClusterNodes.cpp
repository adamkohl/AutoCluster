//
//  ClusterNodes.cpp
//  BoundaryCalculator
//
//  Created by Adam Kohl on 12/12/16.
//  Copyright © 2016 Adam Kohl. All rights reserved.
//

// Local includes
#include "ClusterNodes.h"

// Standard includes
#include <iterator> 


void ClusterNodes::addNewClusterNode(std::map<int, std::pair<std::string, std::vector<float> > > new_pts, int node_num, int map_pos)
{
    Cluster new_cluster;
    new_cluster.nodeID = node_num;
    new_cluster.all_positions.push_back(map_pos);
    
    // populate new points into storage
    std::map<int, std::pair<std::string, std::vector<float> > >::iterator it;
    
    for (it = new_pts.begin(); it != new_pts.end(); ++it)
    {
        new_cluster.pts[it->first] = std::pair<std::string, std::vector<float> >(it->second.first, it->second.second);
    }

    //  Calculate cluster's basic attributes
    new_cluster.numpts = new_pts.size();
    new_cluster.compmean = _calculator->component_mean(new_cluster.pts);
    new_cluster.compstd = _calculator->component_std(new_cluster.pts);
    _clusters.push_back(new_cluster);
}

void ClusterNodes::process_cluster_relations(void)
{
    calcPairPoints();
    calcAvgStd();
    calcIntraDensity();
    calcSeperationRate();
}

void ClusterNodes::calcPairPoints(void)
{
    for (int i=0; i < _clusters.size(); i++)
    {
        std::map<int, std::pair<std::vector<float>, std::vector<float> > > pptemp;
        
        for (int j=0; j < _clusters.size(); j++)
        {
            if (i != j)
            {
                std::pair<int, int> minpair = _calculator->min_pairpoint_dist(_clusters[i].pts, _clusters[j].pts);
                pptemp[_clusters[j].nodeID].first = _clusters[i].pts[minpair.first].second;
                pptemp[_clusters[j].nodeID].second = _clusters[j].pts[minpair.second].second;
            }
            else
                continue;
        }
        
        _clusters[i].pairpts = pptemp;
    }
}

void ClusterNodes::calcAvgStd(void)
{
    std::vector<std::vector<float> > allstd;
    
    for (std::vector<Cluster>::iterator it = _clusters.begin(); it != _clusters.end(); ++it)
    {
        allstd.push_back(it->compstd);
    }
    
    float std = _calculator->avg_std(allstd);
    
    for (std::vector<Cluster>::iterator it = _clusters.begin(); it != _clusters.end(); ++it)
    {
        it->avgstd = std;
    }
}

void ClusterNodes::calcIntraDensity(void)
{
    for (std::vector<Cluster>::iterator it = _clusters.begin(); it != _clusters.end(); ++it)
    {
        it->intra_density = _calculator->intracluster_density(it->pts, it->avgstd);
        
    }
}

void ClusterNodes::calcSeperationRate(void)
{
    
    // Iterate through all clusters
    for (std::vector<Cluster>::iterator it = _clusters.begin(); it != _clusters.end(); ++it)
    {
        std::vector<float> intervec;

        // Iterate through all the pair points within the cluster
        std::map<int, std::pair<std::vector<float>, std::vector<float> > >::iterator iter;
        for (iter = it->pairpts.begin(); iter != it->pairpts.end(); ++iter)
        {
            // Find cluster standard deviation for the pair point's cluster
            for (std::vector<Cluster>::iterator it2 = _clusters.begin(); it2 != _clusters.end(); ++it2)
            {
                if (it2->nodeID == iter->first)
                {
                    intervec.push_back(_calculator->intercluster_density(iter->second.first, iter->second.second, it->compstd, it2->compstd, it->avgstd));

                }
                else
                    continue;
            }
        
            std::cout<< "stop:" << std::endl;

        }
        
    }
}



