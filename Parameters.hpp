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
    friend class Q_Value;
    
protected:
    
    
public:
    int num_indv = 1;
    int x_dim = 13;
    int y_dim = 13;
    int num_states = x_dim*y_dim;
    int goal_x = 10;
    int goal_y = 10;
    int goal_state = goal_x + (goal_y*x_dim);
    int agent_start_x = 0;
    int agent_start_y = 0;
    double epsilon = 0.1;
    double alpha = 0.1;
    double gamma = 0.9;
    int num_tries = 50;
    int num_sr = 10;
    
    
    
    
private:
};


#endif /* Parameters_hpp */
