#pragma once
#pragma once

#include <windows.h>
#include <GLFW/glfw3.h>

using namespace System::Windows::Forms;

namespace OpenGLForm
{
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

            cp->X = 0;
            cp->Y = 0;
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

        virtual System::Void Render(System::Void)
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
            

            glBegin(GL_TRIANGLES);


            glVertex2f(0.0f, 0.0f);
            glVertex2f(1, 1);
            glVertex2f(1, 0);
            glEnd();										
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
            //glClearDepth(1.0f);								
            //glEnable(GL_DEPTH_TEST);						
            //glDepthFunc(GL_LEQUAL);							
            //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
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

            // Calculate The Aspect Ratio Of The Window
            //gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

            glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
            glLoadIdentity();									// Reset The Modelview Matrix
        }
    };
}