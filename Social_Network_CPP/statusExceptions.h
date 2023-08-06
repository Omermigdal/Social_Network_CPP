#ifndef __STATUS_EXCEPTIONS
#define  __STATUS_EXCEPTIONS
#include <iostream>
class statusExceptions
{
public:

	void what()const { std::cout << "Status can't be empty" << std::endl; }
};

#endif // __STATUS_EXCEPTIONS