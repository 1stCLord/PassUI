package com.ratusapparatus.passui;

import android.app.Fragment;
import android.os.Bundle;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * Created by Sombrero on 25/11/2014.
 */
public class Password extends Fragment
{
    String passID;

    @Override
    public void setArguments(Bundle args)
    {
        passID = args.getString("passID");
        super.setArguments(args);
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        View view = inflater.inflate(R.layout.password, container, false);
        TextView textView = (TextView)view.findViewById(R.id.info_text);
        textView.setText(passID);
        return view;
    }

    public static Password newInstance(String passID)
    {
        Password password = new Password();
        Bundle bundle = new Bundle();
        bundle.putString("passID",passID);
        password.setArguments(bundle);
        return password;
    }
}
