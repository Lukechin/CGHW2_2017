#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include <cstdint>
#include <GL/glew.h>
#include <map>
#include <functional>
#include <glm/glm.hpp>
#include "Buffer.h"

class UniformVariable
{
public:
    UniformVariable();
    explicit UniformVariable(GLuint program, GLint id);
    UniformVariable(const UniformVariable &rhs)=default;
    float operator=(float);
    uint32_t operator=(uint32_t);
    int32_t operator=(int32_t);
    glm::uvec2 operator=(const glm::uvec2 &);
    glm::vec2 operator=(const glm::vec2 &);
    glm::vec3 operator=(const glm::vec3 &);
    glm::ivec3 operator=(const glm::ivec3 &);
    glm::mat4 operator=(const glm::mat4 &);
    UniformVariable &operator=(const UniformVariable &rhs)=default;
    bool valid() const;
private:
    GLuint m_program;
    GLint m_id;
};

class Program
{
public:
    Program()=default;
    Program(const Program &)=default;
    static Program LoadFromFile(const std::string &filename);
    static Program LoadFromFile(const std::string &vs, const std::string &fs);
    static Program LoadFromFile(const std::string &vs, const std::string &gs, const std::string &fs);
    UniformVariable &operator[](const std::string &) const;
    template <class T>
    void bindUniformBuffer(const std::string &name, GLuint bind_point_index, UniformBuffer<T> &ubo);
    template <class T>
    void bindShaderStorage(const std::string &name, GLuint bind_point_index, ShaderStorage<T> &ssbo);

    bool valid() const;
    void use() const;

    void dispatchCompute(uint32_t x, uint32_t y, uint32_t z) const;

    void release();
private:
    static GLuint CreateShader(GLenum type, const std::string &src);
    Program(GLuint prog);
    mutable std::map<std::string, UniformVariable> m_uniformVariables;
    GLuint m_program;
};

#include "ShaderProgram.inl"
#endif