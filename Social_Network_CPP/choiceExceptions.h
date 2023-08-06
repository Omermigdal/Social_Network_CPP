#ifndef __CHOICE_EXCEPTION_H
#define  __CHOICE_EXCEPTION_H
#include "adminExceptions.h"

class choiceExceptions
{
	int m_min, m_max;

public:

	choiceExceptions(int min, int max) : m_min(min), m_max(max) {}
	void what() { std::cout << "Invalid choice, please enter a number between " << m_min << " and " << m_max << std::endl; }





};


#endif //CHOICE_EXCEPTION

