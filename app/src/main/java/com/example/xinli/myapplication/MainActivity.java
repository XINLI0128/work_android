package com.example.xinli.myapplication;

import android.app.ActionBar;
import android.opengl.GLSurfaceView;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private GLSurfaceView mGLview;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mGLview = new MySurfaceView(this);
        setContentView(mGLview);
        //ActionBar ac=getActionBar();
        //ac.hide();

        // Example of a call to a native method
 /*   TextView tv = (TextView) findViewById(R.id.sample_text);
    tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
  /*  public native String stringFromJNI();

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }*/
    }
}
