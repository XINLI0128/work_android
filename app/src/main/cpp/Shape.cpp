//
// Created by xinli on 17-10-10.
//#define STB_IMAGE_IMPLEMENTATION
#include "Shape.h"
#include <math.h>
#include "mesh.h"
#include <stb_image.h>

//#include "stb_image.h"



float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

void Shape::loadTexture(string s)
{

    glGenTextures(1,&textureID);
    //glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,textureID);
    int height, width, nChannels;
    unsigned char * data=stbi_load(s.c_str(), &width, &height, &nChannels,0);
    if(data)
    {
        LOGI(1,"SUCCEED TO LOAD TEXTURE");
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    LOGI(1,"FAILED TO LOAD TEXTURE");
}


void Shape::initVertex() {

    mVertexArray=new GLfloat[5*36];
    //mColorArray=new GLfloat[4];

    /*mVertexArray[0]=0.0f; mVertexArray[1]=0.5f,mVertexArray[2]=0.0f;
    mVertexArray[3]=-0.5f; mVertexArray[4]=-0.5f,mVertexArray[5]=0.0f;
    mVertexArray[6]=0.5f; mVertexArray[7]=-0.5f,mVertexArray[8]=0.0f;*/
    mVertexArray=cubeVertices;
    //loadTexture("/sdcard/image/top.jpg");

    //mColorArray[0]=1.0f; mColorArray[1]=0.0f; mColorArray[2]=0.0f; mColorArray[3]=1.0f;

}

void Shape::initGL(const char *vertexShaderCode, const char *fragmentShaderCode) {

    shader.create(vertexShaderCode,fragmentShaderCode);
    mProgram=shader.getID();
    //mProgram=GLUTIL::createProgram(vertexShaderCode,fragmentShaderCode);
    loadTexture("/sdcard/image/left.jpg");
    mUMVPMatrixHandle=glGetUniformLocation(mProgram,"uMVPMatrix");
    mAPositionHandle=glGetAttribLocation(mProgram,"aPosition");
    mATexCoordsHandle=glGetAttribLocation(mProgram,"aTexCoords");
    mTexture=glGetUniformLocation(mProgram,"texture_diffuse");
    //glUniformMatrix4fv(mUMVPMatrixHandle,1,GL_FALSE,mvpMatrix);
    //glVertexAttribPointer(mAPositionHandle,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray);
    //glVertexAttribPointer(mATexCoordsHandle,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray+3*sizeof(GLfloat));

    //glActiveTexture(GL_TEXTURE1);
    //glBindTexture(GL_TEXTURE_2D, textureID);
    //glUniform1i(mTexture,1);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    //mTexture1=glGetUniformLocation(mProgram,"texture_diffuse1");
    //mAColorHandle=glGetAttribLocation(mProgram,"aColor");
}

void Shape::draw(float *mvpMatrix) {
    //glUseProgram(mProgram);
    shader.use();
    glUniformMatrix4fv(mUMVPMatrixHandle,1,GL_FALSE,mvpMatrix);
    glVertexAttribPointer(mAPositionHandle,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray);
    glVertexAttribPointer(mATexCoordsHandle,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),mVertexArray+3*sizeof(GLfloat));
    glEnableVertexAttribArray(mAPositionHandle);
    glEnableVertexAttribArray(mATexCoordsHandle);

    glActiveTexture(GL_TEXTURE1);
    glUniform1i(mTexture,1);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glDrawArrays(GL_TRIANGLES,0,36);

    //glBindTexture(GL_TEXTURE_2D,0);
}

Shape::Shape() {
    initVertex();
}

Shape::~Shape() {
    delete [] mVertexArray;
    //delete [] mColorArray;
}

