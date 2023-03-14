#include <iostream>
#include "TestHugeInteger.h"

using namespace std;
// Add code for comparing running time
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std::chrono;
using namespace boost::multiprecision;

void runningTimeCompare()
{
    int MAXRUN = 9000; // Tune it such that durationMs >= 500
    int MAXNUMINTS = 100; // at least 100
    system_clock::time_point startTime, endTime;
    double runTime = 0.0;
    double runTime_cpp_int = 0.0;
    double durationMs = 0.0;
    int n = 1; // measure the running time for various values of n, e.g., 10, 100, 500, 1000, 5000, 10000
    for (int numInts = 0; numInts < MAXNUMINTS; numInts++) {
        HugeInteger huge1(n); //creates a random integer of n digits
        HugeInteger huge2(n); //creates a random integer of n digits
        cpp_int c1(huge1.toString());
        cpp_int c2(huge2.toString());
        startTime = system_clock::now();
        for (int numRun = 0; numRun < MAXRUN; numRun++) {
            HugeInteger huge3 = huge1.multiply(huge2);
        }
        endTime = system_clock::now();
        durationMs = (duration<double, std::milli>(endTime - startTime)).count();
        runTime += durationMs / ((double)MAXRUN);
        cout << "durationMs: " << durationMs << endl; // Tune MAXRUN such that durationMs >= 500
        startTime = system_clock::now();
        for (int numRun = 0; numRun < MAXRUN; numRun++) {
            cpp_int c3 = c1 + c2;
        }
        endTime = system_clock::now();
        durationMs = (duration<double, std::milli>(endTime - startTime)).count();
        runTime_cpp_int += durationMs / ((double)MAXRUN);
    }
    runTime = runTime / ((double)MAXNUMINTS);
    runTime_cpp_int = runTime_cpp_int / ((double)MAXNUMINTS);
    cout << "Runing time for HugeInteger add with n=" << n << " is:" << runTime << " ms" << endl;
    cout << "Runing time for cpp_int + with n=" << n << " is:" << runTime_cpp_int << " ms" << endl;
}

int main() {
    runningTimeCompare();
    return 0;
 /*
    // when test failed, the size of number <= NUM_DISPLAY, display the number
    unsigned int num_display = 1000;
    // iterate the MAX_SIZE_ARRAY MAX_RUN times
    unsigned int max_run = 50;
    // use for generating invalid string for constructor 1 (with string input)
    unsigned int max_invalid_string = 5;
    // different size for test
    vector<int> max_size_array = {1,20,50,500};

    double totalMark = 0;

    string demoLab = "Lab2"; // set to Lab1 or Lab2

    TestHugeInteger thi(num_display, max_run, max_invalid_string, max_size_array);

    if (demoLab == "Lab1"){
        totalMark += thi.testConstructorString();
        totalMark += thi.testConstructorNumber();
        totalMark += thi.testPositiveAddition();
    }else{
        totalMark += thi.testAdditionSubtraction();
        totalMark += thi.testCompareTo();
        totalMark += thi.testMultiplication();
    }

    cout << "******************************" << endl;
    cout << "*** FINAL TOTAL MARK IS " << totalMark << " ***" << endl;
    cout << "******************************" << endl;

	return 0;
   */
}
