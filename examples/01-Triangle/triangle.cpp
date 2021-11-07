// opengl-1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include <glad/glad.h> 
//#include <GLFW/glfw3.h>

#include "GLShaderManager.h"
#include <GLTools.h>
#include <GL/glut.h>

//定义一个，着色管理器
GLShaderManager shaderManager;

/*
 在Mac 系统下，`#include<glut/glut.h>`
 在Windows 和 Linux上，我们使用freeglut的静态库版本并且需要添加一个宏
*/

//简单的批次容器，是GLTools的一个简单的容器类。
GLBatch triangleBatch;

//边长/2
GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {
    -blockSize, -blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    blockSize, blockSize, 0.0f,
    -blockSize, blockSize, 0.0f
};

GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;

/*
 在窗口大小改变时，接收新的宽度&高度。
 */
void changeSize(int w, int h)
{
    /*
      x,y 参数代表窗口中视图的左下角坐标，而宽度、高度是像素为表示，通常x,y 都是为0
     */
    glViewport(0, 0, w, h);

}

//渲染，GPU真正执行的地方
void RenderScene(void)
{

    //1.执行清空颜色缓存区，使用的是glClearColor设置的颜色缓存区，清除一个或者一组特定的缓存区
    /*
     缓冲区是一块存在图像信息的储存空间，红色、绿色、蓝色和alpha分量通常一起分量通常一起作为颜色缓存区或像素缓存区引用。
     OpenGL 中不止一种缓冲区（颜色缓存区、深度缓存区和模板缓存区）
      清除缓存区对数值进行预置
     参数：指定将要清除的缓存的
     GL_COLOR_BUFFER_BIT :指示当前激活的用来进行颜色写入缓冲区
     GL_DEPTH_BUFFER_BIT :指示深度缓存区
     GL_STENCIL_BUFFER_BIT:指示模板缓冲区
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    //2.设置一组浮点数来表示绿色
    GLfloat vGreen[] = { 0.0,1.0,0.0,1.0f };

    //传递到存储着色器，即GLT_SHADER_IDENTITY着色器（单元着色器），这个着色器只是使用指定颜色以默认笛卡尔坐标第在屏幕上渲染几何图形
    //shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
    
    // x y z w(缩放因子1.0)
    M3DMatrix44f mTransformMatrix, mFinalTransform, mRotationMatix;
    
    //平移
    m3dTranslationMatrix44(mTransformMatrix,xPos, yPos, 0.0f );

    static float ZRot = 0.0f;
    

    m3dRotationMatrix44(mRotationMatix, m3dDegToRad(ZRot), 0.0f, 0.0f, 1.0f);

    //矩阵相乘
    m3dMatrixMultiply44(mFinalTransform, mTransformMatrix, mRotationMatix);
    ZRot += 5.0f;

    //平面着色器
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vGreen);

    //提交着色器
    triangleBatch.Draw();

    //在开始的设置openGL 窗口的时候，我们指定要一个双缓冲区的渲染环境。这就意味着将在后台缓冲区进行渲染，渲染结束后交换给前台。这种方式可以防止观察者看到可能伴随着动画帧与动画帧之间的闪烁的渲染过程。缓冲区交换平台将以平台特定的方式进行。
    //将后台缓冲区进行渲染，然后结束后交换给前台
    glutSwapBuffers();

}

void SpeacialKeys(int key, int x, int y)
{
    //移动正方形，方法二
    GLfloat stepSize = 0.025f;
    if (key == GLUT_KEY_UP) {
        yPos += stepSize;
    }

    if (key == GLUT_KEY_DOWN) {
        yPos -= stepSize;
    }

    if (key == GLUT_KEY_LEFT) {
        xPos -= stepSize;
    }

    if (key == GLUT_KEY_RIGHT) {
        xPos += stepSize;
    }

    //边界检测
    if (xPos < -1.0f + blockSize)
        xPos = -1.0f + blockSize;

    if (xPos > 1.0f - blockSize)
        xPos = 1.0f - blockSize;

    if (yPos < -1.0f + blockSize)
        yPos = -1.0f + blockSize;

    if (yPos > 1.0f - blockSize)
        yPos = 1.0f - blockSize;

    //执行下面语句后，glutDisplayFunc(RenderScene);这个回调将会被调用，即执行渲染动作
    glutPostRedisplay();

#if 0
    //移动正方形，方法一
    GLfloat stepSize = 0.025f;
    //D点
    GLfloat blockX = vVerts[9];
    GLfloat blockY = vVerts[10];

    if (key == GLUT_KEY_UP) {
        blockY += stepSize;
    }

    if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }

    if (key == GLUT_KEY_LEFT) {
        blockX -= stepSize;
    }

    if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }

    //超出边界判断
    if (blockX < -1.0f) {
        blockX = -1.0f;
    }

    if (blockX > 1.0f - blockSize * 2) {
        blockX = 1.0f - blockSize * 2;
    }

    if (blockY > 1.0f) {
        blockY = 1.0f;
    }

    if (blockY < -1.0f + blockSize * 2) {
        blockY = -1.0f + blockSize * 2;
    }

    //更新其他的定点位置
    // A点
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;

    // B点
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;

    // C点
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;

    // D点
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    triangleBatch.CopyVertexData3f(vVerts);

    //执行下面语句后，glutDisplayFunc(RenderScene);这个回调将会被调用，即执行渲染动作
    glutPostRedisplay();
#endif
}

//顶点设置
void setupRC()
{
    //设置清屏颜色（背景颜色），把颜色设置到颜色缓存区，没有真正执行
    glClearColor(0.98f, 0.40f, 0.7f, 1);


    //没有着色器，在OpenGL 核心框架中是无法进行任何渲染的。初始化一个渲染管理器。
    //在前面的课程，我们会采用固管线渲染，后面会学着用OpenGL着色语言来写着色器
    shaderManager.InitializeStockShaders();


    ////指定顶点 x y z
    ////在OpenGL中，三角形是一种基本的3D图元绘图原素。
    //GLfloat vVerts[] = {
    //    -0.5f,0.0f,0.0f,
    //    0.5f,0.0f,0.0f,
    //    0.5f,0.5f,0.0f,
    //    -0.5f,0.5f,0.0f
    //};

    //用不同的模式来绘图 primitive:三角形模式    nVerts:顶点个数
    triangleBatch.Begin(GL_POLYGON, 4);
    //把三角形的定点拷贝进去
    triangleBatch.CopyVertexData3f(vVerts);
    //结束
    triangleBatch.End();

}

int main(int argc, char* argv[])
{
    //设置当前工作目录，针对MAC OS X
    /*
     `GLTools`函数`glSetWorkingDrectory`用来设置当前工作目录。实际上在Windows中是不必要的，因为工作目录默认就是与程序可执行执行程序相同的目录。但是在Mac OS X中，这个程序将当前工作文件夹改为应用程序捆绑包中的`/Resource`文件夹。`GLUT`的优先设定自动进行了这个中设置，但是这样中方法更加安全。
     */
    gltSetWorkingDirectory(argv[0]);


    //初始化GLUT库,这个函数只是传说命令参数并且初始化glut库
    glutInit(&argc, argv);

    /*
     初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区

     --GLUT_DOUBLE`：双缓存窗口，是指绘图命令实际上是离屏缓存区执行的，然后迅速转换成窗口视图，这种方式，经常用来生成动画效果；
     --GLUT_DEPTH`：标志将一个深度缓存区分配为显示的一部分，因此我们能够执行深度测试；
     --GLUT_STENCIL`：确保我们也会有一个可用的模板缓存区。
     深度、模板测试后面会细致讲到
     */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

    //GLUT窗口大小、窗口标题
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");

    /*
     GLUT 内部运行一个本地消息循环，拦截适当的消息。然后调用我们不同时间注册的回调函数。我们一共注册2个回调函数：
     1）为窗口改变大小而设置的一个回调函数
     2）包含OpenGL 渲染的回调函数
     */
     //注册重塑函数
    glutReshapeFunc(changeSize);
    //注册显示函数
    glutDisplayFunc(RenderScene);

    glutSpecialFunc(SpeacialKeys);
    /*
     初始化一个GLEW库,确保OpenGL API对程序完全可用。
     在试图做任何渲染之前，要检查确定驱动程序的初始化过程中没有任何问题
     */
    GLenum status = glewInit();
    if (GLEW_OK != status) {

        printf("GLEW Error:%s\n", glewGetErrorString(status));
        return 1;

    }

    //设置我们的渲染环境
    setupRC();

    glutMainLoop();




    return  0;

}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
