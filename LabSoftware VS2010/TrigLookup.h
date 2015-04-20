#ifndef TRIGLOOKUP_
#define TRIGLOOKUP_

#define PI 3.14159

class TrigLookup
{
	
public:

	/******************
	Description: Creates if needed and returns the TrigLookup singleton object
	Parameters: NIL
	Preconditions: NIL
	Postconditions: NIL
	Returns:  The trigLookup singleton.
	*******************/
	static TrigLookup* getSingleton();

	/******************
	Description:Looks up the value of cos(x) in degrees
	Parameters: int x: number of degrees
	Preconditions: 0 <= x <= 360
	Postconditions: NIL
	Returns:  The value of cos(x)
	*******************/
	double cosLookup(int x);

	/******************
	Description:Looks up the value of sin(x) in degrees
	Parameters: int x: number of degrees
	Preconditions: 0 <= x <= 360
	Postconditions: NIL
	Returns:  The value of sin(x)
	*******************/
	double sinLookup(int x);

	static const int MAX_VALUES = 360;

private:
	
	//The cos and sin lookup tables
	double cosL[MAX_VALUES], sinL[MAX_VALUES];
	
	/******************
	Description:Fills the sin and cos arrays with the value of cos(index) or sin(index)
	Parameters: int x: number of degrees
	Preconditions: NIL
	Postconditions: sin and cos lookup tables are filled
	Returns:  void
	*******************/
	TrigLookup();



};


#endif