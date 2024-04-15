#pragma once
#include "keymap_french.h" 
#include <stdint.h>

// Change panels on the left
#define VSC_SWF RCS(FR_E) // Switch to files panel
#define VSC_SWS RCS(FR_F) // Switch to search panel
#define VSC_SWG RCS(FR_G) // Switch to git panel
#define VSC_SWD RCS(FR_D) // Switch to debug panel

typedef uint16_t vscode_key_t;

typedef struct{
  const uint8_t nb;
  const vscode_key_t *keys;
}vscode_combo_t;

//extern const vscode_combo_t vscode_combos[];
