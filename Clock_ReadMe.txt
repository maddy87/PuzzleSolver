===============================================================================
File : ClockSolverDynamic.cpp
Author's  : rss2158 (Rajesh Shetty)
===============================================================================
The program provides the solution to winding a clock forward or backward when the current and actual time is provided. The program recieves the input as n Hours on the dial , Actual Time on the Clock and Current Time on the Clock  The clock puzzle implements the Puzzle class and implements that below methods
1. To initialize the Initial Configuration which intializes the 
   Dial on the clock, Actual Time, Current Time on the clock.
2. Check if the given time matches the Current Configuration.
3. GenerateNextSteps generates the next sequences for the current time.
	For example  : Consider a 12 hour clock.
	Current Time : 4 
	Actual/True Time : 7 
	Below are the sequences been generated
		
		Current Time : 4 
		Winding Clock Forward : 3 
		Winding Clock Backward : 5
	
4. The program accepts input and output in the below combinations
		./water 12 4 7
		where 4 is the Current Time
			  7 is the True Time.


Revision.

The updated version of the clock takes to additional arguments on the hours that we want the clock to be forwarded and the hours we want our clock to be reversed. These two arguments can be negative and the desired 
Updating in the above algorithm will be as follows

1. To initialize the Initial Configuration which intializes the 
   Dial on the clock, Actual Time, Current Time on the clock.
2. Check if the given time matches the Current Configuration.
3. GenerateNextSteps generates the next sequences for the current time.
	For example  : Consider a 12 hour clock.
	Current Time : 4 
	Actual/True Time : 7 
      Move Hand Backward by : 3 Hours
      Move Hand Forward by : 2 Hours

	Below are the sequences been generated
		
		Current Time : 4 
		Winding Clock Forward by ‘X’ hours: 4 + 3 = 7
		Winding Clock Backward by ‘Y’ hours : 4 – 2 = 2
	
4. The program accepts input and output in the below combinations
		./water 12 4 7
		where 4 is the Current Time
			  7 is the True Time
