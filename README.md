# L-System-Visualizer-Importer
Imports files exported by the L-System-Visualizer.

## Overview

The L-System-Visualizer (https://github.com/Binyamin-Brion/L-System-Visualizer) is able to export renders that include the models used in the render, as well as the instances of those models.

In order to use that information in a different project, that information has to be extracted from the exported file. This importer does that.

This importer uses standard C++98, and only requires the glm library, which can be found at:
* https://glm.g-truc.net/0.9.9/index.html

## Usage

To use:

1. Copy the source files into the project, or ensure that the files are included as part of a build.
2. Use the following code:
   
   L_System_Importer::ReadResult readResult;
   
   readResult.readFile(_locationToExportFile_);
   
   readResult.getLoadedModelInstances(); // Use the loaded models and their instances
   
## Notes

The main function is only required to run the test, which uses the Qt Framework (version 5.9.9). Thus, the files main.cpp,
CMakeLists.txt, the files in the Test and TestAssets folder are not required to use the importer.

This importer stores instance matrices for the models using the 4x4 matrix provided by the glm library. 
For the program to work as is, the glm library needs to be included in the project such that the mat4x4 file can be
included unqualified. 

If this cannot be done, then the appropriate _#include_ s will need to be updated with the required
folder prefix, depending on where it is located on the system.

This importer uses glm version 0.9.8, though it should be compatbile with other versions.
