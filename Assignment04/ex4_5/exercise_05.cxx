#include "exercise_05.h"

#include "vtkDataObject.h"
#include "vtkFloatArray.h"
#include "vtkImageData.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPointData.h"
#include "vtkSmartPointer.h"
#include "vtkStreamingDemandDrivenPipeline.h"

#include <array>
#include <cmath>

vtkStandardNewMacro(exercise_05);

exercise_05::exercise_05()
{
    this->SetNumberOfInputPorts(1);
    this->SetNumberOfOutputPorts(1);
}

int exercise_05::FillInputPortInformation(int port, vtkInformation* info)
{
    if (port == 0)
    {
        info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkImageData");
        return 1;
    }

    return 0;
}

int exercise_05::RequestInformation(vtkInformation*, vtkInformationVector**, vtkInformationVector* output_vector)
{
    return 1;
}

int exercise_05::RequestData(vtkInformation*, vtkInformationVector** input_vector, vtkInformationVector* output_vector)
{
    // Retrieve pointers to input and output data
    auto inInfo = input_vector[0]->GetInformationObject(0);
    auto input = vtkImageData::SafeDownCast(inInfo->Get(vtkDataObject::DATA_OBJECT()));

    auto outInfo = output_vector->GetInformationObject(0);
    auto output = vtkImageData::SafeDownCast(outInfo->Get(vtkDataObject::DATA_OBJECT()));

    output->DeepCopy(input);

    // Get array containing the velocity vectors
    auto vectors = input->GetPointData()->GetArray(0);

    // Create an array for the vector properties, name it, and set the number of components and tuples.
    // See https://vtk.org/doc/nightly/html/classvtkFloatArray.html and https://vtk.org/doc/nightly/html/classvtkGenericDataArray.html
    vtkSmartPointer<vtkFloatArray> propertyVector = vtkSmartPointer<vtkFloatArray>::New();
    propertyVector->Initialize();
    propertyVector->SetName("Property Vector");
    propertyVector->SetNumberOfComponents(7);
    propertyVector->SetNumberOfTuples(input->GetNumberOfPoints());
    propertyVector->FillValue(0.0f); // initialize the result array with zeros.

    // Calculate selected property
    static const auto pi = std::acos(-1);
    std::array<double, 3> v;

    switch(this->VectorProperty)
    {
    case 0: // velocity magnitude
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
           input->GetPoint(i, v.data());
	       propertyVector->SetComponent(i, 0, std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2])); 
        }

        break;
    case 1: // x component
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
	       input->GetPoint(i, v.data());
	       propertyVector->SetComponent(i, 1, v[0]);
        }

        break;
    case 2: // y component
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
            input->GetPoint(i, v.data());
            propertyVector->SetComponent(i, 2, v[1]);	
        }

        break;
    case 3: // z component
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
            input->GetPoint(i, v.data());
            propertyVector->SetComponent(i, 3, v[2]);
        }

        break;
    case 4: // r
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
            input->GetPoint(i, v.data());
            propertyVector->SetComponent(i, 4, std::sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
        }

        break;
    case 5: // theta
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
	       // theta = arctan(squr(x^2+y^2)/z)
	       input->GetPoint(i, v.data());    
	       propertyVector->SetComponent(i, 5, std::atan(std::sqrt(v[0] * v[0] + v[1] * v[1]) / v[2])); 
        }

        break;
    case 6: // phi
        for(vtkIdType i = 0; i < input->GetNumberOfPoints(); ++i)
        {
            // TODO: Read the relevant values from the input, compute the wanted value and write it to the created array
            // phi = artan(y/x)
            input->GetPoint(i, v.data());
            propertyVector->SetComponent(i, 6, std::atan(v[1] / v[0]));

        }

        break;
    };

    // TODO: Add the array to the point data output,
    // see https://vtk.org/doc/nightly/html/classvtkDataSet.html#aaf5f8853184dda29249e240aa4cd2c33

        output->GetPointData()->AddArray(propertyVector);

    return 1;
}
