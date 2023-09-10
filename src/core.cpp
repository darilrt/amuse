#include "amuse/core.h"

void amuse::Init(int width, int height) {
	Assets::Init("assets/");
	
    Screen* screen = Screen::Get();
	screen->window = new wm::Window("Game", width, height);

    screen->window->SetVSync(true);
	
	debug::Init(screen->window);

	es::AddEventListener("Quit", [screen](const es::Event& e) {
        screen->window->Close();
	});
}

void amuse::RunGame() {
    Screen* screen = Screen::Get();

    SceneManager::Start();
    while (screen->window->IsOpen()) {
        es::PollEvents();

#ifdef _DEBUG
        debug::InitFrame();
#endif // _DEBUG
        
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
