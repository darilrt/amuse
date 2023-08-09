#include "amuse/core.h"

void amuse::Init(int width, int height) {
	Assets::Init("assets/");
	
    Screen* screen = Screen::Get();
	screen->window = new wm::Window("Game", 1240, 720);
	
	debug::Init(screen->window);

	es::AddEventListener("Quit", [screen](const es::Event& e) {
        screen->window->Close();
	});
}

void amuse::RunGame() {
    Screen* screen = Screen::Get();
    while (screen->window->IsOpen()) {
        es::PollEvents();

        debug::InitFrame();
        
        SceneManager::Update();

        if (Camera::active) {
            Camera::active->Begin();

            gl::Clear();
            SceneManager::Render();

#ifdef _DEBUG
            debug::Draw(*Camera::active);
#endif // _DEBUG

            Camera::active->End();
        }

#ifdef _DEBUG
        debug::DrawGui();
#endif
    
        screen->window->SwapBuffers();
    } 
}
