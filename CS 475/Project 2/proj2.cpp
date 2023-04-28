#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

unsigned int seed = 0;

/* Constants for this simulation */
const float RYEGRASS_GROWS_PER_MONTH =      20.0;
const float ONE_RABBITS_EATS_PER_MONTH =    1.0;
const float ONE_FOX_MAX_EATS_PER_MONTH =    2.0;

const float AVG_PRECIP_PER_MONTH =	        12.0;	// average
const float AMP_PRECIP_PER_MONTH =		    4.0;	// plus or minus
const float RANDOM_PRECIP =			        2.0;	// plus or minus noise

const float AVG_TEMP =				        60.0;	// average
const float AMP_TEMP =				        20.0;	// plus or minus
const float RANDOM_TEMP =			        10.0;	// plus or minus noise

const float MIDTEMP =				        60.0;
const float MIDPRECIP =				        14.0;

/* Variables for this simulation */
int	            NowYear;	    // 2023 - 2028
int	            NowMonth;       // 0 - 11

float	        NowPrecip;		// inches of rain per month
float	        NowTemp;		// temperature this month
float	        NowHeight;		// rye grass height in inches
int	            NowNumRabbits;  // number of rabbits in the current population
int             NowNumFoxes;    // number of foxes in the current population

omp_lock_t	    Lock;
volatile int	NumInThreadTeam;
volatile int	NumAtBarrier;
volatile int	NumGone;

void InitBarrier(int n) {
    NumInThreadTeam = n;
    NumAtBarrier = 0;
    omp_init_lock(&Lock);
}

void WaitBarrier() {
    omp_set_lock(&Lock);
    {
        NumAtBarrier++;
        if (NumAtBarrier == NumInThreadTeam) {
            NumGone = 0;
            NumAtBarrier = 0;

            /* let all other threads get back to what they were doing
			before this one unlocks, knowing that they might immediately
			call WaitBarrier() again: */
            while(NumGone != NumInThreadTeam-1);
            omp_unset_lock(&Lock);
            return;
        }
    }

    omp_unset_lock(&Lock);

    while (NumAtBarrier != 0);

    #pragma omp atomic
    NumGone++;
}

float Ranf(unsigned int* seedp, float low, float high) {
    float r = (float) rand_r(seedp);

    return (low + r * (high-low) / (float)RAND_MAX);
}

void _weather() {
    float ang = (30.*(float)NowMonth + 15.) * (M_PI / 180.);

    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
    NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    NowPrecip = precip + Ranf(&seed,  -RANDOM_PRECIP, RANDOM_PRECIP);
    if (NowPrecip < 0.)
        NowPrecip = 0.;
}

// Returns the number of rabbits after one month under current conditions
int Rabbits() {
    while(NowYear < 2029) {
        int _carryingCapacity = NowHeight;
        int _nextNumRabbits = NowNumRabbits;
        int _numRabbitsEaten = Ranf(&seed, ((float)NowNumFoxes / 2), ONE_FOX_MAX_EATS_PER_MONTH * NowNumFoxes);

        if (NowNumRabbits > _carryingCapacity) {
            _nextNumRabbits -= 1;
        } else {
            _nextNumRabbits += 2;
        }

        _nextNumRabbits -= _numRabbitsEaten;

        if (_nextNumRabbits < 0) _nextNumRabbits = 0;

        WaitBarrier(); // Done computing

        NowNumRabbits = _nextNumRabbits;

        WaitBarrier(); // Done assigning

        // Wait for printing

        WaitBarrier(); // Done printing
    }
}

void RyeGrass() {
    while (NowYear < 2029) {
        float _tempFactor = exp(-pow(((NowTemp - MIDTEMP)/10), 2)); // TF Equation
        float _precipFactor = exp(-pow(((NowPrecip - MIDPRECIP)/10), 2)); // PF Equation
        float _nextHeight = NowHeight;

        // Use these factors to determine how much height RyeGrass has
        _nextHeight += _tempFactor * _precipFactor * RYEGRASS_GROWS_PER_MONTH;
        _nextHeight -= NowNumRabbits * ONE_RABBITS_EATS_PER_MONTH;

        if (_nextHeight < 0) _nextHeight = 0;

        WaitBarrier(); // Done computing

        NowHeight = _nextHeight;

        WaitBarrier(); // Done assigning

        // Wait for printing

        WaitBarrier(); // Done printing
    }
}

void Predator() {
    while (NowYear < 2029) {
        int _carryingCapacity = NowNumRabbits;
        int _nextNumFoxes = NowNumFoxes;

        if (NowNumFoxes > _carryingCapacity) {
            _nextNumFoxes -= 2;
        } else {
            _nextNumFoxes += 1;
        }

        WaitBarrier(); // Done computing

        NowNumFoxes = _nextNumFoxes;

        WaitBarrier(); // Done assigning

        // Wait for printing

        WaitBarrier(); // Done printing
    }
}

void Watcher() {
    int _monthData = 0;

    while (NowYear < 2029) {
        int _nextMonth = NowMonth + 1;
        int _nextYear = NowYear;

        if (_nextMonth == 12) {
            _nextMonth = 0;
            _nextYear++;
        }

        _monthData++;

        WaitBarrier(); // Done computing

        _weather();
        NowYear = _nextYear;
        NowMonth = _nextMonth;

        WaitBarrier(); // Done assigning

        std::cout << _monthData << ";" << NowTemp << ";" << NowPrecip << ";" << NowHeight << ";" << NowNumRabbits << ";" << NowNumFoxes << std::endl;

        WaitBarrier(); // Done printing
    }
}

int main() {
    omp_set_num_threads(4);	// same as # of sections
    InitBarrier(4);

    // Starting values
    NowMonth = 0;
    NowYear = 2023;

    NowNumRabbits = 1;
    NowHeight = 5;

    #pragma omp parallel sections 
    {
        #pragma omp section 
        {
            Rabbits();
        }

        #pragma omp section 
        {
            RyeGrass();
        }

        #pragma omp section 
        {
            Watcher();
        }

        #pragma omp section 
        {
            Predator();
        }
    } // implied barrier -- all functions must return in order to allow any of them to get past here

    return 0;
}