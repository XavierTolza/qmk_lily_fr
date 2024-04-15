#pragma once
#include "keymap_french.h" 

// Change panels on the left
#define VSC_SWF RCS(FR_E) // Switch to files panel
#define VSC_SWS RCS(FR_F) // Switch to search panel
#define VSC_SWG RCS(FR_G) // Switch to git panel
#define VSC_SWD RCS(FR_D) // Switch to debug panel


enum custom_vscode_keycodes {
  ALT_TAB = SAFE_RANGE,
};