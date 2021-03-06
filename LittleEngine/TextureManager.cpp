#include "TextureManager.h"



TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

//Loads all the textures we need
bool TextureManager::Initialise(ID3D12Device * device, ID3D12GraphicsCommandList * commandList)
{
	m_device = device;
	m_commandList = commandList;

	if (!LoadTexture(Texture::LOGO))
	{
		return false;
	}

	if (!LoadTexture(Texture::FLOOR, Bumpmap::FLOOR))
	{
		return false;
	}

	if (!LoadTexture(Texture::WALL, Bumpmap::WALL))
	{
		return false;
	}

	return true;
}

//Recives a texture from the textures map
std::shared_ptr<TextureImporter> TextureManager::GetTexture(const wchar_t * texturePath)
{
	//TODO: change to get so i can sort not found
	return textures[texturePath];
}

//Cleans up all the textures that we loaded
void TextureManager::TextureCleanup()
{
	for (std::map<const wchar_t*, std::shared_ptr<TextureImporter>>::iterator it = textures.begin(); it != textures.end(); it++)
	{
		it->second->TextureCleanup();
	}
}

//Load a texture then save it in the textures map
bool TextureManager::LoadTexture(const wchar_t * texturePath, const wchar_t* bumpPath)
{
	std::shared_ptr<TextureImporter> temp = std::make_shared<TextureImporter>();
	temp->Initialise(m_device, m_commandList);
	
	//If we have a bump path load it
	if (bumpPath != nullptr)
	{
		if (!temp->LoadTexture(texturePath, bumpPath))
		{
			return false;
		}
	}
	else
	{
		if (!temp->LoadTexture(texturePath))
		{
			return false;
		}
	}
	
	textures[texturePath] = temp;

	return true;
}
