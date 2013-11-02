#include "Texture.h"
#include <QGLWidget>

#include <iostream>
Texture::Texture(const std::string& imageFilename)
{
	// Load image to use for the texture from a file
	QImage loadedImage(imageFilename.c_str());
	// Make sure the image is in the correct format to be consumed by OpenGL
	texImage = QGLWidget::convertToGLFormat(loadedImage);
	std::cout << texImage.width() << " " << texImage.height() << std::endl;
	// Define a texture in OpenGL
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	// Specifying pixels for the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texImage.width(), texImage.height(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, texImage.bits());
	// Set clamping and interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	// Set texture mode (how texels are combined with vertex pixels)
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

Texture::~Texture()
{
	// Release resources used by OpenGL for this texture
	glDeleteTextures(1, &texID);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::width() const
{
	return texImage.width();
}

int Texture::height() const
{
	return texImage.height();
}
