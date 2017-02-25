//
//  Parameters.hpp
//  ME-791_SF_HW_2_project
//
//  Created by Scott S Forer on 2/22/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Parameters_hpp
#define Parameters_hpp

#include <stdio.h>

using namespace std;


class Parameters
{
    friend class Q_Learner;
    friend class Individual;
    friend class Enviornment;
    
protected:
    
    
public:
    int num_indv = 1;
    int x_dim = 13;
    int y_dim = 13;
    int num_states = x_dim*y_dim;
    int goal_x = 5;
    int goal_y = 5;
    int agent_start_x = 20;
    int agent_start_y = 0;
    
    
    
    
private:
};


#endif /* Parameters_hpp */
