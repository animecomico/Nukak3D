/**
 * ***** BEGIN GPL LICENSE BLOCK *****
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * The Original Code is Copyright (C) 2007-2010 by Bioingenium Research Group.
 * Bogota - Colombia
 * All rights reserved.
 *
 * Author(s): Alexander Pinz�n Fern�ndez.
 *
 * ***** END GPL LICENSE BLOCK *****
 */

/** 
 * @file nkIODialog.cpp
 * @brief Generic dialog for input, output information.
 * @author  Byron P�rez, Alexander Pinzon
 * @version 0.3
 * @date 27/12/2007 03:37 p.m.
*/
#include "nkIODialog.h"

nkIODialog::nkIODialog(wxWindow* parent, 
	   wxString unasEtiquetas[100],
	   int un_tamanio,
	   wxWindowID id, 
	   const wxString& title, 
	   const wxPoint& pos, 
	   const wxSize& size, 
	   long style, 
	   const wxString& name):
	wxDialog(parent, id, title, pos, size, style, name)
{
	this->prv_tamanio = un_tamanio;
	for (int i=0; i<prv_tamanio; i++){
		new wxStaticText(this,
			-1,
			unasEtiquetas[i],
			wxPoint(20,20*(i+1)));
		prv_wxTCValores[i] = new wxTextCtrl(this,
			-1,
			wxT("0"),
			wxPoint(200,20*(i+1)));
	}
	new wxButton(this, wxID_OK, _("OK"),wxPoint(40,prv_tamanio*20+40));	
	new wxButton(this, wxID_CANCEL, _("Cancel"),wxPoint(170,prv_tamanio*20+40));

	CenterOnParent();

}

nkIODialog::nkIODialog(wxWindow* parent, 
	   wxString p_text,
	   wxWindowID id, 
	   const wxString& title, 
	   const wxPoint& pos, 
	   const wxSize& size, 
	   long style, 
	   const wxString& name):
	wxDialog(parent, id, title, pos, size, style, name)
{
	new wxTextCtrl(this,-1,p_text,wxPoint(30,30),wxSize(580,240),wxTE_MULTILINE | wxTE_READONLY );
	new wxButton(this, wxID_OK, _("OK"),wxPoint(270,280));	

	CenterOnParent();

}

nkIODialog::~nkIODialog(){
	/**/
}

void nkIODialog::cambiarValor(wxString un_valor, int un_indice){
	if (un_indice<prv_tamanio){
		prv_wxTCValores[un_indice]->SetValue(un_valor);
	}
}

wxString nkIODialog::obtenerValor(int un_indice){
	wxString miValor = wxT("");
	if (un_indice<prv_tamanio){
		miValor = prv_wxTCValores[un_indice]->GetValue();
	}
	return miValor;
}

nkCalendarDialog::nkCalendarDialog(wxWindow* parent, 
								   wxWindowID id, 
								   wxString title, 
								   wxPoint pos, 
								   wxSize size, 
								   long style, 
								   wxString name):
		wxDialog(parent, id, title, pos, size, style, name){

	my_cal = new wxCalendarCtrl(this, wxID_ANY);
	my_cmdOk = new wxButton(this, wxID_OK, _("Ok"));
	wxFlexGridSizer * my_sizer =  new wxFlexGridSizer(2, 1, 5, 5);
	my_sizer->Add(my_cal, 0,  wxALL, 5);
	my_sizer->Add(my_cmdOk, 0, wxALIGN_CENTER_HORIZONTAL , 5);
	my_sizer->SetMinSize(my_cal->GetSize().GetWidth() + 10, my_cal->GetSize().GetHeight() + 70 );
	this->SetSizer(my_sizer);
    my_sizer->Fit(this);
	this->SetSize(my_cal->GetSize().GetWidth() + 10, my_cal->GetSize().GetHeight() + 70 );
}

const wxDateTime & nkCalendarDialog::getDate(){
	return my_cal->GetDate();
}