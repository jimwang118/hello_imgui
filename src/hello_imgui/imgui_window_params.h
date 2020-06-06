#pragma once
#include "imgui.h"
#include <functional>

namespace HelloImGui
{
enum class DefaultImGuiWindowType
{
    /// ProvideFullScreenWindow: a full window is provided in the background
    ProvideFullScreenWindow,
    /// ProvideFullScreenDockSpace: a full screen dockspace is provided in the background
    ProvideFullScreenDockSpace,
    /// No default window is provided (except for ImGui's default "debug" window)
    NoDefaultWindow
};

/// ImGuiWindowParams: defines the ImGui inner windows params
struct ImGuiWindowParams
{
    /// By default, a full window is provided in the background
    /// (you can still add window on top, since the Z-order of this background window is always behind)
    DefaultImGuiWindowType defaultImGuiWindowType = DefaultImGuiWindowType::ProvideFullScreenWindow;

    /// backgroundColor (only visible is defaultImGuiWindowType is NoDefaultWindow !)
    ImVec4 backgroundColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    /// Show Menu bar on top of imgui windows
    bool showMenuBar = false;

    /// Make windows only movable from the title bar
    bool configWindowsMoveFromTitleBarOnly = true;

    /// Callback that will create the initial docking layout
    std::function<void(ImGuiID /* fullDockSpace */)> InitialDockLayoutFunction = nullptr;
    /// Call this function from the code in order to restore the dock layout
    /// to the initial layout provided by InitialDockLayoutFunction
    void ResetDockLayout();

    /// wasDockLayoutApplied is an internal variable (set by InitialDockLayoutFunction() and ResetDockLayout())
    bool wasDockLayoutApplied = false;
};

// Internal functions below
namespace DockingDetails
{
    void ConfigureImGuiDocking(const ImGuiWindowParams& imGuiWindowParams);
    void ProvideWindowOrDock(ImGuiWindowParams& imGuiWindowParams);
    void CloseWindowOrDock(ImGuiWindowParams& imGuiWindowParams);
}  // namespace DockingDetails

}  // namespace HelloImGui