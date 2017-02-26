//
//  Enviornment.hpp
//  ME-791_SF_HW_2_project
//
//  Created by Scott S Forer on 2/22/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Enviornment_hpp
#define Enviornment_hpp

#include <stdio.h>

class Enviornment
{
    friend class Parameters;
    friend class Q_Learner;
    friend class Individual;
    friend class Q_Value;
    
protected:
    
    
public:
    vector<vector<double>> board;
    vector<double> reward_table;
    
    
    
    
private:
};

#endif /* Enviornment_hpp */
