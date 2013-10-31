#ifndef COMPOSITE_DRAWABLE_H
#define COMPOSITE_DRAWABLE_H

#include "Drawable.h"

class CompositeDrawable : public Drawable
{

public:
    virtual ~CompositeDrawable();
    
    /* Add drawable to this composite. Note that any drawables
     * added using this method are now OWNED BY THE COMPOSITE
     * DRAWABLE! This means you don't have to manually delete
     * given drawables. The composite's destructor does this
     * for you automatically. */
    void addDrawable(Drawable* drawable);
    bool removeDrawable(Drawable* drawable);
    
    virtual void render();
    
private:
    std::vector<Drawable*> drawables;
    
};

#endif
