#pragma once
#include "arch.h"
#include <memory>
#include <utility>
#include <vector>
#include <windef.h>
#include "winrt.hpp"
#include <winrt/TranslucentTB.Xaml.h>

#include "../../ProgramLog/error/winrt.hpp"
#include "undoc/uxtheme.hpp"
#include "../windows/windowclass.hpp"
#include "xamlpagehost.hpp"
#include "xamlthread.hpp"

class XamlThreadPool {
	WindowClass m_WndClass;
	WindowClass m_DragRegionClass;
	winrt::TranslucentTB::Xaml::App m_App = nullptr;

	std::vector<std::unique_ptr<XamlThread>> m_Threads;
	XamlThread &GetAvailableThread(std::unique_lock<Util::thread_independent_mutex> &lock);

public:
	XamlThreadPool(const XamlThreadPool &) = delete;
	XamlThreadPool &operator =(const XamlThreadPool &) = delete;

	inline XamlThreadPool(HINSTANCE hInst) :
		m_WndClass(MessageWindow::MakeWindowClass(L"XamlPageHost", hInst)),
		m_DragRegionClass(MessageWindow::MakeWindowClass(L"XamlDragRegion", hInst))
	{ }

	template<typename T, typename Callback, typename... Args>
	void CreateXamlWindow(xaml_startup_position pos, PFN_SHOULD_APPS_USE_DARK_MODE saudm, Callback &&callback, Args&&... args)
	{
		if (!m_App)
		{
			try
			{
				m_App = { };
			}
			HresultErrorCatch(spdlog::level::critical, L"Failed to create XAML application");
		}

		std::unique_lock<Util::thread_independent_mutex> guard;
		XamlThread &thread = GetAvailableThread(guard);
		thread.CreateXamlWindow<T>(std::move(guard), m_WndClass, m_DragRegionClass, pos, saudm, std::forward<Callback>(callback), std::forward<Args>(args)...);
	}

	~XamlThreadPool();
};