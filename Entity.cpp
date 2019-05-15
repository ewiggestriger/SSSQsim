/*
 * Implementation for the Entity class.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#include "Entity.h"

int Entity::_nextID = 1;

Entity::Entity(Time arrivalTime)
{
    //assign a unique id to the entity and increment the id counter
    _id = _nextID++;

    //log the entity arrival time
    _arrivalTime = arrivalTime;
}

int Entity::GetID()
{
    return _id;
}

Entity::Entity()
{
    _id = _nextID++;
}

void Entity::setDepartureTime(Time departureTime)
{
    //set the departure time
    _departureTime = departureTime;
}

void Entity::setServiceStartTime(Time serviceStartTime)
{
    //set service start time and update its private variable
    _serviceStartTime = serviceStartTime;
}

Time Entity::getArrivalTime()
{
    //return arrival time
    return _arrivalTime;
}

Time Entity::getDepartureTime()
{
    //return the departure time
    return _departureTime;
}

Time Entity::getServiceStartTime()
{
    //return the service time
    return _serviceStartTime;
}
