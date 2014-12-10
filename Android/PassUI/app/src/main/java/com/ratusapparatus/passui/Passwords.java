package com.ratusapparatus.passui;

import android.app.Activity;
import android.app.DialogFragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageButton;

import com.ratusapparatus.passssh.PassSSH;

public class Passwords extends Fragment
{

    public Passwords()
    {
        // Required empty public constructor
    }
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        FragmentManager fragmentManager = getActivity().getFragmentManager();

        PassUI passUI = (PassUI)getActivity();
        String server = PreferenceManager.getDefaultSharedPreferences(getActivity()).getString("Server", "");
        String username = PreferenceManager.getDefaultSharedPreferences(getActivity()).getString("Name", "");
        String password = PreferenceManager.getDefaultSharedPreferences(getActivity()).getString("Pass", "");
        String port = PreferenceManager.getDefaultSharedPreferences(getActivity()).getString("Port", "22");
        boolean keyAuth = PreferenceManager.getDefaultSharedPreferences(getActivity()).getBoolean("KeyAuth", false);
        passUI.passSSH.Init(server,Integer.parseInt(port),username,password, keyAuth ? PassSSH.AuthType.AUTH_TYPE_PRIVATE_KEY : PassSSH.AuthType.AUTH_TYPE_PASSWORD);
        String[] passIDs = passUI.passSSH.GetPassIDs();
        //passUI.passSSH.GetPass("");
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        for(String passID : passIDs)
        {
            fragmentTransaction.add(R.id.scrollLayout, Password.newInstance(passID));
        }

        fragmentTransaction.commit();
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_passwords, container, false);
    }

    public static Passwords newInstance()
    {
        return new Passwords();
    }
}
