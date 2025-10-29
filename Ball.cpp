#include "Ball.h"

Ball::Ball() 
{
    x = 0; 
    y = 0; 
    xvel = 50; 
    yvel = 50; 
    width = 1024; 
    height = 600; 
    size = 10; 
}
void Ball::Update() {
    x+=xvel; 
    y+=yvel; 

    if (x > width) {
        xvel*= -1; 
    }
    // ball bounces off bottom 
    if (y > height) {
        yvel *= -1; 
    }
    // ball bounces off left
    if (x < 0) {
        xvel *= -1; 
    } 
    // ball bounces off top
    if (y < 0) {
        yvel *= -1; 
    }
}
