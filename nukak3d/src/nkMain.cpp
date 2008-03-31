/** 
 * @file nkMain.cpp
 * @brief Application nukak3d.
 * @details Class for creation of application
 * @author Alexander Pinzon Fernandez.
 * @version 0.1
 * @date 18/10/2007 02:50 p.m.
 */

#include "nkMain.h"
#include "nkNukak3D.h"

bool nkMain::OnInit(){
	int language_system = mi_locale.GetSystemLanguage();
	if (language_system >= wxLANGUAGE_SPANISH && language_system <= wxLANGUAGE_SPANISH_VENEZUELA ){
		language_system = wxLANGUAGE_SPANISH;
	}else{
		language_system = wxLANGUAGE_DEFAULT;
	}
	
	if ( !mi_locale.Init(wxLANGUAGE_SPANISH/*language_system*/, wxLOCALE_CONV_ENCODING) ){
		wxLogError(_T("This language is not supported by the system."));
		return false;
	}

	wxLocale::AddCatalogLookupPathPrefix(_("."));
	mi_locale.AddCatalog(wxT("nukak3d"));
	#ifndef __WIN32__
		{
        wxLogNull noLog;
        mi_locale.AddCatalog(_T("fileutils"));
		}
	#endif
	
	//! Object of main window
	nkNukak3D* mi_nukak3D = new nkNukak3D ( (wxWindow*)(NULL) , -1, 
		wxT("nukak3D"),
		wxDefaultPosition, 
		wxSize(1024,768));

	//! Splash screen 
	new wxSplashScreen(wxBitmap(logo_bioingenium_xpm),
          wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
          6000, mi_nukak3D, -1, wxDefaultPosition, wxDefaultSize,
          wxSIMPLE_BORDER|wxSTAY_ON_TOP);
	wxYield();

	//! Show maximize window.
	this->SetTopWindow (mi_nukak3D);
	mi_nukak3D->Maximize(true);
	mi_nukak3D->Show (true);
	return true;
}

IMPLEMENT_APP (nkMain)