#include <iostream>
#include <fstream>
#include <string>

int main()
{
    int jokesCount = 0;
    std::string infile("blagues.txt");
    std::ifstream in(infile.c_str());
    if (!in.is_open())
        return 1;
    std::string line;
    for (;std::getline(in, line);jokesCount++)
        ;
    in.close();
    in.open("blagues.txt", std::ifstream::in);
    srand(time(NULL));
    int random = rand() % jokesCount;
    std::cout << random << std::endl;
    for (int j = 0;std::getline(in, line) && j < random; j++)
        ;
    std::cout << line << std::endl;
}