#ifndef TRIGLOOKUP_
#define TRIGLOOKUP_



#define PI 3.14159

class TrigLookup
{
	
public:

	static TrigLookup* getSingleton();

	double cosLookup(int x);

	double sinLookup(int x);
	static const int MAX_VALUES = 360;

private:
	

	double cosL[MAX_VALUES], sinL[MAX_VALUES];
	
	TrigLookup();



};


#endif