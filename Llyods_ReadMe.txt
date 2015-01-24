===============================================================================
File : llyod.cpp
Author's  : rss2158 (Rajesh Shetty)
===============================================================================
The program simulates a Sam Llyods puzzle and provides the desired output when 
the initial and desired configuration are entered. The Llyods puzzle implements 
the Puzzle class and implements that below methods
1. To initialize the Initial Configuration
2. Check if the given configuration meets the goal.
3. Generate Next Steps generates the next sequences.
	For example  : Consider the input config 3 X 3 with initial config
	Initital Config  :  a . b
						c d e
						f g h 
	Moving Left      :  . a b
						c d e
						f g h 
	Moving Right      :  a b .
						c d e
						f g h 
	Moving Down      : a d c
						c . e
						f g h 
4. The program accepts input and output in the below combinations
		./llyod inputfilename outputfilename
		./llyod - outputfilename
		./llyod inputfilename -
		./llyod - -