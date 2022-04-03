#pragma once

#include "core/Constants.h"

namespace TUNA
{

    class Shader
    {

    public:
        Shader(const std::string &name, const std::string &filepath);                                    // load Vertex & Fragment shaders from same file
        Shader(const std::string &name, const std::string &vertex_src, const std::string &fragment_src); // load Vertex & Fragment shaders from different files
        ~Shader();

        void bind() const;
        void unbind() const;

        void set_int(const std::string &name, int value);
        void set_int_array(const std::string &name, int *values, uint32_t count);
        void set_float(const std::string &name, float value);
        void set_float2(const std::string &name, const glm::vec2 &value);
        void set_float3(const std::string &name, const glm::vec3 &value);
        void set_float4(const std::string &name, const glm::vec4 &value);
        void set_mat4(const std::string &name, const glm::mat4 &value);

        static Shader &create(const std::string &filepath);
        static Shader &create(const std::string &name, const std::string &vertex_src, const std::string &fragment_src);

        const std::string &get_name() const { return _name; }

        void upload_uniform_int(const std::string &name, int value);
        void upload_uniform_intArray(const std::string &name, int *values, uint32_t count);

        void upload_uniform_float(const std::string &name, float value);
        void upload_uniform_float2(const std::string &name, const glm::vec2 &value);
        void upload_uniform_float3(const std::string &name, const glm::vec3 &value);
        void upload_uniform_float4(const std::string &name, const glm::vec4 &value);

        void upload_uniform_mat3(const std::string &name, const glm::mat3 &matrix);
        void upload_uniform_mat4(const std::string &name, const glm::mat4 &matrix);

        void debug_print();

    private:
        uint32_t _id;          // the shader's id that is used to reference the shader
        std::string _filepath; // the path of the _source_code
        std::string _name;     // user defined name of shader
        
        struct _shader_source_code
        {
            std::string vertex_shader;
            std::string fragment_shader;
        } _shader_source_code; // the source code for the shader (0) vertex, (1) fragment

        uint32_t _vertex_shader;
        uint32_t _fragment_shader;

    private:
        void process_shaders(std::string &shader_src);
        uint32_t compile(uint32_t shader_type, std::string &shader); // compiles the shader program
        void create_program();                                       // creates the shader program to be compiled
    };

    class ShaderLibrary
    {
    private:
        std::unordered_map<std::string, Shader &> _shaders; // map to keep track of all the shaders

    public:
        void add(const std::string &name, const Shader &shader); // adds a shader to the map
        const Shader &load(const std::string &filepath);         // returnes a shader
        Shader &load(const std::string &name, const std::string &filepath);

        Shader &get(const std::string &name);

        bool exists(const std::string &name) const;
    };
}