// Michael McCain
// 08/10/2023
// This is a 2D top down fantasy action game.

// Libraries
#include "raylib.h"
#include "raymath.h"

int main ()
{
   const int windowWidth {384};
   const int windowHeight {384};
   
   // Initialize Window
   InitWindow(windowWidth, windowHeight, "Top Down Fantasy");     // Width, Height Title window params

   // Load Map Texture and Vector Location
   Texture2D map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
   Vector2 mapPos{0.0,0.0};
   float speed = 4.0;

   // Character
   Texture2D knight = LoadTexture("characters/knight_idle_spritesheet.png");
   Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
   Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");

   Vector2 knightPos {
    (float)windowWidth/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
    (float)windowHeight/2.0f - 4.0f * (0.5f * (float)knight.height)
    };
    // 1 : facing right, - 1 : facing left
    float rightLeft {1.f};
    // Animation Variables
    float runningTime {};
    int frame{};
    const int maxFrames{6};
    const float updateTime{1.f/12.f}; // UPdates animation 12 times per second

   SetTargetFPS(60);


   // Display Game Window
   while (!WindowShouldClose())
    {
      BeginDrawing();
      ClearBackground(WHITE);

      Vector2 direction {};
      
      // Movement Keystrokes
      if (IsKeyDown(KEY_A)) direction.x -= 1.0;
      if (IsKeyDown(KEY_D)) direction. x += 1.0;
      if (IsKeyDown(KEY_W)) direction.y -= 1.0;
      if (IsKeyDown(KEY_S)) direction.y += 1.0;

      // Checks direction magnitude and sets map pos and knight animation
      if (Vector2Length(direction) != 0.0)
      {
        
        // Set map pos = mapPos - Direction, but scaled using speed
        mapPos = Vector2Subtract(mapPos, Vector2Scale(Vector2Normalize(direction), speed));

        // turnary (sp?) statement to check left/right character face
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        knight = knight_run;
      }
      else {
        knight = knight_idle; // directon is 0 and knight is idle
      }

      // Draw Map
      DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);
      
      // Update animation frame
      runningTime += GetFrameTime();
      if (runningTime >= updateTime)
      {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrames) frame = 0;
      }

      
      // Draw Character   
      // Source (first frame in animation for x and y /animation frame divided by 6 for width)   
      Rectangle src = {frame * (float)knight.width/6.f, 0.f, rightLeft * (float)knight.width/6.f, (float)knight.height};

      // Destination (draw location of x and y for the character/ scale the spirte by 4.0/ )
      Rectangle dest = {knightPos.x, knightPos.y, 4.0f * (float)knight.width/6.0f, 4.0f * (float)knight.height};

      // Draw the knight (charcter knight, source rec, dest rec, vector of 0.0/0.0, rotation, and tint)
      DrawTexturePro(knight, src, dest, Vector2{},0.f, WHITE);


      // --Game Logic Ends--

      // --Stop Drawing--
      EndDrawing();
    }
    // --Unload Textures--
    UnloadTexture(map);

    // --End Program--
    CloseWindow();
  }
