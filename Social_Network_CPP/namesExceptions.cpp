#include "namesExceptions.h"
using namespace std;


bool nameException::isNameValid(string& name)
{
	int len = (int)name.length();
	if (len == 0)
		return false;

	for (int i = 0; i < len; i++)
	{
		if (name[i] == ' ')
			continue;
		if (!((name[i] >= 'a' && name[i] <= 'z') || (name[i] >= 'A' && name[i] <= 'Z')))
		{
			return false;

		}
	}

	return true;


}