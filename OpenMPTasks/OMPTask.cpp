#include <omp.h>
#include <stdio.h>
#include <windows.h>

void Task1_2() {
	omp_set_num_threads(2);
#pragma omp parallel num_threads(22)
	{
		printf("Hello world!\n");
	}
}

void Task3() {
	int k;
	scanf_s("%d", &k);
#pragma omp parallel num_threads(k)
	{
		//if (omp_get_thread_num() % 2 == 0)
		//{
			printf("I am %d thread from %d threads!\n",
				omp_get_thread_num(), //Ќомер нити в параллельной области
				omp_get_num_threads() // оличество нитей в параллельной области
			);
		//}
	}
}

void Task4() {
	int k, rank;
	scanf_s("%d", &k);
#pragma omp parallel num_threads(k) shared(rank)
	{
		rank = omp_get_thread_num();
		//Sleep(1000);
		printf("I am %d thread.\n", rank);
	}
}

void Task5_1() {
	int n, sum;
	sum = 0;
	scanf_s("%d", &n);
#pragma omp parallel num_threads(2) shared(n) reduction(+:sum)
	{
		if (omp_get_thread_num() == 0) {
			for (int i = 1; i <= n/2; i++)
			{
				sum += i;
			}
			printf("[%d]: Sum = <%d>\n", omp_get_thread_num(), sum);
		}
		else {
			for (int i = (n/2)+1; i <= n; i++)
			{
				sum += i;
			}
			printf("[%d]: Sum = <%d>\n", omp_get_thread_num(), sum);
		}
	}
	printf("Sum = <%d>\n", sum);
}

void Task5_2() {
	int k, n, sum, intgr, mod;
	sum = 0;
	scanf_s("%d", &k);
	scanf_s("%d", &n);
	intgr = n / k;
	mod = n % k;
#pragma omp parallel num_threads(k) shared(n, intgr, mod) reduction(+:sum)
	{
		int thread = omp_get_thread_num();

		if (mod > 0)
		{
			if (thread < mod)
			{
				for (int i = thread * (intgr + 1) + 1; i < (thread + 1) * (intgr + 1) + 1; i++)
					sum += i;
			}
			else
			{
				for (int i = thread * intgr + 1 + mod; i < intgr * (thread + 1) + 1 + mod; i++)
					sum += i;
			}
		}
		else
		{
			for (int i = thread * intgr + 1; i < intgr * (thread + 1) + 1; i++)
				sum += i;
		}
		printf("[%d]: Sum =  %d\n", thread, sum);
	}
	printf("Sum = <%d>\n", sum);
}

void main() {
	Task1_2();
	Task3();
	Task4();
	Task5_1();
	Task5_2();
}