//
// Created by xinli on 17-10-12.
//
#define STB_IMAGE_IMPLEMENTATION
#include "Shape.h"
#include <vector>
#include <stb_image.h>

#include <android/log.h>
#define LOGI(level,...) __android_log_print(ANDROID_LOG_INFO, "NATIVE_LOG", __VA_ARGS__)
using namespace std;

GLfloat skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
};

class CubeMap : public Shape
{
    public:
    //GLint mATexCoordsHandle;
    //GLfloat *mTexCoordsArray;
    vector<string> faces;
    GLuint mSkybox;
    unsigned int textureID;

    unsigned int loadCubemap()
    {
            //unsigned int textureID;
            glGenTextures(1, &textureID);
            glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);

            int width,height,nrChannels;

            for(unsigned int i=0; i<faces.size(); i++)
            {
                   unsigned char *data=stbi_load(faces[i].c_str(), &width, &height, &nrChannels,0);
                   if(data)
                   {
                        LOGI(1,"cubemap texture success to load->%s",faces[i].c_str());
                        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
                        stbi_image_free(data);
                   }
                   else
                   {
                        //cout << "Cubemap texture failed to load at path: " << faces[i] << endl;

                        LOGI(1,"cubemap texture failed to load->%s",faces[i].c_str());
                        stbi_image_free(data);
                   }

            }

            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

            return textureID;
    }




    void initVertex()
    {
            mVertexArray=new GLfloat[5*36];
            //mColorArray=new GLfloat[4];

            mVertexArray=  skyboxVertices;
    }


   void initGL(const char *vertexShaderCode, const char *fragmentShaderCode) {

       shader.create(vertexShaderCode,fragmentShaderCode);
       mProgram=shader.getID();
       loadCubemap();
       //mProgram=GLUTIL::createProgram(vertexShaderCode,fragmentShaderCode);
       mUMVPMatrixHandle=glGetUniformLocation(mProgram,"uMVPMatrix");
       mAPositionHandle=glGetAttribLocation(mProgram,"aPosition");

       /*glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
       glUniform1i(glGetUniformLocation(shader.getID(),"skybox"),0);*/

       //mATexCoordsHandle=glGetAttribLocation(mProgram,"aTexCoords");
   }

   void draw(float *mvpMatrix) {
       //glUseProgram(mProgram);
       //shader.use();
       glDepthFunc(GL_LEQUAL);
       shader.use();
       glUniformMatrix4fv(mUMVPMatrixHandle,1,GL_FALSE,mvpMatrix);
       glVertexAttribPointer(mAPositionHandle,3,GL_FLOAT,GL_FALSE,3*sizeof(GLfloat),mVertexArray);
       //glVertexAttribPointer(mATexCoordsHandle,2,GL_FLOAT,GL_FALSE,2*sizeof(GLfloat),mTexCoordsArray);
       glEnableVertexAttribArray(mAPositionHandle);
       //glEnableVertexAttribArray(mATexCoordsHandle);
       glActiveTexture(GL_TEXTURE0);
       glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);
       glUniform1i(glGetUniformLocation(shader.getID(),"skybox"),0);

       glDrawArrays(GL_TRIANGLES,0,36);
   }

   CubeMap()
   {
       initVertex();
       faces.push_back("/sdcard/image/right.jpg");
       faces.push_back("/sdcard/image/left.jpg");
       faces.push_back("/sdcard/image/top.jpg");
       faces.push_back("/sdcard/image/bottom.jpg");
       faces.push_back("/sdcard/image/back.jpg");
       faces.push_back("/sdcard/image/front.jpg");

       /*faces.push_back("/sdcard/image/po_rt.tga");
       faces.push_back("/sdcard/image/po_lf.tga");
       faces.push_back("/sdcard/image/po_up.tga");
       faces.push_back("/sdcard/image/po_dn.tga");
       faces.push_back("/sdcard/image/po_bk.tga");
       faces.push_back("/sdcard/image/po_ft.tga");*/

   }

   ~CubeMap()
   {
        delete [] mVertexArray;
        //delete [] mTexCoordsArray;
   }
};