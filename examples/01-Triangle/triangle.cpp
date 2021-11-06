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

void RenderScene(void)
{

    //1.���һ������һ���ض��Ļ�����
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
    GLfloat vRed[] = { 1.0,0.0,0.0,1.0f };

    //���ݵ��洢��ɫ������GLT_SHADER_IDENTITY��ɫ���������ɫ��ֻ��ʹ��ָ����ɫ��Ĭ�ϵѿ������������Ļ����Ⱦ����ͼ��
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);

    //�ύ��ɫ��
    triangleBatch.Draw();

    //�ڿ�ʼ������openGL ���ڵ�ʱ������ָ��Ҫһ��˫����������Ⱦ�����������ζ�Ž��ں�̨������������Ⱦ����Ⱦ�����󽻻���ǰ̨�����ַ�ʽ���Է�ֹ�۲��߿������ܰ����Ŷ���֡�붯��֮֡�����˸����Ⱦ���̡�����������ƽ̨����ƽ̨�ض��ķ�ʽ���С�
    //����̨������������Ⱦ��Ȼ������󽻻���ǰ̨
    glutSwapBuffers();

}

void setupRC()
{
    //����������ɫ��������ɫ��
    glClearColor(0.98f, 0.40f, 0.7f, 1);


    //û����ɫ������OpenGL ���Ŀ�������޷������κ���Ⱦ�ġ���ʼ��һ����Ⱦ��������
    //��ǰ��Ŀγ̣����ǻ���ù̹�����Ⱦ�������ѧ����OpenGL��ɫ������д��ɫ��
    shaderManager.InitializeStockShaders();


    //ָ������
    //��OpenGL�У���������һ�ֻ�����3DͼԪ��ͼԭ�ء�
    GLfloat vVerts[] = {
        -0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f
    };

    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
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
