

#ifndef core_h
#define core_h

#include <stdio.h>
#define TRUE 1
#define FALSE 0
enum cellValues
{
	0,1,2,3,4,5,6,7,8,9
};

typedef struct cell
{
	int value;
	int visited = FALSE; 
};
#endif /* core_h */
