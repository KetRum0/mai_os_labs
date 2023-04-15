#include <gtest/gtest.h>
#include <chrono>
#include <stdlib.h>    

float answer = 3/51;
float accuracy = 0.06;
extern "C" {
    #include <lab3.h>
}

TEST(ThirdLabTests, SingleThread) {
    EXPECT_NEAR(chance(100,1),answer, accuracy);
    EXPECT_NEAR(chance(10000,1),answer, accuracy);
    EXPECT_NEAR(chance(1000000,1),answer, accuracy);
}

TEST(ThirdLabTest, MultipleThreads) {
    auto performTestForGivenSize = [](int n, int maxThreadCount) {
        for(int i = 2; i < maxThreadCount; ++i) {
            EXPECT_NEAR(chance(n, i), answer, accuracy);
        }
    };

    performTestForGivenSize(10000, 2);
    performTestForGivenSize(10000, 8);
    performTestForGivenSize(10000000, 15);
    performTestForGivenSize(400000, 4);
}

TEST(ThirdLabTest, PerfomanceTest) {
    auto getAvgTime = [](int threadCount) {
        auto n = 10000000;

        constexpr int runsCount = 10;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();
            chance(n, threadCount);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}
