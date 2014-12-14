package com.ratusapparatus.passui;

import android.app.Activity;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.Bundle;
import android.app.Fragment;
import android.preference.PreferenceManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ToggleButton;

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
        View view = inflater.inflate(R.layout.fragment_server, container, false);

        SharedPreferences preferences = PreferenceManager.getDefaultSharedPreferences(getActivity());
        String server   =   preferences.getString("Server", "");
        String username =   preferences.getString("Name", "");
        String password =   preferences.getString("Pass", "");
        String port     =   preferences.getString("Port", "");
        boolean keyAuth =   preferences.getBoolean("KeyAuth", false);
        String key      =   preferences.getString("Key", "");
        String pubkey      =   preferences.getString("PubKey", "");
        EditText addressEditText = (EditText)view.findViewById(R.id.addressEditText);
        EditText nameEditText = (EditText)view.findViewById(R.id.nameEditText);
        EditText passEditText = (EditText)view.findViewById(R.id.passEditText);
        EditText portEditText = (EditText)view.findViewById(R.id.portEditText);
        ToggleButton keyAuthToggleButton = (ToggleButton)view.findViewById(R.id.keyAuthToggleButton);
        EditText keyEditText = (EditText)view.findViewById(R.id.privateKeyEditText);
        EditText pubkeyEditText = (EditText)view.findViewById(R.id.publicKeyEditText);
        addressEditText.setText(server);
        nameEditText.setText(username);
        passEditText.setText(password);
        portEditText.setText(port);
        keyAuthToggleButton.setChecked(keyAuth);
        keyEditText.setText(key);
        keyEditText.setVisibility(keyAuth ? View.VISIBLE : View.GONE);
        pubkeyEditText.setText(pubkey);
        pubkeyEditText.setVisibility(keyAuth ? View.VISIBLE : View.GONE);

        return view;
   }

    public void SaveData()
    {
        EditText addressEditText = (EditText)getView().findViewById(R.id.addressEditText);
        EditText nameEditText = (EditText)getView().findViewById(R.id.nameEditText);
        EditText passEditText = (EditText)getView().findViewById(R.id.passEditText);
        EditText portEditText = (EditText)getView().findViewById(R.id.portEditText);
        ToggleButton keyAuthToggleButton = (ToggleButton)getView().findViewById(R.id.keyAuthToggleButton);
        EditText keyEditText = (EditText)getView().findViewById(R.id.privateKeyEditText);
        EditText pubkeyEditText = (EditText)getView().findViewById(R.id.publicKeyEditText);
        String server = addressEditText.getText().toString();
        String username = nameEditText.getText().toString();
        String password = passEditText.getText().toString();
        String port = portEditText.getText().toString();
        boolean keyAuth = keyAuthToggleButton.isChecked();
        String key = keyEditText.getText().toString();
        String pubkey = pubkeyEditText.getText().toString();
        SharedPreferences.Editor editor = PreferenceManager.getDefaultSharedPreferences(getActivity()).edit();
        editor.putString("Server", server);
        editor.putString("Name", username);
        editor.putString("Pass", password);
        editor.putString("Port", port);
        editor.putBoolean("KeyAuth", keyAuth);
        editor.putString("Key", key);
        editor.putString("PubKey", pubkey);
        editor.commit();
    }

    public static Server newInstance()
    {
        return new Server();
    }
}
