#ifndef TEXTURECACHE_H
#define TEXTURECACHE_H

#include "UIFCore.h"

namespace UIF{

	class TextureCache{
		private:
			std::unordered_map<std::string, uint32_t> redirect_lookup; /*Check if the image data has already been loaded based on filepath.*/
		
		static constexpr uint32_t DUMMY_TEXTURE{ 1 };
		SDL_Texture* dummy_texture{ nullptr };
		std::vector<SDL_Texture*> textures { nullptr, dummy_texture }; //Insert one elemnt to reserve index 0 as sentinel i.e. 0 = 'No Texture',
									       //1 = 'Texture Creation Failure' <- Component is intended to be asset based.


		public:	
		
		void Add_Texture(const std::string& filepath, UIF::Window* window, UIF::Component* component);	
		SDL_Texture* Get_Texture(UIF::Component* component);
		
		bool Needs_RendererForDummy();
		void Make_Dummy(SDL_Renderer* renderer);

		TextureCache() = default;
	        ~TextureCache();
		TextureCache(const TextureCache&) = delete;
		TextureCache& operator=(const TextureCache&) = delete;
	};
};


#endif //TEXTURECACHE_H
