===============================================================================
File : water.cpp
Author's  : rss2158 (Rajesh Shetty)
===============================================================================
The file simulates a N Water Jug problem, where we can get the deisred amount of 
water with the help of multiple containers provided.
The water puzzle implements the Puzzle class and implements that below methods
1. To initialize the Initial Configuration which intializes the capacities 
	of all the containers to ZERO.
2. Check if the given capacity in any of the 'N' containers match the desired 
	capacity or the goal.
3. GenerateNextSteps generates the next sequences.
	For example  : Consider the input containers be 3 and 5 
	Desired Goal  :  4 Litres
	Below are the sequences been genarated
							Container 3 Container 5
	Filling Both Containers  3			0
	Filling Both Containers  0			5
    Emptying Both Containers 0			5
	Emptying Both Containers 0			0
	Pouring container 3 -->5 0			3
	Pouring container 5 -->3 2			5
4. The program accepts input and output in the below combinations
		./water 4 3 5
		where 4 is the desired goal
		3 and 5 are the containers.