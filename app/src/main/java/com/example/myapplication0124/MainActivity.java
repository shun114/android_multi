package com.example.myapplication0124;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.view.View;
import android.widget.Button;


public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private int m_value = 0;
    private float f_value = 0;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // ボタンイベントの設定
        Button button = this.findViewById(R.id.button);
        Button button2 = this.findViewById(R.id.button2);
        Button button3 = this.findViewById(R.id.button3);

        button.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Log.d("debug", "upボタン押した！");
                m_value = countup(m_value);
                // Example of a call to a native method
                TextView tv = findViewById(R.id.sample_text);
                tv.setText(stringFromJNI() + m_value);
            }
        });

        button2.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Log.d("debug", "downボタン押した！");
                m_value = countdown(m_value);
                // Example of a call to a native method
                TextView tv = findViewById(R.id.sample_text);
                tv.setText(stringFromJNI() + m_value);
            }
        });

        button3.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                Log.d("debug", "matrixボタン押した！");
                f_value = matrix(f_value);
                // Example of a call to a native method
                TextView tv = findViewById(R.id.sample_text);
                tv.setText(stringFromJNI() + f_value);
            }
        });

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI() + m_value);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int countup(int value);
    public native int countdown(int value);
    public native float matrix(float value);
}
