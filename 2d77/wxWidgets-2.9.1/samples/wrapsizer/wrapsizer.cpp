/////////////////////////////////////////////////////////////////////////////
// Name:        wrapsizer.cpp
// Purpose:     wxWidgets sample demonstrating wxWrapSizer use
// Author:      Arne Steinarson
// Created:     21.01.2008
// RCS-ID:      $Id: wrapsizer.cpp 58744 2009-02-08 01:01:00Z FM $
// Copyright:   (c) Arne Steinarson
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "wx/log.h"
#include "wx/wrapsizer.h"
#include "wx/artprov.h"

#ifndef __WXMSW__
    #include "../sample.xpm"
#endif


// ----------------------------------------------------------------------------
// definitions
// ----------------------------------------------------------------------------

class WrapSizerFrame : public wxFrame
{
public:
    WrapSizerFrame();

private:
    void OnButton(wxCommandEvent& WXUNUSED(event))
    {
        Close();
    }

    void AddToolBarButton(wxToolBar *tb,
                          const wxString& label,
                          const wxString& artid)
    {
        wxBitmap
            bm = wxArtProvider::GetBitmap(artid, wxART_TOOLBAR, wxSize(16, 16));
        tb->AddTool(wxID_ANY, label, bm);
    }

    wxToolBar *MakeToolBar()
    {
        wxToolBar *tb = new wxToolBar(this, wxID_ANY,
                                      wxDefaultPosition, wxDefaultSize,
                                      wxTB_NODIVIDER);
        AddToolBarButton(tb, "Help", wxART_HELP_BOOK);
        tb->AddSeparator( );
        AddToolBarButton(tb, "Open", wxART_FILE_OPEN);
        tb->AddSeparator( );
        AddToolBarButton(tb, "Up", wxART_GO_DIR_UP);
        AddToolBarButton(tb, "Execute", wxART_EXECUTABLE_FILE);

        tb->Realize( );
        return tb;
    }
};

class WrapSizerApp : public wxApp
{
public:
    WrapSizerApp() {}

    virtual bool OnInit()
    {
        new WrapSizerFrame;
        return true;
    }
};

IMPLEMENT_APP(WrapSizerApp);


// ----------------------------------------------------------------------------
// WrapSizerFrame
// ----------------------------------------------------------------------------

WrapSizerFrame::WrapSizerFrame()
        : wxFrame(NULL, wxID_ANY, "wxWrapSizer Sample")
{
    SetIcon(wxICON(sample));

    // Root sizer, vertical
    wxSizer * const sizerRoot = new wxBoxSizer(wxVERTICAL);

    // Some toolbars in a wrap sizer
    wxSizer * const sizerTop = new wxWrapSizer( wxHORIZONTAL );
    sizerTop->Add(MakeToolBar());
    sizerTop->Add(20, 1);
    sizerTop->Add(MakeToolBar());
    sizerTop->Add(20, 1);
    sizerTop->Add(MakeToolBar());
    sizerRoot->Add(sizerTop, wxSizerFlags().Expand().Border());

    // A number of checkboxes inside a wrap sizer
    wxSizer *sizerMid = new wxStaticBoxSizer(wxVERTICAL, this,
                                                "With check-boxes");
    wxSizer * const sizerMidWrap = new wxWrapSizer(wxHORIZONTAL);
    for ( int nCheck = 0; nCheck < 6; nCheck++ )
    {
        wxCheckBox *chk = new wxCheckBox
                                (
                                this,
                                wxID_ANY,
                                wxString::Format("Option %d", nCheck)
                                );

        sizerMidWrap->Add(chk, wxSizerFlags().Centre().Border());
    }

    sizerMid->Add(sizerMidWrap, wxSizerFlags(100).Expand());
    sizerRoot->Add(sizerMid, wxSizerFlags(100).Expand().Border());


    // A shaped item inside a box sizer
    wxSizer *sizerBottom = new wxStaticBoxSizer(wxVERTICAL, this,
                                                "With wxSHAPED item");
    wxSizer *sizerBottomBox = new wxBoxSizer(wxHORIZONTAL);
    sizerBottom->Add(sizerBottomBox, wxSizerFlags(100).Expand());

    sizerBottomBox->Add(new wxListBox(this, wxID_ANY,
                                        wxPoint(0, 0), wxSize(70, 70)),
                        wxSizerFlags().Expand().Shaped());
    sizerBottomBox->AddSpacer(10);
    sizerBottomBox->Add(new wxCheckBox(this, wxID_ANY,
                                        "A much longer option..."),
                        wxSizerFlags(100).Border());
    sizerRoot->Add(sizerBottom, wxSizerFlags(100).Expand().Border());

    // OK Button
    sizerRoot->Add(new wxButton(this, wxID_OK),
                    wxSizerFlags().Centre().DoubleBorder());
    Connect(wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED,
                wxCommandEventHandler(WrapSizerFrame::OnButton));

    // Set sizer for window
    SetSizerAndFit(sizerRoot);

    Show();
}

