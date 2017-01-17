//
//  InputParser.cpp


#include "InputParser.h"
#include <fstream>
#include <vector>
#include <sstream>

InputParser::InputParser(void)
{
    
}

InputParser::~InputParser(void)
{
    
}

std::map<int, std::pair<std::string, std::vector<float> > > InputParser::readInputFile(std::string filelocation)
{
    std::string value;
    std::vector<std::string> stringInputs;
    std::ifstream reader(filelocation);
    
    if(! reader)
    {
        std::cout << "Error opening input file" << std::endl;
    }
    
    int i =0;
    
    std::map<int, std::pair<std::string, std::vector<float> > > inputs;
    
    while (! reader.eof()) //assigns each string to variable
    {
        getline(reader,value,'\r');
        
        if (value == "\n")
        {
            break;
        }
        
        stringInputs.push_back(value);
        
        std::stringstream ss(stringInputs[i]);
        std::string token;
        std::vector<float> temp;
        
        while(std::getline(ss, token, ','))
        {
            temp.push_back(std::stof(token));
        }
        
//        inputs.push_back(temp);
        inputs[i] = std::pair<std::string, std::vector<float> >("null", temp);
        i++;
    }
    
    reader.close();
    
    return inputs;
}




