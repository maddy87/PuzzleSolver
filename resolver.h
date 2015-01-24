/**
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * FileName    : resolver.h
 * Description : The abstract class that simulates an BFS to solve puzzles
 				 which once possible outputs and desired output is provided
 * @version  :  resolver.h v 1.0  2014/11/30  05:12 PM
 * 
 * @author(s)  rss2158 (Rajesh Shetty)
 
 * 
 *=============================================================================
 */


//#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <cstdlib>
#include <algorithm>
using namespace std;

/* Class Name : Resolver
 * 
 * Descrition : Abstract Class that is used as template by the puzzles
 *		
 */
template<class T>
class Resolver
{
  public:
  	T desiredSolution;
  	T intialStep;
 
    //Constructor To Initiaze the initial config
  	Resolver(T initconfig)
	{intialStep = initconfig;
    }
	
  	//Virtual fucntions that are defined in the derived class
     virtual list<T> GetNextStep(T currentStep)=0;
     virtual bool IfSolutionMet(T currentStep)=0;
     virtual void PrintSteps(T currentStep)=0;
};

/* Function Name : Resolve
 * 
 * Description : Defines the solver function which implements pure
 *				 BFS to reach the final solution from the  
 *               intial config
 */
template<class T>
list< T > Resolve(Resolver< T > &resolve)
{
	   map<T,T> mVisitedSteps;
	   queue<T> qCurrentSteps;
	   list<T> lSolution;
	   T iCurrentTime = resolve.intialStep; ///Changing here 3:40 AM
	   T iActualTime;
      
	 
	   //Adding current config to Visited Steps
	   mVisitedSteps[resolve.intialStep] = resolve.intialStep;
	   //Adding the first config to the qCurrentSteps
	   qCurrentSteps.push(iCurrentTime);
	   //while(!(qCurrentSteps.empty()) && (qCurrentSteps.front() != iActualTime))
	   while(!qCurrentSteps.empty() && (!resolve.IfSolutionMet(iActualTime = qCurrentSteps.front())))
	   {

		   //Get the top value from the Queue and pop it out
	   	   //cout <<"Size of the queue " << qCurrentSteps.size() << endl;
		   T frontValue = qCurrentSteps.front();
		   //cout << " Queue Current Steps Front Value  "<< frontValue<<endl;
		   qCurrentSteps.pop();
		   //Get the next steps or sequences from the first one 
		   list<T> NextSteps = resolve.GetNextStep(frontValue);
		   while(!NextSteps.empty())
		   { 

			   T curr = NextSteps.front();
			   //cout << " NextSteps Front Value  "<< curr<<endl;
			   NextSteps.pop_front();
			   if((mVisitedSteps.find(curr) == mVisitedSteps.end()))
			   {
				   //Not Visited Then Add To Visited And SolutionSteps Queue
			   	   qCurrentSteps.push(curr);
				   mVisitedSteps[curr] = frontValue;
			   }
			   
		   }
		   //Displaying the Map
		   //map<T,T> mVisitedSteps::iterator i;
		   //for(i=mVisitedSteps.begin();i<mVisitedSteps.end();i++)
		   //{cout << i->first < " " < i->second;}
		   iActualTime = qCurrentSteps.front();
		   
		   //cout << "Currently Reached Actual Time "<<iActualTime<<endl; 
	   }
       
	   //cout << " REACHED HERE  "<< endl;
	   if(resolve.IfSolutionMet(iActualTime = qCurrentSteps.front()))
	   {


		   T NextSolution = qCurrentSteps.front();
		   lSolution.push_front(qCurrentSteps.front());
		   //Push the solution in the list

		   while(NextSolution != iCurrentTime)
		   {
		     NextSolution = mVisitedSteps[NextSolution];
	 		 lSolution.push_front(NextSolution);
		   }

	   }

		/*if(bForward)
		{
			if(bCrossOver)
				cout<<endl<<"Winding the ClockBackward to Match the correctTime"<<endl;	
			else
			   cout<<endl<<"Winding the ClockForward to Match the correctTime" <<endl;
			
		}
		else
		{
			if(bCrossOver)
				cout<<endl<<"Winding the ClockForward to Match the correctTime" <<endl;
			else 
				cout<<endl<<"Winding the ClockBackward to Match the correctTime"<<endl;
			
		}*/
	   return lSolution;
}



