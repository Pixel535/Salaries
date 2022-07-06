#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>
#define MAXN 1000004

// pi != i - przelozony pracownika i
// pi == i - nr dyrektora bfo
// zi > 0 - wysokosc pensji pracownika nr i
// zi == 0 - pensja pracownika nr i nie jest znana

int SalariesArr[MAXN];
int BossesArray[MAXN];
int UsedSalariesArr[MAXN];
int NumOfWorkersArr[MAXN];
int OneWorker[MAXN];
int level[MAXN];
int queue[MAXN];
int start = 0;
int end = 0;
int n;
int pi;
int zi;

void printArr()
{
    for(int i = 1; i < n; i++)
    {
        std::cout << SalariesArr[i] << std::endl;
    }
}

void How_Many_Workers()
{
    for(int i = 1; i < n; i++)
    {
        level[i] = 0;
    }
    for(int i = 1; i < n; i++)
    {
        level[BossesArray[i]]++;
    }
    for(int i = 1; i < n; i++)
    {
        if(level[i] == 0)
        {
            queue[end++] = i;
        }
    }
    while(start < end)
    {
        int QueueVal = queue[start++];
        int BossVal = BossesArray[QueueVal];
        if(SalariesArr[QueueVal] == 0)
        {
            if(--level[BossVal] == 0)
            {
                queue[end++] = BossVal;
            }
            NumOfWorkersArr[BossVal] += NumOfWorkersArr[QueueVal]+1;
        }
    }
}

void Used_Salary()
{
    for(int i = 1; i < n; i++)
    {
        if(SalariesArr[i] != 0)
        {
            UsedSalariesArr[SalariesArr[i]] = i;
        }
        else if(OneWorker[BossesArray[i]] == 0)
        {
            OneWorker[BossesArray[i]] = i;
        }
        else
        {
            OneWorker[BossesArray[i]] = -1;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    
    std::cin >> n;

    if (n > 1000004 || n < 1)
    {
        std::cout << "n must be >= 1 and <= 1 000 004";
    }
    else
    {
        for(int i = 1; i <= n; i++)
        {
            std::cin >> pi;
            std::cin >> zi;
            
            if ((pi < 1 || pi > n) || (zi < 0 || zi > n))
            {
                std::cout << "pi must be >= 1 and <= n OR zi must be >= 0 and <= n";
            }
            else
            {
                SalariesArr[i] = zi;
                BossesArray[i] = pi;
                
                if(BossesArray[i] == i) SalariesArr[i] = n;
                if(SalariesArr[i] != 0) BossesArray[i] = n+1;
            }
        }
        n++;
        BossesArray[n] = n;
        SalariesArr[n] = n;
        How_Many_Workers();
        Used_Salary();
        int x = 0;
        int NotUsedSalary = 0;
        int NumberOfValuesLeft = 0;
        while(x < n-1)
        {
            while(x < n-1 && UsedSalariesArr[x+1] == 0)
            {
                NumberOfValuesLeft++;
                NotUsedSalary++;
                x++;
            }
            while(x < n-1 && UsedSalariesArr[x+1] != 0)
            {
                x++;
                int UsedSalVal = UsedSalariesArr[x];
                int l = x;
                NotUsedSalary -= NumOfWorkersArr[UsedSalVal];
                if(NotUsedSalary == 0)
                {
                    while(NumberOfValuesLeft-- && OneWorker[UsedSalVal] > 0)
                    {
                        while(UsedSalariesArr[l])
                        {
                            l--;
                        }
                        UsedSalVal = OneWorker[UsedSalVal];
                        SalariesArr[UsedSalVal] = l;
                        UsedSalariesArr[l] = UsedSalVal;
                    }
                    NumberOfValuesLeft = 0;
                }
                if(NumOfWorkersArr[UsedSalVal] != 0)
                {
                    NumberOfValuesLeft = 0;
                }
            }
        }
        printArr();
    }
}
