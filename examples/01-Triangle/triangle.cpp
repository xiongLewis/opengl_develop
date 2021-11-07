// opengl-1.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
//#include <glad/glad.h> 
//#include <GLFW/glfw3.h>

#include "GLShaderManager.h"
#include <GLTools.h>
#include <GL/glut.h>

//����һ������ɫ������
GLShaderManager shaderManager;

/*
 ��Mac ϵͳ�£�`#include<glut/glut.h>`
 ��Windows �� Linux�ϣ�����ʹ��freeglut�ľ�̬��汾������Ҫ���һ����
*/

//�򵥵�������������GLTools��һ���򵥵������ࡣ
GLBatch triangleBatch;

//�߳�/2
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
 �ڴ��ڴ�С�ı�ʱ�������µĿ��&�߶ȡ�
 */
void changeSize(int w, int h)
{
    /*
      x,y ��������������ͼ�����½����꣬����ȡ��߶�������Ϊ��ʾ��ͨ��x,y ����Ϊ0
     */
    glViewport(0, 0, w, h);

}

//��Ⱦ��GPU����ִ�еĵط�
void RenderScene(void)
{

    //1.ִ�������ɫ��������ʹ�õ���glClearColor���õ���ɫ�����������һ������һ���ض��Ļ�����
    /*
     ��������һ�����ͼ����Ϣ�Ĵ���ռ䣬��ɫ����ɫ����ɫ��alpha����ͨ��һ�����ͨ��һ����Ϊ��ɫ�����������ػ��������á�
     OpenGL �в�ֹһ�ֻ���������ɫ����������Ȼ�������ģ�建������
      �������������ֵ����Ԥ��
     ������ָ����Ҫ����Ļ����
     GL_COLOR_BUFFER_BIT :ָʾ��ǰ���������������ɫд�뻺����
     GL_DEPTH_BUFFER_BIT :ָʾ��Ȼ�����
     GL_STENCIL_BUFFER_BIT:ָʾģ�建����
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


    //2.����һ�鸡��������ʾ��ɫ
    GLfloat vGreen[] = { 0.0,1.0,0.0,1.0f };

    //���ݵ��洢��ɫ������GLT_SHADER_IDENTITY��ɫ������Ԫ��ɫ�����������ɫ��ֻ��ʹ��ָ����ɫ��Ĭ�ϵѿ������������Ļ����Ⱦ����ͼ��
    //shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vGreen);
    
    // x y z w(��������1.0)
    M3DMatrix44f mTransformMatrix, mFinalTransform, mRotationMatix;
    
    //ƽ��
    m3dTranslationMatrix44(mTransformMatrix,xPos, yPos, 0.0f );

    static float ZRot = 0.0f;
    

    m3dRotationMatrix44(mRotationMatix, m3dDegToRad(ZRot), 0.0f, 0.0f, 1.0f);

    //�������
    m3dMatrixMultiply44(mFinalTransform, mTransformMatrix, mRotationMatix);
    ZRot += 5.0f;

    //ƽ����ɫ��
    shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vGreen);

    //�ύ��ɫ��
    triangleBatch.Draw();

    //�ڿ�ʼ������openGL ���ڵ�ʱ������ָ��Ҫһ��˫����������Ⱦ�����������ζ�Ž��ں�̨������������Ⱦ����Ⱦ�����󽻻���ǰ̨�����ַ�ʽ���Է�ֹ�۲��߿������ܰ����Ŷ���֡�붯��֮֡�����˸����Ⱦ���̡�����������ƽ̨����ƽ̨�ض��ķ�ʽ���С�
    //����̨������������Ⱦ��Ȼ������󽻻���ǰ̨
    glutSwapBuffers();

}

void SpeacialKeys(int key, int x, int y)
{
    //�ƶ������Σ�������
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

    //�߽���
    if (xPos < -1.0f + blockSize)
        xPos = -1.0f + blockSize;

    if (xPos > 1.0f - blockSize)
        xPos = 1.0f - blockSize;

    if (yPos < -1.0f + blockSize)
        yPos = -1.0f + blockSize;

    if (yPos > 1.0f - blockSize)
        yPos = 1.0f - blockSize;

    //ִ����������glutDisplayFunc(RenderScene);����ص����ᱻ���ã���ִ����Ⱦ����
    glutPostRedisplay();

#if 0
    //�ƶ������Σ�����һ
    GLfloat stepSize = 0.025f;
    //D��
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

    //�����߽��ж�
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

    //���������Ķ���λ��
    // A��
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;

    // B��
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;

    // C��
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;

    // D��
    vVerts[9] = blockX;
    vVerts[10] = blockY;

    triangleBatch.CopyVertexData3f(vVerts);

    //ִ����������glutDisplayFunc(RenderScene);����ص����ᱻ���ã���ִ����Ⱦ����
    glutPostRedisplay();
#endif
}

//��������
void setupRC()
{
    //����������ɫ��������ɫ��������ɫ���õ���ɫ��������û������ִ��
    glClearColor(0.98f, 0.40f, 0.7f, 1);


    //û����ɫ������OpenGL ���Ŀ�������޷������κ���Ⱦ�ġ���ʼ��һ����Ⱦ��������
    //��ǰ��Ŀγ̣����ǻ���ù̹�����Ⱦ�������ѧ����OpenGL��ɫ������д��ɫ��
    shaderManager.InitializeStockShaders();


    ////ָ������ x y z
    ////��OpenGL�У���������һ�ֻ�����3DͼԪ��ͼԭ�ء�
    //GLfloat vVerts[] = {
    //    -0.5f,0.0f,0.0f,
    //    0.5f,0.0f,0.0f,
    //    0.5f,0.5f,0.0f,
    //    -0.5f,0.5f,0.0f
    //};

    //�ò�ͬ��ģʽ����ͼ primitive:������ģʽ    nVerts:�������
    triangleBatch.Begin(GL_POLYGON, 4);
    //�������εĶ��㿽����ȥ
    triangleBatch.CopyVertexData3f(vVerts);
    //����
    triangleBatch.End();

}

int main(int argc, char* argv[])
{
    //���õ�ǰ����Ŀ¼�����MAC OS X
    /*
     `GLTools`����`glSetWorkingDrectory`�������õ�ǰ����Ŀ¼��ʵ������Windows���ǲ���Ҫ�ģ���Ϊ����Ŀ¼Ĭ�Ͼ���������ִ��ִ�г�����ͬ��Ŀ¼��������Mac OS X�У�������򽫵�ǰ�����ļ��и�ΪӦ�ó���������е�`/Resource`�ļ��С�`GLUT`�������趨�Զ���������������ã����������з������Ӱ�ȫ��
     */
    gltSetWorkingDirectory(argv[0]);


    //��ʼ��GLUT��,�������ֻ�Ǵ�˵����������ҳ�ʼ��glut��
    glutInit(&argc, argv);

    /*
     ��ʼ��˫���崰�ڣ����б�־GLUT_DOUBLE��GLUT_RGBA��GLUT_DEPTH��GLUT_STENCIL�ֱ�ָ
     ˫���崰�ڡ�RGBA��ɫģʽ����Ȳ��ԡ�ģ�建����

     --GLUT_DOUBLE`��˫���洰�ڣ���ָ��ͼ����ʵ����������������ִ�еģ�Ȼ��Ѹ��ת���ɴ�����ͼ�����ַ�ʽ�������������ɶ���Ч����
     --GLUT_DEPTH`����־��һ����Ȼ���������Ϊ��ʾ��һ���֣���������ܹ�ִ����Ȳ��ԣ�
     --GLUT_STENCIL`��ȷ������Ҳ����һ�����õ�ģ�建������
     ��ȡ�ģ����Ժ����ϸ�½���
     */
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);

    //GLUT���ڴ�С�����ڱ���
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");

    /*
     GLUT �ڲ�����һ��������Ϣѭ���������ʵ�����Ϣ��Ȼ��������ǲ�ͬʱ��ע��Ļص�����������һ��ע��2���ص�������
     1��Ϊ���ڸı��С�����õ�һ���ص�����
     2������OpenGL ��Ⱦ�Ļص�����
     */
     //ע�����ܺ���
    glutReshapeFunc(changeSize);
    //ע����ʾ����
    glutDisplayFunc(RenderScene);

    glutSpecialFunc(SpeacialKeys);
    /*
     ��ʼ��һ��GLEW��,ȷ��OpenGL API�Գ�����ȫ���á�
     ����ͼ���κ���Ⱦ֮ǰ��Ҫ���ȷ����������ĳ�ʼ��������û���κ�����
     */
    GLenum status = glewInit();
    if (GLEW_OK != status) {

        printf("GLEW Error:%s\n", glewGetErrorString(status));
        return 1;

    }

    //�������ǵ���Ⱦ����
    setupRC();

    glutMainLoop();




    return  0;

}
// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
