package com.ratusapparatus.passui;

import android.app.Activity;

import android.app.ActionBar;
import android.app.DialogFragment;
import android.app.Fragment;
import android.app.FragmentManager;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.support.v4.widget.DrawerLayout;
import android.view.Window;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.TextView;

import com.ratusapparatus.passssh.PassSSH;

import junit.framework.Assert;


public class PassUI extends Activity implements NavigationDrawerFragment.NavigationDrawerCallbacks
{

    /**
     * Fragment managing the behaviors, interactions and presentation of the navigation drawer.
     */
    private NavigationDrawerFragment mNavigationDrawerFragment;

    /**
     * Used to store the last screen title. For use in {@link #restoreActionBar()}.
     */
    private CharSequence mTitle;

    public PassSSH passSSH = new PassSSH();

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pass_ui);

        mNavigationDrawerFragment = (NavigationDrawerFragment)getFragmentManager().findFragmentById(R.id.navigation_drawer);
        mTitle = getTitle();

        // Set up the drawer.
        mNavigationDrawerFragment.setUp(R.id.navigation_drawer,(DrawerLayout) findViewById(R.id.drawer_layout));
    }

    private Fragment currentFragment = null;
    @Override
    public void onNavigationDrawerItemSelected(int position)
    {
        // update the main content by replacing fragments
        switch (position)
        {
            case 0:
                currentFragment = Server.newInstance();
                break;
            case 1:
                String server = "";
                String username = "";
                String password = "";
                if(currentFragment instanceof Server)
                {
                    EditText addressEditText = (EditText)currentFragment.getView().findViewById(R.id.addressEditText);
                    EditText nameEditText = (EditText)currentFragment.getView().findViewById(R.id.nameEditText);
                    EditText passEditText = (EditText)currentFragment.getView().findViewById(R.id.passEditText);
                    server = addressEditText.getText().toString();
                    username = nameEditText.getText().toString();
                    password = passEditText.getText().toString();
                }

                passSSH.Init(server,username,password, PassSSH.AuthType.AUTH_TYPE_PASSWORD);
                currentFragment = Passwords.newInstance();
                break;
            default:
                Assert.assertNotNull(null);
                break;
        }

        FragmentManager fragmentManager = getFragmentManager();
        fragmentManager.beginTransaction().replace(R.id.container, currentFragment).commit();
    }

    public void onSectionAttached(int number)
    {
        switch (number)
        {
            case 1:
                mTitle = getString(R.string.title_section1);
                break;
            case 2:
                mTitle = getString(R.string.title_section2);
                break;
        }
    }

    public void restoreActionBar()
    {
        ActionBar actionBar = getActionBar();
        actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_STANDARD);
        actionBar.setDisplayShowTitleEnabled(true);
        actionBar.setTitle(mTitle);
    }

    public void showAddPassDialog(View view)
    {
        DialogFragment newFragment = new AddPassDialog();
        newFragment.show(getFragmentManager(), "dialog");
    }
}
