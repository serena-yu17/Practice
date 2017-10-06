# Written by Eric Martin and Feng Yu for COMP9021

'''
Illustrates the use of the queue ADT in modeling a real queue.

Prompts the user to input:
- the average time, lambda, between two successive arrivals of customers joining the queue,
  in minutes;
- the average time, mu, needed to serve a customer when her turn comes, in minutes;
- how long the simulation should be run, in hours.

It is assumed that the inter-arrival time between successive customers and the service time
for a given customer are modeled by an exponentially distributed random variables with
an expected value of lambda and mu, respectively.

The first two inputs allow one to theoretically estimate:
- the average number of customers in the queue including those being served;
- the average number of customers in the queue waiting to be served;
- the average waiting time for a customer, excluding service time;
- the average waiting and service time for a customer.
These estimates are computed and displayed.

Then a simulation is run, with at every second, the following happening.
- Some customers possibly join the queue, their total number being randomly generated
  following a Poisson distribution with an expected value of lambda, based on the relationship
  the latter has with the exponential distribution with the same expected value.
- The requested service time of the customers who have just joined the queue, if any,
  is randomly generated following an exponential distribution with an expected value of mu,
  and rounded to an integral number of seconds.
- If somebody is being served but the remainig service time is 0, then that customer leaves
  the queue.
- Whether the previous case applies or nobody is being served, if the queue is not empty then the
  customer at the front of the queue starts being served. Her requested service time could be 0,
  in which case she would immediately quit the queue and the process would repeat with the next
  customer, if any; otherwise what remains of the service time for this customer is decreased by 1.
- Running sums of how long a customer had to wait before she could start being served, of how long
  it took a customer to wait and be fully served, and of how long the queue is after the customers
  who have just been served have left,including or not the customer now being served, if any, are
  kept. At the end of the simulation, these sums are divided by the number of seconds during which
  the simulation has been run to yield the empirical values of the entities that have previously
  been theoretically estimated.
  The total number of customers who have joined the queue is also displayed.
'''