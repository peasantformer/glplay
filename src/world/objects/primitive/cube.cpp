#include "cube.h"

#include <src/util/fileutils.h>

#include <sstream>

Cube::Cube(const std::string &name, const Space &space, const glm::vec3 &dimensions)
    : Prop(name,space)
    , dimensions(dimensions)
{
}

Cube::~Cube()
{
}

void Cube::populateData(GLMeshSource &source)
{
    source.data.resize(8*8,0);

    float hw = dimensions.x  / 2.0f;
    float hd = dimensions.y  / 2.0f;
    float hh = dimensions.z / 2.0f;


    source.data[0+8*0] = -hw;
    source.data[1+8*0] = -hd;
    source.data[2+8*0] =  hh;

    source.data[0+8*1] = -hw;
    source.data[1+8*1] =  hd;
    source.data[2+8*1] =  hh;

    source.data[0+8*2] =  hw;
    source.data[1+8*2] =  hd;
    source.data[2+8*2] =  hh;

    source.data[0+8*3] =  hw;
    source.data[1+8*3] = -hd;
    source.data[2+8*3] =  hh;

    /////////////////////////

    source.data[0+8*4] = -hw;
    source.data[1+8*4] = -hd;
    source.data[2+8*4] = -hh;

    source.data[0+8*5] = -hw;
    source.data[1+8*5] =  hd;
    source.data[2+8*5] = -hh;

    source.data[0+8*6] =  hw;
    source.data[1+8*6] =  hd;
    source.data[2+8*6] = -hh;

    source.data[0+8*7] =  hw;
    source.data[1+8*7] = -hd;
    source.data[2+8*7] = -hh;


    source.vertices.push_back(0);
    source.vertices.push_back(1);
    source.vertices.push_back(2);
    source.vertices.push_back(2);
    source.vertices.push_back(3);
    source.vertices.push_back(0);

    source.vertices.push_back(4);
    source.vertices.push_back(5);
    source.vertices.push_back(6);
    source.vertices.push_back(6);
    source.vertices.push_back(7);
    source.vertices.push_back(4);


    source.vertices.push_back(0);
    source.vertices.push_back(1);
    source.vertices.push_back(4);
    source.vertices.push_back(1);
    source.vertices.push_back(5);
    source.vertices.push_back(4);

    source.vertices.push_back(2);
    source.vertices.push_back(3);
    source.vertices.push_back(6);
    source.vertices.push_back(3);
    source.vertices.push_back(7);
    source.vertices.push_back(6);

    source.vertices.push_back(0);
    source.vertices.push_back(3);
    source.vertices.push_back(4);
    source.vertices.push_back(3);
    source.vertices.push_back(7);
    source.vertices.push_back(4);

    source.vertices.push_back(3);
    source.vertices.push_back(7);
    source.vertices.push_back(0);
    source.vertices.push_back(7);
    source.vertices.push_back(4);
    source.vertices.push_back(0);

    source.shaders.push_back(
                GLCompileShader::ShaderSource(
                    GLCompileShader::Vertex,
                    FileUtils::readToString("primitive/cube.vtx")
                    )
                );

}

std::string Cube::genCacheKey()
{
    std::stringstream ss;
    ss << "x:" << dimensions.x << "y:" << dimensions.y << "z:" << dimensions.z;
    std::string result;
    ss >> result;
    return result;
}
