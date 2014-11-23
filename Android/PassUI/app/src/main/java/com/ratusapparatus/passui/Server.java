package com.ratusapparatus.passui;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class Server extends Fragment
{
    public Server()
    {
        // Required empty public constructor
    }

   @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
   {
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_server, container, false);
    }

    public static Server newInstance()
    {
        return new Server();
    }

}
