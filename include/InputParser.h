//
//  InputParser.h
//  2DNURBS
//
//  Created by Adam Kohl on 2/19/16.
//
//

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map> 

class InputParser
{
    
public:
    
    InputParser(void);
    
    ~InputParser(void);
    
    std::map<int, std::pair<std::string, std::vector<float> > > readInputFile(std::string filelocation);
    
};
