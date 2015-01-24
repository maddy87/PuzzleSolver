



#include "resolver.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

/* Class Name : NJugSolver
 * 
 * Descrition : Class created from the Resolver Template 
                which implents the virtual functions
 */
class NJugSolver : public Resolver< vector<int> >
{
 public:
   
   vector<int> iContainers;
   vector<int> iInitialCapacity;
   int iGoal;
   //Constructor to Initialize current capacity
   NJugSolver(vector<int> Containers,vector<int> InitialCap,int goal)
   :Resolver(InitialCap),iGoal(goal),iContainers(Containers),iInitialCapacity(InitialCap){}
   
   /* Function Name: IfSolutionMet
   * 
   * Description: Checks if the desired portion of water was 
   *              available in any of the jugs
   * CurrentStepQuantities : vector containing current quantities of all containers
   *                
   */
   bool IfSolutionMet(vector<int> CurrentQuantities)
   {
      for(int iLoop = 0; iLoop<CurrentQuantities.size();iLoop++)
      	   {
      	   	if(CurrentQuantities[iLoop] == iGoal)
      	   	    return true;
      	   }
	  return false;
   }
   
   /* Function Name: PrintSteps
   * 
   * Description: Prints the solution with the brief traversal
   *              of the nodes that lead to the solution.
   * CurrentCapacities : vector argument containing the current quantities of all containers
   */
   void PrintSteps(vector<int> CurrentCapacities)
   {
   	  
  	  cout<< " Intermediate Status  : ";
  	  for(int iLoop = 0; iLoop<CurrentCapacities.size();iLoop++)
     	  {
     	  	
  	      cout<< "<" << CurrentCapacities[iLoop]<<">"<<iContainers[iLoop]<<"  ";   
  	    }
  	  cout <<endl;
   }

   

  /* Function Name: GetNextStep
   * 
   * Description: Generates a list of next configurations from the current input
   * return list : List contains all the possible sequences that were generated 
   *               using input config
   */

   list< vector<int> > GetNextStep(vector<int> iCurrentStatus)
   {

        list< vector<int> > lCurrentCapacity;
        
        //Filling the CurrenCapacities Fully
        cout <<endl;
        for(int iLoop=0;iLoop<iCurrentStatus.size();iLoop++)
        {
        	vector<int> cFilledStatus = iCurrentStatus;
        	//To update the values in the vector which point to Filled Status
        
              cFilledStatus[iLoop] = iContainers[iLoop];       
              if(cFilledStatus != iCurrentStatus)
              {
                lCurrentCapacity.push_back(cFilledStatus);
                cout << " Filling Container "<<cFilledStatus[iLoop];
              }
        }
   		  cout<<endl;

   	   	//Emptying the Containers
        for(int iLoop=0;iLoop<iCurrentStatus.size();iLoop++)
        {
        	vector<int> cFilledStatus = iCurrentStatus;
        	//To update the values in the vector which point to Filled Status
              cFilledStatus[iLoop] = 0; 
              if(cFilledStatus != iCurrentStatus)
              {
                lCurrentCapacity.push_back(cFilledStatus);
                cout << " Emptying Container's "<<cFilledStatus[iLoop];
              }
        }
        
        //Pour Each Container Into Another. Repeat for N jugs
        vector<int> cFilledStatus = iCurrentStatus;
        int iOverFlow;
        for(int iLoop = 0;iLoop<iCurrentStatus.size();iLoop++)
        {
        	  cFilledStatus = iCurrentStatus;
            int iPourFrom = iCurrentStatus[iLoop];
         	for(int iInnerLoop = 0;iInnerLoop<iCurrentStatus.size();iInnerLoop++)
        	{
            //Dont repeat for same Container
        		if(iInnerLoop != iLoop)
        		{
              //Get the capacity of the current containers
        			int iPourIn = iCurrentStatus[iInnerLoop];
        			int iNewCapacity = iPourIn + iPourFrom;
              //If OverFlowed then take care of it 
        			if(iNewCapacity > iContainers[iInnerLoop])
        			{
        			 iOverFlow = iNewCapacity - iContainers[iInnerLoop];
        			 cFilledStatus[iLoop] = iOverFlow;
        			 cFilledStatus[iInnerLoop] = iContainers[iInnerLoop];
        			}
              //If NOT Overflowed
        			else
        			{
        				cFilledStatus[iInnerLoop] = iNewCapacity;
        				cFilledStatus[iLoop] = 0;
        			}
              //Printing the Poured Value and adding it to the list of generated sequences
        			if(cFilledStatus != iCurrentStatus)
        			{
        	           lCurrentCapacity.push_back(cFilledStatus);
                       //cout <<endl<< " Poured Container <"<<cFilledStatus[iLoop]<<"> in"<<iContainers[iLoop]<< " into  <"<<cFilledStatus[iInnerLoop]<<"> in"<<iContainers[iInnerLoop];
                       cout<<endl << " Pouring Container "<<iContainers[iLoop]<< " ----->  "<<iContainers[iInnerLoop];
        			}
        		}
        	}
        }
   		

   	    return lCurrentCapacity;
    }
};
int main(int argc,char const *argv[])
{

  //Check if Invalid No of Arguments
  if ( argc < 3)
 	{
		cout << "Insufficient/Invalid Input. Arguments expected : Desired Amount Container1 Capacity | Container2 Capacity ....." << endl;
		return -1;
 	}

  //Declaring Variables
 	vector<int> iTotalContainers;
 	vector<int> iInitialCap;
 	list<vector<int> > Solution;
	list<vector<int> >::iterator it;
  int iGoalValue = atoi(argv[1]);
	int iLoop =2;

  //Pushing Initial Config and get the Container Capacity
 	for(;iLoop < argc;++iLoop)
 	{
 		//Initial Empty Containers
 		iInitialCap.push_back(0);
 		iTotalContainers.push_back(atoi(argv[iLoop]));
 		//cout << iTotalContainers[iLoop] << "   " ;
 	}
  
  //Printing the containers that we have  
  for(int i=0;i<iTotalContainers.size();i++)
    	 cout << " "<< iTotalContainers[i];
     
  cout <<endl;

  //Initializing the values
  NJugSolver solve(iTotalContainers,iInitialCap,iGoalValue);
  //Get the solution 
    Solution = Resolve(solve);

	cout<<endl;
	it = Solution.begin();
  //Printing the Solution
	if(!Solution.empty())
	{
	  cout << "               : <FilledAmount of Container>Size Of Container"<<endl;
      for(;it!=Solution.end();++it)
      {
	 	  solve.PrintSteps(*it);
	  }	
	}
  //If No Solution Exists
  else
    cout<<" The desired amount of water cannot be obtained from the given list of Containers";
    
}