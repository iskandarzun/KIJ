#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

uint32_t lcg_rand(uint32_t a)
{
    return ((uint64_t)a * 279470273UL) % 4294967291UL;
}

long long int generatePrime()
{
	long long int random = 0;
	int prime = 0;
	long long int result;

	while (random % 2 == 0 || prime == 0)
	{
		random = rand() % 100000;

		long long int limit = sqrt(random);

		prime = 1;
		for (long long int i = 3; i <= limit; i+=2)
		{
			if(random % i == 0)
			{
				prime = 0;
				break;
			}
		}

		if(prime == 1)
		{
			result = random;
		}
	}

	return result;
}

long long int getRandomPrimitiveRoot(long long int prime)
{
	long long int result[100000];
	int count = 0;

	long long int limit = sqrt(prime);


    for (long long int i = 2; i < limit; i++) 
    {

        long long int start = 1;
        int flag = 1;

        for (long long int j = 0; j< prime / 2; j++) 
        {
            start = (start * i) % prime;
            if (start % prime == 1) 
            {
                flag = 0;
                break;
            }
        }
        if (flag) 
        {
        	printf("%llu is proot\n", i);
            result[count] = i;
            count++;
        }
    }
    
    long long int random = rand() % count;
    printf("random = %llu\nsizeof result = %d\n", random, count);

    return result[random];

}

int main()
{
	srand(time(NULL));

	long long int random;
	long long int proot = 0;

	random = generatePrime();
	proot = getRandomPrimitiveRoot(random);

	uint64_t large_number = pow(3, 32);

	printf("%llu is prime and %llu is primitive root of it\n", random, proot);
	printf("%llu is a big number\n", large_number);

}

