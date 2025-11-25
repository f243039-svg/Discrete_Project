#ifndef MODULE10_BENCHMARKING_H
#define MODULE10_BENCHMARKING_H

#include <iostream>
#include <string>
#include <ctime>
#include "Course.h"
#include "Student.h"
#include "Module1_Scheduling.h"
#include "Module2_Grouping.h"
#include "Module3_Induction.h"
#include "Module5_Sets.h"

using namespace std;

// check performance
// measure execution time 


//find execution time 
class Timer
{
private:
    clock_t startTime;
    clock_t endTime;

public:
    Timer()
    {
        startTime = 0;
        endTime = 0;
    }

    void start()
    {
        startTime = clock();
    }

    void stop()
    {
        endTime = clock();
    }

    double getElapsedMs()
    {
        return ((double)(endTime - startTime) / CLOCKS_PER_SEC) * 1000.0;
    }

    void printElapsed(const string &operation)
    {
        cout << operation << " took: " << getElapsedMs() << " ms\n";
    }
};


class FibonacciMemo
{
private:
    long long memo[100];
    int callCount;

public:
    FibonacciMemo()
    {
        for (int i = 0; i < 100; i++)
            memo[i] = -1;
        callCount = 0;
    }

    //
    long long fibRecursive(int n)
    {
        callCount++;
        if (n <= 1)
            return n;
        return fibRecursive(n - 1) + fibRecursive(n - 2);
    }

    long long fibMemo(int n)
    {
        callCount++;
        if (n <= 1)
            return n;
        if (memo[n] != -1)
            return memo[n];

        memo[n] = fibMemo(n - 1) + fibMemo(n - 2);
        return memo[n];
    }

    long long fibIterative(int n)
    {
        if (n <= 1)
            return n;

        long long prev = 0, curr = 1;
        for (int i = 2; i <= n; i++)
        {
            long long temp = prev + curr;
            prev = curr;
            curr = temp;
        }
        return curr;
    }

    void resetCallCount() { callCount = 0; }
    int getCallCount() { return callCount; }
};

//use operators like & and |
// O(1) comp
class BitSetOperations
{
public:
    static unsigned int setBit(unsigned int set, int pos)
    {
        return set | (1u << pos);
    }

    static bool checkBit(unsigned int set, int pos)
    {
        return (set & (1u << pos)) != 0;
    }

    static unsigned int unionSets(unsigned int a, unsigned int b)
    {
        return a | b;
    }

    static unsigned int intersectSets(unsigned int a, unsigned int b)
    {
        return a & b;
    }

    static unsigned int differenceSets(unsigned int a, unsigned int b)
    {
        return a & (~b);
    }

    static int countElements(unsigned int set)
    {
        int count = 0;
        while (set)
        {
            count += (set & 1);
            set >>= 1;
        }
        return count;
    }

    static void printBitSet(unsigned int set, int maxBits = 8)
    {
        cout << "{ ";
        bool first = true;
        for (int i = 0; i < maxBits; i++)
        {
            if (checkBit(set, i))
            {
                if (!first)
                    cout << ", ";
                cout << i;
                first = false;
            }
        }
        cout << " }";
    }
};

class BenchmarkModule
{
private:
    Timer timer;

    void generateLargeCourseSet(Course courses[], int &count, int size)
    {
        count = size;
        for (int i = 0; i < size; i++)
        {
            string code = "CS" + to_string(100 + i);
            string name = "Course " + to_string(i);
            courses[i] = Course(code, name, 3);

            if (i > 0)
            {
                courses[i].addPrerequisite("CS" + to_string(100 + i - 1));
            }
            if (i > 2)
            {
                courses[i].addPrerequisite("CS" + to_string(100 + i - 3));
            }
        }
    }

    void generateLargeStudentSet(Student students[], int &count, int size)
    {
        count = size;
        for (int i = 0; i < size; i++)
        {
            string id = "S" + to_string(1000 + i);
            string name = "Student" + to_string(i);
            students[i] = Student(id, name);

            for (int j = 0; j < (i % 5); j++)
            {
                students[i].addCompleted("CS" + to_string(100 + j));
            }
        }
    }

public:
    //compare the time taken with module 5 operations and bit manipula
    void benchmarkSetOperations()
    {

        string setA[50], setB[50], result[100];
        int sizeA = 30, sizeB = 25;

        for (int i = 0; i < sizeA; i++)
            setA[i] = "E" + to_string(i);
        for (int i = 0; i < sizeB; i++)
            setB[i] = "E" + to_string(i + 10);

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            int resSize = setUnion(setA, sizeA, setB, sizeB, result);
            (void)resSize;
        }
        timer.stop();
        timer.printElapsed("Array based Union");

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            int resSize = setIntersection(setA, sizeA, setB, sizeB, result);
            (void)resSize;
        }
        timer.stop();
        timer.printElapsed("Array based Intersection");

        unsigned int bitSetA = 0, bitSetB = 0;
        for (int i = 0; i < 15; i++)
            bitSetA = BitSetOperations::setBit(bitSetA, i);
        for (int i = 5; i < 20; i++)
            bitSetB = BitSetOperations::setBit(bitSetB, i);

        timer.start();
        for (int iter = 0; iter < 1000; iter++)
        {
            unsigned int res = BitSetOperations::unionSets(bitSetA, bitSetB);
            (void)res;
        }
        timer.stop();
        timer.printElapsed("Bit-based Union (1000 iterations)");

        cout << "Bit operations are ~100-1000x faster for small sets!\n";
    }

    //num of fun calls fro the 3 methods 
    // measure execution time and the func calls 
    // prove using recursion is slow than iteratra
    void benchmarkRecursion()
    {

        FibonacciMemo fib;
        int n = 30;
        // M1 exponential complexity
        // skips iof graeter than 35
        if (n <= 35)
        {
            timer.start();
            fib.resetCallCount();
            long long result = fib.fibRecursive(n);
            timer.stop();
            cout << "Recursive: Result = " << result << " Calls = " << fib.getCallCount() << ", ";
            cout << "Time: " << timer.getElapsedMs() << " ms\n";
        }
        else
        {
            cout << "slow\n";
        }

        //M2 N comp
        // store f(k) in memo so when needed check memo
        // top down approach 
        timer.start();
        fib.resetCallCount();
        long long result2 = fib.fibMemo(n);
        timer.stop();
        cout << "Memoized  Result = " << result2 << " Calls = " << fib.getCallCount() << endl;
          cout << "Time: " << timer.getElapsedMs() << " ms\n";

          //fastest way
          //M3  buttom up approach 
        timer.start();
        long long result3 = fib.fibIterative(n);
        timer.stop();
        cout << "Iterative: Result = " << result3 << ", ";
        cout << "Time: " << timer.getElapsedMs() << " ms\n";

    }

    // perform inductions and provide runtime 
    void benchmarkPrerequisiteChecking()
    {
        cout << "\nPrerequisite Verification \n";

        Course courses[20];
        int courseCount;
        generateLargeCourseSet(courses, courseCount, 15);

        Student students[50];
        int studentCount;
        generateLargeStudentSet(students, studentCount, 30);

        InductionModule im;
        string proof[500];
        int proofCount;

        timer.start();
        int checksPerformed = 0;
        for (int s = 0; s < studentCount; s++)
        {
            for (int c = 0; c < courseCount; c++)
            {
                bool result = im.canTakeCourse_StrongInduction(
                    courses, courseCount, students[s], courses[c].getCode(),
                    proof, proofCount);
                (void)result;
                checksPerformed++;
            }
        }
        timer.stop();

        timer.printElapsed("Total time");
        cout << "time per check: " << (timer.getElapsedMs() / checksPerformed) << "\n";
    }

    //time taken to generate all combinations 
    //find expected count and verify combinations 
    //find average time
    void benchmarkCombinations()
    {

        Student students[30];
        int studentCount;
        generateLargeStudentSet(students, studentCount, 20);

        int k = 3;

        timer.start();

        int combCount = listAllCombinations(students, studentCount, k);
        timer.stop();

        cout << "Generated C(" << studentCount << ", " << k << ") = " << combCount << " combinations.\n";
        timer.printElapsed("Time");

        long long expected = 1;
        for (int i = 0; i < k; i++)
        {
            expected *= (studentCount - i);
            expected /= (i + 1);
        }
        cout << "Expected combinations: " << expected << "\n";

        if (combCount > 0)
        {
            cout << "Average time per combination: " << (timer.getElapsedMs() / combCount) << " ms\n";
        }
    }
    static void combine(Student *a, int n, int k, int start, int depth,
                        Student *out, int &cnt)
    {
        if (depth == k)
        {
            ++cnt;
            return;
        }

        for (int i = start; i <= n - k + depth; ++i)
        {
            out[depth] = a[i];
            combine(a, n, k, i + 1, depth + 1, out, cnt);
        }
    }

    //possible groups of size k from the n students 
    static int listAllCombinations(Student *students, int n, int k)
    {
        if (k <= 0 || k > n)
            return 0;
        Student *buf = new Student[k];
        int counter = 0;
        combine(students, n, k, 0, 0, buf, counter);
        delete[] buf;
        return counter;
    }

    // combine all the above functions and print the resukts
    void runFullBenchmark()
    {
       

        benchmarkSetOperations();
        benchmarkRecursion();
        benchmarkPrerequisiteChecking();
        benchmarkCombinations();


    }

    //use of bitwise operations to perform set operations 
    //show how small sets of 32 elements can be performed in 1 complexity 
    void demoBitSetOperations()
    {
        cout << "Using bits to represent efficiently\n\n";

        //setA will have 1 3 5 bit set 
        unsigned int setA = 0;
        setA = BitSetOperations::setBit(setA, 1);
        setA = BitSetOperations::setBit(setA, 3);
        setA = BitSetOperations::setBit(setA, 5);

        
        unsigned int setB = 0;
        setB = BitSetOperations::setBit(setB, 3);
        setB = BitSetOperations::setBit(setB, 4);
        setB = BitSetOperations::setBit(setB, 5);

        cout << "Set A: ";
        BitSetOperations::printBitSet(setA);
        cout << "\n";
        cout << "Set B: ";
        BitSetOperations::printBitSet(setB);
        cout << "\n";

        // bitwise or |
        unsigned int unionSet = BitSetOperations::unionSets(setA, setB);
        cout << "A U B: ";
        BitSetOperations::printBitSet(unionSet);
        cout << "\n";
        //bitwose and &
        unsigned int interSet = BitSetOperations::intersectSets(setA, setB);
        cout << "A ∩ B: ";
        BitSetOperations::printBitSet(interSet);
        cout << "\n";

        unsigned int diffSet = BitSetOperations::differenceSets(setA, setB);
        cout << "A - B: ";
        BitSetOperations::printBitSet(diffSet);
        cout << "\n";
    }
};

#endif

