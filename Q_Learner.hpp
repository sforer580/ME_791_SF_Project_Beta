//
//  Q_Learner.hpp
//  ME-791_SF_HW_2_project
//
//  Created by Scott S Forer on 2/22/17.
//  Copyright © 2017 Scott S Forer. All rights reserved.
//

#ifndef Q_Learner_hpp
#define Q_Learner_hpp

#include <stdio.h>

using namespace std;


class Q_Learner
{
    friend class Parameters;
    friend class Individual;
    friend class Enviornment;
    
protected:
    
    
public:
    Parameters* pP;
    Enviornment* pE;
    
    vector<Individual> agent;
    
    void Build_Population();
    void Assign_Starting_Location();
    void Assign_Goal_Location();
    void Assign_Goal_Value();
    void Build_Board();
    void Build_Grid_World();
    void Human_Move_Agent();
    void Auto_Move_Agent();
    void Run_Human_Control();
    void Run_Auto_Control();
    void Display_Board();
    void Run_Program();
    
   
    
    
private:
};


//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------
//Builds population of individuals
void Q_Learner::Build_Population()
{
    for (int i=0; i<pP->num_indv; i++)
    {
        Individual I;
        agent.push_back(I);
    }
}


//-------------------------------------------------------------------------
//Assigns the starting location for the agent
void Q_Learner::Assign_Starting_Location()
{
    if ((pP->agent_start_x < 0)|| (pP->agent_start_x > pP->x_dim))
    {
        int r = rand() % pP->x_dim;
        pP->agent_start_x = r;
    }
    if ((pP->agent_start_y < 0)|| (pP->agent_start_y > pP->y_dim))
    {
        int r = rand() % pP->y_dim;
        pP->agent_start_y = r;
    }
    agent.at(0).x = pP->agent_start_x;
    agent.at(0).y = pP->agent_start_y;
    assert(agent.at(0).x > 0 || agent.at(0).x < pP->x_dim);
    assert(agent.at(0).y > 0 || agent.at(0).y < pP->y_dim);
    cout << "TEST A PASSED" << endl;
    pE->board.at(agent.at(0).y).at(agent.at(0).x) = 1;
}


//-------------------------------------------------------------------------
//Builds the board
void Q_Learner::Build_Board()
{
    vector<double> temp;
    for (int j=0; j<pP->y_dim; j++)
    {
        temp.push_back(0);
    }
    for (int i=0; i<pP->x_dim; i++)
    {
        pE->board.push_back(temp);
    }
}


//-------------------------------------------------------------------------
//Assigns the goal location
void Q_Learner::Assign_Goal_Location()
{
    if ((pP->goal_x < 0)|| (pP->goal_x > pP->x_dim))
    {
        int r = rand() % pP->x_dim;
        pP->goal_x = r;
    }
    if ((pP->goal_y < 0)|| (pP->goal_y > pP->y_dim))
    {
        int r = rand() % pP->y_dim;
        pP->goal_y = r;
    }
}


//-------------------------------------------------------------------------
//Assigns the goal value
void Q_Learner::Assign_Goal_Value()
{
    pE->board.at(pP->goal_x).at(pP->goal_y) = 100;
}


//-------------------------------------------------------------------------
//Displays the board
void Q_Learner::Display_Board()
{
    for (int x=0; x<pP->x_dim; x++)
    {
        for(int y=0;y<pP->y_dim; y++)
        {
            cout << pE->board.at(x).at(y) << "\t";
        }
        cout << endl;
    }
}


//-------------------------------------------------------------------------
//Builds the grid world
void Q_Learner::Build_Grid_World()
{
    Build_Population();
    Build_Board();
    Assign_Starting_Location();
    Assign_Goal_Location();
    Assign_Goal_Value();
    cout << "INTIAL GRID" << endl;
    Display_Board();
}


//-------------------------------------------------------------------------
//Human moves the agent
void Q_Learner::Human_Move_Agent()
{
    int move;
    cout << "INPUT MOVEMENT" << endl;
    cout << "1 UP, 2 RIGHT, 3 DOWN, 4 LEFT" << endl;
    cin >> move;
    int new_x = 0;
    int new_y = 0;
    if (move == 1)
    {
        new_y = agent.at(0).y - 1;
        new_x = agent.at(0).x;
    }
    else if(move == 2)
    {
        new_x = agent.at(0).x + 1;
        new_y = agent.at(0).y;
    }
    else if(move == 3)
    {
        new_y = agent.at(0).y + 1;
        new_x = agent.at(0).x;
    }
    else if(move == 4)
    {
        new_x = agent.at(0).x - 1;
        new_y = agent.at(0).y;
    }
    if ((new_x < 0) || (new_x > pP->x_dim) || (new_y < 0) || (new_y > pP->x_dim))
    {
        cout << "OUT OF BOUNDS" << endl;
    }
    else
    {
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 0;
        agent.at(0).x = new_x;
        agent.at(0).y = new_y;
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 1;
    }
    Display_Board();
}

//-------------------------------------------------------------------------
//Runs the human conctrol
void Q_Learner::Run_Human_Control()
{
    Build_Grid_World();
    while ((agent.at(0).x != pP->goal_x))
    {
        Human_Move_Agent();
        while ((agent.at(0).y != pP->goal_y))
        {
            Human_Move_Agent();
        }
    }
    cout << "REACHED GOAL!!!!!!" << endl;
    cout << "TEST B PASSED" << endl;
}



//-------------------------------------------------------------------------
//Auto moves the agent
void Q_Learner::Auto_Move_Agent()
{
    int move;
    int new_x = 0;
    int new_y = 0;
    if (agent.at(0).x < pP->goal_x)
    {
        new_x = agent.at(0).x + 1;
        new_y = agent.at(0).y;
        cout << "MOVE RIGHT" << endl;
    }
    else if(agent.at(0).x > pP->goal_x)
    {
        new_x = agent.at(0).x - 1;
        new_y = agent.at(0).y;
        cout << "MOVE LEFT" << endl;
    }
    else if(agent.at(0).y < pP->goal_y)
    {
        new_x = agent.at(0).x;
        new_y = agent.at(0).y + 1;
        cout << "MOVE DOWN" << endl;
    }
    else if(agent.at(0).y > pP->goal_y)
    {
        new_x = agent.at(0).x;
        new_y = agent.at(0).y - 1;
        cout << "MOVE UP" << endl;
    }
    if ((new_x < 0) || (new_x > pP->x_dim) || (new_y < 0) || (new_y > pP->x_dim))
    {
        cout << "OUT OF BOUNDS" << endl;
    }
    else
    {
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 0;
        agent.at(0).x = new_x;
        agent.at(0).y = new_y;
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 1;
    }
    Display_Board();
}





//-------------------------------------------------------------------------
//Runs the auto control
void Q_Learner::Run_Auto_Control()
{
    Build_Grid_World();
    while ((agent.at(0).x != pP->goal_x))
    {
        Auto_Move_Agent();
        while ((agent.at(0).y != pP->goal_y))
        {
            Auto_Move_Agent();
        }
    }
    cout << "REACHED GOAL!!!!!!" << endl;
    cout << "TEST C PASSED" << endl;
}


//-------------------------------------------------------------------------
//Runs the enitre program
void Q_Learner::Run_Program()
{
    cout << "------------------------------------------------------------------------" << endl;
    cout << "HUMAN CONTROL" << endl;
    Run_Human_Control();
    cout << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "RULE OF THUMB" << endl;
    Run_Auto_Control();
}

#endif /* Q_Learner_hpp */
