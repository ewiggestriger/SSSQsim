/*
 * This is the implementation of the SSSQ header.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#include "SSSQ.h"
#include <iostream>

using namespace std;

SSSQ::SSSQ(std::string name, Sink * sink, Distribution * serviceTime)
{
    //initialize all private variables
    _prevDepartureTime = 0;
    _sink = sink;
    _serviceTime = serviceTime;
    _name = name;
    _totalServiceTime = 0;
    _totalentitiesarrived = 0;
    _totalDelayInQueue = 0;
    _maxDelayInQueue = 0;
    _delayInQueue = 0;
}

class SSSQ::ArriveEvent : public Event
{
public:
    ArriveEvent(SSSQ *sssq, Entity *en)
    {
        //update private variables
        _sssq = sssq;
        _en = en;
    }

    void Execute()
    {
        //execute the arrive method
        _sssq->Arrive(_en);
    }

private:
    SSSQ *_sssq;
    Entity *_en;
};

void SSSQ::ScheduleArrivalIn(Time deltaT, Entity *en)
{
    //schedule an arrive event with the Simulation Executive
    ScheduleEventIn(deltaT, new ArriveEvent(this, en));
}

Time SSSQ::TotalServiceTime()
{
    //return total service time
    return _totalServiceTime;
}

class SSSQ::DepartEvent : public Event
{
public:
    DepartEvent(SSSQ *sssq, Entity *en)
    {
        //Initialize private variables
        _sssq = sssq;
        _en = en;
    }

    void Execute()
    {
        //call the Depart method
        _sssq->Depart(_en);

    }

private:
    SSSQ *_sssq;
    Entity *_en;
};

void SSSQ::Arrive(Entity * en)
{
    //increment the total arrival counter
    _totalentitiesarrived++;

    //delay computation TODO here implement wait times somehow
    Time enDelay = _serviceTime->GetRV();
    //compute total delay in queue time for this entity
    en->setServiceStartTime(this->GetCurrentSimTime() + _prevDepartureTime);
    en->setDepartureTime(en->getServiceStartTime() + enDelay);
    double entityDelay = en->getDepartureTime() - en->getArrivalTime();
    //compute max delay in queue
    if (_maxDelayInQueue < entityDelay)
        _maxDelayInQueue = entityDelay;
    //tally the total delay in queue
    _totalDelayInQueue += enDelay;
    //set entity departure time
    en->setDepartureTime(en->getArrivalTime() + entityDelay);
    _prevDepartureTime = en->getDepartureTime();
    //schedule the departure event
    DepartEvent *_Departure = new DepartEvent(this, en);
    _Departure->Execute();
    //computes total service time
    //checks if endttime is not set and if the entity departure happens before the end of simulation
    if (this->GetEndTime() >= 0.1)
    {

        if (en->getDepartureTime() < this->GetEndTime())
        {
            //if yes, add the total service time of the entity
            _totalServiceTime += enDelay;
        }
        else
            {
            // if not, add the service time of the entity until the simulation endtime
            _totalServiceTime += (this->GetEndTime() - en->getServiceStartTime());
        }
    } else
        _totalServiceTime += enDelay;
}

//Depart method must send the entity to the sink
void SSSQ::Depart(Entity * en)
{
    //Call the Depart method
    _sink->Depart(en);

}

int SSSQ::TotalEntitiesArrived()
{
    //return total entities arrived
    return _totalentitiesarrived;
}

Time SSSQ::AverageDelayInQueue()
{
    //return average delay in queue
    return (_totalDelayInQueue / _totalentitiesarrived);
}

Time SSSQ::MaxDelayInQueue()
{
    //return max delay in queue
    return _maxDelayInQueue;
}
