#include "texture.h"
#include "Texture Loader/stb_image.h"
#include <iostream>
using namespace std;

Texture::Texture(const std::string& fileName, int texUnit_)
{
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
	texUnit = texUnit_;
    if(data == NULL)
		cout<< "Unable to load texture: " << fileName << endl;

	glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture); 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//OpenGL 3.0+ only!
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D, m_texture); 

    stbi_image_free(data);
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
	glActiveTexture(texUnit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
/*
GLuint Texture::loadDDS(const char * imagepath, int texUnit)
{
	int width, height;int numComponents; 
	GLuint m_texture;
	unsigned char* data = stbi_load(imagepath,&width, &height, &numComponents, 4);
	texUnit = texUnit;
	if(data == NULL)
	{
		cout<< "Unable to load texture: " ;
		printf(imagepath);
		cout<<endl;
	}
	glActiveTexture(texUnit);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);       
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//OpenGL 3.0+ only!
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0); 

	stbi_image_free(data);
	cout << "text txture loaded" <<endl;
	return m_texture;
}

*/

//GLuint Texture::loadBMP_custom(const char * imagepath)
//{
//	// Data read from the header of the BMP file
//unsigned char header[54]; // Each BMP file begins by a 54-bytes header
//unsigned int dataPos;     // Position in the file where the actual data begins
//
//unsigned int imageSize;   // = width*height*3
//// Actual RGB data

//
//// open the file
//file * file = fopen(imagepath,"rb");
//if (!file)                              {printf("image could not be opened\n"); return 0;}
//
//if ( fread(header, 1, 54, file)!=54 ){ // if not 54 bytes read : problem
//    printf("not a correct bmp file\n");
//    return false;
//}
//if ( header[0]!='b' || header[1]!='m' ){
//    printf("not a correct bmp file\n");
//    return 0;
//}
//// read ints from the byte array
//datapos    = *(int*)&(header[0x0a]);
//imagesize  = *(int*)&(header[0x22]);
//width      = *(int*)&(header[0x12]);
//height     = *(int*)&(header[0x16]);
//// some bmp files are misformatted, guess missing information
//if (imagesize==0)    imagesize=width*height*3; // 3 : one byte for each red, green and blue component
//if (datapos==0)      datapos=54; // the bmp header is done that way
//// create a buffer
//data = new unsigned char [imagesize];
// 
//// read the actual data from the file into the buffer
//fread(data,1,imagesize,file);
// 
////everything is in memory now, the file can be closed
//fclose(file);
//}

