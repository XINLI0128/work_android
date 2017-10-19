package com.example.xinli.myapplication;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;

/**
 * Created by xinli on 17-10-10.
 */

class MySurfaceView extends GLSurfaceView {

    private MyRenderer mRenderer;
    private float mPreviousX;
    private float mPreviousY;
    private final float TOUCH_SCALE_FACTOR=0.0001F;
    private boolean firstAction=true;

    public MySurfaceView(Context context) {
        super(context);
        this.setEGLContextClientVersion(2);
        mRenderer=new MyRenderer(context);
        this.setRenderer(mRenderer);
        this.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
    }

    public boolean onTouchEvent(final MotionEvent event)
    {
       float x = event.getX();
        float y = event.getY();

        switch (event.getAction())
        {
            case MotionEvent.ACTION_MOVE:

                if(firstAction)
                {
                    mPreviousX=x;
                    mPreviousY=y;
                    firstAction=false;
                }
                float dx=mPreviousX-x;
                float dy=y-mPreviousY;
                mRenderer.xoffset=dx;
                mRenderer.yoffset=dy;

                float rate=Math.abs(dy)/Math.abs(dx);

              /*  if(dy>0 && rate>0.5)
                {
                    mRenderer.flag=true;
                    mRenderer.rotateY+=2;
                }
                if(dy<0 && dy/dx>0.5)
                {
                    mRenderer.flag=true;
                    mRenderer.rotateY -= 2;
                }
                if(dx>0 && rate<0.5)
                {
                    mRenderer.flag=false;
                    mRenderer.rotateX+=2;
                }
                if(dx<0 && rate<0.5)
                {
                    mRenderer.flag=false;
                    mRenderer.rotateX -= 2;
                }*/



                requestRender();

        }

        mPreviousX=x;
        mPreviousY=y;

        return true;
    }

}
