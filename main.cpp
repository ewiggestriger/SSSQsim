/*
 * Welcome to the main method.
 *
 * The main method sets the simulation end time (zero if an end time is not used),
 * makes instances of the Source, which generates entities to be processed and sends them to the SSSQ,
 * the SSSQ, which is the single server and its queue that holds and processes entities, and finally the Sink,
 * which receives entities from the SSSQ and disposes of them, which in this case means collects statistics on them
 * and reports them back to main.
 * Finally main will give a roll up of analytic stats pertaining to the operation of the queue.
 * Of note, SSSQ and source require as parameters a statistical distribution. Here a triangular distribution is used but
 * many others are provided for the Distribution header and source in this project.
 *
 * After the three components of the simulation have been called, the simulation is run. There are two methods for
 * running a simulation, one that takes an end time parameter and will halt the simulation when that time is reached,
 * and the other which runs until all events have been processed. This run uses the latter, so the other method is
 * commented out and endTime set to 0.
 *
 * Created by Steve Kostoff on 2019-03-25
*/

#include "SimObj.h"
#include <iostream>
#include "Distribution.h"
#include "Sink.h"
#include "SSSQ.h"
#include "Source.h"

using namespace std;

int main()
{
    double endTime = 0;

    Sink sink("Sink");

    SSSQ sssq("SSSQ", &sink, new Triangular(2, 3, 4));

    Source source("Source", &sssq, new Triangular(1, 3, 5), 100); // create 100 entities

    //Source source("Source", &sssq, new Triangular(1, 3, 5));

    SimObj::RunSimulation();							//runs the simulation until no events are left

    //SimObj::RunSimulation(endTime);					//runs the simulation to a specific end time

    //Display DES Performance Measures
    cout << "Total Entities Arrived in Queue: " << sssq.TotalEntitiesArrived() << endl;

    cout << "Total Entities Processed in Simulation: " << sink.TotalEntitiesProcessed() << endl;

    cout << "Average Delay in Queue (total delay / total entities that arrived in SSSQ): " << sssq.AverageDelayInQueue() << " seconds." << endl;

    cout << "Maximum Delay in Queue: " << sssq.MaxDelayInQueue() << " seconds." << endl;

    cout << "Average Flow Time: " << sink.AverageFlowTime() << " seconds." << endl;

    cout << "Max Flow Time: " << sink.MaxFlowTime() << " seconds." << endl;

    cout << "Total Service Time: " << sssq.TotalServiceTime() << " seconds." << endl;

    cout << "Server Utilization: " << ((sssq.TotalServiceTime() / ((endTime == 0.0) ? sink.GetEndTime() : endTime)) * 100.0) << "%" << endl;

    return 0;

}