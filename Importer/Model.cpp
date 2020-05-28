//
// Created by binybrion on 5/22/20.
//

#include "Model.h"

namespace L_System_Importer
{
    // Splitting this class across a header and source file doesn't do anything in terms of compile timers;
    // it is done to have consistency in the fact that a user-defined structure with functions is split across
    // declaration and implementation. This is a personal choice only.

    Model::Model(std::string modelLocation, const std::vector<glm::mat4x4>& instances)
            :
                modelLocation{std::move(modelLocation)},
                instances{instances}
    {

    }

    const std::string &Model::getModelLocation() const
    {
        return modelLocation;
    }

    const std::vector<glm::mat4x4> &Model::getInstances() const
    {
        return instances;
    }
}