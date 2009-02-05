/** 
 * @file nkFindSCU.h
 * @brief DICOM C-Find.
 * @details Clases for config and execute C-Find request.
 * @author Alexander Pinz�n Fernandez
 * @version 0.1
 * @date 26/01/2009 01:12 p.m.
*/

#ifndef _NKFINDSCU_H_
#define _NKFINDSCU_H_

#include "vtkINRIA3DConfigure.h"
#include  "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include  "wx/wx.h"
#endif

#include "wx/config.h"
#include "wx/confbase.h"

#include "wx/app.h"
#include "wx/aui/aui.h"
#include "wx/aui/auibook.h"
#include "wx/calctrl.h"
#include "wx/checkbox.h"
#include "wx/datetime.h"
#include "wx/dirdlg.h"
#include "wx/dynarray.h"
#include "wx/fileconf.h"
#include "wx/filename.h"
#include "wx/filefn.h"
#include "wx/grid.h"
#include "wx/list.h"
#include "wx/listbox.h"
#include "wx/listctrl.h"
#include "wx/numdlg.h"
#include "wx/panel.h"
#include "wx/process.h"
#include "wx/stdpaths.h"
#include "wx/string.h"
#include "wx/txtstrm.h"
#include "wx/thread.h"

#include <fstream>
#include <string>
#include <stdio.h>
#include <iostream>

#include "nkPipedProcess.h"
#include "nkStoreSCP.h"

#include "nkDICOMDictionary.h"
#include "nkDICOMServer.h"
#include "nkIODialog.h"
#include "nkNukak3D.h"
#include "nkUtilities.h"

/**
 * @brief Panel for search patient's.
 * @details Using DICOM C-FIND dcmtk application for searching patient's. 
*/
class nkFindSCU: public wxPanel{
public:
	/** 
	 * Event identifier.
	*/
	enum{
		ID_CALENDAR_STUDY_DATE_FROM  = wxID_HIGHEST + 1800,	/**< Display Calendar Control. */
		ID_CALENDAR_STUDY_DATE_TO,							/**< Display Calendar Control. */
		ID_CHECK_STUDY_DATE_FROM,							/**< Use Date From. */
		ID_CHECK_STUDY_DATE_TO,								/**< Use Date To. */
		ID_CLEAR,											/**< Clear fields. */
		ID_GET_STUDY,										/**< Get selected study. */
		ID_SEARCH,											/**< Searc in DICOM Q/R. */
		ID_SERVER_LOCATION,									/**< Configure DICOM Server's. */	
		ID_SELECT_CELL										/**< Select study in grid. */
	};
	/**
	 * @brief Class constructor.
	*/
	nkFindSCU(nkNukak3D * parent, 
		wxWindowID id = wxID_ANY, 
		const wxString& title = "Nukak3D: Find Patient's", 
		const wxPoint& pos = wxDefaultPosition, 
		const wxSize& size = wxDefaultSize);
	virtual ~nkFindSCU();
protected:
	/**
	 * @brief Read list of servers register in this OS.
	*/
	void loadServers();
	/**
	 * @brief Event Manager for use date from.
	*/
	void prEventUseDateFrom(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event Manager for use date to.
	*/
	void prEventUseDateTo(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event manager to display calendar dialog.
	*/
	void prEventChangeDateFrom(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event manager to display calendar dialog.
	*/
	void prEventChangeDateTo(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Display dialog for set serve's.
	*/
	void prEventServerLocation(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event manager for clear the fields..
	*/
	void prEventClear(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event manager to search a patient.
	*/
	void prEventSearch(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Event manager to retrieve study.
	*/
	void prEventGetStudy(wxCommandEvent& WXUNUSED(event));
	/**
	 * @brief Manage event to capture number of row grid selected.
	*/
	void prEventSelectCell(wxGridEvent &event);
	/**
	 * @brief Get selected server of the list box.
	*/
	int getServer();
	/**
	 * @brief Analyze the process stream provided in the output.
	*/
	void analyzeOutput(wxString a_cad);
private:
	nkListDICOMServer prv_listServers;

	wxPanel * my_searchPanel;				//! Panel fields to search
	wxButton * my_cmdServerLocaltion;		//! Button to change server's
	wxListBox * my_listServerLocaltion;		//! List for display server's
	wxTextCtrl * my_textPatienID;			//! Search field to patient id.
	wxTextCtrl * my_textFirstName;			//! Search field to first name.
	wxTextCtrl * my_textAccessionNumber;	//! Search field to accession number.
	wxCheckBox * my_chkStudyDateFrom;		//! Checkout to use date from.
	wxButton * my_cmdStudyDateFrom;			//! Button to call calendar dialog.
	wxTextCtrl * my_textStudyDateFrom;		//! Search field to date from.
	wxCheckBox * my_chkStudyDateTo;			//! Checkout to use date to.
	wxButton * my_cmdStudyDateTo;			//! Button to call calendar dialog.
	wxTextCtrl * my_textStudyDateTo;		//! Search field to date from.
	wxTextCtrl * my_textstudyDescription;	//! Search field to study description.
	wxTextCtrl * my_textInstitutionName;	//! Search field to Institution name.
	wxButton * my_cmdSearch;				//! Command button to start search.
	wxButton * my_cmdClear;					//! Command button to clear fields.
	wxButton * my_getStudy;					//! Command button to get study.
	wxGrid * prv_wxGridPatients;			//! Grid to view patient's.
	int my_selectedCell;					//! Variable to save selected study in grid.
	nkNukak3D * my_parent;					//! Pointer to Nukak3D to load DICOM images.
	wxAuiManager prv_auiManager;			//! Administrator for Aui.
	DECLARE_EVENT_TABLE()					//! Macro for declare events.
};


#endif //_NKFINDSCU_H_