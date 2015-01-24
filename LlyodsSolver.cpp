/**
 * ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 * FileName    : LlyodsSolver.cpp
 * Description : The program simulates a Sam Llyods puzzle and provides the 
 * desired output when the initial and desired configuration are entered
 *  
 * @version  :  LlyodsSolver.cpp v 1.0  2014/11/30  2:04 AM
 * 
 * @author(s)  rss2158 (Rajesh Shetty)
 *            
 * 
 *=============================================================================
 */


 //Including Header Files
//#include "stdafx.h"
#include "resolver.h"
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
#include <fstream>
using namespace std;

/* Class Name : LlyodSolver
 * 
 * Descrition : Class created from the Resolver Template 
                which implents the virtual functions
 */
class LloydSolver : public Resolver<string>
{ 
  
 public:
   int iHeight;
   int iWidth;
   string sInitalInput;
   string sDesiredOutput;
   
   //Constructor to intiailize the Box dimensions
   LloydSolver(string sInput,string sOutput,int Height,int Width)
   :Resolver(sInput),iHeight(Height),iWidth(Width),sInitalInput(sInput),sDesiredOutput(sOutput){}
   
   /* Function Name: IfSolutionMet
   * 
   * Description: Checks if the desired goal was met and 
   *              returns TRUE if met and False if otherwie
   * CurrentPatter : string argument containing the current
   *                 pattern popped off from the queue
   */
   bool IfSolutionMet(string CurrentPattern)
   {
       return sDesiredOutput == CurrentPattern;
   }
   
   /* Function Name: PrintSteps
   * 
   * Description: Prints the solution with the brief traversal
   *              of the nodes that lead to the solution.
   * CurrentPatter : string argument containing the current
   *                 pattern popped off from the top of the queue
   */  
   void PrintSteps(string CurrenPattern)
   {
      cout<< " Intermediate Status  : ";
      cout<<CurrenPattern; cout <<endl;
   }

   
   /* Function Name: SwapPosition
   * 
   * Description: Swaps the characters present at the iCurr and
   *              iModified position and returns the modified pattern
   * sPattern : string argument containing the current
   *            pattern popped off from the top of the queue
   * iCurr : Swap Position which has the whitespace '.'
   * iModified : Swap Position where  '.' needs to be moved.
   */  
   string SwapPosition(string sPattern,int iCurr,int iModified)
   {
      
      string sModified = sPattern;
      //Retireve char at Postion iCurr
      string  sCurr = sModified.substr(iCurr,1); //"" + sPattern.at(iCurr);
      //Retireve char at Postion iModified
      string  sModi = sModified.substr(iModified,1);//"" + sPattern.at(iModified);
      
      //Swap The chars and generate new String 
      sModified.replace(iCurr,1,sModi);
      sModified.replace(iModified,1,sCurr);
      return sModified;
   }

   /* Function Name: CheckBoundaries
   * 
   * Description: Handles the Out of Bounds Error by validating the 
   *              position to be inside the boundaries
   * sCurrentPattern : Current string value to checked
   * iModified : Position/Index on which Swap was requested.
   */  
   bool CheckBoundaries (string sCurrentPattern,int iModified)
   {
    
      if(iModified < 0 || iModified > (sCurrentPattern.size() -1))
      {
        return false;
      }
      else
      {
        return true;
      }
   }

   /* Function Name: GetNextStep
   * 
   * Description: Generates a list of Patterns from the input string
   * sCurrentPattern : Input string that ensures that patterns can be generated
   * return list : List contains all the possible sequences that were generated 
   *               using input string 
   */  
   list<string> GetNextStep(string sCurrentPattern)
   {

        list<string> lCurrentCapacity;
        string sGeneratedPattern = sCurrentPattern;
        //Get the position in the current string where '.' is placed
        int iPosition = sGeneratedPattern.find('.');
        int iModified = iPosition;

       
        //Swap One Step Left
        // Example abcd.efgh =  abc.defgh
        if(CheckBoundaries(sCurrentPattern,iModified-1)) //Check if withing Boundaries
        {
            sGeneratedPattern =  SwapPosition(sCurrentPattern,iPosition,iModified-1);
            //cout << sGeneratedPattern <<endl;
            if(sGeneratedPattern!= sCurrentPattern)
            {
              lCurrentCapacity.push_back(sGeneratedPattern);
            }
        }
        

        //Swap One Step Right
        // Example abcd.efgh =  abcde.fgh
        if(CheckBoundaries(sCurrentPattern,iModified+1)) //Check if withing Boundaries
            {
              sGeneratedPattern =  SwapPosition(sCurrentPattern,iPosition,iModified+1);
              //cout << sGeneratedPattern <<endl;
              if(sGeneratedPattern!= sCurrentPattern)
              {
                 lCurrentCapacity.push_back(sGeneratedPattern);
              }
            }
        
        //Swap One Step Up
        // Example abcd.efgh =  a.cdbefgh
        if(CheckBoundaries(sCurrentPattern,iModified-iWidth)) //Check if withing Boundaries
        {
            sGeneratedPattern =  SwapPosition(sCurrentPattern,iPosition,iModified-iWidth);
            //cout << sGeneratedPattern <<endl;
            if(sGeneratedPattern!= sCurrentPattern)
            {
              lCurrentCapacity.push_back(sGeneratedPattern);
            }
        }
        

        //Swap One Step Down
        // Example abcd.efgh =  abcdgef.h
        if(CheckBoundaries(sCurrentPattern,iModified+iWidth)) //Check if withing Boundaries
        {
            sGeneratedPattern =  SwapPosition(sCurrentPattern,iPosition,iModified+iWidth);
            //cout << sGeneratedPattern <<endl;
            if(sGeneratedPattern!= sCurrentPattern)
            {
              lCurrentCapacity.push_back(sGeneratedPattern);
            }
        }
        
      return lCurrentCapacity;

    }
  
};

int main(int argc,char const *argv[])
{
  
   
  string sFileName; // Will Contain the name of the input file
  string sOutputFileName; // Will Contain the name of the output file
  string sTotalInput; //String which contains the raw total input
  string sInitialState; //String deduced form sTotalInput to represent initial configuration
  string sFinalState; //String deduced from sTotalInput to represent final configuration
  //Height and Widht 
  int iWidth;
  int iHeight;
  int iLoop;
  //Lsit ot store the Solutions Generated
  list<string> Solution;
  list<string>::iterator it;
  //Get the desired input file 
  cout << "Enter the name of the Input File (InCase of No File press '-' )  : ";
  cin >> sFileName;
  //If Input is expected from Standard In
  if(sFileName == "-")
  {
      cout<<"Taking input from STD "<<endl<<endl;
      //Process Input
      cout<<"Enter the Width of the Box : ";
      cin >> iWidth;
      cout<<"Enter the Height of the Box : ";
      cin >> iHeight;
      //Get Row wise Input from STDIN
      string sInput[iHeight];
      //Get Row wise Desired Output from STDIN
      string sFinalConfig[iHeight];;
  

      //Get the Configuration of the Input
       
      for(iLoop =0;iLoop<iHeight;iLoop++)
      {
         cout << " Enter the Row "<<iLoop+1<<" of the Llyods Config : ";
         cin >> sInput[iLoop];
         if(sInput[iLoop].size()!= iWidth)
              {
                cout << " Entered Row config is not correct. "<<endl;
                cout << " You will have to enter all the Information Again."<<endl;
                cout << " You can use a File to avoid this"<<endl;
                return -1;
              }
      }

      //Get the Configuration of the Output
      cout<<endl<<endl<<" Please provide the desired final config "<<endl<<endl;
      for(iLoop =0;iLoop<iHeight;iLoop++)
      {
         cout << " Enter the Row "<<iLoop+1<<" of the Llyods Desired Final Config : ";
         cin >> sFinalConfig[iLoop];
         if(sFinalConfig[iLoop].size() != iWidth)
              {
                cout <<endl<< " Entered Row config is not correct. "<<endl;
                cout << " You will have to enter all the Information Again."<<endl;
                cout << " You can use a File to avoid this"<<endl;
                return -1;
              }
      }

      //Printing the Input & Output
      cout<<endl<<endl<<"Input Configuration For LLyods Puzzle "<<endl<<endl;
      //cout<<endl<< "Height " << iHeight << " Width "<<iWidth<<endl;
      for(int iLoop = 0;iLoop<iHeight;iLoop++)
      {
        cout<<sInput[iLoop]<<endl ;
        sTotalInput = sTotalInput + sInput[iLoop];
        sInitialState = sInitialState + sInput[iLoop];
      } 
      /*
      for(int iLoop = 0;iLoop<iHeight;iLoop++)
      {
        cout<<sFinalConfig[iLoop]<<endl ;
        sTotalInput = sTotalInput + sFinalConfig[iLoop];
        sFinalState = sFinalState + sFinalConfig[iLoop];
      } 

      cout<<sTotalInput<<endl;
      cout<<" Input State "<<sInitialState<<endl;
      cout<<" Final State "<<sFinalState<<endl;
      */
 }
 //Read Input From the File
 else
 {
   
   string sInput;
   string sFirstLine;
   //To Read Input 
   ifstream fInputFile;
   fInputFile.open("input.txt");
   //GEtting the first line of the file which has the width and height
   while(!fInputFile.eof())
   {
       //cout << " Here ";
        getline(fInputFile,sFirstLine);
        if(!(sFirstLine.size() == 0))
              break;
   }
   
   //Reading Rest of the Lines
   while(!fInputFile.eof())
   {
       //cout << " Here ";
        getline(fInputFile,sInput);
        cout << sInput<<endl;
        sTotalInput = sTotalInput + sInput;
   }
   
   //cout << sFirstLine<<endl;
   //cout << sTotalInput;
   int iPosition = sFirstLine.find(' ');
   string sWidth = sFirstLine.substr(0,iPosition);
   string sHeight = sFirstLine.substr(iPosition);
   //cout <<" Width "<< sWidth<<" Height "<<sHeight;

   //Close the file after reading
   fInputFile.close();
   iHeight = atoi(sHeight.c_str());
   iWidth = atoi(sWidth.c_str());
   //cout <<" Width "<< iWidth<<" Height "<<iHeight;
 }
   //Diving the Raw Input into Initial and Final
   int iDivide = iHeight*iWidth;
   //cout<<iDivide<<endl;
   //cout <<"TotatlInput "<<sTotalInput<<endl;
   sInitialState = sTotalInput.substr(0,iDivide);
   sFinalState = sTotalInput.substr(iDivide);
   //cout<<" Input State "<<sInitialState<<endl;
   //cout<<" Final State "<<sFinalState<<endl;
   
   //Get the Name of the Output File 
    cout << "Enter the name of the Output File (InCase of No File press '-' )  : ";
    cin >> sOutputFileName;
    cout<<endl<<" Processing "<<endl<<endl;

 //Initialize the Constructor
 LloydSolver solve(sInitialState,sFinalState,iHeight,iWidth);
 //Get the solution by calling the resolve function.
 Solution = Resolve(solve);
 cout<<endl;
 //If the Out is required in the File
 if(sOutputFileName != "-")
 {
   cout<<endl<<"Writing Output To File "<<sOutputFileName<<endl<<endl;  
   ofstream fOutput;
   fOutput.open("output.txt");
   it = Solution.begin();
    //Write the Output to the file
    if(!Solution.empty())
    {
      fOutput << " The Solution : \n\n";
      string sLast;
      //Write the combinations
      for(;it!=Solution.end();++it)
       {
          fOutput << *it<<"\n";  
          sLast = *it;
       } 
       fOutput<<"\n\n";
       //Write the output configurations
       for(int iLoop= 0;iLoop<iHeight;iLoop++)
       {
          string sLine = sLast.substr(0,iWidth);
          fOutput << sLine<<"\n";
          sLast = sLast.substr(iWidth);
       }
       //Close the file
       fOutput.close();
    }

 }
 //Output the Solution to STDOUT
 else
 {
 	 it = Solution.begin();
	 if(!Solution.empty())
	 {

      for(;it!=Solution.end();++it)
      {
      //Print the output
	 	  solve.PrintSteps(*it);
	    } 	
	 }
  } 
}