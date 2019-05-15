/*
 * Header for the Sink class. Sink receives entities from the server
 * and disposes of them. Most importantly, Sink collects analytic statistics on the entities as
 * they leave the server (SSSQ).
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#pragma once

#include <string>
#include "Entity.h"

class Sink
{
public:
    Sink(std::string name);
    /*
        Sink
            Parameters:
                string	name	the name of the entity departing
            Return value:
                none
            Behavior:
                Constructor for the sink class
    */

    void Depart(Entity *en);
    /*
        Depart
            Parameters:
                Entity	*en	pointer to the departing entity
            Return value:
                none
            Behavior:
                identifies the entity departing the application
    */

    int TotalEntitiesProcessed();
    //Returns total entities processed

    Time AverageFlowTime();
    //returns average flow time

    Time MaxFlowTime();
    //returns max flow time

    Time GetEndTime();
    //returns simulation end time


private:
    std::string _name;
    int _totalEntitiesProcessed;
    Time _totalFlowTime;
    Time _maxFlowTime;
    Time _flowTime;
    Time _endTime;
};

