/*********************************************************************
This is simple 3D object rotation and 2D projection example.
It uses 64x48 oled display with SSD1306 controller.
Driving to oled display, Adafruit_SSD1306(this is not original library 64x48 support added by https://github.com/mcauser/Adafruit_SSD1306) and Adafruit_GFX libraries are used.
*********************************************************************/
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4  // PIN4
Adafruit_SSD1306 display(OLED_RESET);

float cube[8][3];
uint8_t point_conn[8][8]={0};
float rad_X=PI/4;
float rad_Y=PI/3;
float rad_Z=PI/8;
unsigned long t1=0;
double fps;

void setup(){  
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();

  createConn(point_conn);
}


void loop() {
  /* Define cube corner coordinates */
  /* Every loop cube needs to start from first shape, otherwise floating point */
  /* numbers will saturate or go zero */
  createCube(cube);
 
  t1=micros();
    
  display.clearDisplay();

  /* 3D rotation in world coords */
  rotate_X(cube, 8, rad_X);
  rotate_Y(cube, 8, rad_X);
  rotate_Z(cube, 8, rad_Z);
  
  filldispbuffer(cube,point_conn,8);

  /* Print FPS */
  display.setCursor(50,40);
  display.print(fps,0);
  
  display.display();

  /* random rotation */
  rad_X+=0.06;
  rad_Y+=0.06;
  rad_Z+=0.04;

  fps=(double)(micros()-t1);
  fps=1000000/fps;
  
}

void filldispbuffer(float obj[][3], uint8_t edges[][8], uint8_t num_point){

  uint16_t x1,y1;
  uint16_t x2,y2;
     
  for(uint8_t i=0; i<8; i++)
    for(uint8_t j=i+1; j<8; j++)
      if( edges[i][j] ){

        //Simple 2D projection
        x1=(uint16_t)(obj[i][1]*26)+24;
        y1=(uint16_t)(obj[i][2]*26)+24;

        x2=(uint16_t)(obj[j][1]*26)+24;
        y2=(uint16_t)(obj[j][2]*26)+24;

        display.drawLine(x1, y1, x2, y2, WHITE);
      }  
}

void rotate_X(float result[][3], uint8_t num_point, float rad){
  float temp;
  for(uint8_t i=0; i<num_point; i++){
    temp=result[i][1]*(float)cos(rad)-result[i][2]*(float)sin(rad);
    result[i][2]=result[i][1]*(float)sin(rad)+result[i][2]*(float)cos(rad);
    result[i][1]=temp;    
  }
}

void rotate_Y(float result[][3], uint8_t num_point, float rad){
  float temp;
  for(uint8_t i=0; i<num_point; i++){
    temp=result[i][0]*(float)cos(rad)+result[i][2]*(float)sin(rad);
    result[i][2]=-result[i][0]*(float)sin(rad)+result[i][2]*(float)cos(rad);
    result[i][0]=temp;    
  }
}

void rotate_Z(float result[][3], uint8_t num_point, float rad){
  float temp;
  for(uint8_t i=0; i<num_point; i++){
    temp=result[i][0]*(float)cos(rad)-result[i][1]*(float)sin(rad);
    result[i][1]=-result[i][0]*(float)sin(rad)+result[i][1]*(float)cos(rad);
    result[i][0]=temp;    
  }
}

/* manual definition for cube corner coordinates */
void createCube(float obj[][3]){
    obj[0][0]=0.5;
    obj[0][1]=0.5;
    obj[0][2]=0.5;

    obj[1][0]=0.5;
    obj[1][1]=0.5;
    obj[1][2]=-0.5;

    obj[2][0]=0.5;
    obj[2][1]=-0.5;
    obj[2][2]=0.5;

    obj[3][0]=0.5;
    obj[3][1]=-0.5;
    obj[3][2]=-0.5;

    obj[4][0]=-0.5;
    obj[4][1]=0.5;
    obj[4][2]=0.5;

    obj[5][0]=-0.5;
    obj[5][1]=0.5;
    obj[5][2]=-0.5;

    obj[6][0]=-0.5;
    obj[6][1]=-0.5;
    obj[6][2]=0.5;

    obj[7][0]=-0.5;
    obj[7][1]=-0.5;
    obj[7][2]=-0.5;   
};

/* manual definition for edge connectivity */
void createConn(uint8_t edges[][8]){
   edges[0][1]=1;
   edges[0][2]=1;
   edges[0][4]=1;
  
   edges[1][0]=1;
   edges[1][5]=1;
   edges[1][3]=1;
  
   edges[2][0]=1;
   edges[2][3]=1;
   edges[2][6]=1;
  
   edges[3][7]=1;
   edges[3][2]=1;
   edges[3][1]=1;
  
   edges[4][0]=1;
   edges[4][5]=1;
   edges[4][6]=1;
  
   edges[5][4]=1;
   edges[5][1]=1;
   edges[5][7]=1;  

   edges[6][2]=1;
   edges[6][4]=1;
   edges[6][7]=1;

   edges[7][3]=1;
   edges[7][5]=1;
   edges[7][6]=1;
}

