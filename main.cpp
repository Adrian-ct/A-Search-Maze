#include <iostream>
#include "A_star.h"
#include <fstream>
void ReadFromFile(std::istream& in,A_star& a_star)
{
    in >> a_star;
}
int main()
{
    A_star a_star;
    std::ifstream f("date.txt");

    ReadFromFile(f, a_star);

    
    a_star.search();

    return 0;
}

