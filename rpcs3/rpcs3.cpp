#include "stdafx.h"
#include "Utilities/Log.h"
#include "Emu/Memory/Memory.h"
#include "Emu/System.h"
#include "rpcs3.h"
#include "Ini.h"
#include "Gui/ConLogFrame.h"
#include "Emu/GameInfo.h"

#ifdef _WIN32
#include <wx/msw/wrapwin.h>
#endif

#ifdef __UNIX__
#include <X11/Xlib.h>
#endif

wxDEFINE_EVENT(wxEVT_DBG_COMMAND, wxCommandEvent);

IMPLEMENT_APP(Rpcs3App)
Rpcs3App* TheApp;

bool Rpcs3App::OnInit()
{
	TheApp = this;
	SetAppName(_PRGNAME_);
	wxInitAllImageHandlers();

	Ini.Load();

	Emu.Init();
	OnArguments();

	if(use_gui)
	{
		m_MainFrame = new MainFrame();
		SetTopWindow(m_MainFrame);

		m_MainFrame->Show();
		m_MainFrame->DoSettings(true);
	}
	
	return true;
}

void Rpcs3App::OnArguments()
{
	// Usage:
	//   rpcs3-*.exe               Initializes RPCS3
	//   rpcs3-*.exe [(S)ELF]      Initializes RPCS3, then loads and runs the specified (S)ELF file.
	
	for(int i = 1; i< Rpcs3App::argc ; ++i)
	{
		if(argv[i] == "--nogui")
		{
			use_gui = false;
		}
	}

	if (Rpcs3App::argc > 1)
	{
		// Force this value to be true
		Ini.HLEExitOnStop.SetValue(true);
		
		Emu.SetPath(fmt::ToUTF8(argv[1]));
		Emu.Load();
		Emu.Run();
	}
}

void Rpcs3App::Exit()
{
	Emu.Stop();
	Ini.Save();

	wxApp::Exit();
}

void Rpcs3App::SendDbgCommand(DbgCommand id, CPUThread* thr)
{
	wxCommandEvent event(wxEVT_DBG_COMMAND, id);
	event.SetClientData(thr);
	AddPendingEvent(event);
}

Rpcs3App::Rpcs3App(): use_gui(true)
{
	#if defined(__UNIX__) && !defined(__APPLE__)
	XInitThreads();
	#endif
}
/*
CPUThread& GetCPU(const u8 core)
{
	return Emu.GetCPU().Get(core);
}*/

GameInfo CurGameInfo;
