#pragma once

#include <string>

using namespace std;

namespace WTF
{
	class Shader
	{
	public:
		Shader(const string& vertexSource, const string& fragmentSource);

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t rendererID;
	};
}