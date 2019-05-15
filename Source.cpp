/*
 * Implementation of the Source header.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#include "Source.h"
#include <iostream>

using namespace std;

class Source::CreateEntityEvent : public Event
{
public:
    CreateEntityEvent(Source *source)
    {
        //initialize source private variable
        _source = source;
    }

    void Execute()
    {
        //run the CreateEntity() method
        _source->CreateEntity();
    }

private:
    Source *_source;
};

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime)
{
    //initialize all private variables
    _sssq = sssq;
    _interarrivalTime = interarrivalTime;
    _name = name;

    //schedule first event creation as part of initialization
    CreateEntityEvent *newEvent = new CreateEntityEvent(this);
    newEvent->Execute();
}

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime, int numGen)
{
    //initialize all private variables
    _sssq = sssq;
    _interarrivalTime = interarrivalTime;
    _name = name;
    _numGen = numGen;

    //schedule first event creation as part of initialization
    CreateEntityEvent *newEvent = new CreateEntityEvent(this);
    newEvent->Execute();
}

void Source::CreateEntity()
{
    if ((_numGen == -1) || (_numGen > 0))
    {
        if (_numGen > 0)
        {
            _numGen--;
        }

        //create a new entity and assign arrival time to the system
        double arrivalTime = _interarrivalTime->GetRV();
        Entity *_Entity = new Entity(arrivalTime);

        //schedule entity arrival at the SSSQ
        _sssq->ScheduleArrivalIn(_Entity->getArrivalTime()+_sssq->GetCurrentSimTime(), _Entity);

        //schedule the next arrival event
        //loop through all the number of entities and create the desired amount
        //and schedule them
        for (int i = 0; i < _numGen; ++i)
        {
            Time nextArrivalTime = _interarrivalTime->GetRV();
            Entity *_Entity = new Entity(nextArrivalTime);
            _sssq->ScheduleArrivalIn(nextArrivalTime, _Entity);
        }


    }
}
