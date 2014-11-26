package com.ratusapparatus.passui;

import android.app.Activity;
import android.app.DialogFragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.media.Image;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
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
        String[] passIDs = passUI.passSSH.GetPassIDs();
        //passUI.passSSH.GetPass("");
        FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
        for(String passID : passIDs)
        {
            fragmentTransaction.add(R.id.scrollLayout, Password.newInstance(passID));
        }
        /*Password fragment = new Password();
        Password fragment2 = new Password();
        Password fragment3 = new Password();
        Password fragment4 = new Password();
        Password fragment5 = new Password();

        fragmentTransaction.add(R.id.scrollLayout, fragment);
        fragmentTransaction.add(R.id.scrollLayout, fragment2);
        fragmentTransaction.add(R.id.scrollLayout, fragment3);
        fragmentTransaction.add(R.id.scrollLayout, fragment4);
        fragmentTransaction.add(R.id.scrollLayout, fragment5);*/
        fragmentTransaction.commit();
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_passwords, container, false);
    }

    public static Passwords newInstance()
    {
        return new Passwords();
    }
}
