package com.example.fillbin_call;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.android.volley.AuthFailureError;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public class FillActivity extends AppCompatActivity {
    TextView rx;
    Button button;

RequestQueue requestQueue;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_fill);
         button = findViewById(R.id.buttonto);
         rx = findViewById(R.id.testdb);

    }

    public void oncLick(View view){

        String url = "http://192.168.177.35:8080/city/sql.php";
        StringRequest stringRequest = new StringRequest(Request.Method.POST,url,
                response -> rx.setText(response),
                error -> Toast.makeText(FillActivity.this,"ERROR",Toast.LENGTH_LONG).show()){
            @Nullable
            @Override
            protected Map<String, String> getParams() throws AuthFailureError {
                Map<String, String> params = new HashMap<>();
                params.put("task","gym");
                Date date = new Date();
                params.put("time",date.toString());
                return super.getParams();
            }
        };

        requestQueue = Volley.newRequestQueue(FillActivity.this);
        requestQueue.add(stringRequest);

        //button.setOnClickListener(new View.OnClickListener() {
            //@Override
            //public void onClick(View v) {
                int textViewCount = 7;
                TextView[] textViewArray = new TextView[textViewCount];
                textViewArray[0] = findViewById(R.id.Bin1);
                textViewArray[1] = findViewById(R.id.Bin2);
                textViewArray[2] = findViewById(R.id.Bin3);
                textViewArray[3] = findViewById(R.id.Bin4);

                String num = rx.getText().toString();
                String[] ar = num.split(",");
                textViewArray[0].setBackgroundResource(R.drawable.shape);
                textViewArray[1].setBackgroundResource(R.drawable.shape);
                textViewArray[2].setBackgroundResource(R.drawable.shape);
                textViewArray[3].setBackgroundResource(R.drawable.shape);
                for(String temp : ar){
                    //for(TextView x : textViewArray){
                    //if(temp.equals(x.getText().toString())){
                    if(temp.equals("Bin1")){
                        textViewArray[0].setBackgroundResource(R.drawable.shapered);
                    }
                    else if(temp.equals("Bin2")){
                        textViewArray[1].setBackgroundResource(R.drawable.shapered);
                    }
                    else if(temp.equals("Bin3")){
                        textViewArray[2].setBackgroundResource(R.drawable.shapered);
                    }
                    else if(temp.equals("Bin4")){
                        textViewArray[3].setBackgroundResource(R.drawable.shapered);
                    }
                    System.out.println(temp);
                    //x.setBackgroundResource(R.drawable.shapered);
                    // }
                    //}
                }
            }
       // });

   // }
}