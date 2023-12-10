#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleOpenGL.h"
#include "ModuleWindow.h"
#include "ModuleTexture.h"
#include "ModuleLoader.h"
#include <vector>

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
    //bool show_demo_window = false;
    //ImGui::ShowDemoWindow(&show_demo_window);

    bool show_about_window = false;

    //--> START TOP MENU BAR
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
                show_about_window = true; 
            }
            if (ImGui::MenuItem("Go to GitHub Repo")) {
                ShellExecuteA(NULL, "open", GITHUB_URL, NULL, NULL, SW_SHOWNORMAL);
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
    // <--- END TOP MENU BAR


    //--> START COMPONENTS WINDOW
    if (ImGui::Begin("Components"))   
    {
        if (ImGui::CollapsingHeader("Geometry"))
        {

            Model* model = App->moduleLoader->GetModel();
            std::vector<Mesh*> meshes = App->moduleLoader->GetModel()->GetMeshes();
            unsigned int numVertices = 0;
            unsigned int numIndices = 0;
            for (const auto& srcmesh : meshes) {
                numVertices += srcmesh->GetNumberOfVertices();
				numIndices += srcmesh->GetNumberOfIndices();
            }

            ImGui::Text("Meshes: %d", meshes.size());
            ImGui::Text("Vertices: %d", numVertices);
            ImGui::Text("Indices: %d", numIndices);

            static const char* minificationFilters[]{ "Nearest", "Linear", "Nearest MipMap Nearest","Linear MipMap Nearest", "Nearest MipMap Linear", "Linear MipMap Linear" };
            static int SelectedMin = 5;
            if (ImGui::Combo("MIN Filter", &SelectedMin, minificationFilters, IM_ARRAYSIZE(minificationFilters)))
            {
                switch (SelectedMin)
                {
                case 0:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    break;
                case 1:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    break;
                case 2:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
                    break;
                case 3:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                    break;
                case 4:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
                    break;
                case 5:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    break;
                }
            }

            static const char* magnificationFilters[]{ "Nearest","Linear" };
            static int SelectedMag = 1;
            if (ImGui::Combo("MAG filter", &SelectedMag, magnificationFilters, IM_ARRAYSIZE(magnificationFilters)))
            {
                switch (SelectedMag)
                {
                case 0:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case 1:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                }
            }
        }

        if (ImGui::CollapsingHeader("Texture"))
        {
            ImGui::Text("Format: %s", App->texture->GetFormat());
            ImGui::Text("Width: %i px", App->texture->GetWidth());
            ImGui::Text("Height: %i px", App->texture->GetHeight());
            ImGui::Text("Mip levels: %i", App->texture->GetMipLevels());

            static const char* minificationFilters[]{ "Nearest", "Linear", "Nearest MipMap Nearest","Linear MipMap Nearest", "Nearest MipMap Linear", "Linear MipMap Linear"};
            static int SelectedMin = 5;
            if (ImGui::Combo("MIN Filter", &SelectedMin, minificationFilters, IM_ARRAYSIZE(minificationFilters)))
            {
                switch (SelectedMin)
                {
					case 0:
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
						break;
					case 1:
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                        break;
                    case 2:
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
						break;
                    case 3:
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
                        break;
					case 4:
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
						break;
                    case 5:
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
						break;
				}
            }

            static const char* magnificationFilters[]{ "Nearest","Linear" };
            static int SelectedMag = 1;
            if (ImGui::Combo("MAG filter", &SelectedMag, magnificationFilters, IM_ARRAYSIZE(magnificationFilters)))
            {
                switch (SelectedMag)
                {
                case 0:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                case 1:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                }
            }
        }

        if (ImGui::CollapsingHeader("System Information")) {

            //TODO: Add more data to the system information
            ImGui::Text("FPS: %.1f", (ImGui::GetIO().Framerate));
            ImGui::Text("Frame rendering time: %.3f ms/frame (avg.)",(1000/ImGui::GetIO().Framerate));
            ImGui::Text("Window Size: %d x %d", App->window->GetWidth(), App->window->GetHeight());

            ImGui::Separator();

            ImGui::TextWrapped("HARDWARE");
            ImGui::Text("Vendor: %s", glGetString(GL_VENDOR));
            ImGui::Text("Graphic Card: %s", glGetString(GL_RENDERER));
            
            ImGui::Separator();

            ImGui::TextWrapped("SOFTWARE");
            ImGui::Text("OpenGL: %s", glGetString(GL_VERSION));
            ImGui::Text("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
            ImGui::Text("SDL: %d.%d.%d", SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL);

            ImGui::Separator();
        }

        ImGui::End();  
    }
    //<--- END MAIN TOOLS WINDOW


    if (show_about_window) {
        ImGui::OpenPopup("About");
    }

    // Set popup size and calcula middle of the window
    const float newWindowWidth = App->window->GetWidth() / 2.f;
    const float newWindowHeight = App->window->GetHeight() / 2.f;
    ImGui::SetNextWindowSize({ newWindowWidth, newWindowHeight});
    ImGui::SetNextWindowPos({ App->window->GetWidth() - (newWindowWidth/2.f), App->window->GetHeight() - (newWindowHeight / 2.f) });

    if (ImGui::BeginPopupModal("About"))
    {

        ImGui::TextWrapped("OxEngine - 3D Game Engine written in C++");
		ImGui::Separator();
        ImGui::TextWrapped("Developed for the Master's Degree in Advanced Programming for AAA Video Games");
        ImGui::Separator();
        ImGui::TextWrapped("HOW TO USE");
        ImGui::TextWrapped("Drag the model.gLTF file to the engine window");
        ImGui::TextWrapped("Camera controls");
        ImGui::TextWrapped("W->Move FRONT");
        ImGui::TextWrapped("A->Move LEFT");
        ImGui::TextWrapped("S->Move RIGHT");
        ImGui::TextWrapped("D->Move BACK");
        ImGui::TextWrapped("Q->Move UP");
        ImGui::TextWrapped("E->Move DOWN");
        ImGui::TextWrapped("F->Focus the camera around the geometry");
        ImGui::TextWrapped("Mouse Wheel->ZoomIn / ZoomOut");
        ImGui::TextWrapped("Right Click(Hold)->Add free look(Can be combined with movement)");
        ImGui::TextWrapped("SHIFT(Hold)->Duplicates movement speed");
        ImGui::TextWrapped("Alt + Left click Orbit the object");
        ImGui::Separator();
        ImGui::TextWrapped("LICENSE");
        ImGui::TextWrapped("MIT");
        ImGui::Separator();

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

