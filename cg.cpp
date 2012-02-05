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

/*************************�ʼ�************************************
1.����buffer
�����OpenGL�Ŀͻ���/������ģ�ͣ���buffer�͵��ڰ����ݴ浽����ˣ��Ӷ��ӿ��ٶȣ��������
�������ƺ��ǰ�������ʾ�طŵ��Դ��С�buffer�ĳ�ʼ���Ͱ󶨲ο�������롣
����buffer����һ�����˵�����ǣ�����buffer֮�������������Ҫ��ר�õĺ����ˣ�����������е�
glDrawElements�����ң���ͼ�任�����յȶ���Ҫ����Ӧ�Ĳ�������������ο�������롣

����buffer�����ӣ�http://www.programfan.com/club/showtxt.asp?id=275223

2.������ͼ
������Ҫ�ĸ��
�ռ�ģ�ͣ�OPENGL������ͼ��ѧ����ͼ���Ǿ�̬�ĸ�����Ƕ�̬�ģ�ʵ�ֶ�̬�ķ�������ģ�ͣ���νģ�;��ǿռ伸���塣�ռ伸�����ȷ����ͨ��һЩ�ռ�ĵ㣬�ռ�ĵ�����򼯺Ͼ���ģ�͡�
�ӿڣ�ģ�Ϳ����Ƕ�ά�ģ�Ҳ��������ά�ģ����������ʾ���Ƕ�ά�ģ��ռ�ģ�ͱ���ͶӰ�������ν�ӿڵ�ƽ���У������ܱ�Ǩ�Ƶ��������Ļ����ʾ�������ӿھ����Ǹ����屻ͶӰ��������ƽ�档
�Ӿ��壺���ͼ��ѧ�н���̬ģ��ת����ʾ���������������������������գ��Ӿ�����ָ���������ڿռ�ļ��ϣ�����ռ伯�Ͽ����ǿ͹۵ģ���͸�ӵ�ͶӰ�任����Ҳ���������۵ģ�͸�ӱ任�������������۵ģ���Ϊ�俴���Ķ��������ڹ�Ǿ����ĵ��ģ���͸��ͶӰ�任�����ġ�
���ԣ�OPENGL����ͼ���γɾ��ǽ��ض��Ӿ����еĿռ�ģ�ͽ���ͶӰ�任���ӿ��ϲ����ú�ó���

����һ������ͼ�ΰ������漸�����裺
��ͼ�任��gluLookAtΪ���ı任������ȷ�������������۾������õ�λ�õ�
ģ�ͱ任��gluTranslatef��gluRote�ȶ���ģ�ͱ任����ԭʼ�ļ����屾����б任
ͶӰ�任�� glOrtho��glFrustum��gluPerspective�ȣ�������ν�������ͶӰ��������У�͸�ӣ�����ƽ�ӣ����༴�۾��ܿ����ķ�Χ��͸��Ч��
�ӿڱ任��glViewportΪ���ı任�������Ӵ��Ĵ�С�����������ã�ֻ�Ǿ�������Ļ����ʾ�Ĵ�С
���ƣ���ͼ�任��ģ�ͱ任������һ��ģ����Ƕ�glMatrixMode (GL_MODELVIEW)�༴ģ����ͼ����ջ�Ĳ���������ͶӰ�任���ӿڱ任�����໥����������ʵ��������ӿڱ任��Ҫ��ģ��ȷ��֮ǰ����˱Ƚ������˳���ǣ��ӿڱ任ȷ���ӿ�->ͶӰ�任ȷ�����ͶӰ->��ͼ�任ȷ�����λ��->ģ�ͱ任->����ģ��

������ͼ�����ӣ�http://hi.baidu.com/zhujianzhai/blog/item/24e9c11ec9a91c64f724e43c.html


3.���ڹ���
���ձȽϸ��ӣ����յ����͡����ʵ����͡����ߵĸ��٣�opengl�����Զ����ٹ��ߣ�ʶ���Ƿ��ڵ�������������У�����û�б��ڵ������Ի���ַ��������󣩣�����Щ���ӡ�
����˵����
	opengl������Ҫ�ǿ��Ʋ�ͬ���͹��յ�ǿ�Ⱥ���ɫ���Լ���������������Ĳ�ͬ���͹��յ�ǿ������ɫ��
	�ڱ������У������ڣ�0,0,0����İ׹���ҫ��ע�⣺��Ȼ��Ȳ��Կ���������������ڵ���ϵ�������߲����ڵ���OPENGL�ƺ����߱��Զ����������Ҫ����Աȥ������
ͨ���趨��ͬ�Ĳ������ԣ����淴��⣺��ɫ��ɢ��⣺��ɫ�������⣺��ɫ�������ǿ��Ժ�������ⲻͬ�������͵ľ��庬�壬����ο�ͼƬ��
��Ҫ�������ͣ�	
	�����⣺�뷨��������Դλ���޹صľ���ǿ�ȵĹ���
	ɢ��⣺�뷨��������Դλ���йص��ܱ�ɢ��Ĺ���
	����⣺�뷨��������Դλ���йص�ֻ�ܱ����淴��Ĺ���
��Ҫ�������ԣ�
	����������ɫ���Ի�����ķ�ɫ��ɫ
	ɢ����ɫ����ɢ����ɢ����ɫ
	������ɫ���Ծ����ķ�����ɫ
	��ɫǿ�ȣ�shininess
	���ϱ��淢�⣺emission

���յ�ʹ�ã�
��������λ�����ù�Դ��glLightfv() / ������Դ�붨λ��Դ�ģ���������Ĳ����Ƚ϶࣬�ο��챦�� glEnable() / ���ù�Դ�����þ���Ĺ�Դ
ѡ�����ģ��:glLightModel �ο��챦���
����������ԣ�glMaterialf /��������Ĳ���Ҳ�Ƚ϶࣬�ο��챦�� ���������Ե�ʹ���ڴ������弸������ǰ���Ӷ�����ʵ�ֲ�ͬ�ļ�������ӵ�в�ͬ�Ĳ���
��󣬴�����������
����bufferҪ����Ӧ���ӹ���������ο�������롣

4.������ͼ
�ο����ο�����texbind�������ǰѼ����������ض����Ӧ������
����bufferҪ����Ӧ���ӹ���������ο�������롣

**************************************************************/
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h> 
#include <stdio.h>
#include <math.h>
#include "highgui.h"
#include "cv.h"
  


double lookingat[9];
const double step=0.1;//����
const double step_angle=0.174;//ת��
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
GLfloat mat_specular[] = { 1.0, 0.0, 0.0, 1.0 }	;				//���Ͼ��淢��ϵ��
GLfloat mat_diffuse[]={0,1,0,1};
GLfloat mat_shininess[] = { 50.0 };									//���淴��ǿ��
GLfloat qaDiffuseLight[] = { 1.0, 1.0, 1.0, 1.0 }	;				
GLfloat qaSpecularLight[] = { 1,1,1,1.0 };				
GLfloat lmodel_ambient[]={0.0,0.0,1.0,1.0};
GLfloat mat_emission[]={0.5,0.5,0.5,1},mat_emission_null[]={0,0,0,0};
bool q=false; 

#define IMAGE_NUM 3
static GLuint texName[IMAGE_NUM];
int image_width[IMAGE_NUM],image_height[IMAGE_NUM];
GLubyte *(image[IMAGE_NUM]);
int image_byte_length[IMAGE_NUM];//�������������˳����в���Ҫ
//GLubyte image_one[677][500][4];
void read_texture_image(int image_num, char*name)//�����ͼƬname
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
    glGenBuffers(1, &buffer);																	//�ӿ���buffer�з���һ��buffer������
    glBindBuffer(type, buffer);																	//ȷ��buffer����
    glBufferData(type, buffer_size, buffer_data, GL_STATIC_DRAW);				//�����ݸ㵽buffer��ȥ
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
	glVertexPointer(3,GL_FLOAT,0,NULL);													//�����㻺���ƶ������������ע�����һ������Ϊƫ����
	glEnableClientState(GL_VERTEX_ARRAY);												//�ͻ��˿������㻺��״̬

	make_buffer(GL_ARRAY_BUFFER,texture,sizeof(texture));  
	glTexCoordPointer(2,GL_FLOAT, 0, NULL);												//�������Ӧ��ϵ�����ϴ��������������ע�⣬���һ�����㱻����湲��������涼��Ҫ��ͼ����Ҫ����Щ����ֿ�
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);									//����������״̬


	
	for (i=0;i<sizeof (indices)/sizeof(GLuint);i++)
		_indices[i]=i;
	make_buffer(GL_ELEMENT_ARRAY_BUFFER,_indices,sizeof(_indices)); 		//����������������ϴ���
	
	cal_normalv();																					//���㷨����
	make_buffer(GL_ARRAY_BUFFER,_normalv,sizeof(_normalv));
	glNormalPointer(GL_FLOAT,3*sizeof(GLfloat),NULL);								//�ϴ�������
	glEnableClientState(GL_NORMAL_ARRAY);												//��������������״̬
}

void draw_imaze(void)
{  
	glColor3f (1.0, 0.0, 0.0);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//�����������
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glDrawElements(GL_QUADS,16 ,GL_UNSIGNED_INT,(GLubyte*)(0*sizeof(GLuint)));//pillar	
	glColor3f (1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//�����������
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glDrawElements(GL_QUADS,8 ,GL_UNSIGNED_INT,(GLubyte*)(16*sizeof(GLuint)));		//ceiling and floor
	glColor3f (0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//�����������
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glDrawElements(GL_QUADS,24 ,GL_UNSIGNED_INT,(GLubyte*)(24*sizeof(GLuint)));		//wall,inside 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);		//�����������
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);		//�����������
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	if (q)
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	else
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission_null);
	glutSolidSphere (.50, 20, 16);
} 

void visual_reposition()
{
	lookingat[0]=2.5;		//�۾�λ��x
	lookingat[1]=0.5;		//�۾��߶ȣ�����
	lookingat[2]=2.5;		//�۾�λ��z
	lookingat[3]=0;		//�۾�����x
	lookingat[4]=0.5;		//ֱ����ǰ��������
	lookingat[5]=0;		//�۾�����z
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
	glEnable(GL_LIGHTING);													//��������
	glEnable(GL_LIGHT0);													//������һ���� 
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

	//BUG�����Լ���
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


 