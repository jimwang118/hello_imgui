#pragma once
#include "imgui.h"
#include "hello_imgui/screen_bounds.h"
#include <string>



namespace HelloImGui
{
enum class FullScreenMode
{
    NoFullScreen,
    FullScreen,                    // Full screen with specified resolution
    FullScreenDesktopResolution,   // Full screen with current desktop mode & resolution
    FullMonitorWorkArea            // Fake full screen, maximized window on the selected monitor
};


enum class WindowSizeState
{
    Standard,
    Minimized,
    Maximized
};


enum class WindowPositionMode
{
    OsDefault,
    MonitorCenter,
    FromCoords,
};


enum class WindowSizeMeasureMode
{
    // ScreenCoords: measure window size in screen coords.
    //     Note: screen coordinates *might* differ from real pixel on high dpi screens; but this depends on the OS.
    //         - For example, on apple a retina screenpixel size 3456x2052 might be seen as 1728x1026 in screen
    //           coordinates
    //         - Under windows, and if the application is DPI aware, ScreenCoordinates correspond to real pixels, 
    //           even on high density screens
    ScreenCoords,

    // RelativeTo96Ppi enables to give screen size that are independant from the screen density.
    // For example, a window size expressed as 800x600 will correspond to a size
    //    800x600 (in screen coords) if the monitor dpi is 96
    //    1600x120 (in screen coords) if the monitor dpi is 192
    RelativeTo96Ppi
};


/**
@@md#WindowGeometry

__WindowGeometry__ is a struct that defines the window geometry.

Members:
* `size`: _int[2], default="{800, 600}"_. Size of the application window
  used if fullScreenMode==NoFullScreen and sizeAuto==false
* `sizeAuto`: _bool, default=false_
  If true, adapt the app window size to the presented widgets
* `fullScreenMode`: _FullScreenMode, default=NoFullScreen_.
   You can choose between several full screen modes:
   ````cpp
        NoFullScreen,
        FullScreen,                    // Full screen with specified resolution
        FullScreenDesktopResolution,   // Full screen with current desktop mode & resolution
        FullMonitorWorkArea            // Fake full screen, maximized window on the selected monitor
    ````
* `positionMode`: _WindowPositionMode, default = OsDefault_.
   You can choose between several window position modes:
   ````cpp
        OsDefault,
        MonitorCenter,
        FromCoords,
    ````
* `monitorIdx`: _int, default = 0_.
  used if positionMode==MonitorCenter or if fullScreenMode!=NoFullScreen
* `windowSizeState`: _WindowSizeState, default=Standard_
   You can choose between several window size states:
   ````cpp
        Standard,
        Minimized,
        Maximized
    ````
* `windowSizeMeasureMode`: _WindowSizeMeasureMode_, default=RelativeTo96Ppi
  how the window size is specified:
  * RelativeTo96Ppi enables to give screen size that are independant from the screen density.
     For example, a window size expressed as 800x600 will correspond to a size
        - 800x600 (in screen coords) if the monitor dpi is 96
        - 1600x120 (in screen coords) if the monitor dpi is 192
      (this works with Glfw. With SDL, it only works under windows)
  * ScreenCoords: measure window size in screen coords
    (Note: screen coordinates might differ from real pixels on high dpi screen)
@@md
**/
struct WindowGeometry
{
    // used if fullScreenMode==NoFullScreen and sizeAuto==false. Value=(800, 600)
    ScreenSize size = DefaultWindowSize;

    // If true, adapt the app window size to the presented widgets
    bool sizeAuto = false;

    FullScreenMode fullScreenMode = FullScreenMode::NoFullScreen;

    WindowPositionMode positionMode = WindowPositionMode::OsDefault;

    // used if windowPositionMode==FromCoords, default=(40, 40)
    ScreenPosition position = DefaultScreenPosition;

    // used if positionMode==MonitorCenter or if fullScreenMode!=NoFullScreen
    int monitorIdx = 0;

    WindowSizeState windowSizeState = WindowSizeState::Standard;

    WindowSizeMeasureMode windowSizeMeasureMode = WindowSizeMeasureMode::RelativeTo96Ppi;
};


/**
@@md#AppWindowParams

__AppWindowParams__ is a struct that defines the application window display params.
See [doc_src/hello_imgui_diagram.png](https://raw.githubusercontent.com/pthom/hello_imgui/master/src/hello_imgui/doc_src/hello_imgui_diagram.png)
for details.

Members:
* `windowTitle`: _string, default=""_. Title of the application window
* `windowGeometry`: _WindowGeometry_
  Enables to precisely set the window geometry (position, monitor, size, full screen, fake full screen, etc.)
   _Note: on a mobile device, the application will always be full screen._
* `restorePreviousGeometry`: _bool, default=false_.
  If true, then save & restore windowGeometry from last run (the geometry will be written in imgui_app_window.ini)
* `borderless`: _bool, default = false_.
* `resizable`: _bool, default = false_.

Output Member:
* `outWindowDpiFactor`: _float, default = 1_.
   This value is filled by HelloImGui during the window initialisation. On Windows and Linux, it can be > 1
   on high resolution monitors (on MacOS, the scaling is handled by the system).
   When loading fonts, their size should be multiplied by this factor.
@@md
**/
struct AppWindowParams
{
    std::string windowTitle;

    WindowGeometry windowGeometry;

    // if true, then save & restore from last run
    bool restorePreviousGeometry = false;

    bool borderless = false;
    bool resizable = true;

    float outWindowDpiFactor = 1.;
};

}  // namespace HelloImGui