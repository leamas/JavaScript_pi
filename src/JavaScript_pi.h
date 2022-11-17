/**************************************************************************
* Project:  OpenCPN
* Purpose:  JavaScript Plugin
* Author:   Tony Voss 16/05/2020
*
* Copyright Ⓒ 2022 by Tony Voss
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License, under which
* you must including a copy of these terms in all copies
* https://www.gnu.org/licenses/gpl-3.0.en.html
***************************************************************************
*/
#ifndef JavaScript_pi_h
#define JavaScript_pi_h

#include "version.h"
#include "buildConfig.h"
#include "wx/wx.h"
#include <wx/fileconf.h>
#include "ocpn_plugin.h" //Required for OCPN plugin functions
#include "JavaScriptgui.h"
#include "toolsDialogImp.h"
#include <bitset>
#include "config.h"

enum Options{
    DONT_CARE,
    MUST_EXIST,
    MUST_NOT_EXIST
};

// Minimised console height is platform dependent
#ifdef __WXMSW__
#define MIN_CONSOLE_HEIGHT 16
#else
#define MIN_CONSOLE_HEIGHT 28
#endif

typedef  std::bitset<8> status_t;

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

 #define CONSOLE_POSITION    -1          // Request default positioning of toolbar tool

class Console;

class Position {
public:
    double lat; double lon;
    };

class JavaScript_pi : public opencpn_plugin_117
{
public:
    JavaScript_pi(void *ppimgr);
    ~JavaScript_pi(void);
    int m_leftclick_tool_id;

//  The required PlugIn Methods
    int Init(void);
    bool DeInit(void);

    int GetAPIVersionMajor();
    int GetAPIVersionMinor();
    int GetPlugInVersionMajor();
    int GetPlugInVersionMinor();
    wxBitmap *GetPlugInBitmap();
    wxString GetCommonName();
    wxString GetShortDescription();
    wxString GetLongDescription();

//  The required override PlugIn Methods
    int GetToolbarToolCount(void);
    void OnToolbarToolCallback(int id);
    void OnContextMenuItemCallback(int id);
    void SetCursorLatLon(double lat, double lon);

//  Optional plugin overrides
    void SetColorScheme(PI_ColorScheme cs);

//  Other public methods
    void OnTimer            (wxTimerEvent& tick);
    void SetPluginMessage             (wxString &message_id, wxString &message_body);
    void SetNMEASentence               (wxString &sentence);
    void SetPositionFixEx              (PlugIn_Position_Fix_Ex &pfix);
    void SetActiveLegInfo   ( Plugin_Active_Leg_Info &leg_info);
    void OnJavaScriptConsoleClose   ();
    void ShowPreferencesDialog (wxWindow* m_parent_window);
    ToolsClass *pTools {nullptr};   // points to the Tools dialogue if exists, else nullptr
    wxArrayString recentFiles;	// array of recent file strings
    wxSortedArrayString favouriteFiles; //array of favourite file strings

    Console         *mpFirstConsole;   // pointer to the first console
    Console*        mpBin;      // the bin for consoles to be deleted
    bool            mpPluginActive {false};
    wxWindow        *m_parent_window;
    bool            mShowingConsoles;
    int             m_display_width, m_display_height;
    wxFileConfig    *m_pconfig;
    wxString        mCurrentDirectory;
    PlugIn_Position_Fix_Ex  m_positionFix;  // latest position fix - if none yet, time is NULL
    Plugin_Active_Leg_Info m_activeLeg;     // latest active leg info
    Position        mCursorPosition;     // latest cursor position
    
    wxTimer         mTimer;
    bool            mTraceLevelStated {false};  // will be set true after first run of a script
    int				nextID = 1;		// used to generate unique IDs
    wxString        openCPNConfig {wxEmptyString};  // to store the OpenCPN config JSON
	bool			m_bShowJavaScript;

private:
    wxBitmap        m_panelBitmap;
    bool            m_bJavaScriptShowIcon;
    bool            LoadConfig(void);
    bool            SaveConfig(void);
    };

#endif  // JavaScript_pi_h
