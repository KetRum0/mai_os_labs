#include <gtest/gtest.h>
#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

extern "C" {
    #include <parent.h>
}

TEST(FirstLabTests, SimpleTest) {
    constexpr int inputSize = 5;

    std::array<const char*, inputSize> input = {
            "1.1 2.2 3.3 10",
            "0 1 0.1",
            "-10.5 9.5 -1",
            "1.101",
            ""
    };

    std::array<float, inputSize> expectedOutput = {
            16.6, 1.1, -2, 1.101, 0
    };

    for (int i = 0; i < inputSize; i++){
        chdir("../lab4");
        std::ofstream test; 
        test.open("test.txt", std::ofstream::out | std::ofstream::trunc);
        test << input[i];test.close();
        float output = ParentRoutine("test.txt");
        EXPECT_EQ(output, expectedOutput[i]);
        
    }
    
}