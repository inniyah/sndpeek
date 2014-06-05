#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/gl.h>
#include <FL/glu.h>
#include <FL/glut.H>
#include <cstdlib>
#include <cstdio>
#include <cstring>

class MainGLWwindow : public Fl_Gl_Window {
public:
	MainGLWwindow(int x,int y, int w,int h, const char*l = 0) : Fl_Gl_Window(x,y,w,h,l) {
	}

private:
	void draw();
	int handle(int event);
	void resize(int X,int Y,int W,int H);

	int x, y;
	int cx, cy;

};

void MainGLWwindow::draw() {
	if (!valid()) { // valid() is magic set after first draw() call.
		valid(1);
		glLoadIdentity();
		glViewport(0,0,w(),h());
		ortho();
	}

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
		glColor3d(1,0,0);
		glVertex3f(10,10,0);
		glColor3d(0,1,0);
		glVertex3f(w()-10,10,0);
		glColor3d(0,0,1);
		glVertex3f(w()-10,h()-10,0);
		glColor3d(1,1,0);
		glVertex3f(10,h()-10,0);
	glEnd();
}


void MainGLWwindow::resize(int X,int Y,int W,int H) {
	Fl_Gl_Window::resize(X,Y,W,H);
	glLoadIdentity();
	glViewport(0,0,W,H);
	glOrtho(-W,W,-H,H,-1,1);
	redraw();
}


int MainGLWwindow::handle(int event) {
	switch(event) {
		case FL_PUSH:
			printf("FL_PUSH\n");
			// mouse down pos in Fl::event_x() and Fl::event_y()
			x = Fl::event_x();
			y = Fl::event_y();
			printf("  x=%d, y=%d\n", x, y);
			return 1;
		case FL_DRAG:
			printf("FL_DRAG\n");
			cx = Fl::event_x();
			cy = Fl::event_y();
			printf("  cx=%d, cy=%d\n", cx, cy);
			return 1;
		case FL_RELEASE:
			printf("FL_RELEASE\n");
			return 1;
		case FL_FOCUS:
			printf("FL_FOCUS\n");
			return 1;			 // return 1 to get keyboard events
		case FL_UNFOCUS:
			printf("FL_UNFOCUS\n");
			return 1;			 // Return 1 to get keyboard events
		case FL_KEYBOARD:
			printf("FL_KEYBOARD\n");
			// key in Fl::event_key(), ascii in Fl::event_text()
			printf("Key: %s\n", Fl::event_text());
			return 0;			 // return 1 input was understood
		case FL_SHORTCUT:
			printf("FL_SHORTCUT\n");
			// key in Fl::event_key(), ascii in Fl::event_text()
			return 0;			 // return 1 input was understood
		default:
			return Fl_Gl_Window::handle(event);
	}
}


int main(int argc,char* argv[]) {
	Fl_Window win(500,500, "FLTK OpenGL Test");
	MainGLWwindow window(10,10,win.w()-20,win.h()-20);
	win.end();
	win.resizable(window);
	win.show(argc,argv);
	return Fl::run();
}
