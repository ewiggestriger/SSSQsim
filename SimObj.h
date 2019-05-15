/*
 * Header for the SimObj, Event, and EventSet classes
 * SimObj contains the basic engine for a distributed event simulation.
 * SimObj class schedules events and runs the simulation.
 * It contains an EventSet class that holds all the events in a linked list, which are structs called EventNodes
 * with relevant time and pointers for the LL as well as the entity they contain.
 * Event is a virtual class that is implemented elsewhere (SSSQ in this project), but the Event objects
 * are intended to contain Entities that carry the executable code and relevant sim data.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#pragma once

typedef double Time;

class Event
{
public:
    Event()
    {

    }
    virtual void Execute() = 0;
};

class SimObj
{
public:
    static Time GetCurrentSimTime();
    /*
        GetCurrentSimTime
            Parameters:
                none
            Return value:
                Current simulation time
            Behavior:
                Returns the simulation time of the currently executing event
    */

    static void RunSimulation();
    /*
        RunSimulation
            Parameters:
                none
            Return value:
                none
            Behavior:
                Executes events in time stamp order. Continues executing
                until no future events remain to execute. Simultaneous events
                are executed in the order they were scheduled.
    */

    static void RunSimulation(Time endTime);
    /*
        RunSimulation
            Parameters:
                Time	endTime		Simulation time that the simulation should end.
            Return value:
                none
            Behavior:
                Executes events in time stamp order. Continues executing
                until either the current simulation time exceeds endTime
                or not future events remain to execute. Simultaneous events
                are executed in the order they were scheduled.
    */

    Time GetEndTime();
    /*
    GetEndTime
    Paramters:
    none
    Return value:
    End time of simulation
    Behavior:
    gets the end time of the simulation
    */


protected:
    SimObj();
    /*
        SimObj
            Parameters:
                none
            Return value:
                none
            Behavior:
                Constructor, no change in state
    */

    void ScheduleEventIn(Time deltaTime, Event *ev);
    /*
        ScheduleEVentIn
            Parameters:
                Time	deltaTime	simulation time delay before event is executed
                Event	*ev		event to be executed
            Return value:
                none
            Behavior:
                Schdedules event ev to be executed when the current simulation time
                reaches the current simulation time + deltaTime.
    */

    void ScheduleEventAt(Time time, Event *ev);
    /*
        ScheduleEventAt
            Parameters:
                Time	time	Simulation time when the event should be executed.
                Event	*ev		event to be executed
            Return value:
                none
            Behavior:
                Schedules event ev to be executed when the current simulation time reaches time
    */


private:
    static Time _currentTime;	//maintains the current time for the entire simulation

    class EventSet;				//container for all the scheduled events
    //Constructor initialzes a pointer to the first event
    //Method AddEvent creates an event node and adds it to the event set
    //Method GetEvent returns a pointer to the next event in the event set
    //Method GetTime returns the time of the next event
    //Method HasEvent checks to see if the EventSet is empty
    //Contains the EventNode structure

    static EventSet _eventSet;	//event set for the entire simulation

    static Time _endTime;		//end time of simulation

};
