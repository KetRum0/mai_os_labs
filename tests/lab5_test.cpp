#include <gtest/gtest.h>
#include <vector>

extern "C" {
    #include <func.h>
}


TEST(FiveLabTests, Derivative_Test) { 
    constexpr int inputSize = 3;

    const std::vector <std::vector <float>> input = {
        {1, 0.0001},
        {-5, 0.00001},
        {3.14, 0.000001}
    };

    for (int i = 0; i < inputSize; i++){
        float output = Derivative(input[i][0],input[i][1]);
        float answer = -sin(input[i][0]);
        EXPECT_NEAR(output, answer, 0.001);
    }


}

TEST(FiveLabTests, GCF_Test) { 

    constexpr int inputSize = 3;

    const std::vector <std::vector <int>> input = {
        {21, 27},
        {50, 25},
        {11, 100}
    };
    const std::vector <int> expectedOutput = {3, 25, 1};

    for (int i = 0; i < inputSize; i++){
        float output = GCF(input[i][0],input[i][1]);
        EXPECT_EQ(output, expectedOutput[i]);
        
    }

}