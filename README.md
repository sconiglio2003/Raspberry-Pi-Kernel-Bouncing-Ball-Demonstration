# Raspberry-Pi-Kernel-Bouncing-Ball-Demonstration
Fully working Raspberry Pi 3B+ bootable image. 
Created using the circle project. 
How to Use these Files
  This bootable image should only work on raspberry pi 3B+ I would not try it on other hardware it has not been tested by me. 
  Format an SD card as Fat32. 
  Ensure the partition is 32GB or less before you format it. 
  Load all the files from this project onto the SD card. 
  Plug in the raspberry pi to power
  plug in the hdmi display to the raspberry pi 
  
  
Purpose: 
  I pulled together working examples from the circle project and made this working bouncing ball program - namely, the HDMI library 
  and the circle drawing commands are what took so long to get working. 
  This project is what I use to ensure my toolchain is set up properly. I'm new to the make system and toolchains - the circle project       also has tons of macros. One small mistake kills the build process. The bouncing ball demo is known to work. If I ever have questions     of whether or not the circle project make settings are configured correctly, I just build this bouncing ball demo. If it works, then       my toolchains and other configurations are working just fine. Works on a 1024 x 600 HDMI display. 
  
Description: 
  The program draws 10,000 balls of random sizes at random locations in the screen. 
  Utilizes a ball class that I wrote from memory - we wrote this many times in college for practice, though never in C++. The ball class     seperates definition and implementation into Ball.h and Ball.cpp for best practices.     This avoids compilation errors - if the line     #include 'ball.h' was in multiple files it would lead to multiple definitions of ball 
    class which is generally super annoying. 
  Works on HDMI screen. 
  The balls will never have a velocity of 0 - custom logic implemented
  The balls receive random velocities 
  Utilized bit shifting to ensure the random number (which is a set number of bits) is a small enough value that the range is acceptable. 
  

