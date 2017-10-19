package com.example.xinli.myapplication;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;


import static android.opengl.GLES20.glClear;
import static android.opengl.GLES20.glClearColor;
import static android.opengl.GLES20.glViewport;
import static android.opengl.GLES20.GL_COLOR_BUFFER_BIT;

/**
 * Created by xinli on 17-10-10.
 */

public class MyRenderer implements GLSurfaceView.Renderer {
    public float rotateX;
    public float rotateY;
    public boolean flag;
    public float xoffset;
    public float yoffset;

    private Context mContext;
    public MyRenderer(Context context){
        super();
        mContext=context;
       // Log.i("1","sssss");
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {

        //glClearColor(1.0f,0.0f,0.0f,0.0f);
        String vertexShaderStr=LoadShaderStr(mContext, R.raw.vshader);
        String fragmentShaderStr=LoadShaderStr(mContext, R.raw.fshader);
        //nativeInit(vertexShaderStr,fragmentShaderStr);

        String vertexShaderStrSkybox=LoadShaderStr(mContext,R.raw.vskybox);
        String fragmentShaderStrSkybox=LoadShaderStr(mContext,R.raw.fskybox);

        String vertexShaderForModel=LoadShaderStr(mContext,R.raw.vmodel);
        String fragmentShaderForModel=LoadShaderStr(mContext,R.raw.fmodel);
        nativeInit(vertexShaderStr,fragmentShaderStr,vertexShaderStrSkybox,fragmentShaderStrSkybox,vertexShaderForModel,fragmentShaderForModel);
    }

    @Override
    public void onDrawFrame(GL10 gl)
    {
        //nativeDraw(rotateX,rotateY,flag);
        nativeDraw(xoffset,yoffset);
    }

    @Override
    public void onSurfaceChanged(GL10 gl,int width, int height)
    {
        //glViewport(0,0,width,height);
        nativeSurfaceChanged(width,height);
    }

    private String LoadShaderStr(Context context, int resId)
    {
        StringBuffer strBuf = new StringBuffer();
        try{
            InputStream inputStream = context.getResources().openRawResource(resId);
            BufferedReader in = new BufferedReader(new InputStreamReader(inputStream));
            String read=in.readLine();
            while(read!=null)
            {
                strBuf.append(read+"\n");
                read=in.readLine();
            }
            strBuf.deleteCharAt(strBuf.length()-1);
        } catch (IOException e) {
            e.printStackTrace();
        }
        return  strBuf.toString();
    }

    static {
        System.loadLibrary("native-lib");
    }

    public static native void nativeInit(String vertexShaderCode, String fragmentShaderCode, String vertexShaderCodeSkybox, String fragmentShaderCodeSkybox, String vertexShaderForModel, String fragmentShaderForModel);

    //private static native void nativeDraw(float AngleX, float AngleY,boolean flag);
    private static native void nativeDraw(float xoffset, float yoffset);

    private static native void nativeSurfaceChanged(int width, int height);
}
