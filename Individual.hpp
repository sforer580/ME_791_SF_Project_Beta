//
//  Individual.hpp
//  ME-791_SF_HW_2_project
//
//  Created by Scott S Forer on 2/22/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Individual_hpp
#define Individual_hpp

#include <stdio.h>

using namespace std;

class Individual
{
    friend class Parameters;
    friend class Q_Learner;
    friend class Enviornment;
    
protected:
    
    
public:
    int x;
    int y;
    
    
private:
};


#endif /* Individual_hpp */
