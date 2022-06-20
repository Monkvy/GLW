#pragma once
#include <iostream>


namespace GLW
{
	class Texture 
	{
	public:
		Texture(const std::string& filepath);
		~Texture();

		// Bind this texture to a given slot on the GPU.
		void Bind(uint32_t slot=0) const;
		void Unbind() const;

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

	private:
		uint32_t m_RendererID;
		std::string m_Filepath;
		unsigned char* m_LocalBuffer;
		int m_Width, m_Height, m_BPP;
	};
}