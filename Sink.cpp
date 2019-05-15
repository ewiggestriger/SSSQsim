/*
 * This is the implementation of the Sink header.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#include "Sink.h"
#include "SimObj.h"
#include <iostream>

using namespace std;

typedef double Time;

Sink::Sink(std::string name)
{
    //initialize all private variables
    _name = name;
    _totalEntitiesProcessed = 0;
    _totalFlowTime = 0;
    _maxFlowTime = 0;
    _flowTime = 0;
    _endTime = 0.0;
}

void Sink::Depart(Entity * en)
{
    //print out all data for each entity
    cout << "SIMULATION RESULTS:\n";
    cout << "Entity " << en->GetID() << " arrived in the system at " << en->getArrivalTime() << " seconds." << endl;
    cout << "Entity " << en->GetID() << " was processed by the server at " << en->getServiceStartTime() << " seconds." << endl;
    cout << "Entity " << en->GetID() << " departed the system at " << en->getDepartureTime() << " seconds." << endl;
    cout << "Entity " << en->GetID() << " had a flow time of " << (en->getDepartureTime() - en->getArrivalTime()) << " seconds." << endl;
    Time flowTime = en->getDepartureTime() - en->getArrivalTime();
    //count the total entities completing the process
    _totalEntitiesProcessed++;
    //compute total flow time for this entity
    _totalFlowTime += flowTime;
    //compute max flow time
    if (flowTime > _maxFlowTime)
        _maxFlowTime = flowTime;
    //tally the end time
    if (_endTime < en->getDepartureTime())
        _endTime = en->getDepartureTime();
}

int Sink::TotalEntitiesProcessed()
{
    //return the total entities processed
    return _totalEntitiesProcessed;
}

Time Sink::AverageFlowTime()
{
    //return average flow time
    return _totalFlowTime / _totalEntitiesProcessed;
}

Time Sink::MaxFlowTime()
{
    //return max flow time
    return _maxFlowTime;
}

Time Sink::GetEndTime()
{
    //return end time
    return _endTime;
}

