/**
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * FileName    : ClockSolverDynamic.cpp
 * Description : The program provides the solution to winding a clock 
 *				 forward or backward when the current and actual time is provided
 *  			 The clock here is an 'n' modulo clock
 * @version  :  ClockSolver.cpp v 1.0  2014/11/30  11:04 AM
                ClockSolverDynamic v 1.2 2014/12/11 1:53 AM
                Updated the clock to take multiple arguments 
 * 
 * @author(s)  rss2158 (Rajesh Shetty)
 * 
 *=============================================================================
 */


//#include "stdafx.h"
#include "resolver.h"
#include <iostream>
#include <queue>
using namespace std;

/* Class Name : ClockSolverDynamics
 * 
 * Descrition : Class created from the Resolver Template 
                which implents the virtual functions
 */
class ClockSolver : public Resolver<int>
{
 public:

   int iNoOfHours;
   int iCurrentTime;
   int iActualTime;
   int iHandForward; //Unused
   int iHandBackward; //Unused
   list<int> iArguments; // List that will store the the 'N' arguments that are passed


   //Constructor to intiailizes the Clock Hours Dial and Actual and list with 'n' arguments
   ClockSolver(int nHours, int Curr, int Actual,list<int>& aArgs)
   :Resolver(Curr),iNoOfHours(nHours),iCurrentTime(Curr),iActualTime(Actual), iArguments(aArgs){}
   
  /* Function Name: IfSolutionMet
   * 
   * Description: Checks if the desired goal was met and 
   *              returns TRUE if met and False if otherwie
   * CurrentStep : int argument containing the current value popped from the queue
   *                
   */
   bool IfSolutionMet(int CurrentStep)
   {
	return CurrentStep == iActualTime;
   }
   
   /* Function Name: PrintSteps
   * 
   * Description: Prints the solution with the brief traversal
   *              of the nodes that lead to the solution.
   * CurrentStep : int argument containing the current config
   */
   void PrintSteps(int CurrentStep)
   {
	   cout<< " " <<CurrentStep;
   }

   /* Function Name: getHours()
   * 
   * Description: returns the hours set for the dial
   *
   */
   int getHours()
   {
   	 return iNoOfHours;
   }

   /* Function Name: GetNextStep
   * 
   * Description: Generates a list of next configurations from the current input
   * return list : List contains all the possible sequences that were generated 
   *               using input config
   */
   list<int> GetNextStep(int iCurrentStep)
   {
        list<int> iNextSteps;
        //Creating a copy of the existing arguments
		list<int> iSeedSequence = iArguments;
		int iSequence;

		//Till all the arguments are processed for the current input 
		while(!iSeedSequence.empty())
		{

           int iCurr = iSeedSequence.front();
           iSeedSequence.pop_front();
           iSequence = iCurrentStep + iCurr;

           //Validate if Out of Bounds and Fix it
           if(iSequence<1)
             {iSequence = (iSequence +iNoOfHours);}
           if(iSequence>iNoOfHours)
           	  {iSequence = (iSequence%iNoOfHours);}
           

           //Add it to the list
           iNextSteps.push_back(iSequence);
		}

		return iNextSteps;
   }
};

int main(int argc,char const *argv[])
{
	//Check if Enough Arguments are recived
    if ( argc <= 4 )
 	{
		cout << "Insufficient/Invalid Input. Arguments expected : NoOfHours Current Time Actual Time InputTime1 InputTime2 ....." << endl;
		return -1;
 	}

 	//Get the valid values from the arguments
	int iHoursInDial = atoi(argv[1]);
	int iCurrentTime = atoi(argv[2]);
	int iActualTime = atoi(argv[3]);
	//int iForward = atoi(argv[4]);
	//int iBackward = atoi(argv[5]);
	int iNoOfArguments = argc -4;
	

	list<int> iArguments;

     cout<<endl<<endl;
     cout<<" The Current Hours in the dial : "<<iHoursInDial<<endl;
     cout<<" The Current time in the dial : "<<iCurrentTime<<endl;
     cout<<" The Actual/Desired time in the dial : "<<iCurrentTime<<endl;
     cout << endl << "Total No. of Arguments Passed " << iNoOfArguments <<endl;
     cout<<endl<<endl;
     cout<<"   Processing ......"<<endl<<endl;
    
    //ADd the 'n' arguments to the List 
	for(int i=0;i<(argc-4);i++)
	{
		iArguments.push_back(atoi(argv[i+4]));
	}

	list<int> Solution;
	list<int>::iterator i;
	//Check for the validity of the Arguments
	if(iCurrentTime < 1 || iActualTime < 1 || iHoursInDial < 1)
	{
		cout << " Incorrect Arguments : Time entered is not correct/invalid";
		return -1;
	}
	//Sufficient But Incorrect
	if(iCurrentTime <= iHoursInDial && iActualTime <= iHoursInDial)
	{
	    //ClockSolver<int> solve(atoi(argv[1]),atoi(argv[2]),atoi(argv[3]));
	    //Initialize Values
		ClockSolver solve(iHoursInDial,iCurrentTime,iActualTime,iArguments);
		//Get the Solution 
		Solution = Resolve(solve);
		cout<<endl;
		//Print the Solution 
		if(!Solution.empty())
		{
		  cout <<" Printing Solution :"<<endl<<endl;
		  cout <<" START ";
	     for( i= Solution.begin();i!=Solution.end();++i)
	      {
			  cout<<"  -->  " << *i;
		  }
		  cout<< " -->  END " <<endl<<endl;
		}
		else
		{		    
		 cout << " No solutions exists.  Try changing the arguments and try again." << endl;
	    }
    }
    //If Invalid Arguments
    else
	{
		cout << " Incorrect Arguments : Current/Actual Time cannot be greater than the hours on the dial";
		return -1;
	}

}