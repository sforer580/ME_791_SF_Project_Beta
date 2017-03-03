//
//  main.cpp
//  ME-791_SF_HW_2_project
//
//  Created by Scott S Forer on 2/22/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <time.h>
#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <ctime>
#include <random>

#include "Parameters.hpp"
#include "Individual.hpp"
#include "Enviornment.hpp"
#include "Q_Learner.hpp"


int main()
{
    srand(time(NULL));
    Parameters P;
    Enviornment E;
    Q_Learner Q;
    Q.pP = &P;
    Q.pE = &E;
    Parameters* pP;
    pP = &P;
    Q.Delete_txt_Files();
    Q.Build_Population();
    for (int sr=0; sr<pP->num_sr; sr++)
    {
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        Q.Run_Program(sr);
    }
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    cout << "NEW STATE REPRESENTATION" << endl;
    for (int sr=0; sr<pP->num_sr; sr++)
    {
        cout << "-----------------------------------------------------------------------------------------------" << endl;
        Q.Run_Test_G(sr);
    }
    
}
