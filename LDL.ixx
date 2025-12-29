module;

export module LDL;

import std;

export namespace LDL
{
	template <typename T>
	class Vec2
	{
	public:
		Vec2() :
			x(0),
			y(0)
		{
		}

		Vec2(T px, T py) :
			x(px),
			y(py)
		{
		}
	private:
		T x;
		T y;
	};

	using Vec2i  = Vec2<int>;
}

using namespace LDL;

/********************************************************************************************************************
                                                         BaseWindow
********************************************************************************************************************/

class BaseWindow
{
public:
	BaseWindow(const Vec2i& pos, const Vec2i& size, const std::string& title) :
		_pos(pos),
		_size(size),
		_title(title)
	{
	}

	const Vec2i& GetPos()
	{
		return _pos;
	}

	void SetPos(const Vec2i& pos)
	{
		_pos = pos;
	}

	const Vec2i& GetSize()
	{
		return _size;
	}

	void SetSize(const Vec2i& size)
	{
		_size = size;
	}

	const std::string& GetTitle()
	{
		return _title;
	}

	void SetTitle(const std::string& title)
	{
		_title = title;
	}
private:
	Vec2i       _pos;
	Vec2i       _size;
	std::string _title;
};

class MainWindow
{
public:
	MainWindow(const Vec2i& pos, const Vec2i& size, const std::string& title) :
		_baseWindow(pos, size, title)
	{
	}

	const Vec2i& GetPos()
	{
		return _baseWindow.GetPos();
	}

	void SetPos(const Vec2i& pos)
	{
		_baseWindow.SetPos(pos);
	}

	const Vec2i& GetSize()
	{
		return _baseWindow.GetSize();
	}

	void SetSize(const Vec2i& size)
	{
		_baseWindow.SetSize(size);
	}

	const std::string& GetTitle()
	{
		return _baseWindow.GetTitle();
	}

	void SetTitle(const std::string& title)
	{
		_baseWindow.SetTitle(title);
	}
private:
	BaseWindow  _baseWindow;
};

export namespace LDL
{
	using Window = MainWindow;
}