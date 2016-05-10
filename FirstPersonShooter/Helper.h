#include <glm/glm.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
using namespace glm;
class HelperMethods
{
public:
	HelperMethods()
	{
	}

	~HelperMethods()
	{}
	static vec3 Get_Random_Direction()
	{
		time_t seconds ;
		time(&seconds);
		srand(seconds+rand()%10000000000000000);
		float RandZ = 2 * (double)rand() / (double)RAND_MAX - 1;
		float RandX = 2 * (double)rand() / (double)RAND_MAX - 1;
		
		return vec3(RandX,0,RandZ);
	}
};

