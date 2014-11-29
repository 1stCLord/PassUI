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
        System.loadLibrary("sslcrypto");
        System.loadLibrary("ssl");
        System.loadLibrary("passssh");
        nativeObject = Create();
        Init("server","name","passphrase",AuthType.AUTH_TYPE_PASSWORD);
    }
    long nativeObject;

    private native long Create();

    private long ptr(){return nativeObject;}

    //SSH details to use
    public native boolean Init(String server, String username, String passphrase, AuthType authType);

    //Fetch
    public native String[] GetPassIDs();
    public native String GetPass(String id);

    //Set
    public native void InsertPass(String id, String pass);
    public native void GeneratePass(String id, boolean withSymbols, int length);
}
