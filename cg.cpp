/**************************************************************
*iMaze
*A place built in 3D model which just looks like a maze but not a maze, for now ..
*Designed by Chentingpc, 2011-12-20, All rights reserved.
*	1.This demo program uses the 3-dimesion points to construct a space geometirc 
*solid, which concers the buffer usage.
*	2.The position of eyes can be modified by the keyboard so it uses the basic 
*concept of view forming in OpenGL.
*	3.The wall, floor, ground and pillar use the texture so the usage of texture is 
*also concerns.
*	4.The light is added to the model so the usage of the light is also concerns.
*notes:This program use OpenCV to load the jpg texture file..
***************************************************************/

/*************************笔记************************************
1.关于buffer
这基于OpenGL的客户端/服务器模型，用buffer就等于把数据存到服务端，从而加快速度，如果对于
单机，似乎是把数据显示地放到显存中。buffer的初始化和绑定参考下面代码。
关于buffer，有一点必须说明的是，用了buffer之后作几何体就需要用专用的函数了，如下面程序中的
glDrawElements，并且，视图变换、光照等都需要有相应的操作，具体操作参考下面代码。

关于buffer的链接：http://www.programfan.com/club/showtxt.asp?id=275223

2.关于视图
几个重要的概念：
空间模型：OPENGL或计算机图形学中作图不是静态的概念，而是动态的，实现动态的方法就是模型，所谓模型就是空间几何体。空间几何体的确定是通过一些空间的点，空间的点的有序集合就是模型。
视口：模型可以是二维的，也可以是三维的，但计算机显示器是二维的，空间模型必须投影到这个所谓视口的平面中，最后才能被迁移到计算机屏幕上显示出来，视口就是那个物体被投影到的有限平面。
视景体：理解图形学中将动态模型转换显示的形象比喻可以来自于照相机拍照，视景体是指成像景物所在空间的集合，这个空间集合可以是客观的（非透视的投影变换），也可以是主观的（透视变换），人眼是主观的，因为其看到的东西类似于广角镜下拍到的，是透视投影变换得来的。
所以，OPENGL中视图的形成就是将特定视景体中的空间模型进行投影变换到视口上并剪裁后得出。

绘制一个几何图形包括下面几个步骤：
视图变换：gluLookAt为主的变换，用来确定你的照相机（眼睛）放置的位置的
模型变换：gluTranslatef、gluRote等都是模型变换，对原始的几何体本身进行变换
投影变换： glOrtho、glFrustum、gluPerspective等，决定如何将几何体投影到照相机中（透视，还是平视），亦即眼睛能看到的范围和透视效果
视口变换：glViewport为主的变换，最终视窗的大小，不决定剪裁，只是决定在屏幕上显示的大小
绘制：视图变换和模型变换是连在一起的，都是对glMatrixMode (GL_MODELVIEW)亦即模型视图矩阵栈的操作，而与投影变换、视口变换各自相互独立，不过实验表明，视口变换需要在模型确定之前，因此比较理想的顺序是：视口变换确定视口->投影变换确定如何投影->视图变换确定相机位置->模型变换->给出模型

关于视图的链接：http://hi.baidu.com/zhujianzhai/blog/item/24e9c11ec9a91c64f724e43c.html


3.关于光照
光照比较复杂，光照的类型、材质的类型、光线的跟踪（opengl不会自动跟踪光线，识别是否被遮挡，在这个程序中，光线没有被遮挡，所以会出现非物理现象），都有些复杂。
事先说明：
	opengl光照主要是控制不同类型光照的强度和颜色，以及控制物体所反射的不同类型光照的强度与颜色。
	在本程序中，我用在（0,0,0）点的白光照耀（注意：虽然深度测试开启，几何体存在遮挡关系，但光线不被遮挡，OPENGL似乎不具备自动检测能力需要程序员去做），
通过设定不同的材质属性（镜面反射光：红色；散射光：绿色；环境光：蓝色），我们可以很容易理解不同光照类型的具体含义，具体参考图片。
主要光照类型：	
	环境光：与法向量、光源位置无关的均匀强度的光照
	散射光：与法向量、光源位置有关的能被散射的光线
	镜面光：与法向量、光源位置有关的只能被镜面反射的光线
主要材质特性：
	环境反射颜色：对环境光的反色颜色
	散射颜色：对散射光的散射颜色
	镜面颜色：对镜面光的反射颜色
	反色强度：shininess
	材料表面发光：emission

光照的使用：
创建、定位、启用光源：glLightfv() / 创建光源与定位光源的，这个函数的参数比较多，参考红宝书 glEnable() / 启用光源与启用具体的光源
选择光照模型:glLightModel 参考红宝书吧
定义材料属性：glMaterialf /这个函数的参数也比较多，参考红宝书 。材料属性的使用在创建具体几何物体前，从而可以实现不同的几何物体拥有不同的材料
最后，创建几何物体
若用buffer要做相应连接工作，具体参考下面代码。

4.关于贴图
参考“参考代码texbind”，就是把几何与纹理特定点对应起来。
若用buffer要做相应连接工作，具体参考下面代码。

**************************************************************/
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h> 
#include <stdio.h>
#include <math.h>
#include "highgui.h"
#include "cv.h"
  


double lookingat[9];
const double step=0.1;//步长
const double step_angle=0.174;//转角
GLfloat vertices[][3]={
	{0,0,0},{0,0,1},{0,0,2},{0,0,3},{1,0,0},{1,0,1},{1,0,2},{1,0,3},{2,0,0},{2,0,1},{2,0,2},{2,0,3},{3,0,0},{3,0,1},{3,0,2},{3,0,3},
	{0,1,0},{0,1,1},{0,1,2},{0,1,3},{1,1,0},{1,1,1},{1,1,2},{1,1,3},{2,1,0},{2,1,1},{2,1,2},{2,1,4},{3,1,0},{3,1,1},{3,1,2},{3,1,3}
}; 
GLfloat _vertices[72][3];
GLuint indices[][4]={
	{22,26,10,6},{26,25,9,10},{25,21,5,9},{21,22,6,5},//pillar
	{19,31,28,16},//ceiling
	{3,0,12,15},//floor
	{3,15,31,19},{15,12,28,31},//whole wall,inside
	{2,3,19,18},{0,1,17,16},{4,0,16,20},{12,8,24,28}, //part wall,inside
	{19,31,15,3},{28,12,15,31},//whole wall,outside, not used
	{18,19,3,2},{16,17,1,0},{20,16,0,4},{28,24,8,12}//part wall,outside, not used	 
};
GLuint _indices[72];
GLfloat normalv[][3]={
	{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},
	{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0}
};
GLfloat _normalv[72][3]={0};
GLfloat texture[][2]={
	{1,0},{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},{1,0},{0,0},{0,1},{1,1},//pillar
	{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},//ceiling+floor+whole wall
	{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0}//part wall
	//,{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0},{1,1},{0,1},{0,0},{1,0}
};
GLfloat light_position[][4]={
	{0,0,0,1},{0,1,0,0}                                                                            
};
GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 }	;				//材料镜面发射系数
GLfloat mat_diffuse[]={0,1,0,1};
GLfloat mat_shininess[] = { 50.0 };									//镜面反射强度
GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1.0 }	;				
GLfloat qaSpecularLight[] = { 1,1,1,1.0 };				
GLfloat lmodel_ambient[]={0.0,0.0,1.0,1.0};
GLfloat mat_emission[]={0.5,0.5,0.5,1},mat_emission_null[]={0,0,0,0};
bool q=false; 

#define IMAGE_NUM 3
static GLuint texName[IMAGE_NUM];
int image_width[IMAGE_NUM],image_height[IMAGE_NUM];
GLubyte *(image[IMAGE_NUM]);
int image_byte_length[IMAGE_NUM];//可用于析构，此程序中不需要
//GLubyte image_one[677][500][4];
void read_texture_image(int image_num, char*name)//序号与图片name
{
	int i, j, c; 
	//reading in the texture by opencv
	IplImage *texture=cvLoadImage(name); 
	if(!texture)
	{
		printf("read in the texture file failure..");
		exit(-1);
	}
	image_width[image_num]=texture->width;
	image_height[image_num]=texture->height ;
	image_byte_length[image_num]=image_height[image_num]*image_width[image_num]*4;
	image[image_num]=(GLubyte*)new GLubyte[image_byte_length[image_num]];
	for (i=0;i<image_height[image_num];i++){
		for (j=0;j<image_width[image_num];j++){
			CvScalar temp=cvGet2D(texture,i,j);
			image[image_num][i*image_width[image_num]*4+j*4+0]=(GLubyte)temp.val[0]; 
			image[image_num][i*image_width[image_num]*4+j*4+1]=(GLubyte)temp.val[1];
			image[image_num][i*image_width[image_num]*4+j*4+2]=(GLubyte)temp.val[2];
			image[image_num][i*image_width[image_num]*4+j*4+3]=0;
		}
	}
	cvReleaseImage(&texture);
}

static GLuint make_buffer(
    GLenum type,
    const void *buffer_data,
    GLsizei buffer_size
) {
    GLuint buffer;
    glGenBuffers(1, &buffer);																	//从空闲buffer中分配一个buffer名出来
    glBindBuffer(type, buffer);																	//确定buffer类型
    glBufferData(type, buffer_size, buffer_data, GL_STATIC_DRAW);				//将数据搞到buffer中去
    return buffer;
}	

void cal_normalv(void)
{
	int i,j;
	GLfloat x1,x2,x3,y1,y2,y3,z1,z2,z3;
	GLfloat tempx1,tempx2,tempy1,tempy2,tempz1,tempz2;
	GLfloat resultx,resulty,resultz;
	GLfloat length;
	memset(_normalv,0,sizeof(_normalv));
	for (i=0;i<72;i+=4 )
	{
		x1=_vertices[_indices[i]][0];
		y1=_vertices[_indices[i]][1];
		z1=_vertices[_indices[i]][2];
		x2=_vertices[_indices[i+1]][0];
		y2=_vertices[_indices[i+1]][1];
		z2=_vertices[_indices[i+1]][2];
		x3=_vertices[_indices[i+2]][0];
		y3=_vertices[_indices[i+2]][1];
		z3=_vertices[_indices[i+2]][2];
		tempx1=x3-x2;
		tempx2=x2-x1;
		tempy1=y3-y2;
		tempy2=y2-y1;
		tempz1=z3-z2;
		tempz2=z2-z1;
		resultx=tempy1*tempz2-tempy2*tempz1;
		resulty=tempz1*tempx2-tempx1*tempz2;
		resultz=tempx1*tempy2-tempx2*tempy1;
		length=sqrt(resultx*resultx+resulty*resulty+resultz*resultz);
		resultx/=length;
		resulty/=length;
		resultz/=length;
		_normalv[i][0]=_normalv[i+1][0]=_normalv[i+2][0]=resultx;
		_normalv[i][1]=_normalv[i+1][1]=_normalv[i+2][1]=resulty;
		_normalv[i][2]=_normalv[i+1][2]=_normalv[i+2][2]=resultz; 
	}
} 
void prepare_mazedata()
{
	int i,j,k;

	for (i=k=0;i<sizeof (indices)/(4*sizeof(GLuint));i++)
		for (j=0;j<4;j++,k++)
			memcpy(_vertices[k],vertices[indices[i][j]],3*sizeof(GLuint));
	make_buffer(GL_ARRAY_BUFFER,_vertices,sizeof(_vertices)); 
	glVertexPointer(3,GL_FLOAT,0,NULL);													//将顶点缓存移动到服务器命令，注意最后一个参数为偏移量
	glEnableClientState(GL_VERTEX_ARRAY);												//客户端开启顶点缓存状态

	make_buffer(GL_ARRAY_BUFFER,texture,sizeof(texture));  
	glTexCoordPointer(2,GL_FLOAT, 0, NULL);												//将纹理对应关系数组上传到服务器的命令，注意，如果一个顶点被多个面共享，而多个面都需要贴图，需要把这些顶点分开
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);									//开启纹理缓存状态


	
	for (i=0;i<sizeof (indices)/sizeof(GLuint);i++)
		_indices[i]=i;
	make_buffer(GL_ELEMENT_ARRAY_BUFFER,_indices,sizeof(_indices)); 		//将顶点的连接索引上传。
	
	cal_normalv();																					//计算法向量
	make_buffer(GL_ARRAY_BUFFER,_normalv,sizeof(_normalv));
	glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),NULL);								//上传法向量
	glEnableClientState(GL_NORMAL_ARRAY);												//开启法向量缓存状态
}

void draw_imaze(void)
{  
	glColor3f (1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//定义物体材料
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glDrawElements(GL_QUADS,16 ,GL_UNSIGNED_INT,(GLubyte*)(0*sizeof(GLuint)));//pillar	
	glColor3f (1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//定义物体材料
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glDrawElements(GL_QUADS,8 ,GL_UNSIGNED_INT,(GLubyte*)(16*sizeof(GLuint)));		//ceiling and floor
	glColor3f (0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//定义物体材料
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glDrawElements(GL_QUADS,24 ,GL_UNSIGNED_INT,(GLubyte*)(24*sizeof(GLuint)));		//wall,inside 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//定义物体材料
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		//定义物体材料
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	if (q)
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission_null);
	glutSolidSphere (.50, 20, 16);
} 

void visual_reposition()
{
	lookingat[0]=2.5;		//眼睛位置x
	lookingat[1]=0.5;		//眼睛高度，不变
	lookingat[2]=2.5;		//眼睛位置z
	lookingat[3]=0;		//眼睛朝向x
	lookingat[4]=0.5;		//直视正前方，不变
	lookingat[5]=0;		//眼睛朝向z
	lookingat[6]=0;
	lookingat[7]=1;
	lookingat[8]=0;
	
}
void enable_light()
{ 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);
	//glLightfv(GL_LIGHT0, GL_AMBIENT,{0,0,0,1});
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT,lmodel_ambient);	
	glEnable(GL_LIGHTING);													//开启光照
	glEnable(GL_LIGHT0);													//开启第一束光 
}
 
void display(void)
{  	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); 
	glLoadIdentity ();	
	gluLookAt(lookingat[0],lookingat[1],lookingat[2],lookingat[3],lookingat[4],lookingat[5],lookingat[6],lookingat[7],lookingat[9]); 
	glLightfv(GL_LIGHT0, GL_POSITION, light_position[0]);
	draw_imaze();
	glFlush ();
}

void reshape(int w, int h)
{ 
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity ();	
	gluPerspective(90,(GLsizei)w/(GLsizei)h,0.10,300.0); 
	//glOrtho(-3.0, 3.0, -2.0, 2.0, -70, 122.5);
	glMatrixMode(GL_MODELVIEW);	

	
}

void init(void) 
{ 
	//glClearDepth(1.0f);
	glClearColor(0,0,0,1);
	glEnable(GL_DEPTH_TEST);
	//glDepthRange(0,10);
	glShadeModel (GL_SMOOTH); 
	enable_light();
	visual_reposition(); 
	prepare_mazedata(); 
	glEnable(GL_TEXTURE_2D);
	
	glGenTextures(2, texName);	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//texture of pillar
	read_texture_image(0,"girl.jpg"); 
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width[0],
		image_height[0], 0, GL_RGBA, GL_UNSIGNED_BYTE,
		image[0]);

	//	texture of wall
	read_texture_image(1,"wall.jpg"); 
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width[1],
		image_height[1], 0, GL_RGBA, GL_UNSIGNED_BYTE,
		image[1]);  

    //	texture of ground
	read_texture_image(2,"ground.jpg"); 
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
			GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
			GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width[2],
		image_height[2], 0, GL_RGBA, GL_UNSIGNED_BYTE,
		image[2]);  

	//BUG：先自加载
	reshape(600,600);
	display();
}

void keyboard(unsigned char key, int x, int y)
{
	double tempx,tempz,temp;
	tempx=lookingat[3]-lookingat[0];
	tempz=lookingat[5]-lookingat[2];
   switch (key) {
      case 27:
         exit(0);
         break;
	  case 'f':
		  temp=tempx*cos(step_angle)-tempz*sin(step_angle);
		  tempz=tempx*sin(step_angle)+tempz*cos(step_angle);
		  tempx=temp;
		  lookingat[3]=lookingat[0]+tempx;
		  lookingat[5]=lookingat[2]+tempz;
		  break;
	  case 's':
		  temp=tempx*cos(step_angle)+tempz*sin(step_angle);
		  tempz=-tempx*sin(step_angle)+tempz*cos(step_angle);
		  tempx=temp;
		  lookingat[3]=lookingat[0]+tempx;
		  lookingat[5]=lookingat[2]+tempz;
		  break;	  
	  case 'd':
		  lookingat[0]-=step*(tempx/sqrt((double)tempx*tempx+tempz*tempz));
		  lookingat[2]-=step*(tempz/sqrt((double)tempx*tempx+tempz*tempz));
		  lookingat[3]=lookingat[0]+tempx;
		  lookingat[5]=lookingat[2]+tempz;
		  break;
	  case 'e':
		  lookingat[0]+=step*(tempx/sqrt((double)tempx*tempx+tempz*tempz));
		  lookingat[2]+=step*(tempz/sqrt((double)tempx*tempx+tempz*tempz));
		  lookingat[3]=lookingat[0]+tempx;
		  lookingat[5]=lookingat[2]+tempz;
		  break;
	  case 'r':
		  visual_reposition();
		  break;
	  case 'q':
		  q=!q;  
		  break;
   }
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
 
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(600, 600);
   glutInitWindowPosition(100, 100);
   glutCreateWindow(argv[0]);  
   glewInit(); 
    if (!GLEW_VERSION_2_0) {
        fprintf(stderr, "OpenGL 2.0 not available\n");
        return 1;
    }
   init();
   glutReshapeFunc(reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0; 
}   


 