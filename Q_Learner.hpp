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
    friend class Q_Value;
    
protected:
    
    
public:
    Parameters* pP;
    Enviornment* pE;
    
    vector<Individual> agent;
    
    //Enviornment Functions
    void Assign_Goal_Location();
    void Assign_Goal_Value();
    void Build_Reward_Table();
    void Assign_Boundaries_To_Q_Table();
    void Assign_Values_To_Reward_Table();
    void Build_Board();
    void Display_Board();
    void Display_Reward_Table();
    //Agent Functions
    void Build_Population();
    void Assign_Starting_Location();
    //Human Control Functions
    void Human_Move_Agent();
    void Run_Human_Control();
    //Auto Control Functions
    void Auto_Move_Agent();
    void Run_Auto_Control();
    //Q_Leaner Control Functions
    void Sense();
    void Decide();
    void Act();
    void Greedy_Move();
    void Random_Move();
    void React();
    void Q_Learner_Move_Agent();
    void Run_Q_Learner_Control();
    void Display_Q_Table();
    //Q_Leaner Functions
    void Build_Grid_World();
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
        vector<double> temp;
        for (int j=0; j<4; j++)
        {
            temp.push_back(0.0001);
        }
        for (int k=0; k<pP->x_dim*pP->y_dim; k++)
        {
            agent.at(i).q_table.push_back(temp);
        }
    }
}


//-------------------------------------------------------------------------
//Assigns a negative number to the actions that would be out of bounds
void Q_Learner::Assign_Boundaries_To_Q_Table()
{
    for (int y=0; y<pP->y_dim; y++)
    {
        for (int x=0; x<pP->x_dim; x++)
        {
            int s = x+(y*pP->x_dim);
            if (y == 0)
            {
                //pE->reward_table.at(s).at(0) = -1;
                agent.at(0).q_table.at(s).at(0) = -1;
                //Display_Reward_Table();
            }
            if (x == pP->x_dim-1)
            {
                //pE->reward_table.at(s).at(1) = -1;
                agent.at(0).q_table.at(s).at(1) = -1;
                //Display_Reward_Table();
            }
            if (y == pP->y_dim-1)
            {
                //pE->reward_table.at(s).at(2) = -1;
                agent.at(0).q_table.at(s).at(2) = -1;
                //Display_Reward_Table();
            }
            if (x == 0)
            {
                //pE->reward_table.at(s).at(3) = -1;
                agent.at(0).q_table.at(s).at(3) = -1;
                //Display_Reward_Table();
            }
        }
    }
    
}


//-------------------------------------------------------------------------
//Assigns a negative reward to the actions that would be out of bounds
void Q_Learner::Assign_Values_To_Reward_Table()
{
    for (int i=0; i<pP->y_dim*pP->x_dim; i++)
    {
        pE->reward_table.push_back(-1);
    }
    for (int s=0; s<(pP->y_dim)*(pP->x_dim); s++)
    {
        if (s == pP->goal_state)
        {
            pE->reward_table.at(s) = 100;
        }
    }
    
}



//-------------------------------------------------------------------------
//Builds the reward table
void Q_Learner::Build_Reward_Table()
{
    //Assign_Boundaries_To_Q_Table();
    Assign_Values_To_Reward_Table();
    Display_Reward_Table();
    Display_Q_Table();
    
}


//-------------------------------------------------------------------------
//Displays the Q-table
void Q_Learner::Display_Reward_Table()
{
    cout << "REWARD TABLE" << endl;
    int c = 0;
    for (int s=0; s<pP->num_states; s++)
    {
        if (c%(pP->x_dim) == 0 && c != 0)
        {
            cout << endl;
        }
        cout << pE->reward_table.at(s) << "\t";
        c += 1;
    }
    cout << endl;
    cout << endl;
}


//-------------------------------------------------------------------------
//Displays the Q-table
void Q_Learner::Display_Q_Table()
{
    cout << "Q_TABLE TABLE" << endl;
    for(int s=0;s<pP->x_dim*pP->y_dim; s++)
    {
        cout << "STATE" << "\t" << s << "\t";
    }
    cout << endl;
    for (int x=0; x<4; x++)
    {
        if (x==0)
        {
            cout << "UP   " << "\t";
        }
        if (x==1)
        {
            cout << "RIGHT" << "\t";
        }
        if (x==2)
        {
            cout << "DOWN" << "\t";
        }
        if (x==3)
        {
            cout << "LEFT" << "\t";
        }
        for(int y=0;y<pP->x_dim*pP->y_dim; y++)
        {
            cout << agent.at(0).q_table.at(y).at(x) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}


//-------------------------------------------------------------------------
//Assigns the starting location for the agent
void Q_Learner::Assign_Starting_Location()
{
    if ((pP->agent_start_x < 0)|| (pP->agent_start_x > pP->x_dim-1))
    {
        int r = rand() % pP->x_dim;
        pP->agent_start_x = r;
    }
    if ((pP->agent_start_y < 0)|| (pP->agent_start_y > pP->y_dim-1))
    {
        int r = rand() % pP->y_dim;
        pP->agent_start_y = r;
    }
    agent.at(0).x = pP->agent_start_x;
    agent.at(0).y = pP->agent_start_y;
    int s =agent.at(0).x + (agent.at(0).y*pP->x_dim);
    agent.at(0).path.push_back(s);
    assert(agent.at(0).x > 0 || agent.at(0).x < pP->x_dim);
    assert(agent.at(0).y > 0 || agent.at(0).y < pP->y_dim);
    cout << "TEST A PASSED" << endl;
    cout << endl;
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
    if ((pP->goal_x < 0)|| (pP->goal_x > pP->x_dim-1))
    {
        int r = rand() % pP->x_dim;
        pP->goal_x = r;
    }
    if ((pP->goal_y < 0)|| (pP->goal_y > pP->y_dim-1))
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
    cout << "BOARD" << endl;
    for (int x=0; x<pP->x_dim; x++)
    {
        for(int y=0;y<pP->y_dim; y++)
        {
            cout << pE->board.at(x).at(y) << "\t";
        }
        cout << endl;
    }
    cout << endl;
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
    Build_Reward_Table();
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
    int new_x = agent.at(0).x;
    int new_y = agent.at(0).y;
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
    if ((new_x < 0) || (new_x > pP->x_dim-1) || (new_y < 0) || (new_y > pP->y_dim-1))
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
    cout << "------------------------------------------------------------------------" << endl;
    cout << "HUMAN CONTROL" << endl;
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
    cout << endl;
}



//-------------------------------------------------------------------------
//Auto moves the agent
void Q_Learner::Auto_Move_Agent()
{
    int move;
    int new_x = agent.at(0).x;
    int new_y = agent.at(0).y;
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
    if ((new_x < 0) || (new_x > pP->x_dim-1) || (new_y < 0) || (new_y > pP->y_dim-1))
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
    cout << "------------------------------------------------------------------------" << endl;
    cout << "RULE OF THUMB" << endl;
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
    cout << endl;
}


//-------------------------------------------------------------------------
//Sneses the agents state
void Q_Learner::Sense()
{
    int A = agent.at(0).x;
    int B = agent.at(0).y*pP->x_dim;
    agent.at(0).state = A+B;
    cout << "AGENT STATE" << "\t" << agent.at(0).state << endl;
}


//-------------------------------------------------------------------------
//Decides if greedy or not
void Q_Learner::Decide()
{
    double r = (double)rand()/RAND_MAX;
    if (r <= (1-pP->epsilon))
    {
        agent.at(0).greedy = 1;     //will do a greedy action
    }
    else
    {
        agent.at(0).greedy = 0;     //will do a random action
    }
}


//-------------------------------------------------------------------------
//Performs a greedy move
void Q_Learner::Greedy_Move()
{
    int s = agent.at(0).state;
    int best = 0;
    for (int m=0; m<4; m++)
    {
        if (agent.at(0).q_table.at(s).at(best) < agent.at(0).q_table.at(s).at(m))
        {
            best = m;
        }
    }
    int new_x = agent.at(0).x;
    int new_y = agent.at(0).y;
    if (best == 0)
    {
        new_y = agent.at(0).y - 1;
        cout << "MOVE UP" << endl;
    }
    if (best == 1)
    {
        new_x = agent.at(0).x + 1;
        cout << "MOVE RIGHT" << endl;
    }
    if (best == 2)
    {
        new_y = agent.at(0).y + 1;
        cout << "MOVE DOWN" << endl;
    }
    if (best == 3)
    {
        new_x = agent.at(0).x - 1;
        cout << "MOVE LEFT" << endl;
    }
    if ((new_x < 0) || (new_x > pP->x_dim-1) || (new_y < 0) || (new_y > pP->y_dim-1))
    {
        cout << "OUT OF BOUNDS" << endl;
        new_x = agent.at(0).x;
        new_y = agent.at(0).y;
    }
    else
    {
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 0;
        agent.at(0).x = new_x;
        agent.at(0).y = new_y;
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 1;
    }
    int ss = agent.at(0).x + (agent.at(0).y*pP->x_dim);
    agent.at(0).path.push_back(ss);
    agent.at(0).actions.push_back(best);
}


//-------------------------------------------------------------------------
//Performs a random move
void Q_Learner::Random_Move()
{
    int r = (int)rand() % 4;
    int new_x = agent.at(0).x;
    int new_y = agent.at(0).y;
    if (r == 0)
    {
        new_y = agent.at(0).y - 1;
        cout << "MOVE UP" << endl;
    }
    if (r == 1)
    {
        new_x = agent.at(0).x + 1;
        cout << "MOVE RIGHT" << endl;
    }
    if (r == 2)
    {
        new_y = agent.at(0).y + 1;
        cout << "MOVE DOWN" << endl;
    }
    if (r == 3)
    {
        new_x = agent.at(0).x - 1;
        cout << "MOVE LEFT" << endl;
    }
    if ((new_x < 0) || (new_x > pP->x_dim-1) || (new_y < 0) || (new_y > pP->y_dim-1))
    {
        cout << "OUT OF BOUNDS" << endl;
        new_x = agent.at(0).x;
        new_y = agent.at(0).y;
    }
    else
    {
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 0;
        agent.at(0).x = new_x;
        agent.at(0).y = new_y;
        pE->board.at(agent.at(0).y).at(agent.at(0).x) = 1;
    }
    int ss = agent.at(0).x + (agent.at(0).y*pP->x_dim);
    agent.at(0).path.push_back(ss);
    agent.at(0).actions.push_back(r);
}


//-------------------------------------------------------------------------
//Reacts to the movement and updates the Q_Table
void Q_Learner::React()
{
    int action_1 = agent.at(0).actions.at(agent.at(0).actions.size()-1);
    int s = agent.at(0).path.at(agent.at(0).path.size()-2);
    int ss = agent.at(0).path.at(agent.at(0).path.size()-1);
    double A = agent.at(0).q_table.at(s).at(action_1);
    int best = 0;
    for (int m=0; m<4; m++)
    {
        if (agent.at(0).q_table.at(ss).at(best) < agent.at(0).q_table.at(ss).at(m))
        {
            best = m;
        }
    }
    double B = agent.at(0).q_table.at(ss).at(best);
    double R = pE->reward_table.at(ss);
    agent.at(0).q_table.at(s).at(action_1) = A+pP->alpha*(R+(pP->gamma*B)-A);
}


//-------------------------------------------------------------------------
//Moves the agent based on if it is a greedy action or not
void Q_Learner::Act()
{
    if (agent.at(0).greedy == 1)
    {
        Greedy_Move();
    }
    if (agent.at(0).greedy == 0)
    {
        Random_Move();
    }
}


//-------------------------------------------------------------------------
//Runs the Q_Learner movement functions
void Q_Learner::Q_Learner_Move_Agent()
{
    Sense();
    Decide();
    Act();
    React();
    Display_Q_Table();
    Display_Board();
}


//-------------------------------------------------------------------------
//Runs the Q_learner
void Q_Learner::Run_Q_Learner_Control()
{
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Q_Learner" << endl;
    cout << endl;
    Build_Grid_World();
    cout << "BEGIN Q_LEANER" << endl;
    cout << endl;
    int move_counter = 0;
    while ((agent.at(0).x != pP->goal_x))
    {
        move_counter += 1;
        cout << "MOVE NUMBER" << "\t" << move_counter << endl;
        Q_Learner_Move_Agent();
        while ((agent.at(0).y != pP->goal_y))
        {
            move_counter += 1;
            cout << "MOVE NUMBER" << "\t" << move_counter << endl;
            Q_Learner_Move_Agent();
        }
    }
    cout << "REACHED GOAL!!!!!" << endl;
    cout << "NUMBER OF MOVES" << "\t" << move_counter << endl;
}


//-------------------------------------------------------------------------
//Runs the enitre program
void Q_Learner::Run_Program()
{
    //Run_Human_Control();
    //Run_Auto_Control();
    Run_Q_Learner_Control();
}

#endif /* Q_Learner_hpp */
