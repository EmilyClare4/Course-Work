//Emily Rutherford ID 21013503
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

class pixel_class {
private:
  int red, green, blue;
  bool exclude;  // if true, do not check this pixel
public:
  void loaddata(int v1, int v2, int v3);
  void datatofile(fstream & ppmfile);
  int getR() { return red; }
  int getG() { return green; }
  int getB() { return blue; }
  void setexclude(bool ex) { exclude = ex; }
  bool getexclude() { return exclude; }
};

void loadButtons();
void findConnectedPixels(int x, int y);
void redBox();
void greenBox();

int total, xmin, xmax, ymin, ymax;
int screenx, screeny, maxcolours;
pixel_class picture[600][600];

int main() {
  int x, y;
  string filename;
  fstream myfile;
  // Step 1 : read in the image from Buttons.ppm
  loadButtons();
  // Step 2 : identify buttons and draw boxes
  for (y = 0; y < screeny; y++) {//runs slower than x, along the vertical axis of the picture
    for (x = 0; x < screenx; x++) {//runs faster than y, along the horizontal axis of the picture
      if ((picture[x][y].getR() > 128) && (picture[x][y].getexclude() == false)){//checks if pixels are valid
        xmin = x;
        xmax = x;
        ymin = y;
        ymax = y;
        total = 0;
        findConnectedPixels(x,y);
        if (total < 7660){//I set the minimum pixel count of a button to 7660 because some of them seem to have slightly different sized holes but are still functioning buttons.
          redBox();
        } else {
          greenBox();
        }
      }
    }
  }
  cout <<"Checking buttons..."<<endl;
  // Step 3 : output the final .ppm file
  filename = "checkedButtons.ppm";
  myfile.open(filename.c_str(), fstream::out);
  myfile << "P3\n";
  myfile << "# " << filename << endl;
  myfile << 600 << " " << 600 << endl;
  myfile << 256 << endl;
  for (y = 0; y < screeny; y++) {
    for (x = 0; x < screenx; x++) {
      picture[x][y].datatofile(myfile);
    }
    myfile << endl;
  }
  myfile.close();
  cout <<"Checking complete! Open file "<<filename<<" to review."<<endl;
}

//--------------- FUNCTIONS ------------
void loadButtons() {
  // load the picture from Buttons.ppm
  int x, y, R, G, B;
  fstream infile;
  string infilename, line;
  infilename = "Buttons.ppm";
  infile.open(infilename.c_str(), fstream::in);
  if (infile.is_open() == false) {
    cout << "ERROR: not able to open " << infilename << endl;
    exit(2);
  }
  getline(infile, line);  // this line is "P3"
  getline(infile, line);  // this line is "# filename"
  infile >> screenx >> screeny;  // this line is the size
  infile >> maxcolours;  // this line is 256
  for (y = 0; y < screeny; y++) {
    for (x = 0; x < screenx; x++) {
      infile >> R >> G >> B;
      picture[x][y].loaddata(R, G, B);
      picture[x][y].setexclude(false);
    }
  }
  infile.close();
}

void findConnectedPixels(int x, int y){
  //for each pixel > 128 found, find any connected pixels and also check their surrounding pixels
  if (picture[x][y].getexclude() == true) { return; } // base case one
  if (picture[x][y].getR() <= 128) {  return;} // base case two
  if (x > xmax){
    xmax = x;
  } else if (x < xmin){
    xmin = x;
  }
  if (y > ymax){
    ymax = y;
  } else if (y < ymin){
    ymin = y;
  }
  total++;
  picture[x][y].setexclude(true); // do not look at this pixel again
  findConnectedPixels (x - 1, y);
  findConnectedPixels (x + 1, y);
  findConnectedPixels (x, y - 1);
  findConnectedPixels (x, y + 1);
}

void redBox(){
  int x, y;
  for (x = xmin; x <= xmax; x++) {
    picture[x][ymin].loaddata(240, 12, 12);
    picture[x][ymin].setexclude(true);
    picture[x][ymax].loaddata(240, 12, 12);
    picture[x][ymax].setexclude(true);
  }
  for (y = ymin; y <= ymax; y++){
    picture[xmin][y].loaddata(240, 12, 12);
    picture[xmin][y].setexclude(true);
    picture[xmax][y].loaddata(240, 12, 12);
    picture[xmax][y].setexclude(true);
  }
}

void greenBox(){
  int x, y;
  for (x = xmin; x <= xmax; x++) {
    picture[x][ymin].loaddata(51, 255, 51);
    picture[x][ymin].setexclude(true);
    picture[x][ymax].loaddata(51, 255, 51);
    picture[x][ymax].setexclude(true);
  }
  for (y = ymin; y <= ymax; y++){
    picture[xmin][y].loaddata(51, 255, 51);
    picture[xmin][y].setexclude(true);
    picture[xmax][y].loaddata(51, 255, 51);
    picture[xmax][y].setexclude(true);
  }
}

//--------------- methods for the pixel_class ------------
void pixel_class::loaddata(int v1, int v2, int v3) {
  red = v1;
  green = v2;
  blue = v3;
}

void pixel_class::datatofile(fstream & ppmfile) {
  // write the data for one pixel to the ppm file
  ppmfile << red << " " << green;
  ppmfile << " " << blue << "  ";
}
