
#define GL_SILENCE_DEPRECATION
#include "GLFW/glfw3.h"
#include <math.h>

//--初期化—------------------------------------------------------------------
void myinit(GLFWwindow** window)
{
    glfwInit();
    *window = glfwCreateWindow(600, 600, "surface", NULL, NULL); // 600*600の大きさで surface という名前のウィンドウをつくる
    glfwMakeContextCurrent(*window);
    glClearColor(0, 0, 0, 1); // 背景色の設定
}

//--描画内容--------------------------------------------------------------------
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5f, 0.5f);
        glVertex2f( 0.5f, 0.5f);
        glVertex2f( 0.5f,-0.5f);
        glVertex2f(-0.5f,-0.5f);
    glEnd();
}

//--メイン関数------------------------------------------------------------------
int main(void)
{
    //初期化処理 (ウィンドウサイズや表示位置、タイトル、背景色、...を決める)
    GLFWwindow* window; // ウィンドウの変数をつくる
    myinit(&window); // ウィンドウのポインタを渡して初期化
    
    //イベント処理ループ
    //--------------------------------------------------------
    do{
        display();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }while( !glfwWindowShouldClose(window) );//ウィンドウが表示されるかぎりループする

   glfwTerminate();

    return 0;
}

