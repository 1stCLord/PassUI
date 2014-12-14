package com.ratusapparatus.passui;

import android.app.Activity;

import android.app.ActionBar;
import android.app.AlertDialog;
import android.app.DialogFragment;
import android.app.Fragment;
import android.app.FragmentManager;
import android.content.ClipData;
import android.content.ClipboardManager;
import android.content.Context;
import android.content.DialogInterface;
import android.os.Build;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.support.v4.widget.DrawerLayout;
import android.view.ViewParent;
import android.view.Window;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TableLayout;
import android.widget.TextView;
import android.widget.ToggleButton;

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
                ((Server)currentFragment).SaveData();
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

    public void showPasswordTextView(View view)
    {
        final EditText input = new EditText(this);
        final View srcView = view;

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("");
        builder.setMessage("");
        builder.setView(input);
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton)
            {
                showPassword(srcView,input.getText().toString());
            }
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton) {
                // Do nothing.
            }
        });
        builder.show();
    }

    public void showPassword(View view, String gpg_password)
    {
        ViewParent viewParent = view.getParent().getParent();
        if(viewParent instanceof LinearLayout)
        {
            LinearLayout viewGroup = (LinearLayout)viewParent;
            TextView textView = (TextView) viewGroup.findViewById(R.id.info_text);
            if(textView != null)
            {
                String textID = textView.getText().toString();
                String pass = passSSH.GetPass(textID,gpg_password);
                textView.setText(pass);
            }
        }
    }

    public void copyPasswordTextView(View view)
    {
        final EditText input = new EditText(this);
        final View srcView = view;

        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("");
        builder.setMessage("");
        builder.setView(input);
        builder.setPositiveButton("Ok", new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton)
            {
                copyPassword(srcView,input.getText().toString());
            }
        });
        builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener()
        {
            public void onClick(DialogInterface dialog, int whichButton) {
                // Do nothing.
            }
        });
        builder.show();
    }

    public void copyPassword(View view, String gpg_password)
    {
        ViewParent viewParent = view.getParent().getParent();
        if(viewParent instanceof LinearLayout)
        {
            LinearLayout viewGroup = (LinearLayout)viewParent;
            TextView textView = (TextView) viewGroup.findViewById(R.id.info_text);
            if(textView != null)
            {
                String textID = textView.getText().toString();
                String pass = passSSH.GetPass(textID,gpg_password);
                ClipboardManager clipboardManager = (ClipboardManager)getSystemService(CLIPBOARD_SERVICE);
                clipboardManager.setPrimaryClip(ClipData.newPlainText("",pass));
            }
        }
    }

    public void keyBasedAuthToggle(View view)
    {
        ViewParent viewParent = view.getParent().getParent();
        if(viewParent instanceof TableLayout && view instanceof ToggleButton)
        {
            TableLayout viewGroup = (TableLayout)viewParent;
            ToggleButton toggleButton = (ToggleButton)view;
            EditText editText = (EditText) viewGroup.findViewById(R.id.privateKeyEditText);
            editText.setVisibility(toggleButton.isChecked() ? View.VISIBLE : View.GONE);
            EditText pubeditText = (EditText) viewGroup.findViewById(R.id.publicKeyEditText);
            pubeditText.setVisibility(toggleButton.isChecked() ? View.VISIBLE : View.GONE);
        }
    }
}
