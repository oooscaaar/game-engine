#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"


ModuleEditor::ModuleEditor()
{
    
}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
    LOG("Init ImGUI");

    bool ret = true;
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(App->window->GetWindow(), App->render->GetContext());
    ImGui_ImplOpenGL3_Init("#version 460");

    return ret;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->GetWindow());
    ImGui::NewFrame();
   
	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);

    bool show_about_window = false;

    
    if (ImGui::BeginMainMenuBar())
    {
        
        if (ImGui::BeginMenu("File"))
        { 
            if (ImGui::MenuItem("Exit", "Alt+F4")) {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About")) {
                LOG("About window opened");
                show_about_window = true; 
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }


    if (show_about_window) {
        //TODO: Fix rendering outside of the window. Nonetheless, it sets the windows position relative to the top left corner of the entire screen.
        // ImVec2 windowPos = { App->window->GetWidth() / 2.f,  App->window->GetHeight() / 2.f };


        ImGui::OpenPopup("About");
    }

    // LOG("Window Position: [ x = %f ] [ y = %f]\n", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);
    //LOG("Window Size: [ x = %f ] [ y = %f]\n", ImGui::GetWindowSize().x, ImGui::GetWindowSize().y);

    ImGui::SetNextWindowSize({ 400, 200 });

    if (ImGui::BeginPopupModal("About"))
    {
        
        // LOG("Window Position INSIDE POPUP: [ x = %f ] [ y = %f]\n", ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

        //
        //ImGui::SetNextWindowPos({ ImGui::GetWindowSize().x / 2.f, ImGui::GetWindowSize().y / 2.f });

        ImGui::TextWrapped("I'll add some information about the project, the licenses, and Me :)");
        ImGui::Separator();
        static float slider_value = 0.0f;
        ImGui::SliderFloat("Slider", &slider_value, 0.0f, 100.0f);
        ImGui::Separator();
        LOG("Test Slider: %f", slider_value);
        if (ImGui::Button("Ok")) ImGui::CloseCurrentPopup();
        ImGui::EndPopup();
    }



    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate() {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(App->window->GetWindow(), App->render->GetContext());
        return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    LOG("Quitting ImGUI");
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

