//
//  NodeCalculations.h
//  BOUNDARYMODULE
//
//  Created by Adam Kohl on 1/13/17.
//
//

#ifndef NodeCalculations_h
#define NodeCalculations_h

// Standard includes
#include <vector>
#include <string>
#include <map>
#include <iostream>

// Eigen math includes
#include <Eigen/Dense>

class NodeCalculator
{

public:
    
    NodeCalculator(){};
    
    ~NodeCalculator(){};

    Eigen::MatrixXf convert_cluster_data(std::map<int, std::pair<std::string, std::vector<float> > >    data);
    
    Eigen::MatrixXf convert_vecs2Eigen(std::vector<std::vector<float> > pts);
    
    std::vector<float> convert_mat2vec(Eigen::MatrixXf x);
    
    std::vector<float> component_mean(std::map<int, std::pair<std::string, std::vector<float> > >    data);
    
    std::vector<float> component_std(std::map<int, std::pair<std::string, std::vector<float> > >    data);
    
    std::pair<int, int> min_pairpoint_dist(std::map<int, std::pair<std::string, std::vector<float> > >    ipts, std::map<int, std::pair<std::string, std::vector<float> > >    jpts);
    
    float avg_std(std::vector<std::vector<float> > cstds);
    
    float intracluster_density(std::map<int, std::pair<std::string, std::vector<float> > >    data, float avgstd);
    
    float intercluster_density(std::vector<float> ipts, std::vector<float> jpts, std::vector<float> istd, std::vector<float> jstd, float avgstd);
};

#endif /* NodeCalculations_h */
