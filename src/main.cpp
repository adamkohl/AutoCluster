//
//  main.cpp
//  BoundaryCalculator
//
//  Created by Adam Kohl on 12/12/16.
//  Copyright © 2016 Adam Kohl. All rights reserved.
//

#include <iostream>

//  Local Includes
#include "ClusterManager.h"
#include "InputParser.h"

int main(int argc, const char * argv[]) {
    
    //  Read in neuron points from matlab trained som
    //  Dataset: 4x4 SOM
    //  neuron 9 didn't have any associated points
    
    std::string filepath = "/Users/herbert/Code/Cluster_Boundary_Module/data/cluster";
    
    InputParser* reader;

    std::vector<std::map<int, std::pair<std::string, std::vector<float> > > > clusters;
    clusters.push_back(reader->readInputFile(filepath + "1.csv"));
    clusters.push_back(reader->readInputFile(filepath + "2.csv"));
    clusters.push_back(reader->readInputFile(filepath + "3.csv"));
    clusters.push_back(reader->readInputFile(filepath + "4.csv"));
    clusters.push_back(reader->readInputFile(filepath + "5.csv"));
    clusters.push_back(reader->readInputFile(filepath + "6.csv"));
    clusters.push_back(reader->readInputFile(filepath + "7.csv"));
    clusters.push_back(reader->readInputFile(filepath + "8.csv"));
    clusters.push_back(reader->readInputFile(filepath + "10.csv"));
    clusters.push_back(reader->readInputFile(filepath + "11.csv"));
    clusters.push_back(reader->readInputFile(filepath + "12.csv"));
    clusters.push_back(reader->readInputFile(filepath + "13.csv"));
    clusters.push_back(reader->readInputFile(filepath + "14.csv"));
    clusters.push_back(reader->readInputFile(filepath + "15.csv"));
    clusters.push_back(reader->readInputFile(filepath + "16.csv"));
    
    std::vector<int> position;
    position.push_back(1);
    position.push_back(2);
    position.push_back(3);
    position.push_back(4);
    position.push_back(5);
    position.push_back(6);
    position.push_back(7);
    position.push_back(8);
    position.push_back(10);
    position.push_back(11);
    position.push_back(12);
    position.push_back(13);
    position.push_back(14);
    position.push_back(15);
    position.push_back(16);
    
    // Map Stats
    int row = 4;
    int col = 4;
    
    // Cluster Manager steps
    ClusterManager manager;
    manager.set_map_parameters(row, col);
    manager.import_test_clusters(clusters, position);
    manager.start_clustering_process();
    
    return 0;
}
