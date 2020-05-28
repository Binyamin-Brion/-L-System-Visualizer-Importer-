//
// Created by BinyBrion on 2020-05-27.
//

#ifndef L_SYSTEM_VISUALIZER_IMPORTER_TESTS_TESTIMPORTER_H
#define L_SYSTEM_VISUALIZER_IMPORTER_TESTS_TESTIMPORTER_H

#include <QObject>

namespace Tests
{
    /**
     * Tests the Importer to ensure that it loads models correctly from the passed in file.
     */

    class TestImporter : public QObject
    {
            Q_OBJECT

        private slots:

            /**
             * Checks that the importer does not return anything if given an empty file.
             */
            void testEmptyFile();

            /**
             * Checks that the importer correctly loads a project file with a single model with a single instance.
             */
            void testFile_SingleModel_SingleInstance();

            /**
             * Tests that the model imports a project file with more than one model, each of which has more than one instance.
             */
            void testFile_MultipleModels_MultipleInstances();

        private:

            /**
             * Get the location of the folder holding the test files.
             *
             * @return the location of the test asset folder
             */
            QString getTestAssetFolder() const;
    };
}

#endif //L_SYSTEM_VISUALIZER_IMPORTER_TESTS_TESTIMPORTER_H
