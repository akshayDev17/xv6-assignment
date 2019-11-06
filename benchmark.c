#include "types.h"
#include "user.h"


int
main(int argc, char *argv[])
{
	if (argc != 2){
				printf(1, "Usage: benchmark <n>\n");
				exit();
 		}
	int i;
	int n;
	int j = 0;
	int start_priority = 100;
	int k;
	int rutime;
	int stime;
	int sums[3][2];
	for (i = 0; i < 3; i++)
		for (j = 0; j < 2; j++)
			sums[i][j] = 0;
	n = atoi(argv[1]);
	i = n; //unimportant
	int pid;
	for (i = 0; i < 3 * n; i++) {
		j = i % 3;
		pid = fork();
		if(pid > 0){
			// parent process
			int id1 = getpid();
            chpr(id1, start_priority);
		}
		else if (pid == 0) {//child
			int id2 = getpid();
            chpr(id2, start_priority);
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			switch(j) {
				case 0: //CPU‐bound process (CPU):
					for (k = 0; k < 1000; k++){
						for (j = 0; j < 1000000; j++){}
					}
					break;
				case 1: //short tasks based CPU‐bound process (S‐CPU):
					for (k = 0; k < 10000; k++){
						for (j = 0; j < 1000000; j++){}
						yield();
					}
					break;
				case 2:// simulate I/O bound process (IO)
					for(k = 0; k < 1000; k++){
						sleep(1);
					}
					break;
			}
			exit(); // children exit here
		}
		start_priority -= 10;
		if(start_priority <= 0){
			start_priority = 100;
		}
		continue; // father continues to spawn the next child
	}
	for (i = 0; i < 3 * n; i++) {
		pid = waitx(&stime, &rutime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: // CPU bound processes
				printf(1, "CPU-bound, pid: %d,  running: %d, sleeping: %d, turnaround: %d\n", pid,  rutime, stime, rutime + stime);
				sums[0][0] += rutime;
				sums[0][1] += stime;
				break;
			case 1: // CPU bound processes, short tasks
				printf(1, "CPU-S bound, pid: %d,  running: %d, sleeping: %d, turnaround: %d\n", pid,  rutime, stime, rutime + stime);
				sums[1][0] += rutime;
				sums[1][1] += stime;
				break;
			case 2: // simulating I/O bound processes
				printf(1, "I/O bound, pid: %d,  running: %d, sleeping: %d, turnaround: %d\n", pid, rutime, stime, rutime + stime);
				sums[2][0] += rutime;
				sums[2][1] += stime;
				break;
		}
	}
	for (i = 0; i < 3; i++)
		for (j = 0; j < 2; j++)
			sums[i][j] /= n;
	printf(1, "\n\nCPU bound:\n Average running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[0][0], sums[0][1],  sums[0][0] + sums[0][1] );
	printf(1, "CPU-S bound:\n Average running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[1][0], sums[1][1], sums[1][0] + sums[1][1] );
	printf(1, "I/O bound:\n Average running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", sums[2][0], sums[2][1], sums[2][0] + sums[2][1] );
	exit();
}
