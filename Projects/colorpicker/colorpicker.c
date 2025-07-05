#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Vector4 RGBToCMYK(Vector3 rgb) {
    float k = fmin(1-rgb.x,fmin(1-rgb.y,1-rgb.z));
    if (k == 1.0) return (Vector4) {0,0,0,1.0};
    float c = (1.0-rgb.x-k)/(1.0-k);
    float m = (1.0-rgb.y-k)/(1.0-k);
    float y = (1.0-rgb.z-k)/(1.0-k);
    return (Vector4) {c,m,y,k};
}

Vector3 RGBFromCMYK(Vector4 cmyk) {
    float r = (1.0 - cmyk.x) * (1.0 - cmyk.w);
    float g = (1.0 - cmyk.y) * (1.0 - cmyk.w);
    float b = (1.0 - cmyk.z) * (1.0 - cmyk.w);
    return (Vector3){r,g,b};
}

Vector3 ColorToRGB(Color color) {
    return (Vector3) {color.r/255.0,color.g/255.0,color.b/255.0};
}

Color ColorFromRGB(Vector3 rgb) {
    return ColorFromNormalized((Vector4){rgb.x,rgb.y,rgb.z,1.0});
}

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 450;
    const int gap = 100;
    const int slider_h = 20;
    const int slider_w = 200;

    const char* formatString = "HEX: #%02X%02X%02X\nR: %.0f\nG: %.0f\nB: %.0f\n\nC: %.0f\nM: %.0f\nY: %.0f\nK: %.0f\n\nH: %.1f°\nS: %.1f%%\nV: %.1f%%";

    InitWindow(screenWidth, screenHeight, "Color picker");

    SetTargetFPS(60);

    Vector3 hsv = {0, 0, 0}; // 0-360, 0-1, 0-1
    Vector3 rgb = {0, 0, 0}; // Normalized
    Vector4 cmyk = {1.0, 1.0, 1.0, 1.0}; // Normalized

    Color new = BLACK;

    while (!WindowShouldClose())
    {
        Vector3 oldhsv = hsv;
        Vector3 oldrgb = rgb;
        Vector4 oldcmyk = cmyk;

        BeginDrawing();

            ClearBackground(RAYWHITE);

            GuiSlider((Rectangle){gap,260+gap+slider_h*0,slider_w,slider_h}, "Hue | 0", "360°", &hsv.x, 0.0, 360.0);
            GuiSlider((Rectangle){gap,260+gap+slider_h*1,slider_w,slider_h}, "Saturation | 0", "1", &hsv.y, 0.0, 1.0);
            GuiSlider((Rectangle){gap,260+gap+slider_h*2,slider_w,slider_h}, "Value | 0", "1", &hsv.z, 0.0, 1.0);

            GuiSlider((Rectangle){gap*2+slider_w,260+gap+slider_h*0,slider_w,slider_h}, "Red | 0", "255", &rgb.x, 0.0, 1.0);
            GuiSlider((Rectangle){gap*2+slider_w,260+gap+slider_h*1,slider_w,slider_h}, "Green | 0", "255", &rgb.y, 0.0, 1.0);
            GuiSlider((Rectangle){gap*2+slider_w,260+gap+slider_h*2,slider_w,slider_h}, "Blue | 0", "255", &rgb.z, 0.0, 1.0);

            GuiSlider((Rectangle){gap*3+slider_w*2,260+gap+slider_h*-1,slider_w,slider_h}, "Cyan | 0", "100", &cmyk.x, 0.0, 1.0);
            GuiSlider((Rectangle){gap*3+slider_w*2,260+gap+slider_h*0,slider_w,slider_h}, "Magenta | 0", "100", &cmyk.y, 0.0, 1.0);
            GuiSlider((Rectangle){gap*3+slider_w*2,260+gap+slider_h*1,slider_w,slider_h}, "Yellow | 0", "100", &cmyk.z, 0.0, 1.0);
            GuiSlider((Rectangle){gap*3+slider_w*2,260+gap+slider_h*2,slider_w,slider_h}, "Black | 0", "100", &cmyk.w, 0.0, 1.0);
            
            DrawRectangle(10, 10, 320, 320, new);
            SetTextLineSpacing(24);
            DrawText(TextFormat(formatString, /*HEX*/(int)(rgb.x*255),(int)(rgb.y*255),(int)(rgb.z*255),/*RGB*/rgb.x*255,rgb.y*255,rgb.z*255,/*CMYK*/cmyk.x*100,cmyk.y*100,cmyk.z*100,cmyk.w*100, hsv.x, hsv.y*100, hsv.z*100), 400, 15, 20, BLACK);

        EndDrawing();

        if (!Vector3Equals(oldhsv, hsv)) {
            new = ColorFromHSV(hsv.x, hsv.y, hsv.z);
            rgb = ColorToRGB(new);
            cmyk = RGBToCMYK(rgb);
        }
        else if (!Vector3Equals(oldrgb, rgb)) {
            new = ColorFromRGB(rgb);
            hsv = ColorToHSV(new);
            cmyk = RGBToCMYK(rgb);
        } 
        else if (!QuaternionEquals(oldcmyk, cmyk)) {
            new = ColorFromRGB(RGBFromCMYK(cmyk));
            hsv = ColorToHSV(new);
            rgb = RGBFromCMYK(cmyk);
        }
    }
    
    CloseWindow();

    return 0;
}