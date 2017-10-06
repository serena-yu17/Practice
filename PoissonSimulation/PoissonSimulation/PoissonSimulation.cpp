// PoissonSimulation.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <random>
#include <iostream>
#include <cmath>
#include <Queue>
#include <iomanip>
#include <thread>
#include <atomic>
using namespace std;

void printTime(unsigned long time)
{
	int sec = time % 60;
	time /= 60;
	int min = time % 60;
	time /= 60;
	int day = time;
	if (day)
		cout << day << " days ";
	if (min)
		cout << min << " min ";
	if ((!min && !day) || sec)
		cout << sec << " s";
	cout << endl;
}

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


void simulate(double arrive_interval, double service_interval)
{
	cout << "\nFor how long, in hours, should the simulation be run? ";
	size_t  simulation_limit;
	cin >> simulation_limit;
	simulation_limit *= 3600;
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
	exponential_distribution<double> service(1/service_interval);

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

	if (nb_of_customers)
	{
		cout << setprecision(3);
		cout << "Number of customers who have joinded the queue: " << nb_of_customers << "\n";
		cout << "Average number of customers in queue including those being served: " << (double)cumulative_queue_length / simulation_limit << "\n";
		cout << "Average number of customers in queue waiting to be served: " << (double)cumulative_waiting_length / simulation_limit << "\n";
		cout << "Average waiting time, excluding serving time: ";
		printTime(cumulative_waiting_time / nb_of_customers);
		cout << "Average waiting time, including serving time: ";
		printTime(cumulative_waiting_and_serving_time / nb_of_customers);
	}
	else
		cout << "No one has joined the queue; a very quiet day..." << endl;
}

void runTests(double arrive_interval, double service_interval)
{

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
	simulate(arrive_interval, service_interval);
	cin.ignore(1000, '\n');
	cin.clear();
	getchar();
	return 0;
}

