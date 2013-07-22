#include <linux/input.h>

#include "util.h"
#include "key_util.h"

#define UK UNKNOWN_KEY

/*
 * The order of the keys is defined in linux/input.h
 */
static char *key_names[] = {
   UK, "<ESC>",
   "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=",
   "<Backspace>", "<Tab>",
   "q", "w", "e", "r", "t", "y", "u", "i", "o", "p",
   "[", "]", "<Enter>", "<LCtrl>",
   "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",
   "'", "`", "<LShift>",
   "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", "/",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

static char *shift_key_names[] = {
   UK, "<ESC>",
   "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "_", "+",
   "<Backspace>", "<Tab>",
   "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
   "{", "}", "<Enter>", "<LCtrl>",
   "A", "S", "D", "F", "G", "H", "J", "K", "L", ":",
   "\"", "~", "<LShift>",
   "|", "Z", "X", "C", "V", "B", "N", "M", "<", ">", "?",
   "<RShift>",
   "<KP*>",
   "<LAlt>", " ", "<CapsLock>",
   "<F1>", "<F2>", "<F3>", "<F4>", "<F5>", "<F6>", "<F7>", "<F8>", "<F9>", "<F10>",
   "<NumLock>", "<ScrollLock>",
   "<KP7>", "<KP8>", "<KP9>",
   "<KP->",
   "<KP4>", "<KP5>", "<KP6>",
   "<KP+>",
   "<KP1>", "<KP2>", "<KP3>", "<KP0>",
   "<KP.>",
   UK, UK, UK,
   "<F11>", "<F12>",
   UK, UK, UK, UK, UK, UK, UK,
   "<KPEnter>", "<RCtrl>", "<KP/>", "<SysRq>", "<RAlt>", UK,
   "<Home>", "<Up>", "<PageUp>", "<Left>", "<Right>", "<End>", "<Down>",
   "<PageDown>", "<Insert>", "<Delete>"
};

#undef UK

/**
 * Determines whether the key code is a shift
 * @param  code the key code to check
 * @return      true if the key is a shift key, false otherwise
 */
bool isShift(uint16_t code) {
   return code == KEY_LEFTSHIFT || code == KEY_RIGHTSHIFT;
}

/**
 * Converts a key code to an ascii character. See linux/input.h for more
 * information
 *
 * @param  code the key code to convert
 * @return      the corresponding ascii character
 */
char *getKeyText(uint16_t code, uint8_t shift_pressed) {
   ASSERT_ON_COMPILE(ARRAY_SIZE(key_names) == ARRAY_SIZE(shift_key_names));

   // LOG("%s", shift_pressed ? "true" : "false");
   char **arr;
   if (shift_pressed != 0) {
      arr = shift_key_names;
   } else {
      arr = key_names;
   }

   if (code < ARRAY_SIZE(key_names)) {
      return arr[code];
   } else {
      LOG("Unknown key: %u", code);
      return UNKNOWN_KEY;
   }
}
