#pragma once

namespace WTF
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return RendererAPI::OpenGL; }
		
	private:
		static RendererAPI rendererAPI;
	};
}