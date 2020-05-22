#pragma once

#include "vtkImageAlgorithm.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"

class exercise_05 : public vtkImageAlgorithm
{
public:
    static exercise_05 *New();
    vtkTypeMacro(exercise_05, vtkImageAlgorithm);

    // TODO: Add the get and set macros for VectorProperty,
    // see https://vtk.org/Wiki/VTK/Examples/Developers/Macros
    vtkSetMacro(VectorProperty, int);
    vtkGetMacro(VectorProperty, int);

protected:
    exercise_05();

    int FillInputPortInformation(int, vtkInformation*);
    int RequestInformation(vtkInformation *, vtkInformationVector **, vtkInformationVector *);
    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *);

private:
    exercise_05(const exercise_05&);
    void operator=(const exercise_05&);

    /// Parameters
    int VectorProperty;
};
