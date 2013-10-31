#ifndef ANIMATION_AXES_H
#define ANIMATION_AXES_H

#include "Bone.h"

class Axes
{

public:
    /* Returns a bone object which contains children
     * bones and surfaces for rendering the standard XYZ
     * axes as cylinders and cones.
     *
     * NOTE: The calling code takes ownership of the
     * returned object and must 'delete' it when no
     * longer needed. */
    static Bone* createXYZAxes(float axisLength, float endpointLength);
    
};

#endif
