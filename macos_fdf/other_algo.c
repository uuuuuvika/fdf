#include "fdf.h"

int ipart(float x) {
    return (int)floor(x);
}
float fpart(float x) {
    return x - ipart(x);
}

float rfpart(float x) {
    return 1 - fpart(x);
}

float lerp(float start, float end, float t) {
    return start + t * (end - start);
}
// Function to plot the pixel at (x, y) with a color gradient
void plot(t_img *img, int x, int y, t_color *color)
{
    img_pix_put(img, y, x, (color->r << 16) | (color->g << 8) | color->b);
    printf("Plotting pixel at (%d, %d) with color (%d, %d, %d)\n", x, y, color->r, color->g, color->b);
}

// Function to draw a line with a color gradient from color1 to color2
void drawLine(t_img *img, int x0, int y0, int x1, int y1, t_color color1, t_color color2)
{
    int steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep)
    {
          int temp = x0;
        x0 = y0;
        y0 = temp;

        temp = x1;
        x1 = y1;
        y1 = temp;
    }

    if (x0 > x1)
    {
         int temp = x0;
        x0 = x1;
        x1 = temp;

        temp = y0;
        y0 = y1;
        y1 = temp;

        // Swap colors if needed
        // const t_color tempColor = color1;
        // color1 = color2;
        // color2 = tempColor;
    }

    int dx = x1 - x0, dy = y1 - y0;
    //float gradient = (dx == 0) ? 1.0 : (float)dy / dx;

    // // Handle first endpoint
    // int xend = round(x0);
    // float yend = y0 + gradient * (xend - x0);
    // float xgap = rfpart(x0 + 0.5);
    // int xpxl1 = xend, ypxl1 = ipart(yend);
    // plotHelper(ypxl1, xpxl1, rfpart(yend) * xgap);
    // plotHelper(ypxl1 + 1, xpxl1, fpart(yend) * xgap);

    // float intery = yend + gradient; // First y-intersection for the main loop

    // // Handle second endpoint
    // xend = round(x1);
    // yend = y1 + gradient * (xend - x1);
    // xgap = fpart(x1 + 0.5);
    // int xpxl2 = xend, ypxl2 = ipart(yend);
    // plotHelper(ypxl2, xpxl2, rfpart(yend) * xgap);
    // plotHelper(ypxl2 + 1, xpxl2, fpart(yend) * xgap);

    // Main loop
    // for (int x = xpxl1 + 1; x < xpxl2; x++)
    // {
    //     plotHelper(ipart(intery), x, rfpart(intery), color1, color2, img, steep);
    //     plotHelper(ipart(intery) + 1, x, fpart(intery), color1, color2, img, steep);
    //     intery += gradient;
    // }
      for (int x = x0; x <= x1; x++) {
        float t = (x - x0) / (float)dx;
        int y = y0 + t * dy;

        float brightness = rfpart(t);
        t_color interpolatedColor;
        interpolatedColor.r = lerp(color1.r, color2.r, brightness);
        interpolatedColor.g = lerp(color1.g, color2.g, brightness);
        interpolatedColor.b = lerp(color1.b, color2.b, brightness);

        plot(img, steep ? y : x, steep ? x : y, &interpolatedColor);
    }
}
