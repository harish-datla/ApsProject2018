#include <bits/stdc++.h>
#include <math.h>
#include <fstream>
#include <chrono>
#include <ctime>
#include <time.h>
using namespace std::chrono;
using namespace std;
ofstream sortedseq;

ofstream randomseq;

int RandomTime()
{
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);

    return nanoseconds.count();
}

int Random()
{

    srand(RandomTime());
    return rand();
    
}


int main()
{
    sortedseq.open ("sorted_seq.txt");
    bool isthere[1048575] = {false}; 
    for(int i = 1 ; i <= 1048575 ; i++)
    {
        
        sortedseq << i  << endl;

    }
    
    sortedseq.close();

    randomseq.open ("random_seq.txt");
    
    for(int i = 1 ; i <= 1048575 ; i++)
    {
       int x = Random() % 1048575;
        if(isthere[x])
        {
         i = i - 1;
        }
        else
        {
            randomseq << x << endl;
            isthere[x] = true;
        }

    }
    randomseq.close();
    

}