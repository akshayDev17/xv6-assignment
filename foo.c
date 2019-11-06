#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[])
{
    int k, n = 1, id, factor = 5;
    double x=0, z;

    int ipr;

    if(argc < 2){
        ipr = 60;  // default value
    }
    else{
        ipr = atoi(argv[1]);  // from user input
        if(argc >= 3){
            factor = atoi(argv[2]);
        }
    }
    if(ipr < 0 || ipr > 100)
        ipr = 60;
    if(factor < 0 || factor > 10){
        factor = 5;
    }


    x = 0;
    id = 0;
    k = 0;
    printf(1, "The value of factor is %d .\n", ipr);
    while(k<n)
    {
        id = fork();
        if(id < 0)
            printf(1, "%d failed in fork!\n", getpid());
        else if(id > 0)
        {   // Parent
            int id1 = getpid();
            chpr(id1, ipr);
            printf(1, "Parent %d creating child %d\n", id1, id);
            wait();
        }
        else
        {   // Child
            int id2 = getpid();
            chpr(id2, ipr);
            printf(1, "Child %d created\n", id2);
            double end = 250000.0 * factor; 
            for(z=0;z<end;z+=0.001)
                x = x + 3.14*89.64; // Useless calculations to consume CPU time
            break;
        }
        k++;
    }
    exit();
}
