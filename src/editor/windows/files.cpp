
#include <filesystem>
#include <fstream>

#include "editor/windows/files.hpp"
#include "amuse/gui.hpp"
#include "amuse/editor.hpp"
#include "icons.hpp"

static std::filesystem::path rename_path;

void rename_file_or_folder_helper(std::filesystem::path path)
{
    static std::string ext;
    static char buffer[256];

    if (std::filesystem::is_directory(path))
    {
        strcpy_s(buffer, path.filename().string().c_str());
        ext = "";
    }
    else
    {
        strcpy_s(buffer, path.stem().string().c_str());
        ext = path.extension().string();
    }

    ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(28, 0));

    ImGui::SetKeyboardFocusHere(0);

    ImGui::InputText("Hello", buffer, 256, ImGuiInputTextFlags_EnterReturnsTrue);

    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    ImGui::PopItemWidth();

    if (ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
    {
        rename_path = "";
    }

    if (ImGui::IsAnyMouseDown() && !ImGui::IsItemHovered())
    {
        rename_path = "";
    }

    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        ImGui::SetActiveID(NULL, ImGui::GetCurrentWindow());
        ImGui::SetKeyboardFocusHere(-1);
        rename_path = "";

        if (!std::filesystem::exists(path.parent_path() / (std::string(buffer) + ext)))
        {
            std::filesystem::rename(path, path.parent_path() / (std::string(buffer) + ext));
        }
    }
}

void file_context_menu_helper(std::filesystem::path path, Editor *editor)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (std::filesystem::is_regular_file(path) && ImGui::MenuItem("Open"))
        {
            editor->open(path);
        }

        if (ImGui::BeginMenu("New"))
        {
            if (ImGui::MenuItem("Folder"))
            {
                if (std::filesystem::is_regular_file(path))
                {
                    path = path.parent_path();
                }

                std::filesystem::create_directory(path / "New Folder");
                rename_path = path / "New Folder";
            }

            if (ImGui::MenuItem("Empty Actor"))
            {
                if (std::filesystem::is_regular_file(path))
                {
                    path = path.parent_path();
                }

                std::ofstream file(path / "new_actor.actor");
                file.close();

                rename_path = path / "new_actor.actor";
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Rename"))
        {
            ImGui::SetItemDefaultFocus();
            rename_path = path;
            ImGui::SetKeyboardFocusHere(-1);
        }

        if (ImGui::MenuItem("Delete"))
        {
            std::filesystem::remove(path);
        }

        if (ImGui::MenuItem("Copy Path"))
        {
            ImGui::SetClipboardText(path.string().c_str());
        }

        if (ImGui::MenuItem("Open Folder In Explorer"))
        {
            const std::filesystem::path folder_path = std::filesystem::current_path() / path.parent_path();
            const std::filesystem::path c = std::filesystem::weakly_canonical(std::filesystem::path(folder_path));

#ifdef _WIN32
            system(("explorer /separate /select,\"" + c.string() + "\"").c_str());
#elif __APPLE__
            system(("open " + c.string()).c_str());
#elif __linux__
            system(("xdg-open " + c.string()).c_str());
#endif
        }

        ImGui::EndPopup();
    }
}

void draw_directory_helper(const std::filesystem::path &path, Editor *editor)
{
    constexpr ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                         ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                         ImGuiTreeNodeFlags_SpanFullWidth;

    for (auto &entry : std::filesystem::directory_iterator(path))
    {
        const std::filesystem::path path = entry.path();
        const std::string filename = path.filename().string();

        bool open = false;

        if (!entry.exists())
        {
            continue;
        }

        if (path.compare(rename_path) == 0)
        {
            rename_file_or_folder_helper(path);
        }
        else if (entry.is_directory())
        {
            open = ImGui::TreeNodeEx(entry.path().filename().string().c_str(), flags);
        }
        else
        {
            ImGui::TreeNodeEx(filename.c_str(), flags | ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen);

            if (ImGui::IsMouseDoubleClicked(ImGuiPopupFlags_MouseButtonLeft) && ImGui::IsItemHovered())
            {
                editor->open(path);
            }

            // const std::string uuid = xtb::AssetDatabase::GetUUIDByPath(_path.string());

            if (/* uuid != "" &&*/ ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
            {
                // xtb::Asset *asset = xtb::AssetDatabase::GetAssetByUUID(uuid);
                // const std::string typeName(asset->GetTypeName());
                const std::string payload_id = "RESOURCE-";

                ImGui::SetDragDropPayload(payload_id.c_str(), nullptr, 0, ImGuiCond_Once);

                ImGui::Text(filename.c_str());

                ImGui::EndDragDropSource();
            }
        }

        file_context_menu_helper(path, editor);

        if (!entry.exists())
        {
            if (open)
                ImGui::TreePop();

            continue;
        }

        if (open)
        {
            draw_directory_helper(entry.path(), editor);
            ImGui::TreePop();
        }
    }
}

void FilesEditor::on_init()
{
}

void FilesEditor::on_gui()
{
    if (editor->current_project_path.empty())
    {
        ImGui::Text("No project loaded");
        return;
    }

    if (!std::filesystem::exists(editor->current_project_path / "assets"))
    {
        ImGui::Text("Invalid project path");
        return;
    }

    constexpr ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow |
                                         ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                         ImGuiTreeNodeFlags_SpanFullWidth;

    const std::filesystem::path asset_path = editor->current_project_path / "assets";

    bool open = ImGui::TreeNodeEx("assets", flags);

    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::BeginMenu("New"))
        {
            if (ImGui::MenuItem("Folder"))
            {
                std::filesystem::create_directory(asset_path / "New Folder");
                rename_path = asset_path / "New Folder";
            }

            if (ImGui::MenuItem("Empty Actor"))
            {
                std::ofstream file(asset_path / "new_actor.actor");
                file.close();

                rename_path = asset_path / "new_actor.actor";
            }

            ImGui::EndMenu();
        }

        if (ImGui::MenuItem("Copy Path"))
        {
            ImGui::SetClipboardText(asset_path.string().c_str());
        }

        if (ImGui::MenuItem("Open Folder In Explorer"))
        {
            const std::filesystem::path folder_path = std::filesystem::current_path() / asset_path.parent_path();
            const std::filesystem::path c = std::filesystem::weakly_canonical(std::filesystem::path(folder_path));

#ifdef _WIN32
            system(("explorer /separate /select,\"" + c.string() + "\"").c_str());
#elif __APPLE__
            system(("open " + c.string()).c_str());
#elif __linux__
            system(("xdg-open " + c.string()).c_str());
#endif
        }

        ImGui::EndPopup();
    }

    if (open)
    {
        draw_directory_helper(asset_path, editor);

        ImGui::TreePop();
    }
}