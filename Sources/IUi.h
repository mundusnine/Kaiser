#pragma once
#include <enginedefs.h>

typedef enum KUiWindowFlags {
    KUiWindowFlags_None                   = 0,
    KUiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    KUiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    KUiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    KUiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
    KUiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
    KUiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it. Also referred to as Window Menu Button (e.g. within a docking node).
    KUiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    KUiWindowFlags_NoBackground           = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
    KUiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    KUiWindowFlags_NoMouseInputs          = 1 << 9,   // Disable catching mouse, hovering test with pass through.
    KUiWindowFlags_MenuBar                = 1 << 10,  // Has a menu-bar
    KUiWindowFlags_HorizontalScrollbar    = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
    KUiWindowFlags_NoFocusOnAppearing     = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
    KUiWindowFlags_NoBringToFrontOnFocus  = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
    KUiWindowFlags_AlwaysVerticalScrollbar= 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
    KUiWindowFlags_AlwaysHorizontalScrollbar=1<< 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
    KUiWindowFlags_AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
    KUiWindowFlags_NoNavInputs            = 1 << 18,  // No gamepad/keyboard navigation within the window
    KUiWindowFlags_NoNavFocus             = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
    KUiWindowFlags_UnsavedDocument        = 1 << 20,  // Display a dot next to the title. When used in a tab/docking context, tab is selected when clicking the X + closure is not assumed (will wait for user to stop submitting the tab). Otherwise closure is assumed when pressing the X, so if you keep submitting the tab may reappear at end of tab bar.
    KUiWindowFlags_NoNav                  = KUiWindowFlags_NoNavInputs | KUiWindowFlags_NoNavFocus,
    KUiWindowFlags_NoDecoration           = KUiWindowFlags_NoTitleBar | KUiWindowFlags_NoResize | KUiWindowFlags_NoScrollbar | KUiWindowFlags_NoCollapse,
    KUiWindowFlags_NoInputs               = KUiWindowFlags_NoMouseInputs | KUiWindowFlags_NoNavInputs | KUiWindowFlags_NoNavFocus,
} KUiWindowFlags;

typedef struct IUi {
    void (*begin)(void);
    void (*end)(void);
    void (*window_set_pos)(float x,float y);
    void (*window_set_size)(float w,float h);
    int (*window_begin)(const char* name,int* open,int flags);
    void(*window_end)(void);
    void (*elem_set_pos)(float x,float y);
    void (*elem_same_line)(void);
    int  (*table_begin)(const char* name,int num_colums);
    void (*table_next_column)(void);
    void (*table_end)();
    void (*image)(UID image_id, float w, float h);
    void (*text)(char* fmt,float fontSize,...);
    int  (*button)(const char* label,float w, float h);
    void (*private_funcs[MAX_PRIVATE_FUNCS])(void* data);
} IUi;

#ifdef __cplusplus
extern "C"{
#endif
void create_ui_provider(void* engine);

#ifdef __cplusplus
}
#endif