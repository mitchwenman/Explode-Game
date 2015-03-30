#ifndef TRIGLOOKUP_
#define TRIGLOOKUP_



class TrigLookup
{
	
public:

	static TrigLookup* getSingleton();

	double cos(int x);

	double sin(int x);
	static const int MAX_VALUES = 360;

private:
	

	int cosLookup[MAX_VALUES], sinLookup[MAX_VALUES];
	
	TrigLookup();



};


#endif