#include "second.hpp"

using namespace std;

void incrementWithLock(int* counter, mutex* lock, int totalIncrementsCount) {
	for (int i = 0; i < totalIncrementsCount; i++) {
		(*lock).lock();
		(*counter)++;
		(*lock).unlock();
	}
}

void exampleWithLock(int incrementsCount) {
	int counter = 0;
	mutex lock;

	auto start = chrono::high_resolution_clock::now();
	thread t1(incrementWithLock, &counter, &lock, incrementsCount), t2(incrementWithLock, &counter, &lock, incrementsCount);
	t1.join();
	t2.join();
	auto end = chrono::high_resolution_clock::now();
	auto timePassed = duration_cast<chrono::seconds>(end - start);
	
	cout << "With lock on " << incrementsCount << " iterations on each thread" << endl << "Value: " << counter << endl << "Time passed: " << timePassed << " seconds" << endl << endl;
}


void incrementWithoutLock(int* counter, int totalIncrementsCount) {
	for (int i = 0; i < totalIncrementsCount; i++) {
		(*counter)++;
	}
}

void exampleWithoutLock(int incrementsCount) {
	int counter = 0;

	auto start = chrono::high_resolution_clock::now();
	thread t1(incrementWithoutLock, &counter, incrementsCount), t2(incrementWithoutLock, &counter, incrementsCount);
	t1.join();
	t2.join();
	auto end = chrono::high_resolution_clock::now();
	auto timePassed = duration_cast<chrono::seconds>(end - start);
	
	cout << "Without lock on " << incrementsCount << " iterations on each thread" << endl << "Value: " << counter << endl << "Time passed: " << timePassed << " seconds" << endl << endl;
}

void incrementSync(int* counter, mutex* lock, int targetValue) {
	bool shouldContinue = true;

	while (shouldContinue) {
		(*lock).lock();
		if ((*counter) >= targetValue) {
			shouldContinue = false;
			(*lock).unlock();
			break;
		}
		(*counter)++;

		(*lock).unlock();
		
	}
}


void exampleWithSyncIncrementing(int incrementCount) {
	int counter = 0;
	mutex lock;

	auto start = chrono::high_resolution_clock::now();
	thread t1(incrementSync, &counter, &lock, incrementCount), t2(incrementSync, &counter, &lock, incrementCount);
	t1.join();
	t2.join();
	auto end = chrono::high_resolution_clock::now();
	auto timePassed = duration_cast<chrono::seconds>(end - start);

	cout << "Sync increment with target valeu " << incrementCount << endl << "Value: " << counter << endl << "Time passed: " << timePassed << " seconds" << endl << endl;
}

int second() {
	exampleWithoutLock(100'000'000);
	exampleWithLock(100'000'000);
	exampleWithSyncIncrementing(100'000'000);

	exampleWithoutLock(1'000'000'000);
	exampleWithLock(1'000'000'000);
	exampleWithSyncIncrementing(1'000'000'000);

	return 0;
}

