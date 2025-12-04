#include "raylib.h"
#include <math.h>
#include <stdlib.h>

#define MAX_BULLETS 100
#define MAX_ENEMIES 50
#define MAX_PARTICLES 200

// --- Math Structures ---
typedef struct {
    Vector2 pos;
    Vector2 vel;
    Vector2 acc;
    float rotation;
    float friction;
    bool active;
    Color color;
} Entity;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float life; // 1.0 to 0.0
    bool active;
    Color color;
} Particle;

// --- Global Arrays (The "Memory Pool") ---
Entity player;
Entity bullets[MAX_BULLETS] = { 0 };
Entity enemies[MAX_ENEMIES] = { 0 };
Particle particles[MAX_PARTICLES] = { 0 };

// --- Math Helper: Spawn Explosion ---
void SpawnExplosion(Vector2 position, int count, Color color) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!particles[i].active && count > 0) {
            particles[i].active = true;
            particles[i].pos = position;
            
            // Random Vector math for explosion
            float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
            float speed = (float)GetRandomValue(200, 500) / 100.0f;
            
            particles[i].vel.x = cosf(angle) * speed;
            particles[i].vel.y = sinf(angle) * speed;
            particles[i].life = 1.0f;
            particles[i].color = color;
            count--;
        }
    }
}

int main(void) {
    // 1. Setup Window
    const int screenWidth = 1200;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "CachyOS: Vector Wars");
    SetTargetFPS(144); // RTX 4080 Speed

    // 2. Setup Player (Vector Dynamics)
    player.pos = (Vector2){ screenWidth/2, screenHeight/2 };
    player.friction = 0.98f; // Friction coefficient (0.98 means 2% drag per frame)
    player.color = SKYBLUE;
    player.active = true;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // --- UPDATE PHASE (The Math) ---

        // 1. Player Physics (Acceleration -> Velocity -> Position)
        Vector2 input = { 0, 0 };
        if (IsKeyDown(KEY_W)) input.y -= 1.0f;
        if (IsKeyDown(KEY_S)) input.y += 1.0f;
        if (IsKeyDown(KEY_A)) input.x -= 1.0f;
        if (IsKeyDown(KEY_D)) input.x += 1.0f;

        // Normalize input vector so diagonal isn't faster
        if (input.x != 0 || input.y != 0) {
            float length = sqrtf(input.x*input.x + input.y*input.y);
            input.x /= length;
            input.y /= length;
            
            // Apply Acceleration (F = ma)
            float speed = 1500.0f;
            player.vel.x += input.x * speed * dt;
            player.vel.y += input.y * speed * dt;
        }

        // Apply Friction (Damping)
        player.vel.x *= player.friction;
        player.vel.y *= player.friction;

        // Apply Velocity to Position
        player.pos.x += player.vel.x * dt;
        player.pos.y += player.vel.y * dt;

        // Screen Wrap (Topology)
        if (player.pos.x > screenWidth) player.pos.x = 0;
        if (player.pos.x < 0) player.pos.x = screenWidth;
        if (player.pos.y > screenHeight) player.pos.y = 0;
        if (player.pos.y < 0) player.pos.y = screenHeight;

        // Player Rotation (Point towards mouse)
        Vector2 mouse = GetMousePosition();
        // atan2(dy, dx) gives the angle in radians between two points
        float dy = mouse.y - player.pos.y;
        float dx = mouse.x - player.pos.x;
        player.rotation = atan2f(dy, dx) * RAD2DEG;

        // 2. Shooting Mechanics
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = true;
                    bullets[i].pos = player.pos;
                    // Calculate velocity vector based on player rotation
                    float rad = player.rotation * DEG2RAD;
                    bullets[i].vel.x = cosf(rad) * 800.0f;
                    bullets[i].vel.y = sinf(rad) * 800.0f;
                    bullets[i].color = YELLOW;
                    break;
                }
            }
        }

        // 3. Enemy Spawning & Tracking
        if (GetRandomValue(0, 100) < 2) { // 2% chance per frame
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (!enemies[i].active) {
                    enemies[i].active = true;
                    // Spawn at random edge
                    if (GetRandomValue(0,1)) {
                        enemies[i].pos.x = GetRandomValue(0, screenWidth);
                        enemies[i].pos.y = GetRandomValue(0,1) ? -20 : screenHeight + 20;
                    } else {
                        enemies[i].pos.x = GetRandomValue(0,1) ? -20 : screenWidth + 20;
                        enemies[i].pos.y = GetRandomValue(0, screenHeight);
                    }
                    enemies[i].color = RED;
                    break;
                }
            }
        }

        // Update Enemies (Homing Logic)
        for (int i = 0; i < MAX_ENEMIES; i++) {
            if (enemies[i].active) {
                // Calculate Vector to Player
                float dx = player.pos.x - enemies[i].pos.x;
                float dy = player.pos.y - enemies[i].pos.y;
                float angle = atan2f(dy, dx);
                
                // Move towards player
                float speed = 200.0f;
                enemies[i].pos.x += cosf(angle) * speed * dt;
                enemies[i].pos.y += sinf(angle) * speed * dt;
                enemies[i].rotation += 200.0f * dt; // Spin!

                // Collision with Player
                if (CheckCollisionCircles(player.pos, 20, enemies[i].pos, 15)) {
                    // Game Over Logic here (we just reset for now)
                    player.pos = (Vector2){screenWidth/2, screenHeight/2};
                    player.vel = (Vector2){0,0};
                    SpawnExplosion(enemies[i].pos, 50, RED);
                    enemies[i].active = false;
                }
            }
        }

        // Update Bullets
        for (int i = 0; i < MAX_BULLETS; i++) {
            if (bullets[i].active) {
                bullets[i].pos.x += bullets[i].vel.x * dt;
                bullets[i].pos.y += bullets[i].vel.y * dt;

                // Despawn if off screen
                if (bullets[i].pos.x < 0 || bullets[i].pos.x > screenWidth ||
                    bullets[i].pos.y < 0 || bullets[i].pos.y > screenHeight) {
                    bullets[i].active = false;
                }

                // Bullet Collision
                for (int j = 0; j < MAX_ENEMIES; j++) {
                    if (enemies[j].active) {
                        if (CheckCollisionCircles(bullets[i].pos, 5, enemies[j].pos, 20)) {
                            enemies[j].active = false;
                            bullets[i].active = false;
                            SpawnExplosion(enemies[j].pos, 20, ORANGE);
                        }
                    }
                }
            }
        }

        // Update Particles
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (particles[i].active) {
                particles[i].pos.x += particles[i].vel.x;
                particles[i].pos.y += particles[i].vel.y;
                particles[i].life -= 2.0f * dt;
                if (particles[i].life <= 0) particles[i].active = false;
            }
        }

        // --- DRAW PHASE (The Graphics) ---
        BeginDrawing();
            ClearBackground(BLACK);
            
            // NEON MODE: Additive Blending makes overlapping colors glow bright
            BeginBlendMode(BLEND_ADDITIVE);

            // Draw Particles
            for (int i = 0; i < MAX_PARTICLES; i++) {
                if (particles[i].active) {
                    DrawCircleV(particles[i].pos, 3.0f, Fade(particles[i].color, particles[i].life));
                }
            }

            // Draw Bullets
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active) DrawCircleV(bullets[i].pos, 4.0f, bullets[i].color);
            }

            // Draw Enemies (Rotating Squares)
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (enemies[i].active) {
                    Rectangle rec = { enemies[i].pos.x, enemies[i].pos.y, 30, 30 };
                    DrawRectanglePro(rec, (Vector2){15,15}, enemies[i].rotation, enemies[i].color);
                }
            }

            // Draw Player (Triangle)
            Vector2 v1 = { player.pos.x + cosf(player.rotation*DEG2RAD)*20, player.pos.y + sinf(player.rotation*DEG2RAD)*20 };
            Vector2 v2 = { player.pos.x + cosf((player.rotation+140)*DEG2RAD)*15, player.pos.y + sinf((player.rotation+140)*DEG2RAD)*15 };
            Vector2 v3 = { player.pos.x + cosf((player.rotation-140)*DEG2RAD)*15, player.pos.y + sinf((player.rotation-140)*DEG2RAD)*15 };
            DrawTriangleLines(v1, v2, v3, player.color);

            EndBlendMode();

            DrawFPS(10, 10);
            DrawText("WASD to Move | Mouse to Aim | Click to Shoot", 10, 40, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
