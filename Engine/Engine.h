#pragma once

struct SDL_Window;

namespace svp
{
	class Engine
	{
		const int msPerFrame = 16; //for 60 fps
		SDL_Window* window{};
	public:
		void Initialize();
		void Load() const;
		void Run();
		void Cleanup();
		
	};
}
