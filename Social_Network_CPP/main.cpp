#include <iostream>
using namespace std;
#include "admin.h"

int main()
{
    std::ifstream inputFile("facebook.dat", std::ios::binary);
    Admin fb(inputFile);
    fb.promptMenu();
    std::ofstream outputFile("facebook.dat", std::ios::binary);
    if (outputFile.good())
        fb.save(outputFile);
    outputFile.close();
}