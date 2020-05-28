//
// Created by binybrion on 5/22/20.
//

#include "ReadResult.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iterator>

namespace L_System_Importer
{
    const std::vector<Model>& ReadResult::getLoadedModelInstances() const
    {
        return loadedModels;
    }

    void ReadResult::readFile(const std::string &fileLocation)
    {
        // Even if the function fails processing the export file, the loadedModels will be in a cleared state- holds neither
        // the previous result or the old result. This is fine as it was stated in the function comments that calling
        // this function will erase the previous read result.
        loadedModels.clear();

        std::fstream fileReader{fileLocation};

        if(!fileReader.is_open())
        {
            throw std::runtime_error{"Unable to open the file for loading - " + fileLocation};
        }

        std::string currentLine;

        while(std::getline(fileReader, currentLine))
        {
            // Only process lines with actual information on them.
            if(currentLine.empty())
            {
                continue;
            }

            processFileLine(currentLine);
        }
    }

    void ReadResult::checkExpectedNumberLineTokens(int numberTokens, std::vector<int> expectedNumberTokens, const std::string &fileLine) const
    {
        auto numberLocation = std::find(expectedNumberTokens.begin(), expectedNumberTokens.end(), numberTokens);

        if(numberLocation == expectedNumberTokens.end()) // Number of tokens is not a number that was expected.
        {
            throw std::runtime_error{"Unexpected formatting (wrong number of tokens) at line: " + fileLine};
        }
    }

    float ReadResult::convertNumber(const std::string &stringToConvert) const
    {
        try
        {
            return std::stof(stringToConvert);
        }
        catch(std::exception &e)
        {
            // Rethrow the exception as a runtime error so that the only exception the user has to worry about
            // when calling readFile() is a runtime_exception.
            throw std::runtime_error{e.what()};
        }
    }

    void ReadResult::processFileLine(const std::string &fileLine)
    {
        std::vector<std::string> lineTokens = splitWhiteSpace(fileLine);

        lineTokens.erase(std::remove(lineTokens.begin(), lineTokens.end(), ","), lineTokens.end());

        /*
         * A user instance line has the following format, when split by white space:
         *
         * Model_Name -- modelName
         *
         * Token 0        Token 2
         *
         *
         *          OR if the line represents the beginning of a matrix
         *
         *  Begin_Matrix
         *
         *  Token 0
         *
         *          OR if the line represents a matrix column:
         *
         *  Value1  ,   Value2  ,   Value3  ,   Value4
         *
         *  Token 0     Token 2     Token 4     Token 6
         *
         *          OR if the line represents the end of a matrix
         *
         *  End_Matrix
         *
         *  Token 0
         *
         *          OR if the line represents the end of instance matrices for a model
         *
         * End_Model_Name
         *
         * Token 0
         *
         * Note: the '--' are tokens but are not listed due to space limitations in the above line.
         *
         */

        checkExpectedNumberLineTokens(lineTokens.size(), {1, 2, 4}, fileLine);

        static std::string modelName;
        static std::vector<glm::mat4x4> modelInstances;
        static int columnCount = 0; // Since a matrix takes four lines, a variable is required to know what column the
                                    // current line is referring to.
        static bool startReadMatrix = false;

        if(lineTokens[0].find("Model_Name") != std::string::npos)
        {
            modelName = lineTokens[1];
        }
        else if(lineTokens[0].find("Begin_Matrix") != std::string::npos)
        {
            modelInstances.emplace_back(glm::mat4{1.0f});

            startReadMatrix = true;
        }
        else if(lineTokens[0].find("End_Matrix") != std::string::npos) // This must be placed before the next
        {                                                                 // if-statement so that the next if-statement
            columnCount = 0;                                              // is not executed even on a line containing "End_Matrix"!

            startReadMatrix = false;
        }
        else if(startReadMatrix)
        {
            modelInstances.back()[columnCount][0] = convertNumber(lineTokens[0]);
            modelInstances.back()[columnCount][1] = convertNumber(lineTokens[1]);
            modelInstances.back()[columnCount][2] = convertNumber(lineTokens[2]);
            modelInstances.back()[columnCount][3] = convertNumber(lineTokens[3]);

            columnCount += 1;
        }
        else if(lineTokens[0].find("END_MODEL") != std::string::npos)
        {
            if(modelName.empty()) // Instances must be associated with a known model.
            {
                throw std::runtime_error{"An error occurred while reading the file: no model name was specified for a model!"};
            }

            loadedModels.emplace_back(modelName, modelInstances);

            modelInstances.clear(); // Make sure this model's matrices does not affect the next model's matrices.
        }
        else
        {
            throw std::runtime_error{"Unexpected file line: " + fileLine};
        }
    }

    std::vector<std::string> ReadResult::splitWhiteSpace(const std::string &currentLine) const
    {
        std::istringstream inputStringStream(currentLine);

        return std::vector<std::string> {std::istream_iterator<std::string>{inputStringStream},std::istream_iterator<std::string>{}};
    }
}