//Linear sieve
//O(n)
bool composite[MAX];
vi primes;

void sieve(){
	for(int i = 2; i < MAX; i++){
		if(!composite[i])
			primes.push_back(i);
		for (int j = 0; j < (int)primes.size() && i * (ll)primes[j] < MAX; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0) break;
		}
	}
}

//Euler totient of numbers from 0 to MAX-1
//O(n)
bool composite[MAX];
int phi[MAX];
vi primes;

void sieve(){
	phi[1] = 1;
	for(int i = 2; i < MAX; i++){
		if(!composite[i]){
			primes.push_back(i);
			phi[i] = i - 1;
		}
		for (int j = 0; j < (int)primes.size() && i * (ll)primes[j] < MAX; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0){ 
				phi[i * primes[j]] = phi[i] * primes[j];
				break;
			}
			else{
				phi[i * primes[j]] = phi[i] * phi[primes[j]];
			}
		}
	}
}


//Compute mobius function of numbers from 0 to MAX-1
//O(n)
bool composite[MAX];
int M[MAX];
vi primes;

void sieve(){
	M[1] = 1;
	for(int i = 2; i < MAX; i++){
		if(!composite[i]){
			primes.push_back(i);
			M[i] = -1;
		}
		for (int j = 0; j < (int)primes.size() && i * (ll)primes[j] < MAX; j++){
			composite[i * primes[j]] = true;
			if(i % primes[j] == 0){ 
				M[i * primes[j]] = 0;
				break;
			}
			else{
				M[i * primes[j]] = M[i] * M[primes[j]];
			}
		}
	}
}