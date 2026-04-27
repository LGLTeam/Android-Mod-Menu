package com.android.sprijin;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.graphics.Color;
import android.view.Gravity;

public class MainActivity extends Activity {
    // AICI ESTE PAROLA TA:
    String cheiaCorecta = "ROYAL-2026"; 

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Design-ul ecranului de Login (Negru și Auriu)
        LinearLayout layout = new LinearLayout(this);
        layout.setOrientation(LinearLayout.VERTICAL);
        layout.setBackgroundColor(Color.BLACK); 
        layout.setGravity(Gravity.CENTER);
        layout.setPadding(60, 60, 60, 60);

        // Titlu Principal
        TextView titlu = new TextView(this);
        titlu.setText("👑 ROYAL AIM 👑");
        titlu.setTextSize(32);
        titlu.setTextColor(Color.parseColor("#FFD700")); 
        titlu.setPadding(0, 0, 0, 80);
        titlu.setGravity(Gravity.CENTER);

        // Caseta pentru parolă
        final EditText inputKey = new EditText(this);
        inputKey.setHint("Introdu Cheia VIP...");
        inputKey.setHintTextColor(Color.GRAY);
        inputKey.setTextColor(Color.WHITE);
        inputKey.setGravity(Gravity.CENTER);

        // Butonul de Login
        Button btnLogin = new Button(this);
        btnLogin.setText("CONECTARE REGALĂ");
        btnLogin.setBackgroundColor(Color.parseColor("#FFD700")); 
        btnLogin.setTextColor(Color.BLACK);
        
        layout.addView(titlu);
        layout.addView(inputKey);
        layout.addView(btnLogin);
        setContentView(layout);

        // Verificarea parolei
        btnLogin.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String keyIntrodusa = inputKey.getText().toString();
                if (keyIntrodusa.equals(cheiaCorecta)) {
                    Toast.makeText(MainActivity.this, "Acces Confirmat!", Toast.LENGTH_SHORT).show();
                    
                    // Această linie pornește meniul din joc (Principal este clasa ta din poză)
                    Principal.Inceput(MainActivity.this);
                    
                    finish(); 
                } else {
                    Toast.makeText(MainActivity.this, "❌ Cheie Incorectă!", Toast.LENGTH_LONG).show();
                }
            }
        });
    }
}

