#ifndef TRIGLOOKUP_
#define TRIGLOOKUP_

#define PI 3.14159

class TrigLookup
{
	
public:

	//Creates if needed and returns the TrigLookup singleton object
	static TrigLookup* getSingleton();

	//Looks up the cos value of x (given in degrees)
	double cosLookup(int x);

	//Looks up the sin value of x (given in degrees)
	double sinLookup(int x);

	static const int MAX_VALUES = 360;

private:
	
	//The cos and sin lookup tables
	double cosL[MAX_VALUES], sinL[MAX_VALUES];
	
	//Creates the TrigLookup object and fills the lookup tables
	TrigLookup();



};


#endif