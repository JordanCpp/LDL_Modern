// Copyright 2025-present Evgeny Zoshchuk (JordanCpp).
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// https://www.boost.org/LICENSE_1_0.txt) 

module;

export module LDL.MainWindow;

import std;
import Win32;
import LDL.Vec2u;
import LDL.BaseWindow;

export namespace LDL
{
	class MainWindow
	{
	public:
		MainWindow(const Vec2u& pos, const Vec2u& size, const std::string& title, size_t mode, HWND hwnd) :
			_hwnd(hwnd),
			_baseWindow(pos, size, title, mode)
		{
		}

		const Vec2u& Pos() const
		{
			return _baseWindow.Pos();
		}

		void Pos(const Vec2u& pos)
		{
			_baseWindow.Pos(pos);
		}

		const Vec2u& Size() const
		{
			return _baseWindow.Size();
		}

		void Size(const Vec2u& size)
		{
			_baseWindow.Size(size);
		}

		const std::string& Title() const
		{
			return _baseWindow.Title();
		}

		void Title(const std::string& source)
		{
			_baseWindow.Title(source);
		}

		bool IsFullScreen() const
		{
			return _baseWindow.IsFullScreen();
		}

		bool IsResized() const
		{
			return _baseWindow.IsResized();
		}

		bool IsFixed() const
		{
			return _baseWindow.IsFixed();
		}

		bool IsMinimized() const
		{
			return _baseWindow.IsMinimized();
		}

		bool IsMaximized() const
		{
			return _baseWindow.IsMaximized();
		}

		bool IsCentered() const
		{
			return _baseWindow.IsCentered();
		}
	private:
		HWND       _hwnd;
		BaseWindow _baseWindow;
	public:
        LRESULT __stdcall Handler(UINT Message, WPARAM WParam, LPARAM LParam)
        {
            return DefWindowProcA(_hwnd, Message, WParam, LParam);
        }
	};

	LRESULT __stdcall GlobalWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (message == WM_NCCREATE)
		{
			CREATESTRUCTA* pCreate = reinterpret_cast<CREATESTRUCTA*>(lParam);
			SetWindowLongA(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreate->lpCreateParams));
		}

		auto* pMainWindow = reinterpret_cast<MainWindow*>(GetWindowLongA(hwnd, GWLP_USERDATA));

		if (pMainWindow)
		{
			return pMainWindow->Handler(message, wParam, lParam);
		}

		return DefWindowProcA(hwnd, message, wParam, lParam);
	}

	std::expected<MainWindow, const char*> MainWindowNew()
	{
		HINSTANCE instance = {};

		instance = GetModuleHandleA(nullptr);
		if (instance == nullptr)
		{
			return std::unexpected("GetModuleHandleA");
		}

		WNDCLASSA windowClass     = {};
		windowClass.hInstance     = instance;
		windowClass.lpszClassName = "";
		windowClass.lpfnWndProc   = GlobalWndProc;
		windowClass.style         = CS_HREDRAW | CS_VREDRAW;
		windowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		windowClass.hIcon         = LoadIconA(nullptr, IDI_APPLICATION);
		windowClass.hCursor       = LoadCursorA(nullptr, IDC_ARROW);

		ATOM atom = RegisterClassA(&windowClass);
		if (atom == INVALID_ATOM)
		{
			return std::unexpected("RegisterClassA");
		}

		HWND hwnd = CreateWindowExA(0L, "", "", 0, 0, 0, 800, 600, 0, 0, instance, 0);
		if (hwnd == nullptr)
		{
			return std::unexpected("CreateWindowExA");
		}

		return MainWindow(Vec2u(0, 0), Vec2u(0, 0), "", 0, hwnd);
	}
}
