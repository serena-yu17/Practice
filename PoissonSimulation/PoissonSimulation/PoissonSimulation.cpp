// PoissonSimulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>
#include <Queue>
#include <iomanip>
#include <atomic>
#include <thread>
using namespace std;

const int nthreads = 10;

struct Customer
{
	size_t arrive_time;
	size_t service_time;
	Customer(size_t arv_time, size_t svc_time)
	{
		arrive_time = arv_time;
		service_time = svc_time;
	}
};

struct Statistics {
	size_t ncustomers;
	size_t cum_queue_length;
	size_t cum_waiting_length;
	size_t cum_waiting_time;
	size_t cum_waiting_and_serving_time;
	size_t total_simulation;
};

void simulate(const double&, const double&, const size_t&, Statistics*);
void printTime(size_t);

void printTime(size_t time)
{
	size_t sec = time % 60;
	time /= 60;
	size_t min = time % 60;
	time /= 60;
	size_t day = time;
	if (day)
		cout << day << " days ";
	if (min)
		cout << min << " min ";
	if ((!min && !day) || sec)
		cout << sec << " s";
	cout << endl;
}

double avg(double* array)
{
	double sum = 0;
	for (int i = 0; i < nthreads; i++)
		sum += array[i];
	return sum / nthreads;
}

size_t avg(size_t* array)
{
	size_t sum = 0;
	for (int i = 0; i < nthreads; i++)
		sum += array[i];
	return sum / nthreads;
}


void runTests(const double& arrive_interval, const double& service_interval)
{
	cout << "\nFor how long, in hours, should the simulation be run? ";
	size_t  simulation_limit;
	cin >> simulation_limit;
	simulation_limit *= 3600 / nthreads;
	thread th[nthreads];
	Statistics stats[nthreads];
	for (int i = 0; i < nthreads; i++)
		th[i] = thread(simulate, arrive_interval, service_interval, simulation_limit, &stats[i]);
	for (int i = 0; i < nthreads; i++)
		th[i].join();

	size_t ncustomers = 0;
	size_t simulation_runs = 0;
	double avg_customers_queue[nthreads];
	double avg_customers_queue_waiting[nthreads];
	size_t avg_waiting_time[nthreads];
	size_t avg_waiting_time_service[nthreads];

	for (int i = 0; i < nthreads; i++)
	{
		if (stats[i].ncustomers)
		{
			ncustomers += stats[i].ncustomers;
			simulation_runs += stats[i].total_simulation;
			avg_customers_queue[i] = (double)stats[i].cum_queue_length / stats[i].total_simulation;
			avg_customers_queue_waiting[i] = (double)stats[i].cum_waiting_length / (double)stats[i].total_simulation;
			avg_waiting_time[i] = stats[i].cum_waiting_time / stats[i].ncustomers;
			avg_waiting_time_service[i] = stats[i].cum_waiting_and_serving_time / stats[i].ncustomers;
		}
	}

	cout << setprecision(3);
	cout << "Number of customers who have joinded the queue: " << ncustomers << "\n";
	cout << "Average number of customers in queue including those being served: "
		<< avg(avg_customers_queue) << "\n";
	cout << "Average number of customers in queue waiting to be served: "
		<< avg(avg_customers_queue_waiting) << "\n";
	cout << "Average waiting time, excluding serving time: ";
	printTime(avg(avg_waiting_time));
	cout << "Average waiting time, including serving time: ";
	printTime(avg(avg_waiting_time_service));
}


void simulate(const double& arrive_interval, const double& service_interval, const size_t& simulation_limit, Statistics* stats)
{
	size_t nb_of_customers = 0;
	size_t cumulative_queue_length = 0;
	size_t cumulative_waiting_length = 0;
	size_t cumulative_waiting_time = 0;
	size_t cumulative_waiting_and_serving_time = 0;
	size_t service_time = -1;

	random_device rd;
	mt19937 mtRand(rd());
	queue<Customer> q;

	poisson_distribution<size_t> customer(1 / arrive_interval);
	exponential_distribution<double> service(1 / service_interval);

	for (size_t simulation_tick = 0; simulation_tick < simulation_limit; simulation_tick++)
	{
		size_t 	new_customers = customer(mtRand);
		nb_of_customers += new_customers;
		for (size_t i = 0; i < new_customers; i++)
		{
			q.push(Customer(simulation_tick, size_t(service(rd) + 0.5)));
		}

		if (service_time == -1 && !q.empty())
		{
			service_time = q.front().service_time;
			cumulative_waiting_time += simulation_tick - q.front().arrive_time;
		}
		while (!service_time && !q.empty())
		{
			cumulative_waiting_and_serving_time += simulation_tick - q.front().arrive_time;
			q.pop();
			if (!q.empty())
			{
				service_time = q.front().service_time;
				cumulative_waiting_time += simulation_tick - q.front().arrive_time;
			}
			else
				service_time = -1;
		}
		cumulative_queue_length += q.size();
		if (!q.empty())
		{
			service_time--;
			cumulative_waiting_length += q.size() - 1;
		}
	}

	stats->ncustomers = nb_of_customers;
	stats->cum_queue_length = cumulative_queue_length;
	stats->cum_waiting_length = cumulative_waiting_length;
	stats->cum_waiting_time = cumulative_waiting_time;
	stats->cum_waiting_and_serving_time = cumulative_waiting_and_serving_time;
	stats->total_simulation = simulation_limit;

}



void calculate(double arrive_interval, double service_interval)
{
	double  traffic_intensity = service_interval / arrive_interval;
	double 	 average_nb_in_queue = traffic_intensity * traffic_intensity / (1 - traffic_intensity);
	double average_waiting_time_in_queue = average_nb_in_queue * arrive_interval;

	cout << setprecision(3) << "Estimated average number of customers in queue including those being served: "
		<< average_nb_in_queue + traffic_intensity << "\n";
	cout << "Estimated average number of customers in queue waiting to be " << average_nb_in_queue << "\n";
	cout << "Estimated average waiting time, excluding serving time: ";
	printTime(average_waiting_time_in_queue);
	cout << "Estimated average waiting time, including serving time: ";
	printTime(average_waiting_time_in_queue + service_interval);
}

int main()
{
	ios::sync_with_stdio(false);
	cout << "Enter the average time, in minutes, between two arrivals: ";
	double arrive_interval;
	cin >> arrive_interval;
	arrive_interval *= 60;
	double service_interval;
	cout << "Enter the average time, in minutes, needed to serve a customer: ";
	cin >> service_interval;
	service_interval *= 60;
	calculate(arrive_interval, service_interval);
	runTests(arrive_interval, service_interval);
	cin.ignore(1000, '\n');
	cin.clear();
	getchar();
	return 0;
}

