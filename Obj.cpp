#include "Obj.h"
#include <string>
#include <sstream>
#include <fstream>


Obj::Obj(const char * filename) {
    std::ifstream in(filename, std::ifstream::in);

    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream ss(line.c_str());
        char command = '\0';
        ss >> command;
        if (command == 'v') {
            float x, y, z;
            ss >> x >> y >> z;
            Point<float> p(x, y, z);
            verts.push_back(p);
        } else if (command == 'f') { 
            std::vector<int> f;
            int idx;
            char trash;
            int itrash;

            while(ss >> idx) {
                ss >> trash;
                ss >> itrash;
                ss >> trash;
                ss >> itrash;
                idx--;
                f.push_back(idx);
            }
            faces.push_back(f);
        }
    }
}

Obj::~Obj() 
{

}
   
void Obj::draw(Framebuffer& f, const Point<float> lightVec, const Transform& t) {
    int width = f.width();
    int height = f.height();
    
    for (int i = 0; i < faces.size(); i++) {
        std::vector<int> face = faces[i];
        Point<float>& v0 = verts[face[0]];
        Point<float>& v1 = verts[face[2]];
        Point<float>& v2 = verts[face[1]];
        Point<float> p0 = v0*t;
        Point<float> p1 = v1*t;
        Point<float> p2 = v2*t;

        Point<float> a = p2-p0; 
        Point<float> b = p1-p0;

        float nx = a.y*b.z - a.z*b.y; 
        float ny = a.z*b.x - a.x*b.z; 
        float nz = a.x*b.y - a.y*b.x; 

        Point<float> n(nx,ny,nz);
        n.normalize();
        float intensity = n*lightVec;

        if (intensity > 0) {
            uint8_t c = intensity*255;
            f.draw_triangle(p0, p1, p2, Color(c,c,c)); 
        }

    }

}
