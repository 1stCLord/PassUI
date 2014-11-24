package com.ratusapparatus.passssh;

/**
 * Created by Sombrero on 24/11/2014.
 */
public class PassSSH
{
    enum AuthType
    {
        AUTH_TYPE_PASSWORD,
        AUTH_TYPE_PRIVATE_KEY
    }

    PassSSH()
    {
        System.loadLibrary("passssh");
    }

    public native boolean Connect(String server, String username, String passphrase, AuthType authType);
    public native String[] GetPassIDs();
    public native String GetPass(String id);
}
