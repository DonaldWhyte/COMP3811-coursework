#include "CompositeDrawable.h"
#include <algorithm>
#include <QGLWidget>

CompositeDrawable::~CompositeDrawable()
{
    for (std::vector<Drawable*>::iterator it = drawables.begin();
        (it != drawables.end()); it++)
    {
        delete (*it);
    }
}
    
void CompositeDrawable::addDrawable(Drawable* drawable)
{
    drawables.push_back(drawable);
}

bool CompositeDrawable::removeDrawable(Drawable* drawable)
{
	// Remove all elements that point to the same drawable
	drawables.erase(std::remove(drawables.begin(), drawables.end(), drawable), drawables.end());
}

void CompositeDrawable::render()
{
	glPushMatrix();
	
    // Apply drawable transformations
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);	
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	// Draw each drawable in turn
    for (std::vector<Drawable*>::iterator it = drawables.begin();
        (it != drawables.end()); it++)
    {
        (*it)->render();
    }
    
    glPopMatrix();
}
