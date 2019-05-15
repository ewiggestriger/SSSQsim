/*
 * This is the header for the Source class and CreateEntityEvent class.
 * Source creates Entities according to parameters and passes them to the SSSQ for scheduling and execution.
 *
 * Created by Steve Kostoff on 2019-03-25.
*/

#pragma once

#include <string>
#include "Distribution.h"
#include "SimObj.h"
#include "SSSQ.h"

class Source : public SimObj
{
public:
    Source(std::string name, SSSQ *sssq, Distribution *interarrivalTime);
    Source(std::string name, SSSQ *sssq, Distribution *interarrivalTime, int numGen);
    /*
        Source
            Parameters:
                string			name				name of entity source
                SSSQ			*sssq				pointer to the destination application for the entities
                Distribution	interarrivalTime	times to create new entities
                int				numGen				the maximum number of entites to generate
            Return value:
                none
            Behavior:
                Constructor for entity source. Initializes private variables and
                schedules first event at time zero

        Calls ScheduleEventAt to schedule the first event in the EventSet
    */

private:
    SSSQ *_sssq;
    Distribution *_interarrivalTime;

    class CreateEntityEvent;
    //Constructor initializes variables
    //Execute Method calls the Source CreateEntity method

    void CreateEntity();
    /*
        CreateEntity
            Parameters:
                none
            Return value:
                none
            Behavior:
                creates new entities as long as we have not reached our entity limit.
                schedules the entity arrival in the application
                schedules the event in the event set at the appropriate interarrival time
    */

    std::string _name;	//name used for outputs
    int _numGen;		//maximum number of entities to generate
};

