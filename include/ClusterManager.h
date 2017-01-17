//
//  ClusterManager.h
//  BoundaryCalculator
//
//  Created by Adam Kohl on 12/12/16.
//  Copyright © 2016 Adam Kohl. All rights reserved.
//

#ifndef ClusterManager_h
#define ClusterManager_h

#include <iostream>

// Local headers
#include "ClusterNodes.h"
#include "BoundaryProcessor.h"
#include "NodeProcessor.h"

class ClusterManager
{
    
public:
    
    ClusterManager();
    
    ~ClusterManager(){};
    
    void import_test_clusters(std::vector<std::map<int, std::pair<std::string, std::vector<float> > > > test, std::vector<int> position);
    
    void set_map_parameters(int row, int col){_numrows = row, _numcols = col;};
    
    void start_clustering_process(void);
    
protected:
    
    std::vector<std::map<int, std::pair<std::string, std::vector<float> > > >    _testclusters;
    
    std::vector<int>    _testposition;
    
    int     _numrows;
    int     _numcols;
};

#endif /* ClusterManager_h */
