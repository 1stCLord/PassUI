package com.ratusapparatus.passssh;

/**
 * Created by Sombrero on 24/11/2014.
 */
public class PassSSH
{
    public enum AuthType
    {
        AUTH_TYPE_PASSWORD,
        AUTH_TYPE_PRIVATE_KEY
    }

    public PassSSH()
    {
        System.loadLibrary("passssh");
        Init("server","name","passphrase",AuthType.AUTH_TYPE_PASSWORD);
    }

    public native boolean Init(String server, String username, String passphrase, AuthType authType);
    public native String[] GetPassIDs();
    public native String GetPass(String id);
}
