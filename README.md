# Bounding-Box-Collision-OpenGL
**Check Collision using Simple Bounding Box Algorithm**

Requirement

Install OpenGL Packages (Ubuntu)

        #GLFW
        $sudo apt-get install libglfw3
        $sudo apt-get install libglfw3-dev

        #GLEW
        $sudo apt-get install libglew-dev
        $sudo apt-get install libglew2.0
        $sudo apt-get install libglewmx-dev
        $sudo apt-get install libglewmx1.13  

        #GLU
        $sudo apt-get install libglu1-mesa
        $sudo apt-get install libglu1-mesa-dev

        #GLM
        $sudo apt-get install libglm-dev

Run Program
     
        g++ Game.cpp -fms-extensions -I/usr/include/libdrm -lglfw -lGLEW -lGLU -lGL -o main; ./main
