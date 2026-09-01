30/08:
- Grid holds BlockType values, not strings/pointers.
- Enum = one choice from a fixed set.
- Struct = a thing with multiple related fields.
- Functions receive copies by default in C.
- A local Player inside spawnPlayer disappears when the function returns.

31/08:
- Make main own rows/columns and one Player.
- Research changing caller data through pointers.
- Verify player position is valid before rendering @.

1/09:
- terminal.c/h - borrowed code, not fully understood yet.
- Purpose: disables "wait for Enter" and "show typed key" terminal behavior.
- Revisit after Phase 1: research ICANON, ECHO, VMIN/VTIME individually.

