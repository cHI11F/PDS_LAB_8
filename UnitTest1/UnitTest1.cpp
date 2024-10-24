#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../PDS_LAB_8/PDS_LAB_8.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestReadGraph)
        {
            
            const char* filename = "test_graph.txt";
            std::ofstream testFile(filename);
            testFile << "0 1 0\n";
            testFile << "1 0 1\n";
            testFile << "0 1 0\n";
            testFile.close();

            
            auto graph = readGraph(filename);

            
            Assert::AreEqual(3, (int)graph.size()); 
            Assert::AreEqual(3, (int)graph[0].size()); 

            Assert::AreEqual(1, graph[0][1]); 
            Assert::AreEqual(0, graph[0][2]); 

            
            std::remove(filename);
        }
    };
}
