//
// Created by BinyBrion on 2020-05-27.
//

#include "TestImporter.h"
#include "Importer/ReadResult.h"
#include <QDir>
#include <QtTest/qtestcase.h>

static Tests::TestImporter testImporter;

using namespace L_System_Importer;

namespace Tests
{
    void TestImporter::testEmptyFile()
    {
        ReadResult readResult;

        readResult.readFile((getTestAssetFolder() + "/emptyFile.txt").toStdString());

        const QString errorMessage = "Expected zero models loaded, but got: " + QString::number(readResult.getLoadedModelInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances().empty(), qPrintable(errorMessage));
    }

    void TestImporter::testFile_MultipleModels_MultipleInstances()
    {
        ReadResult readResult;

        readResult.readFile((getTestAssetFolder() + "/multipleModels_MultipleInstances.txt").toStdString());

        const QString errorMessage = "Expected two models loaded, but got: " + QString::number(readResult.getLoadedModelInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances().size() == 2, qPrintable(errorMessage));

        const QString firstModelName_ErrorMessage = "Expected a model by the name of branch.obj but got: " +
                                                     QString::fromStdString(readResult.getLoadedModelInstances()[0].getModelLocation());

        const QString firstModelInstanceCount_ErrorMessage = "Expected the model branch.obj to have five instances, but got: " + QString::number(readResult.getLoadedModelInstances()[0].getInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances()[0].getModelLocation() == "branch.obj", qPrintable(firstModelName_ErrorMessage));
        QVERIFY2(readResult.getLoadedModelInstances()[0].getInstances().size() == 5, qPrintable(firstModelInstanceCount_ErrorMessage));

        const QString secondModelName_ErrorMessage = "Expected a model by the name of bark.obj but got: " +
                                                    QString::fromStdString(readResult.getLoadedModelInstances()[1].getModelLocation());

        const QString secondModelInstanceCount_ErrorMessage = "Expected the model bark.obj to have five instances, but got: " + QString::number(readResult.getLoadedModelInstances()[1].getInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances()[1].getModelLocation() == "bark.obj", qPrintable(secondModelName_ErrorMessage));
        QVERIFY2(readResult.getLoadedModelInstances()[1].getInstances().size() == 5, qPrintable(secondModelInstanceCount_ErrorMessage));
    }

    void TestImporter::testFile_SingleModel_SingleInstance()
    {
        ReadResult readResult;

        readResult.readFile((getTestAssetFolder() + "/singleModel_SingleInstance.txt").toStdString());

        const QString errorMessage = "Expected two models loaded, but got: " + QString::number(readResult.getLoadedModelInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances().size() == 1, qPrintable(errorMessage));

        const QString firstModelName_ErrorMessage = "Expected a model by the name of branch.obj but got: " +
                                                    QString::fromStdString(readResult.getLoadedModelInstances()[0].getModelLocation());

        const QString firstModelInstanceCount_ErrorMessage = "Expected the model branch.obj to have five instances, but got: " + QString::number(readResult.getLoadedModelInstances()[0].getInstances().size());

        QVERIFY2(readResult.getLoadedModelInstances()[0].getModelLocation() == "branch.obj", qPrintable(firstModelName_ErrorMessage));
        QVERIFY2(readResult.getLoadedModelInstances()[0].getInstances().size() == 1, qPrintable(firstModelInstanceCount_ErrorMessage));
    }

    QString TestImporter::getTestAssetFolder() const
    {
        QDir currentPath = QDir::current();

        if(!(currentPath.cdUp() && currentPath.cd("TestAssets")))
        {
            throw std::runtime_error{"Unable to find test asset folder, located at: projectRootDirectory/TestAssets"};
        }

        return currentPath.path();
    }
}
