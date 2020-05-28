//
// Created by binybrion on 5/22/20.
//

#ifndef L_SYSTEM_VISUALIZER_IMPORTER_READRESULT_H
#define L_SYSTEM_VISUALIZER_IMPORTER_READRESULT_H

#include "Model.h"

namespace L_System_Importer
{
    /**
     * Encapsulates the operations of reading an export file and holding the results of reading an export file.
     */

    class ReadResult
    {
        public:

            /**
             * Get all of the loaded models that were found in the most recently read export file.
             *
             * @return vector of all the loaded models in the previous read operation
             */
            const std::vector<Model>& getLoadedModelInstances() const;

            /**
             * Processes the file at the given location, extracting all models and their instance matrices.
             *
             * The previous load result will be removed by calling this function.
             *
             * @param fileLocation of the export file to read
             * @throws runtime_error if there was an error processing the file
             */
            void readFile(const std::string &fileLocation);

        private:

            /**
             * Checks that the number of tokens on a given line matches one of the expected value.
             *
             * @param numberTokens on a given line in the project file
             * @param expectedNumberTokens vector of expected number of tokens. The numberTokens must match one of the numbers in this vector
             * @param fileLine line that is being checked
             * @throws runtime_exception if the number of tokens does not match any numbers in expectedNumberTokens
             */
            void checkExpectedNumberLineTokens(int numberTokens, std::vector<int> expectedNumberTokens, const std::string &fileLine) const;

            /**
             * Converts the given string to a number, and throws a runtime_exception if the operation could not be performed.
             *
             * @param stringToConvert to be converted to a number
             * @return the number equivalent of the passed in string
             * @throws runtime_exception if the number conversion operation could not be performed
             */
            float convertNumber(const std::string &stringToConvert) const;

            /**
             * Extracts the information about a model- either its name or instance matrices- from the given line.
             *
             * @param fileLine from which to extract an instance matrix
             * @throws runtime_exception if the file line is not of the expected format
             */
            void processFileLine(const std::string &fileLine);

            /**
             * Spits the given line by white space, returning all of the words in the line.
             *
             * @param currentLine to split by white space
             * @return vector of strings as a result of splitting the given line by whitespace
             */
            std::vector<std::string> splitWhiteSpace(const std::string &currentLine) const;

            std::vector<Model> loadedModels;
    };
}

#endif //L_SYSTEM_VISUALIZER_IMPORTER_READRESULT_H
