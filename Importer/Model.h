//
// Created by binybrion on 5/21/20.
//

#ifndef L_SYSTEM_VISUALIZER_IMPORTER_MODEL_H
#define L_SYSTEM_VISUALIZER_IMPORTER_MODEL_H

#include <string>
#include <vector>

#include <mat4x4.hpp>

namespace L_System_Importer
{
    /**
     * Bundles together a model and its instance matrices.
     */

    class Model
    {
        public:

            /**
             * Initializes this object with the file containing the model information, and the model's instance matrices.
             *
             * @param modelLocation of the file holding the model information on the disk
             * @param instances the instance matrices associated with this model
             */

            Model(std::string modelLocation, const std::vector<glm::mat4x4>& instances);

            /**
             * Get the location of the file holding the model data.
             *
             * @return model file location
             */
            const std::string& getModelLocation() const;

            /**
             * Get the instance matrices for this model
             *
             * @return model instance matrices
             */
            const std::vector<glm::mat4x4>& getInstances() const;

        private:

            std::string modelLocation;
            std::vector<glm::mat4x4> instances;
    };
}

#endif //L_SYSTEM_VISUALIZER_IMPORTER_MODEL_H
