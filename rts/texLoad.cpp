#include "texLoad.h"
#include <cstring>

AUX_RGBImageRec* texLoad::LoadBMP(char *Filename)                // Loads A Bitmap Image
{
        FILE *File=NULL;                                // File Handle

        if (!Filename)                                  // Make Sure A Filename Was Given
        {
                return NULL;                            // If Not Return NULL
        }

        File=fopen(Filename,"r");                       // Check To See If The File Exists

        if (File)                                       // Does The File Exist?
        {
                fclose(File);                           // Close The Handle
                return auxDIBImageLoad(Filename);       // Load The Bitmap And Return A Pointer
        }
        return NULL;                                    // If Load Failed Return NULL
}

GLuint texLoad::LoadGLTextures(string bitmap, GLuint texPoint,GLTexType type)                                    // Load Bitmaps And Convert To Textures
{
        int Status=FALSE;                               // Status Indicator

        AUX_RGBImageRec *TextureImage[4];               // Create Storage Space For The Texture

        memset(TextureImage,0,sizeof(void *)*1);        // Set The Pointer To NULL

		Status=TRUE;                            // Set The Status To TRUE
		GLuint texture;
        glGenTextures(1, &texture);          // Create Three Textures
        // Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
		char* bitM;
		bitM = new char[bitmap.length() + 1];
		strcpy(bitM, bitmap.c_str());
		if (TextureImage[0]=LoadBMP(bitM)) {
			//switch(type) {
			//case 0:
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
				glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			//	break;
			//case 1:
			//	glBindTexture(GL_TEXTURE_2D, texture);
			//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			//	glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			//	break;
			//case 2:
			//	glBindTexture(GL_TEXTURE_2D, texture);
			//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			//	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
			//	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
			//	break;
			//}
			texPoint = texture;
		}
        if (TextureImage[0])                            // If Texture Exists
        {
                if (TextureImage[0]->data)              // If Texture Image Exists
                {
                        free(TextureImage[0]->data);    // Free The Texture Image Memory
                }

                free(TextureImage[0]);                  // Free The Image Structure
        }

        return texPoint;                                  // Return The Status
}