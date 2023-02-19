#pragma once

#include <windows.h>
#include <GLFW/glfw3.h>
#include <vector>

using namespace System::Windows::Forms;

namespace OpenGLForm
{
    ref class GLsetting {

    };

    public ref class COpenGl :
        public System::Windows::Forms::NativeWindow
    {
    private:
        HDC m_hDC;
        HGLRC m_hglrc;
    public:
        COpenGl(System::Windows::Forms::Form^ parentForm,
            GLsizei iWidth, GLsizei iHeight)
        {
            CreateParams^ cp = gcnew CreateParams;

            cp->X = 5;
            cp->Y = 5;
            cp->Height = iHeight;
            cp->Width = iWidth;

            cp->Parent = parentForm->Handle;

            cp->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

            this->CreateHandle(cp);

            m_hDC = GetDC((HWND)this->Handle.ToPointer());

            if (m_hDC)
            {
                MySetPixelFormat(m_hDC);
                ReSizeGLScene(iWidth, iHeight);
                InitGL();
            }
                
        }

        virtual System::Void Render(std::vector<std::pair<float, float>> vertexes,
            GLenum mode, System::Object settings)
        {
            glPointSize(5);
            glBegin(mode);
            for (size_t i = 0; i < vertexes.size(); i++)
            {
                glVertex2f(vertexes[i].first, vertexes[i].second);
            }
            glEnd();
        }

        virtual System::Void RenderInit(System::Void)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.17, 0.17, 0.17, 1);
        }

        System::Void SwapOpenGLBuffers(System::Void)
        {
            SwapBuffers(m_hDC);
        }

    protected:
        ~COpenGl(System::Void)
        {
            this->DestroyHandle();
        }

        GLint MySetPixelFormat(HDC hdc)
        {
            PIXELFORMATDESCRIPTOR pfd = {
                sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd 
                1,                                // version number 
                PFD_DRAW_TO_WINDOW |              // support window 
                PFD_SUPPORT_OPENGL |              // support OpenGL 
                PFD_DOUBLEBUFFER,                 // double buffered 
                PFD_TYPE_RGBA,                    // RGBA type 
                16,                               // 24-bit color depth 
                0, 0, 0, 0, 0, 0,                 // color bits ignored 
                0,                                // no alpha buffer 
                0,                                // shift bit ignored 
                0,                                // no accumulation buffer 
                0, 0, 0, 0,                       // accum bits ignored 
                16,                               // 32-bit z-buffer     
                0,                                // no stencil buffer 
                0,                                // no auxiliary buffer 
                PFD_MAIN_PLANE,                   // main layer 
                0,                                // reserved 
                0, 0, 0                           // layer masks ignored 
            };

            GLint  iPixelFormat;

            if ((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
            {
                MessageBox::Show("ChoosePixelFormat Failed");
                return 0;
            }

            if (SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
            {
                MessageBox::Show("SetPixelFormat Failed");
                return 0;
            }

            if ((m_hglrc = wglCreateContext(m_hDC)) == NULL)
            {
                MessageBox::Show("wglCreateContext Failed");
                return 0;
            }

            if ((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
            {
                MessageBox::Show("wglMakeCurrent Failed");
                return 0;
            }

            return 1;
        }

        bool InitGL(GLvoid)									
        {
            glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			
            return TRUE;									
        }
        GLvoid ReSizeGLScene(GLsizei width, GLsizei height)	
        {
            if (height == 0)								
            {
                height = 1;									
            }

            glViewport(0, 0, width, height);				

            glMatrixMode(GL_PROJECTION);					
            glLoadIdentity();								


            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();		
        }
    };
}