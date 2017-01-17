//
//  NodeCalculations.cpp
//  BOUNDARYMODULE
//
//  Created by Adam Kohl on 1/13/17.
//
//

#include "NodeCalculations.h"

Eigen::MatrixXf NodeCalculator::convert_cluster_data(std::map<int, std::pair<std::string, std::vector<float> > >    data)
{
    
    int rows = data.size();
    int col = data[0].second.size();
    Eigen::MatrixXf m(rows,col);
    
    std::map<int, std::pair<std::string, std::vector<float> > >::iterator it;
    
    int row = 0;
    for (it = data.begin(); it != data.end(); ++it)
    {
        std::vector<float> x = it->second.second;
        int col = 0;
        for (int i =0; i<x.size(); i++)
        {
            m(row,col) = x[i];
            col++;
        }
        row++;
    }
    return m;
}

Eigen::MatrixXf NodeCalculator::convert_vecs2Eigen(std::vector<std::vector<float> > pts)
{
    Eigen::MatrixXf mat(pts.size(), pts[0].size());

    for (int i=0; i < pts.size(); i++)
    {
        for (int j=0; j < pts[0].size(); j++)
        {
            mat(i,j) = pts[i][j];
        }
    }
    return mat;
}

std::vector<float> NodeCalculator::convert_mat2vec(Eigen::MatrixXf mat)
{
    std::vector<float> out;
    
    for (int i=0; i<mat.cols(); i++)
    {
        out.push_back(mat.row(0).data()[i]);
    }
    
    return out;
}

std::vector<float> NodeCalculator::component_mean(std::map<int, std::pair<std::string, std::vector<float> > >    data)
{
    Eigen::MatrixXf m = convert_cluster_data(data);
    Eigen::MatrixXf mat = m.colwise().mean();
    std::vector<float> mean = convert_mat2vec(mat);
    return mean;
}

std::vector<float> NodeCalculator::component_std(std::map<int, std::pair<std::string, std::vector<float> > >    data)
{
    Eigen::MatrixXf m = convert_cluster_data(data);
    Eigen::VectorXf mean = m.colwise().mean();
    Eigen::MatrixXf msub = m.rowwise() - mean.transpose();
    Eigen::MatrixXf m1;
    if (m.rows() == 1)
    {
        m1 = msub.array().square().colwise().sum() / m.rows();
    }
    else
    {
        m1 = msub.array().square().colwise().sum() / (m.rows()-1);
    }
    Eigen::MatrixXf colstd = m1.array().sqrt();
    std::vector<float> std = convert_mat2vec(colstd);
    return std;
}

std::pair<int, int> NodeCalculator::min_pairpoint_dist(std::map<int, std::pair<std::string, std::vector<float> > >    ipts, std::map<int, std::pair<std::string, std::vector<float> > >    jpts)
{
    std::pair<int, int> minpair;
    Eigen::MatrixXf mi = convert_cluster_data(ipts);
    Eigen::MatrixXf mj = convert_cluster_data(jpts);
    Eigen::MatrixXf::Index index;
    
    // Store distances and indexes in matrix
    Eigen::MatrixXf mresult(mj.rows(), 2);
    int indr = 0;
    
    for (int i=0; i < mj.rows(); i++)
    {
        (mi.rowwise()-mj.row(i)).rowwise().squaredNorm().array().sqrt().minCoeff(&index);
        Eigen::MatrixXf eucdist = (mi.rowwise()-mj.row(i)).rowwise().squaredNorm().array().sqrt();
        mresult(indr,0) = eucdist.data()[index];
        mresult(indr,1) = index;
        indr++; 
    }
    
    Eigen::MatrixXf::Index index1;
    mresult.col(0).minCoeff(&index1);

    minpair.first = index;
    minpair.second = index1;
    
    return minpair;
}

// Need to redo for euclidean distance of all points
float NodeCalculator::avg_std(std::vector<std::vector<float> > cstds)
{
    Eigen::MatrixXf m = convert_vecs2Eigen(cstds);
    Eigen::MatrixXf m1 = m.rowwise().sum() / m.cols();
    float avgstd = m1.sum() / m1.rows();
    return avgstd;
}

float NodeCalculator::intracluster_density(std::map<int, std::pair<std::string, std::vector<float> > >    data, float avgstd)
{
    Eigen::MatrixXf mat = convert_cluster_data(data);
    
    // row 1 - all output comparision for entire matrix euclidean dist
    Eigen::MatrixXf density = Eigen::MatrixXf::Zero(mat.rows(), mat.rows());
    for (int i=0; i < mat.rows(); i++)
    {
        Eigen::MatrixXf m1 = mat;
        m1.rowwise() -= mat.row(i);
        Eigen::VectorXf eucmat = m1.rowwise().squaredNorm().array().sqrt();
        
        for (int j=0; j < eucmat.rows(); j++)
        {
            if (eucmat(j) <= avgstd)
            {
                density(i,j) = 1.0;
            }
            else
                continue;
        }
    }
    Eigen::VectorXf densvec = density.rowwise().sum();
    float intradensity = densvec.sum();
    return intradensity; 
}

float NodeCalculator::intercluster_density(std::vector<float> ipts, std::vector<float> jpts, std::vector<float> istd, std::vector<float> jstd, float avgstd)
{
    
}
