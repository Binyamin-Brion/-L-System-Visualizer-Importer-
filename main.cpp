#include <QTest>
#include "Tests/TestImporter.h"

int main()
{
    // The only purpose of main is to run the tests; to actually use the importer,
    // copy the files in the "Importer" folder into the current project.

    Tests::TestImporter testImporter;

    QTest::qExec(&testImporter);

    return 0;
}
