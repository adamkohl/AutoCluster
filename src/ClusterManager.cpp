//
//  ClusterManager.cpp
//  BoundaryCalculator
//
//  Created by Adam Kohl on 12/12/16.
//  Copyright © 2016 Adam Kohl. All rights reserved.
//

#include "ClusterManager.h"

ClusterManager::ClusterManager()
{
    std::cout<<"Constructing cluster manager \n";
}

void ClusterManager::import_test_clusters(std::vector<std::map<int, std::pair<std::string, std::vector<float> > > > test, std::vector<int> position)
{
    _testclusters = test;
    _testposition = position;
}

void ClusterManager::start_clustering_process(void)
{
    ClusterNodes cluster;
    
    std::vector<std::map<int, std::pair<std::string, std::vector<float> > > >::iterator it;
    
    for (int i=0; i < _testclusters.size(); i++)
    {
        cluster.addNewClusterNode(_testclusters[i], _testposition[i], _testposition[i]);
    }
    
    cluster.process_cluster_relations(); 
}
