#ifndef TEXTURE_H
#define TEXTURE_H

#include <QImage>
#include <string>

class Texture
{

public:
	Texture(const std::string& imageFilename);
	virtual ~Texture();

	void bind();
	void unbind();
	int width() const;
	int height() const;

private:
	QImage* texImage;
	unsigned int texID; // ID of texture in OpenGL

};

#endif
